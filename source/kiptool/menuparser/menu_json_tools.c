// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "menu_json_tools.h"
#include "jsmn.h"
#include <string.h>
#include <mem/heap.h>
#include <errno.h>
#include "printf.h"

// #define WINDOWS_KIP_TOOL

#ifdef WINDOWS_KIP_TOOL
#include <stdio.h>
#define snprintf sprintf
#endif

#pragma warning(disable : 4996)

#define JSON_TOKENS_COUNT (8096)
#define WORK_BUFFER_SIZE (256)
#define JSON_MAX_TOKENS (17)
#define UNUSED(x) (void)(x)

int32_t error_ptr;

//*
static int jsoneq(const char* json, jsmntok_t* tok, const char* s) {
	if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
		strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	}
	return -1;
}
//*/

void* LocalRealloc(void* original, size_t old_size, size_t new_size)
{
	void* ptr = calloc(new_size, 1);
	if (ptr)
	{
		memcpy(ptr, original, old_size);
	}
	free(original);
	return ptr;
}

void DeleteMenuElement(menu_entry_s* elem)
{
	free(elem->menu_info.help);
	free(elem->menu_info.name);
	free(elem->value_data.unit_name);
	free(elem);
}

// Удаляем временный список элементов
void CleanList(entry_list_s* head, uint8_t cleanup_elements)
{
	entry_list_s* ptr;
	while (head)
	{
		ptr = head->next;
		if (cleanup_elements)
		{
			DeleteMenuElement(head->elem);
		}
		free(head);
		head = ptr;
	}
}

typedef enum value_type_t
{
	VT_HEX,
	VT_UNDEFINED,
	VT_DECIMAL,
	VT_BOOL_TRUE,
	VT_BOOL_FALSE,
	VT_KIP_TOOL_VERSION,
	VT_PARAM,
	VT_PARAM_VALUE,
	VT_FIXED,
	VT_MANUAL,
	VT_RANGE,
	VT_FOLDER_ENTRY
}value_type_t;

#define IsDigit(c)		((c) >= '0' && (c) <= '9')

uint64_t GetHexValue(const char* hex)
{
	size_t len = strlen(hex);
	if (len > 2)
	{
		if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'))
			hex+=2;
	}
	else
		return 0;
	uint64_t val = 0;
	while (*hex) {
		// get current character then increment
		uint8_t byte = *hex++;
		// transform hex character to the 4bit equivalent number, using the ascii table indexes
		if (byte >= '0' && byte <= '9') byte = byte - '0';
		else if (byte >= 'a' && byte <= 'f') byte = byte - 'a' + 10;
		else if (byte >= 'A' && byte <= 'F') byte = byte - 'A' + 10;
		// shift 4 to make space for new digit, and add the 4 bits of the new digit 
		val = (val << 4) | (byte & 0xF);
	}
	return val;
}

int64_t GetLongInt(const char* value)
{
	int64_t out = 0;
	while (value) 
	{
		if (IsDigit(value[0]))
			out = out * 10 + (value[0] - 48);
		else
			return out;
		value++;
	}
	return out;
}

value_type_t GetValueType(char* value)
{
	uint8_t is_number = 1;
	size_t value_len = strlen(value);
	for (size_t i = 0; i < value_len; i++) {
		if (IsDigit(value[i]) == 0) {
			is_number = 0;
			break;
		}
	}

	if (is_number)
		return VT_DECIMAL;

	is_number = 1;
	if (value_len > 2)
	{
		if (value[0] == '0' && (value[1] == 'x' || value[1] == 'X'))
		{
			for (size_t i = 2; i < value_len; i++) {
				if (IsDigit(value[i]) == 0) {
					is_number = 0;
					break;
				}
			}
			if (is_number)
				return VT_HEX;
		}
	}

	// TODO refactor
	if (value_len == 4)
	{
		if (strncmp("true", value, 4) == 0 || strncmp("True", value, 4) == 0 || strncmp("TRUE", value, 4) == 0)
			return VT_BOOL_TRUE;
	}
	else if (value_len == 5)
	{
		if (strncmp("false", value, 5) == 0 || strncmp("False", value, 5) == 0 || strncmp("FALSE", value, 5) == 0)
			return VT_BOOL_FALSE;
		if (strncmp("Param", value, 5) == 0)
			return VT_PARAM;
		if (strncmp("Fixed", value, 5) == 0)
			return VT_FIXED;
		if (strncmp("Range", value, 5) == 0)
			return VT_RANGE;
	}
	else if (value_len == 6)
	{
		if (strncmp("Manual", value, 6) == 0)
			return VT_MANUAL;
	}
	else if (value_len == 10)
	{
		if (strncmp("ParamValue", value, 10) == 0)
			return VT_PARAM_VALUE;
	}
	else if (value_len == 11)
	{
		if (strncmp("FolderEntry", value, 11) == 0)
			return VT_FOLDER_ENTRY;
	}

	char* ptr = value;
	int32_t digit_counter = 0;
	int32_t dotCounter = 0;
	while (ptr[0])
	{
		if (!IsDigit(ptr[0]))
		{
			if (ptr[0] == '.')
			{
				if (digit_counter)
				{
					dotCounter++;
					digit_counter = 0;
				}
				else
					return VT_UNDEFINED;
			}
				
		}
		digit_counter++;
		ptr++;
	}
	if (dotCounter == 2)
		return  VT_KIP_TOOL_VERSION;



	//int res = sscanf(value, "%d.%d.%d", &a, &b, &c);
	//if (res == 3)
	//	return VT_KIP_TOOL_VERSION;

	return VT_UNDEFINED;
}

