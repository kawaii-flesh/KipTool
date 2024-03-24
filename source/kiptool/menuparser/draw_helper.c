#include "draw_helper.h"

#include <string.h>

#include "../../../bdk/mem/heap.h"
#include "../../hid/hid.h"
#include "../gfx/gfx.h"
#include "printf.h"

#define DEBUG_BREAKPOINT                             \
    while (1) {                                      \
        Input_t* input = hidRead();                  \
        if (!(input->buttons)) input = hidWait();    \
        if (input->buttons & (BtnPow | JoyB)) break; \
    }

#define MENU_PARAMETER_NAME_LEN (28)
#define MENU_PARAMETER_CURR_VALUE (11)
#define MENU_PARAMETER_VALUE_NAME (13)
#define MENU_PARAMETER_MODIFIED (8)
#define MENU_STRING_MAX_LEN \
    (MENU_PARAMETER_NAME_LEN + 3 + MENU_PARAMETER_CURR_VALUE + 3 + MENU_PARAMETER_VALUE_NAME + 3 + MENU_PARAMETER_MODIFIED)

uint32_t GetRangeElementsCount(menu_entry_s* nav_temp) {
    uint32_t menu_elements = 0;
    int64_t temp = nav_temp->value_data.min_value;
    while (temp <= nav_temp->value_data.max_value) {
        menu_elements++;
        temp += nav_temp->value_data.step;
    }
    return menu_elements;
}
int64_t GetSelectedParameterValue(menu_entry_s* current, int selected) {
    if (current->value_data.value_type == VALUE_RANGE_SELECTION) {
        return current->value_data.min_value + (int64_t)selected * current->value_data.step;
    } else
        return current->value_data.value;
}

menu_entry_s* LocateChoosenMenu(menu_entry_s* current, uint32_t* index) {
    if (current == NULL) return NULL;
    while (*index != 0) {
        if (current->menu_info.entry_type == ENTRY_VALUE && current->value_data.value_type == VALUE_RANGE_SELECTION) {
            if (*index < GetRangeElementsCount(current)) {
                return current;
            } else {
                *index -= GetRangeElementsCount(current);
            }
        } else
            *index -= 1;
        current = current->item_next;
        if (current == NULL) return NULL;
    }
    return current;
}

uint32_t LocateChoosenInnerMenuParam(menu_entry_s* current)
{
    uint32_t counter = 1;
    menu_entry_s* nav_temp = current->item_inner_group;
    while (nav_temp)
    {
        if(nav_temp->menu_info.entry_type = ENTRY_VALUE)
        {
            if (nav_temp->value_data.value_type == VALUE_FIXED_SELECTION)
            {
                if (current->value_data.current_value == nav_temp->value_data.value)
                    return counter;
                counter++;
            }
            else if (nav_temp->value_data.value_type == VALUE_RANGE_SELECTION)
            {
                int64_t beg = nav_temp->value_data.min_value;
                while (beg <= nav_temp->value_data.max_value)
                {
                    if (beg == current->value_data.current_value)
                        return counter;
                    counter++;
                    beg += nav_temp->value_data.step;
                }
            }
        }
        nav_temp = nav_temp->item_next;
    }
    return 1;
}

menu_entry_s* LocateUpperSelectionMenu(menu_entry_s* current, uint32_t* index) {
    *index = 1;
    if (current->item_upper_group) {
        menu_entry_s* searchPtr = current->item_upper_group;
        uint32_t counter = 1;
        while (searchPtr) {
            if (searchPtr == current->item_parent) break;
            counter++;
            searchPtr = searchPtr->item_next;
        }
        if (searchPtr) {
            *index = counter;
            return current->item_upper_group;
        } else
            return NULL;
    } else
        return NULL;
}

const char* GetMenuHeaderName(menu_entry_s* current) {
    char* out = (char*)calloc(256, 1);
    if (current->item_parent == NULL) {
        strcpy(out, "Main menu");
        return out;
    } else {
        strcpy(out, current->item_parent->menu_info.name);
        return out;
    }
}

uint32_t CalculateEntitys(menu_entry_s* nav_temp) {
    uint32_t menu_elements = 1;
    while (nav_temp) {
        if (nav_temp->menu_info.entry_type == ENTRY_VALUE && nav_temp->value_data.value_type == VALUE_RANGE_SELECTION) {
            menu_elements += GetRangeElementsCount(nav_temp);
            // menu_elements += abs((nav_temp->value_data.max_value - nav_temp->value_data.min_value) /
            // nav_temp->value_data.step) + 1;
        } else {
            menu_elements++;
        }
        nav_temp = nav_temp->item_next;
    }
    return menu_elements;
}

