// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

// Перечисление типов элементов меню
typedef enum entry_type_t
{
    ENTRY_UNDEFINED = 0,
	ENTRY_FOLDER = 1, // Пункт меню
	ENTRY_PARAM = 2, // Параметр, содержит подменю значений
	ENTRY_VALUE = 3, // Значение параметра
} entry_type_t;

// Перечисление типов значений
typedef enum value_type_t
{
    VALUE_UNDEFINED = 0,
	VALUE_FIXED_SELECTION = 1, // Фиксированное значение, пресет
	VALUE_MANUAL_SELECTION = 2, // Ручной выбор, диапазон min-max
	VALUE_RANGE_SELECTION = 3, // Диапазон параметров с min по max, генерация силами фронта
} value_type_t;

// Перечисление типов оборудования
typedef enum hardware_type_t
{
    HARDWARE_COMMON = 0, // Универсальный параметр
    HARDWARE_ERISTA = 1, // Относится только к ERISTA
    HARDWARE_MARIKO = 2, // Относится только к MARIKO
} hardware_type_t;

// Структура описания значения по умолчанию для параметра
typedef struct default_value_s
{
    uint32_t id_common; // Айди параметря, являющийся дефолтным
    int64_t value_common; // Дефолтное значение
    uint32_t id_erista; // Айди параметря, являющийся дефолтным для эристы
    int64_t value_erista; // Дефолтное значение
    uint32_t id_mariko; // Айди параметря, являющийся дефолтным для марико
    int64_t value_mariko; // Дефолтное значение
} default_value_s;

// Структура описания параметров значения, в т.ч. диапазоны
typedef struct value_data_s
{
	uint32_t value_size; // длинна значения
	value_type_t value_type; // Тип значения (преднастройка или ручной выбор)
	ptrdiff_t offset; // Смещение по кипу значения
	int64_t delimiter; // Делитель значения (для мегагерц, к примеру)
	int64_t value; // Значение
	int64_t min_value; // Минимальное значение
	int64_t max_value; // Максимальное значение (включая границы), для manual selection
	int64_t current_value; // Зарезервирован для заполнения текущим значением параметра
	int64_t step;   // Шаг ручной настройки или перебора
	char* unit_name; // Единицы измерения, нуль-терминированная строка
	default_value_s default_value; // Значение по умолчанию
    hardware_type_t hardware_type; // Железо, к которому относится данный параметр
} value_data_s;

// Данные для отрисовки меню, тип эелемента, его имя и хелпа
typedef struct menu_entry_data_s
{
	char* name; // Наименование пункта, нуль-терминирован
	char* help; // Хелпа, нуль терминирована
	char* description; // Короткое описание, отображается рядом с параметром, 15 символов
	entry_type_t entry_type; // Тип, в соответствии с енумом
	uint32_t color; // Цвет
} menu_entry_data_s;

// Le Costil
typedef struct menu_entry_s menu_entry_s;

// Основная структура, описывюащая элемент меню
struct menu_entry_s
{
	menu_entry_data_s menu_info; // Данные меню, для отрисовки и логики отрисовки
	menu_entry_s* item_next; // Указатель на следующий пункт меню в данном уровне вложенности
	menu_entry_s* item_prev; // Указатель на предыдущий пункт меню в данном уровне вложенности
	menu_entry_s* item_inner_group; // Указатель на первый пункт меню в следующем уровне вложенности
	menu_entry_s* item_parent; // Указатель на элемент, к которому привязан данный элемент
	menu_entry_s* item_upper_group; // Указатель на начало верхнего уровня вложенности
	value_data_s value_data; // Структура хранения данных значения (мин-макс, дефолт и прочее)
	uint8_t(*isActive) (menu_entry_s* entry_ptr, menu_entry_s* menu_head); // Указатель на функцию,
	// Которая проверяет, активен ли данный пункт меню в данном сетапе
	/*****KINDA_PRIVATE_ZONE**/
	uint32_t _id; // id пункта, по большей части нужен при парсинге и заполнении
	uint32_t _parent_id; // id родительского элемента, нужен при парсинге и заполнении
};

typedef struct entry_list_s entry_list_s;
struct entry_list_s
{
	uint32_t id;
	menu_entry_s* elem;
	entry_list_s* next;
	entry_list_s* prev;
};

typedef struct menu_creation_res_s
{
	char* authors;
	uint32_t requered_jsons_size;
	uint32_t _requered_json_allocated_size;
	int32_t error_ptr; // Указатель на элемент по смещению N символов, в районе которого произошла ошибка. Если меньше нуля - код возврата, например связанный с OOM (-1)
	int32_t kip_tool_major;
	int32_t kip_tool_minor;
	int32_t kip_tool_fix;
	char* value_error; // Текст ошибки, если удалось создать.
	int64_t kip_version;
	entry_list_s* head;
	char** requered_jsons;

} menu_creation_res_s;

void CopyDataToMenu(menu_entry_s* dst, const menu_entry_s* src);

/// @brief Чтение JSON и складирование всех элементов в список, первый этап создания меню
/// @param json_text нуль-терминированное содержимое файла json, весь файл
/// @return структура с описанием дополнительных файлов, которые нужно прочитать, а так же список всех пунктов меню.
///         Эти пункты не пригодны для создания меню. Дополнительно в структуру menu_creation_res добавляется информация об ошибках, если они произошли.
menu_creation_res_s* ReadJsonMenuFromText(char* json_text);

/// @brief Чтение JSON и добавление элементов в конец списка JSON-элементов
/// @param json_text нуль-терминированное содержимое файла json, весь файл
/// @param menu_creation_res menu_creation_res - по сути результат работы функции ReadJsonMenuFromText
/// @return структура с описанием дополнительных файлов, которые нужно прочитать, а так же список всех пунктов меню. 
///         Эти пункты не пригодны для создания меню. Дополнительно в структуру menu_creation_res добавляется информация об ошибках, если они произошли.
menu_creation_res_s* AppendJsonMenuFromText(char* json_text, menu_creation_res_s* menu_creation_res);

/// @brief Создание меню, проставление зависимостей и добавление избыточной информации
/// @param menu_creation_res menu_creation_res_s* menu_creation_res - по сути результат работы функции ReadJsonMenuFromText
/// @return Указатель на голову меню
///         Дополнительно в структуру menu_creation_res добавляется информация об ошибках, если они произошли.
menu_entry_s* CreateMenu(menu_creation_res_s* menu_creation_res);

/// @brief Удаление структуры с результатами парсинга, не удаляет сами элементы.
/// @param str Указатель на структуру с результатами парсинга
void DeleteMenuCreationRes(menu_creation_res_s* str);


/// @brief Удаление меню и всех его элементов
/// @param header Указатель на голову меню, самый верхний уровень, самый первый пункт меню
void DeleteJsonMenu(menu_entry_s* header);

#ifdef __cplusplus
}
#endif