void SaveErrorData(jsmntok_t* json_tokens, uint32_t* ptr, char* json_text, menu_entry_s* elem, menu_creation_res_s* t, char* work_buffer, const char* reason)
{
	if (json_tokens[*ptr].end - json_tokens[*ptr].start <= WORK_BUFFER_SIZE)
		memset(work_buffer, 0, json_tokens[*ptr].end - json_tokens[*ptr].start);
	t->error_ptr = json_tokens[*ptr].start;
	t->value_error = (char*)calloc(256, 1);
	if (elem)
	{
		free(elem);
	}
	else
	{
		if (t->value_error != 0)
		{
			snprintf(t->value_error, 256,"%s , shift:%ld", reason, json_tokens[*ptr].start);
		}
	}
}

// TODO reduce allocation count for speed-up
menu_entry_s* GetElement(jsmntok_t* json_tokens, uint32_t ptr_max, uint32_t* ptr, char* json_text, char* work_buffer, uint32_t buffer_size, menu_creation_res_s* t, int* version)
{
	uint32_t counter_inserted = 0; // На всякий случай лимитируем число элементов в json-е
	if (*ptr >= ptr_max)
		return NULL;
	int important_fileds = 0;
	if (json_tokens[*ptr].type == JSMN_OBJECT)
	{
		menu_entry_s* elem = (menu_entry_s*)calloc(1, sizeof(menu_entry_s));
		if (elem == NULL)
		{
			t->error_ptr = -1;
			return NULL;
		}

		*ptr += 1;
		while (json_tokens[*ptr].type != JSMN_OBJECT && counter_inserted < JSON_MAX_TOKENS && *ptr < ptr_max && elem) // Объекты всегда начинаются с данного блока, где в т.ч. описан размер
		{
			memcpy(work_buffer, json_text + json_tokens[*ptr].start, json_tokens[*ptr].end - json_tokens[*ptr].start);
			memset(work_buffer, 0, json_tokens[*ptr].end - json_tokens[*ptr].start);
			// Должен существовать способ гибче это парсить, а не IF ELSE
			if (jsoneq(json_text, &json_tokens[*ptr], "name") == 0) {
				*ptr += 1;
				if (elem->menu_info.name)
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "Parameter name already existed: ");
					return NULL;
				}

				elem->menu_info.name = (char*)calloc(json_tokens[*ptr].end - json_tokens[*ptr].start + 1, 1);
				if (elem->menu_info.name == NULL)
				{
					free(elem);
					t->error_ptr = -1;
					return NULL;
				}
				memcpy(elem->menu_info.name, json_text + json_tokens[*ptr].start, json_tokens[*ptr].end - json_tokens[*ptr].start);
				important_fileds++;
			}
			else if (jsoneq(json_text, &json_tokens[*ptr], "help") == 0) {
				*ptr += 1;
				if (elem->menu_info.help)
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "Parameter help already existed: ");
					return NULL;
				}
				elem->menu_info.help = (char*)calloc(json_tokens[*ptr].end - json_tokens[*ptr].start + 1, 1);
				if (elem->menu_info.help == NULL)
				{
					free(elem);
					t->error_ptr = -1;
					return NULL;
				}
				memcpy(elem->menu_info.help, json_text + json_tokens[*ptr].start, json_tokens[*ptr].end - json_tokens[*ptr].start);
			}
			else if (jsoneq(json_text, &json_tokens[*ptr], "id") == 0)
			{
				*ptr += 1;
				if (elem->_id)
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "Parameter id already existed: ");
					return NULL;
				}
				if (json_tokens[*ptr].end - json_tokens[*ptr].start < WORK_BUFFER_SIZE)
					memcpy(work_buffer, json_text + json_tokens[*ptr].start, json_tokens[*ptr].end - json_tokens[*ptr].start);
				else
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "String size exceeded buffer size: ");
					return NULL;
				}
				if (GetValueType(work_buffer) != VT_DECIMAL)
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "id is not decimal: ");
					return NULL;
				}
				elem->_id = (uint32_t)GetLongInt(work_buffer);
				memset(work_buffer, 0, json_tokens[*ptr].end - json_tokens[*ptr].start);
				important_fileds++;
			}
			else if (jsoneq(json_text, &json_tokens[*ptr], "entry_type") == 0)
			{
				if (elem->menu_info.entry_type)
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "Parameter entry_type already existed: ");
					return NULL;
				}
				*ptr += 1;
				if (json_tokens[*ptr].end - json_tokens[*ptr].start < WORK_BUFFER_SIZE)
					memcpy(work_buffer, json_text + json_tokens[*ptr].start, json_tokens[*ptr].end - json_tokens[*ptr].start);
				else
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "String size exceeded buffer size: ");
					return NULL;
				}
				value_type_t type = GetValueType(work_buffer);
				if (type != VT_FOLDER_ENTRY && type != VT_PARAM_VALUE && type != VT_PARAM)
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "entity_type is not FolderEntry, Param or ParamValue: ");
					return NULL;
				}
				if (type == VT_FOLDER_ENTRY)
					elem->menu_info.entry_type = ENTRY_FOLDER;
				else if (type == VT_PARAM)
					elem->menu_info.entry_type = ENTRY_PARAM;
				else
					elem->menu_info.entry_type = ENTRY_VALUE;
				memset(work_buffer, 0, json_tokens[*ptr].end - json_tokens[*ptr].start);
				important_fileds++;
			}
			else if (jsoneq(json_text, &json_tokens[*ptr], "entries") == 0)
			{
				*ptr += 1;
				uint32_t arr_size = json_tokens[*ptr].size;
				if (json_tokens[*ptr].type != JSMN_ARRAY)
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "entries is not JSON_ARRAY: ");
					return NULL;
				}
				for (uint32_t ii = 0; ii < arr_size; ii++)
				{
					*ptr += 1;
					UNUSED(ii);
					if (json_tokens[*ptr].end - json_tokens[*ptr].start < WORK_BUFFER_SIZE)
						memcpy(work_buffer, json_text + json_tokens[*ptr].start, json_tokens[*ptr].end - json_tokens[*ptr].start);
					else
					{
						SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "String size exceeded buffer size: ");
						return NULL;
					}
					if (t->requered_jsons_size == 0)
					{
						t->requered_jsons = (char**)calloc(5, sizeof(char*));
						if (t->requered_jsons == NULL)
						{
							free(elem);
							t->error_ptr = -1;
							return NULL;
						}
						t->_requered_json_allocated_size = 5;
						t->requered_jsons[t->requered_jsons_size] = (char*)calloc(strlen(work_buffer) + 1, 1);
						if (t->requered_jsons[t->requered_jsons_size] == NULL)
						{
							free(elem);
							t->error_ptr = -1;
							return NULL;
						}
						memcpy(t->requered_jsons[t->requered_jsons_size++], work_buffer, strlen(work_buffer)); //-V575
					}
					else
					{
					returnToInsertPath:
						if (t->requered_jsons_size < t->_requered_json_allocated_size)
						{
							t->requered_jsons[t->requered_jsons_size] = (char*)calloc(strlen(work_buffer) + 1, 1);
							if (t->requered_jsons[t->requered_jsons_size] == NULL)
							{
								free(elem);
								t->error_ptr = -1;
								return NULL;
							}
							memcpy(t->requered_jsons[t->requered_jsons_size++], work_buffer, strlen(work_buffer)); //-V575
						}
						else
						{
							char** temp = (char**)LocalRealloc(t->requered_jsons, t->_requered_json_allocated_size * (sizeof(char**)),(t->_requered_json_allocated_size + 5) * (sizeof(char**)));
							if (temp == NULL)
							{
								free(elem);
								t->error_ptr = -1;
								return NULL;
							}
							memset(&temp[t->_requered_json_allocated_size], 0, sizeof(char**) * 5);
							t->_requered_json_allocated_size += 5;
							goto returnToInsertPath;
						}
					}
					memset(work_buffer, 0, json_tokens[*ptr].end - json_tokens[*ptr].start);
				}
			}
			else if (jsoneq(json_text, &json_tokens[*ptr], "default_value") == 0)
			{
				*ptr += 1; // TODO CHECK ARRAY
				if (json_tokens[*ptr].size != 2)
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "default_value requered 2 params (id and value): ");
					return NULL;
				}
				else
				{
					if (json_tokens[*ptr].type != JSMN_ARRAY)
					{
						SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "entries is not JSON_ARRAY: ");
						return NULL;
					}
					*ptr += 1;
					if (json_tokens[*ptr].end - json_tokens[*ptr].start < WORK_BUFFER_SIZE)
						memcpy(work_buffer, json_text + json_tokens[*ptr].start, json_tokens[*ptr].end - json_tokens[*ptr].start);
					else
					{
						SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "String size exceeded buffer size: ");
						return NULL;
					}
					if (GetValueType(work_buffer) != VT_DECIMAL)
					{
						SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "default_value.id is not decimal: ");
						return NULL;
					}
					elem->value_data.default_value.id = (uint32_t)GetLongInt(work_buffer);
					memset(work_buffer, 0, json_tokens[*ptr].end - json_tokens[*ptr].start);
					*ptr += 1;
					if (json_tokens[*ptr].end - json_tokens[*ptr].start < WORK_BUFFER_SIZE)
						memcpy(work_buffer, json_text + json_tokens[*ptr].start, json_tokens[*ptr].end - json_tokens[*ptr].start);
					else
					{
						SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "String size exceeded buffer size: ");
						return NULL;
					}
					if (GetValueType(work_buffer) != VT_DECIMAL)
					{
						SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "default_value.value is not decimal: ");
						return NULL;
					}
					elem->value_data.default_value.value = GetLongInt(work_buffer);
					memset(work_buffer, 0, json_tokens[*ptr].end - json_tokens[*ptr].start);

				}

			}
			else if (jsoneq(json_text, &json_tokens[*ptr], "hide_if") == 0)
			{
				*ptr += 1; // TODO CHECK ARRAY
				if (json_tokens[*ptr].size != 3)
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "hide_if requered 3 params (id, condition and value): ");
					return NULL;
				}
				else
					*ptr += 3; // TODO
			}
			else if (jsoneq(json_text, &json_tokens[*ptr], "parent_id") == 0)
			{
				if (elem->_parent_id)
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "Parameter parent_id already existed: ");
					return NULL;
				}
				*ptr += 1;
				if (json_tokens[*ptr].end - json_tokens[*ptr].start < WORK_BUFFER_SIZE)
					memcpy(work_buffer, json_text + json_tokens[*ptr].start, json_tokens[*ptr].end - json_tokens[*ptr].start);
				else
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "String size exceeded buffer size: ");
					return NULL;
				}
				if (GetValueType(work_buffer) != VT_DECIMAL)
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "parent_id is not decimal: ");
					return NULL;
				}
				elem->_parent_id = (uint32_t)GetLongInt(work_buffer);
				memset(work_buffer, 0, json_tokens[*ptr].end - json_tokens[*ptr].start);
				important_fileds++;
			}
			else if (jsoneq(json_text, &json_tokens[*ptr], "offset") == 0)
			{
				*ptr += 1;
				if (elem->value_data.offset)
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "Parameter offset already existed: ");
					return NULL;
				}
				if (json_tokens[*ptr].end - json_tokens[*ptr].start < WORK_BUFFER_SIZE)
					memcpy(work_buffer, json_text + json_tokens[*ptr].start, json_tokens[*ptr].end - json_tokens[*ptr].start);
				else
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "String size exceeded buffer size: ");
					return NULL;
				}
				value_type_t type = GetValueType(work_buffer);
				if (type != VT_DECIMAL && type != VT_HEX)
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "offset is not decimal or hex: ");
					return NULL;
				}
				if (type == VT_DECIMAL)
				{
					elem->value_data.offset = (ptrdiff_t)GetLongInt(work_buffer);;
				}
				else
				{
					elem->value_data.offset = GetHexValue(work_buffer);
					//int res = sscanf(work_buffer, "%tx", &elem->value_data.offset);
				}

				memset(work_buffer, 0, json_tokens[*ptr].end - json_tokens[*ptr].start);
			}
			else if (jsoneq(json_text, &json_tokens[*ptr], "param_size") == 0)
			{
				*ptr += 1;
				if (elem->value_data.param_size)
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "Parameter param_size already existed: ");
					return NULL;
				}
				if (json_tokens[*ptr].end - json_tokens[*ptr].start < WORK_BUFFER_SIZE)
					memcpy(work_buffer, json_text + json_tokens[*ptr].start, json_tokens[*ptr].end - json_tokens[*ptr].start);
				else
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "String size exceeded buffer size: ");
					return NULL;
				}
				if (GetValueType(work_buffer) != VT_DECIMAL)
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "param_size is not decimal: ");
					return NULL;
				}
				elem->value_data.param_size = (uint32_t)GetLongInt(work_buffer);
				memset(work_buffer, 0, json_tokens[*ptr].end - json_tokens[*ptr].start);
			}
			else if (jsoneq(json_text, &json_tokens[*ptr], "unit_name") == 0)
			{
				*ptr += 1;
				if (elem->value_data.unit_name)
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "Parameter unit_name already existed: ");
					return NULL;
				}
				elem->value_data.unit_name = (char*)calloc(json_tokens[*ptr].end - json_tokens[*ptr].start + 1, 1);
				if (elem->value_data.unit_name == NULL)
				{
					free(elem);
					t->error_ptr = -1;
					return NULL;
				}
				memcpy(elem->value_data.unit_name, json_text + json_tokens[*ptr].start, json_tokens[*ptr].end - json_tokens[*ptr].start);
			}
			else if (jsoneq(json_text, &json_tokens[*ptr], "parameter_type") == 0)
			{
				*ptr += 1;
				if (elem->value_data.param_type)
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "Parameter parameter_type already existed: ");
					return NULL;
				}
				if (json_tokens[*ptr].end - json_tokens[*ptr].start < WORK_BUFFER_SIZE)
					memcpy(work_buffer, json_text + json_tokens[*ptr].start, json_tokens[*ptr].end - json_tokens[*ptr].start);
				else
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "String size exceeded buffer size: ");
					return NULL;
				}
				value_type_t type = GetValueType(work_buffer);
				if (type != VT_FIXED && type != VT_RANGE && type != VT_MANUAL)
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "parameter_type is not Fixed, Manual or Range: ");
					return NULL;
				}
				if (type == VT_FIXED)
					elem->value_data.param_type = PARAM_FIXED_SELECTION;
				else if (type == VT_RANGE)
					elem->value_data.param_type = PARAM_RANGE_SELECTION;
				else
					elem->value_data.param_type = PARAM_MANUAL_SELECTION;
				memset(work_buffer, 0, json_tokens[*ptr].end - json_tokens[*ptr].start);
			}
			else if (jsoneq(json_text, &json_tokens[*ptr], "value") == 0)
			{
				*ptr += 1;
				if (json_tokens[*ptr].end - json_tokens[*ptr].start < WORK_BUFFER_SIZE)
					memcpy(work_buffer, json_text + json_tokens[*ptr].start, json_tokens[*ptr].end - json_tokens[*ptr].start);
				else
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "String size exceeded buffer size: ");
					return NULL;
				}
				value_type_t type = GetValueType(work_buffer);
				if (type != VT_DECIMAL && type != VT_HEX)
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "value is not decimal or hex: ");
					return NULL;
				}
				if (type == VT_DECIMAL)
				{
					elem->value_data.value = GetLongInt(work_buffer);;
				}
				else
				{
					elem->value_data.value = GetHexValue(work_buffer);
				}

				memset(work_buffer, 0, json_tokens[*ptr].end - json_tokens[*ptr].start);
			}
			else if (jsoneq(json_text, &json_tokens[*ptr], "min_value") == 0)
			{
				*ptr += 1;
				if (json_tokens[*ptr].end - json_tokens[*ptr].start < WORK_BUFFER_SIZE)
					memcpy(work_buffer, json_text + json_tokens[*ptr].start, json_tokens[*ptr].end - json_tokens[*ptr].start);
				else
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "String size exceeded buffer size: ");
					return NULL;
				}
				value_type_t type = GetValueType(work_buffer);
				if (type != VT_DECIMAL && type != VT_HEX)
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "min_value is not decimal or hex: ");
					return NULL;
				}
				if (type == VT_DECIMAL)
				{
					elem->value_data.min_value = GetLongInt(work_buffer);;
				}
				else
				{
					elem->value_data.min_value = GetHexValue(work_buffer);
				}
				memset(work_buffer, 0, json_tokens[*ptr].end - json_tokens[*ptr].start);
			}
			else if (jsoneq(json_text, &json_tokens[*ptr], "max_value") == 0)
			{
				*ptr += 1;
				if (json_tokens[*ptr].end - json_tokens[*ptr].start < WORK_BUFFER_SIZE)
					memcpy(work_buffer, json_text + json_tokens[*ptr].start, json_tokens[*ptr].end - json_tokens[*ptr].start);
				else
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "String size exceeded buffer size: ");
					return NULL;
				}
				value_type_t type = GetValueType(work_buffer);
				if (type != VT_DECIMAL && type != VT_HEX)
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "max_value is not decimal or hex: ");
					return NULL;
				}
				if (type == VT_DECIMAL)
				{
					elem->value_data.max_value = GetLongInt(work_buffer);;
				}
				else
				{
					elem->value_data.max_value = GetHexValue(work_buffer);
				}
				memset(work_buffer, 0, json_tokens[*ptr].end - json_tokens[*ptr].start);
			}
			else if (jsoneq(json_text, &json_tokens[*ptr], "delimiter") == 0)
			{
				*ptr += 1;
				if (json_tokens[*ptr].end - json_tokens[*ptr].start < WORK_BUFFER_SIZE)
					memcpy(work_buffer, json_text + json_tokens[*ptr].start, json_tokens[*ptr].end - json_tokens[*ptr].start);
				else
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "String size exceeded buffer size: ");
					return NULL;
				}
				value_type_t type = GetValueType(work_buffer);
				if (type != VT_DECIMAL && type != VT_HEX)
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "delimiter is not decimal or hex: ");
					return NULL;
				}
				if (type == VT_DECIMAL)
				{
					elem->value_data.delimiter = GetLongInt(work_buffer);;
				}
				else
				{
					elem->value_data.delimiter = GetHexValue(work_buffer);
				}
				memset(work_buffer, 0, json_tokens[*ptr].end - json_tokens[*ptr].start);
			}
			else if (jsoneq(json_text, &json_tokens[*ptr], "value_step") == 0)
			{
				*ptr += 1;
				if (json_tokens[*ptr].end - json_tokens[*ptr].start < WORK_BUFFER_SIZE)
					memcpy(work_buffer, json_text + json_tokens[*ptr].start, json_tokens[*ptr].end - json_tokens[*ptr].start);
				else
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "String size exceeded buffer size: ");
					return NULL;
				}
				value_type_t type = GetValueType(work_buffer);
				if (type != VT_DECIMAL && type != VT_HEX)
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "value_step is not decimal or hex: ");
					return NULL;
				}
				if (type == VT_DECIMAL)
				{
					elem->value_data.step = GetLongInt(work_buffer);
				}
				else
				{
					elem->value_data.step = GetHexValue(work_buffer);
				}
				memset(work_buffer, 0, json_tokens[*ptr].end - json_tokens[*ptr].start);
			}
			else if (jsoneq(json_text, &json_tokens[*ptr], "kip_version") == 0)
			{
				*ptr += 1;
				if (t->kip_version)
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "Parameter kip_version already existed: ");
					return NULL;
				}
				if (json_tokens[*ptr].end - json_tokens[*ptr].start < WORK_BUFFER_SIZE)
					memcpy(work_buffer, json_text + json_tokens[*ptr].start, json_tokens[*ptr].end - json_tokens[*ptr].start);
				else
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "String size exceeded buffer size: ");
					return NULL;
				}
				if (GetValueType(work_buffer) != VT_DECIMAL)
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "kip_version is not decimal: ");
					return NULL;
				}
				t->kip_version = GetLongInt(work_buffer);;
				memset(work_buffer, 0, json_tokens[*ptr].end - json_tokens[*ptr].start);
				*version += 1;
			}
			else if (jsoneq(json_text, &json_tokens[*ptr], "kip_tool_min_version") == 0)
			{
				*ptr += 1;
				if (t->kip_tool_major)
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "Parameter kip_tool_min_version already existed: ");
					return NULL;
				}
				if (json_tokens[*ptr].end - json_tokens[*ptr].start < WORK_BUFFER_SIZE)
					memcpy(work_buffer, json_text + json_tokens[*ptr].start, json_tokens[*ptr].end - json_tokens[*ptr].start);
				else
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "String size exceeded buffer size: ");
					return NULL;
				}
				if (GetValueType(work_buffer) != VT_KIP_TOOL_VERSION)
				{
					SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "kip_tol using unknown version, template: %d.%d.%d: ");
					return NULL;
				}
				
				char* temp = work_buffer;

				t->kip_tool_major = (int32_t)GetLongInt(temp);
				while (IsDigit(temp[0]))
					temp++;
				temp++;
				t->kip_tool_minor = (int32_t)GetLongInt(temp);
				while (IsDigit(temp[0]))
					temp++;
				temp++;
				t->kip_tool_fix = (int32_t)GetLongInt(temp);

				memset(work_buffer, 0, json_tokens[*ptr].end - json_tokens[*ptr].start);
				*version += 1;
			}
			else
			{
				SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "Unknown json entity: ");
				return NULL;
			}
			*ptr += 1;
			counter_inserted++;
		}

		if (counter_inserted >= JSON_MAX_TOKENS)
		{
			SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "Too many json entitys: ");
			return NULL;
		}
		if (elem->_id == elem->_parent_id && elem->_id != 0)
		{
			SaveErrorData(json_tokens, ptr, json_text, elem, t, work_buffer, "Id equals parent_id: ");
			return NULL;
		}

		if (elem->_id == 0)
		{
			free(elem);
			elem = NULL;
		}
		else if (important_fileds != 4) // id, parent_id, name, entry_type
		{
			free(elem);
			elem = NULL;
		}


		return elem;
	}
	else
		return NULL;
}