void PopulateMenuValueRange(MenuEntry* menu_header, uint32_t count, uint32_t* menu_ptr, menu_entry_s* nav_temp) {
    // gfx_printf("Min %d Max %d Step %d\r\n\0", (uint32_t)nav_temp->value_data.min_value,
    // (uint32_t)nav_temp->value_data.max_value,
    //            (uint32_t)nav_temp->value_data.step);
    for (int32_t i = nav_temp->value_data.min_value; i <= nav_temp->value_data.max_value; i += nav_temp->value_data.step) {
        // gfx_printf("i on step %d ptr %d\r\n\0", (uint32_t)i, *menu_ptr);
        menu_header[*menu_ptr].entry = calloc(MENU_STRING_MAX_LEN + 1, 1);
        // gfx_printf("Text = %s\r\n\0", nav_temp->menu_info.name);
        if (nav_temp->value_data.delimiter == 1) {
            snprintf(menu_header[*menu_ptr].entry, MENU_STRING_MAX_LEN + 1, nav_temp->menu_info.name, i);
        } else {
            snprintf(menu_header[*menu_ptr].entry, MENU_STRING_MAX_LEN + 1, nav_temp->menu_info.name,
                     (float)i / (float)nav_temp->value_data.delimiter);
        }

        if (nav_temp->item_parent->value_data.default_value.id == nav_temp->_id &&
            nav_temp->item_parent->value_data.default_value.value == i) {
            menu_header[*menu_ptr].optionUnion = COLORTORGB(COLOR_BLUE);
        } else
            menu_header[*menu_ptr].optionUnion = COLORTORGB(COLOR_ORANGE);

        menu_header[*menu_ptr].type = ETLabel;
        *menu_ptr += 1;
    }
}

void DeleteMenuEntry(MenuEntry* menu_header, uint32_t count, menu_entry_s* nav_temp) {
    for (uint32_t i = 0; i < count; i++) {
        free((char*)menu_header[i].entry);
    }
    free(menu_header);
}

MenuEntry* CreateMenuEntity(menu_entry_s* current, uint32_t* menu_elements, uint32_t* reset_presented) {
    menu_entry_s* nav_temp = current;
    *menu_elements = CalculateEntitys(current);
    *reset_presented = 0;
    while (nav_temp)
    {
        if (nav_temp->menu_info.entry_type == ENTRY_PARAM){
            *reset_presented = 1;
            break;
        }
        nav_temp = nav_temp->item_next;
    }
    nav_temp = current;

    MenuEntry* curr_menu = (MenuEntry*)calloc(*menu_elements + *reset_presented , sizeof(MenuEntry));
    uint32_t menu_ptr = 0;
    curr_menu[menu_ptr].entry = GetMenuHeaderName(current);
    curr_menu[menu_ptr].optionUnion = COLORTORGB(COLOR_WHITE);
    curr_menu[menu_ptr].skip = 1;
    curr_menu[menu_ptr++].type = ETLabel;

    while (nav_temp) {
        if (nav_temp->menu_info.entry_type == ENTRY_VALUE && nav_temp->value_data.value_type == VALUE_RANGE_SELECTION) {
            // gfx_printf("Min %d Max %d Step %d Ptr %d Entitys %d\r\n\0", (uint32_t)nav_temp->value_data.min_value,
            // (uint32_t)nav_temp->value_data.max_value,
            //            (uint32_t)nav_temp->value_data.step, menu_ptr, *menu_elements);
            PopulateMenuValueRange(curr_menu, *menu_elements, &menu_ptr, nav_temp);
            // gfx_printf("Min %d Max %d Step %d Ptr %d Entitys %d\r\n\0", (uint32_t)nav_temp->value_data.min_value,
            // (uint32_t)nav_temp->value_data.max_value,
            //            (uint32_t)nav_temp->value_data.step, menu_ptr,*menu_elements);
            // while (1) {
            //     Input_t* input = hidRead();
            //
            //   if (!(input->buttons)) input = hidWait();
            //   if (input->buttons & (BtnPow | JoyB)) break;
            //}
        } else {
            PopulateMenuEntry(nav_temp, &curr_menu[menu_ptr++]);
        }

        nav_temp = nav_temp->item_next;
    }

    if (*reset_presented)
    {
        curr_menu[menu_ptr].entry = calloc(MENU_STRING_MAX_LEN + 1, 1);
        snprintf(curr_menu[menu_ptr].entry, MENU_STRING_MAX_LEN + 1, "Reset all parameters to default");
        curr_menu[menu_ptr].optionUnion = COLORTORGB(COLOR_GREY);
        curr_menu[menu_ptr++].type = ETLabel;
        *menu_elements += 1;
    }

    return curr_menu;
}