// Шаг 1, распарсить json в структуры и сделать карту аля айди - элемент
entry_list_s* ParseJson(jsmntok_t* json_tokens, uint32_t json_cnt, char* json_text, uint32_t* menu_count, entry_list_s* head, menu_creation_res_s* t)
{
	char* buffer = (char*)calloc(WORK_BUFFER_SIZE, sizeof(char));
	if (buffer == NULL)
	{
		t->error_ptr = -1;
		return NULL;
	}
	uint32_t ptr = 0;
	entry_list_s* last_inserted;
	if (head != NULL)
	{
		last_inserted = head;
		while (last_inserted->next)
			last_inserted = last_inserted->next;
	}
	else
		last_inserted = NULL;

	// Заполняем словарь
	while (ptr < json_cnt)
	{
		int version = 0;
		entry_list_s* single_elem = (entry_list_s*)calloc(1, sizeof(entry_list_s));
		if (single_elem == NULL)
		{
			// CleanList(head, 1);
			t->error_ptr = -1;
			free(buffer);
			return NULL;
		}

		single_elem->elem = GetElement(json_tokens, json_cnt, &ptr, json_text, buffer, 2048, t, &version);
		if (t->error_ptr != 0)
		{
			CleanList(single_elem, 1);
			return head;
		}

		if (single_elem->elem == NULL)
		{
			free(single_elem);
			if (version != 2)
			{
				CleanList(head, 1);
				free(buffer);
				return NULL;
			}
			continue;
		}
		single_elem->id = single_elem->elem->_id;

		// Check repeating id
		entry_list_s* search_ptr = head;
		while (search_ptr)
		{
			if (search_ptr->id == single_elem->id)
			{
				SaveErrorData(json_tokens, &ptr, json_text, single_elem->elem, t, buffer, "Repeating id: ");
				CleanList(head, 1);
				free(buffer);
				return NULL;
			}
			search_ptr = search_ptr->next;
		}

		if (head == NULL)
		{
			head = single_elem;
			last_inserted = single_elem;
		}
		else
		{
			last_inserted->next = single_elem;
			single_elem->prev = last_inserted;
			last_inserted = single_elem;
		}

	}
	free(buffer);
	return head;
}