void FindAndFormatValueNameAndValue(menu_entry_s* entity, char* value_name, char* param_value_curr, char* value_modified_ext,
                                    uint32_t* color) {
    menu_entry_s* nav_temp = entity->item_inner_group;
    char value_modified[] = "Modified";
    char value_default[] = "Default";
    while (nav_temp) {
        if (nav_temp->menu_info.entry_type == ENTRY_VALUE && nav_temp->value_data.value_type == VALUE_FIXED_SELECTION) {
            if (entity->value_data.current_value == nav_temp->value_data.value) {
                if (nav_temp->value_data.delimiter == 1) {
                    snprintf(param_value_curr, MENU_PARAMETER_CURR_VALUE + 1, "%lld%s",
                             entity->value_data.current_value, nav_temp->value_data.unit_name);
                } else {
                    snprintf(param_value_curr, MENU_PARAMETER_CURR_VALUE + 1, "%.2f%s",
                             (float)entity->value_data.current_value / (float)nav_temp->value_data.delimiter,
                             nav_temp->value_data.unit_name);
                }
                snprintf(value_name, MENU_PARAMETER_VALUE_NAME + 1, nav_temp->menu_info.name);
                if (entity->value_data.default_value.id == nav_temp->_id) {
                    *color = COLORTORGB(COLOR_DEFAULT_PARAM);
                    snprintf(value_modified_ext, MENU_PARAMETER_MODIFIED + 1, value_default);
                } else {
                    *color = COLORTORGB(COLOR_CHANGED_PARAM);
                    snprintf(value_modified_ext, MENU_PARAMETER_MODIFIED + 1, value_modified);
                }
                return;
            }
        } else if (nav_temp->menu_info.entry_type == ENTRY_VALUE && nav_temp->value_data.value_type == VALUE_MANUAL_SELECTION) {
            if (entity->value_data.current_value >= nav_temp->value_data.min_value &&
                entity->value_data.current_value <= nav_temp->value_data.max_value) {
                if (nav_temp->value_data.delimiter == 1) {
                    snprintf(param_value_curr, MENU_PARAMETER_CURR_VALUE + 1, "%lld%s",
                             entity->value_data.current_value, nav_temp->value_data.unit_name);
                } else {
                    snprintf(param_value_curr, MENU_PARAMETER_CURR_VALUE + 1, "%.2f%s",
                             (float)entity->value_data.current_value / (float)nav_temp->value_data.delimiter,
                             nav_temp->value_data.unit_name);
                }
                snprintf(value_name, MENU_PARAMETER_VALUE_NAME + 1, nav_temp->menu_info.name);
                if (entity->value_data.default_value.id == nav_temp->_id &&
                    entity->value_data.default_value.value == entity->value_data.current_value) {
                    snprintf(value_modified_ext, MENU_PARAMETER_MODIFIED + 1, value_default);
                    *color = COLORTORGB(COLOR_DEFAULT_PARAM);
                } else {
                    snprintf(value_modified_ext, MENU_PARAMETER_MODIFIED + 1, value_modified);
                    *color = COLORTORGB(COLOR_CHANGED_PARAM);
                }
                return;
            }
        } else if (nav_temp->menu_info.entry_type == ENTRY_VALUE && nav_temp->value_data.value_type == VALUE_RANGE_SELECTION) {
            int64_t beg = nav_temp->value_data.min_value;
            while (beg <= nav_temp->value_data.max_value) {
                if (entity->value_data.current_value == beg) {
                    if (nav_temp->value_data.delimiter == 1) {
                        snprintf(param_value_curr, MENU_PARAMETER_CURR_VALUE + 1, "%lld%s",
                                 entity->value_data.current_value, nav_temp->value_data.unit_name);
                    } else {
                        snprintf(param_value_curr, MENU_PARAMETER_CURR_VALUE + 1, "%.2f%s",
                                 (float)entity->value_data.current_value / (float)nav_temp->value_data.delimiter,
                                 nav_temp->value_data.unit_name);
                    }
                    snprintf(value_name, MENU_PARAMETER_VALUE_NAME + 1, nav_temp->menu_info.name,
                             entity->value_data.current_value);
                    if (entity->value_data.default_value.id == nav_temp->_id &&
                        entity->value_data.default_value.value == entity->value_data.current_value) {
                        snprintf(value_modified_ext, MENU_PARAMETER_MODIFIED + 1, value_default);
                        *color = COLORTORGB(COLOR_DEFAULT_PARAM);
                    } else {
                        snprintf(value_modified_ext, MENU_PARAMETER_MODIFIED + 1, value_modified);
                        *color = COLORTORGB(COLOR_CHANGED_PARAM);
                    }
                    return;
                }
                beg += nav_temp->value_data.step;
            }
        }
        nav_temp = nav_temp->item_next;
    }
    if (entity->value_data.current_value < 2000) {
        snprintf(param_value_curr, MENU_PARAMETER_CURR_VALUE + 1, "%lld%s", entity->value_data.current_value,
                 entity->value_data.unit_name);
    } else {
        snprintf(param_value_curr, MENU_PARAMETER_CURR_VALUE + 1, "%.2f%s", (float)entity->value_data.current_value / 1000.0f,
                 entity->value_data.unit_name);
    }
    snprintf(value_name, MENU_PARAMETER_VALUE_NAME + 1, "Unknown");
    if (entity->value_data.default_value.value == entity->value_data.current_value) {
        snprintf(value_modified_ext, MENU_PARAMETER_MODIFIED + 1, value_default);
        *color = COLORTORGB(COLOR_DEFAULT_PARAM);
    } else {
        snprintf(value_modified_ext, MENU_PARAMETER_MODIFIED + 1, value_modified);
        *color = COLORTORGB(COLOR_CHANGED_PARAM);
    }
}