void SaveErrorDependecies(entry_list_s* entity, menu_creation_res_s* res)
{
	res->value_error = (char*)calloc(256, 1);
	if (res->value_error == NULL)
	{
		res->error_ptr = -1;
		return;
	}
	snprintf(res->value_error, 256, "Error: Entity id: %lu have non-existing parent!", entity->elem->_id);
}

void SaveErrorParams(entry_list_s* entity, menu_creation_res_s* res, const char* reason)
{
	res->value_error = (char*)calloc(256, 1);
	if (res->value_error == NULL)
	{
		res->error_ptr = -1;
		return;
	}
	snprintf(res->value_error, 256, "Error: Entity id: %lu parameter error: %s", entity->elem->_id, reason);
}

// Рекурсивный подход, так как не могу спроектировать алгоритм обхода, стека 32 метра, надеюсь влезем, а вложенность у нас не такая огромная
// Как доберусь до листа бумаги с ручкой - перепишу для оптимизации по памяти, иначе сегодня вообще не успею. Максимальная глубина рекурсии здесь равна
// максимальной вложенности текущего меню.
// Дополнительно здесь выставляется дефолтное значение в структуре
void SetUpperEntryFirstItem(menu_entry_s* first_item, menu_entry_s* inner_entry)
{
	menu_entry_s* first_item_start = inner_entry;
	while (inner_entry)
	{
		if (inner_entry->item_inner_group)
		{
			SetUpperEntryFirstItem(first_item_start, inner_entry->item_inner_group);
		}
		if (inner_entry->menu_info.entry_type == ENTRY_VALUE)
		{
			if (inner_entry->_id == inner_entry->item_parent->value_data.default_value.id)
			{
				if (inner_entry->value_data.param_type == PARAM_FIXED_SELECTION)
				{
					inner_entry->item_parent->value_data.default_value.value = inner_entry->value_data.value;
				}
			}
		}
		inner_entry->item_upper_group = first_item;
		inner_entry = inner_entry->item_next;
	}
}