void FormatParamValueEntryName(menu_entry_s* entity, char* buffer, uint32_t* color) {
    if (entity->value_data.value_type == VALUE_FIXED_SELECTION) {
        if (entity->_id != entity->item_parent->value_data.default_value.id) {
            *color = COLORTORGB(COLOR_ORANGE);
            if (entity->menu_info.help) {
                snprintf(buffer, MENU_STRING_MAX_LEN + 1, "%-11s  - %s", entity->menu_info.name, entity->menu_info.help);
            } else
                snprintf(buffer, MENU_STRING_MAX_LEN + 1, "%-11s", entity->menu_info.name);
        } else {
            *color = COLORTORGB(COLOR_BLUE);
            if (entity->menu_info.help) {
                snprintf(buffer, MENU_STRING_MAX_LEN + 1, "%-11s  - %s - Default", entity->menu_info.name,
                         entity->menu_info.help);
            } else
                snprintf(buffer, MENU_STRING_MAX_LEN + 1, "%-11s  - Default", entity->menu_info.name, entity->menu_info.help);
        }

    } else {
        *color = COLORTORGB(COLOR_YELLOW);
        if (entity->value_data.delimiter == 1)
            snprintf(buffer, MENU_STRING_MAX_LEN + 1, "%s - Min: %lld, Max: %lld, step: %lld", entity->menu_info.name,
                     entity->value_data.min_value, entity->value_data.max_value, entity->value_data.step);
        else
            snprintf(buffer, MENU_STRING_MAX_LEN + 1, "%s - Min: %.2f, Max: %.2f, step: %.2f", entity->menu_info.name,
                     (float)entity->value_data.min_value / (float)entity->value_data.delimiter,
                     (float)entity->value_data.max_value / (float)entity->value_data.delimiter,
                     (float)entity->value_data.step / (float)entity->value_data.delimiter);
    }
}

void FormatParamEntryName(menu_entry_s* entity, char* buffer, uint32_t* color) {
    char* param_value_curr = (char*)calloc(MENU_PARAMETER_CURR_VALUE + 1, 1);
    char* value_name = (char*)calloc(MENU_PARAMETER_VALUE_NAME + 1, 1);
    char* value_modified = (char*)calloc(MENU_PARAMETER_MODIFIED + 1, 1);
    FindAndFormatValueNameAndValue(entity, value_name, param_value_curr, value_modified, color);
    snprintf(buffer, MENU_STRING_MAX_LEN + 1, "%-28s - %-11s - %-13s - %-8s", entity->menu_info.name, param_value_curr,
             value_name, value_modified);

    free(param_value_curr);
    free(value_name);
    free(value_modified);
}

void PopulateMenuEntry(menu_entry_s* entity, MenuEntry* curr_element) {
    uint32_t color = 0;
    if (entity->menu_info.entry_type == ENTRY_FOLDER) {
        color = COLORTORGB(COLOR_GREEN);
    }
    // } else if (entity->menu_info.entry_type == ENTRY_PARAM) {
    //     curr_element->optionUnion = COLORTORGB(COLOR_WHITE);
    // } else {
    //     if (entity->value_data.value_type == VALUE_MANUAL_SELECTION) {
    //         curr_element->optionUnion = COLORTORGB(COLOR_ORANGE);
    //     } else
    //         curr_element->optionUnion = COLORTORGB(COLOR_GREY);
    // }
    char* out = (char*)calloc(MENU_STRING_MAX_LEN + 1, 1);

    if (entity->menu_info.entry_type == ENTRY_PARAM) {  //  TODO Type fix
        FormatParamEntryName(entity, out, &color);
    } else if (entity->menu_info.entry_type == ENTRY_VALUE)
        FormatParamValueEntryName(entity, out, &color);
    else
        strcpy(out, entity->menu_info.name);
    curr_element->optionUnion = color;
    curr_element->entry = out;
    curr_element->type = ETLabel;
    return;
}