// Шаг 2 - выставляем зависимости отношений
// TODO оптимизация, так как вычислительно это супер сложная штука из-за постоянного прохода массива с нуля
menu_entry_s* SetDependencies(entry_list_s* map, menu_creation_res_s* res)
{
	menu_entry_s* head = NULL;
	entry_list_s* current_ptr = map;
	entry_list_s* search_ptr;
	while (current_ptr)
	{
		if (current_ptr->elem->_parent_id != 0)
		{
			search_ptr = map;
			while (search_ptr)
			{ // TODO Унифицировать код
				// Если родитель найден
				if (current_ptr->elem->_parent_id == search_ptr->id)
				{  // Тут начну подробно комментировать, что бы не забыть
					// Назначаем найденного родителя элементу, он должен быть до этого не заполнен.
					current_ptr->elem->item_parent = search_ptr->elem;
					// Если у родителя еще нет наследников в нижестоящем меню
					if (!search_ptr->elem->item_inner_group)
					{
						search_ptr->elem->item_inner_group = current_ptr->elem; // Этот элемент становится наследником
						break;
					}
					else
					{ // Если кто-то есть, то необходимо вставить по возрастанию id-шников
						// Получаем первый элемент списка.
						menu_entry_s* inner_element_first = search_ptr->elem->item_inner_group;
						// Если его айди больше текущего элемента, элемент становится первым, а он становится вторым
						if (inner_element_first->_id > current_ptr->elem->_id)
						{
							// Обновляем поля next prev обоих элементов
							current_ptr->elem->item_next = inner_element_first;
							if (inner_element_first->item_prev != NULL)
							{
								SaveErrorParams(current_ptr, res, "first element already have previous element pointer, internal error!");
								return head;
							}
							inner_element_first->item_prev = current_ptr->elem;
							search_ptr->elem->item_inner_group = current_ptr->elem;
							break;
						}
						else
						{
							// Перебор всех элементов списка
							while (inner_element_first->item_next)
							{
								// Если следующий элемент больше по айди, чем наш, то вставляем между ним и предыдущим в списке
								if (inner_element_first->item_next->_id > current_ptr->elem->_id)
								{
									// Меняем предыдущий элемент следующего элемента на нас
									inner_element_first->item_next->item_prev = current_ptr->elem;
									// Меняем наш следующий элемент на следующий элемент прошлого элемента и прошлый (надеюсь я пойму, что имел ввиду)
									current_ptr->elem->item_next = inner_element_first->item_next;
									current_ptr->elem->item_prev = inner_element_first;
									// Подменяем адрес на прошлом элементе на нас
									inner_element_first->item_next = current_ptr->elem;
									break;
								}
								// инкрементируемся
								inner_element_first = inner_element_first->item_next;
							}
							// Если в цикле выше не добавили ( не обновлен прошлый элемент) - добавляемся в конец списка
							if (!current_ptr->elem->item_prev)
							{
								current_ptr->elem->item_prev = inner_element_first;
								inner_element_first->item_next = current_ptr->elem;
								break;
							}
							else
								break;
						}
					}

				}
				search_ptr = search_ptr->next;
			}
			// Если дошли до конца массива - т.е. не нашли родителя - сообщаем о багосе
			if (!search_ptr)
			{
				SaveErrorDependecies(current_ptr, res);
				return head;
			}
		}
		else
		{
			if (!head)
			{
				head = current_ptr->elem;
			}
			else
			{
				if (head->_id > current_ptr->elem->_id)
				{
					current_ptr->elem->item_next = head;
					head->item_prev = current_ptr->elem;
					head = current_ptr->elem;
					continue;
				}
				else
				{
					menu_entry_s* temp = head;
					// Перебор всех элементов списка
					while (temp->item_next)
					{
						// Если следующий элемент больше по айди, чем наш, то вставляем между ним и предыдущим в списке
						if (temp->item_next->_id > current_ptr->elem->_id)
						{
							// Меняем предыдущий элемент следующего элемента на нас
							temp->item_next->item_prev = current_ptr->elem;
							// Меняем наш следующий элемент на следующий элемент прошлого элемента и прошлый (надеюсь я пойму, что имел ввиду)
							current_ptr->elem->item_next = temp->item_next;
							current_ptr->elem->item_prev = temp;
							// Подменяем адрес на прошлом элементе на нас
							temp->item_next = current_ptr->elem;
							break;
						}
						// инкрементируемся
						temp = temp->item_next;
					}
					// Если в цикле выше не добавили ( не обновлен прошлый элемент) - добавляемся в конец списка
					if (!current_ptr->elem->item_prev)
					{

						current_ptr->elem->item_prev = temp;
						temp->item_next = current_ptr->elem;
						continue;
					}
				}
			}
		}
		// Обновляем отдельные вложения параметров
		if (current_ptr->elem->menu_info.entry_type == ENTRY_VALUE)
		{
			if (current_ptr->elem->item_parent)
			{
				current_ptr->elem->value_data.offset = current_ptr->elem->item_parent->value_data.offset;
				if (current_ptr->elem->value_data.offset == 0)
				{
					SaveErrorParams(current_ptr, res, "missing offset info in Param entry");
					return head;
				}
				if (current_ptr->elem->value_data.unit_name == NULL)
				{
					if (current_ptr->elem->item_parent->value_data.unit_name)
					{
						current_ptr->elem->value_data.unit_name = (char*)calloc(strlen(current_ptr->elem->item_parent->value_data.unit_name) + 1, 1);
						if (current_ptr->elem->value_data.unit_name == NULL)
						{
							res->error_ptr = -1;
							return head;
						}
						memcpy(current_ptr->elem->value_data.unit_name, current_ptr->elem->item_parent->value_data.unit_name, strlen(current_ptr->elem->item_parent->value_data.unit_name)); //-V575
					}
				}

				if (current_ptr->elem->value_data.param_size == 0)
				{
					if (current_ptr->elem->item_parent->value_data.param_size == 0)
					{
						current_ptr->elem->item_parent->value_data.param_size = 4;
					}
					current_ptr->elem->value_data.param_size = current_ptr->elem->item_parent->value_data.param_size;
				}

				if (current_ptr->elem->value_data.delimiter == 0)
				{
					if (current_ptr->elem->item_parent->value_data.delimiter == 0)
					{
						if (current_ptr->elem->value_data.max_value <= 2000)
							current_ptr->elem->value_data.delimiter = 1;
						else
							current_ptr->elem->value_data.delimiter = 1000;
					}
					else
						current_ptr->elem->value_data.delimiter = current_ptr->elem->item_parent->value_data.delimiter;

				}
			}
			else
			{
				SaveErrorParams(current_ptr, res, "missing parent pointer, internal error!");
				return head;
			}
		}

		current_ptr = current_ptr->next;
	}

	// Проход 2 - выставляет указатели на начало верхнего уровня меню

	menu_entry_s* current = head;
	menu_entry_s* upper = NULL;

	SetUpperEntryFirstItem(NULL, head);

	return head;
}


menu_creation_res_s* ReadJsonMenuFromText(char* json_text)
{
	jsmn_parser p;
	int tokens_count;
	jsmn_init(&p);
	menu_creation_res_s* t = (menu_creation_res_s*)calloc(1, sizeof(menu_creation_res_s));
	if (t == NULL)
		return NULL;

	jsmntok_t* json_tokens = (jsmntok_t*)calloc(JSON_TOKENS_COUNT * sizeof(jsmntok_t), 1);
	if (json_tokens == NULL)
		return t;
	auto rts = errno;
	tokens_count = jsmn_parse(&p, json_text, strlen(json_text), json_tokens,
		JSON_TOKENS_COUNT);
	uint32_t menu_count = 0;
	entry_list_s* head = NULL;

	head = ParseJson(json_tokens, tokens_count, json_text, &menu_count, head, t);
	if (head == NULL)
		return t;
	t->head = head;
	free(json_tokens);
	json_tokens = NULL;

	return t;
}

menu_creation_res_s* AppendJsonMenuFromText(char* json_text, menu_creation_res_s* t)
{
	jsmn_parser p;
	int tokens_count;
	jsmn_init(&p);

	jsmntok_t* json_tokens = (jsmntok_t*)calloc(JSON_TOKENS_COUNT * sizeof(jsmntok_t), 1);
	if (json_tokens == NULL)
		return t;
	auto rts = errno;
	tokens_count = jsmn_parse(&p, json_text, strlen(json_text), json_tokens,
		JSON_TOKENS_COUNT);
	uint32_t menu_count = 0;

	t->head = ParseJson(json_tokens, tokens_count, json_text, &menu_count, t->head, t);
	free(json_tokens);
	json_tokens = NULL;

	return t;
}

menu_entry_s* CreateMenu(menu_creation_res_s* menu_creation_res)
{
	menu_entry_s* rcs = SetDependencies(menu_creation_res->head, menu_creation_res);
	CleanList(menu_creation_res->head, 0);
	menu_creation_res->head = NULL;
	return rcs;
}

void DeleteMenuCreationRes(menu_creation_res_s* dta)
{
	while (dta->requered_jsons_size)
	{
		dta->requered_jsons_size--;
		free(dta->requered_jsons[dta->requered_jsons_size]);
	}
	CleanList(dta->head, 0);
	free(dta->value_error);
	free(dta->requered_jsons);
	free(dta);
}

// Аналогично рекурсивное удаление, переделаю вместе с алгоритмом SetUpperEntryFirstItem
void DeleteJsonMenu(menu_entry_s* header)
{
	menu_entry_s* temp;
	while (header)
	{
		if (header->item_inner_group)
		{
			DeleteJsonMenu(header->item_inner_group);
		}
		temp = header->item_next;
		DeleteMenuElement(header);
		header = temp;
	}

}

char* GetCurrentValue(menu_entry_s* folder_with_params, int64_t readed_value)
{
	return NULL;
}
