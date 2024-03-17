// KipToolMenuExample.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma warning(disable : 4996)

#include "menu_json_tools.h"

#include <libs/fatfs/ff.h>
#include <mem/heap.h>
#include <utils/sprintf.h>

char* ReadFile(const char* path) {
    FIL file;
    FRESULT result = f_open(&file, path, FA_READ);
    if (result != FR_OK) {
        gfx_printf("Failed to open file: %s\r\n", path);
        return NULL;
    }

    u32 bytes_read;
    u32 file_size = f_size(&file);
    char* json_data = (char*)calloc(file_size + 1, sizeof(char));
    if (json_data == NULL) {
        gfx_printf("Failed to allocate memory!\r\n");
        f_close(&file);
        return NULL;
    }

    result = f_read(&file, json_data, file_size, &bytes_read);
    if (result != FR_OK || bytes_read != file_size) {
        gfx_printf("Failed to read file: %s\r\n", path);
        free(json_data);
        f_close(&file);
        return NULL;
    }

    json_data[file_size] = '\0'; // Null-terminate the string
    f_close(&file);
    return json_data;
}


void MenuUsageExample(menu_entry_s* menu)
{
    menu_entry_s* current = menu;
    menu_entry_s* temp = menu;
    
    char buffer[256];
    while (1)
    {
        // Перебираем все пункты меню через item_next пока не дойдем до nullptr
        int cnt = 0;
        while (temp)
        {
            s_printf(buffer, "%i) %s\r\n\0", cnt++, temp->menu_info.name);
            // printf(buffer);
            temp = temp->item_next;
        }
        s_printf(buffer, "%i) BACK\r\n", cnt);
        // printf(buffer);
        char* input = NULL;
        int input_num = atol(input);

        
        if (input_num >= cnt)
        {
            // Если надо подняться на категорию вверх - читаем указатель на item_upper_group
            // он должен всегда указывать на первый элемент меню на N уровне вложенности.
            temp = current->item_upper_group;
            cnt = 0;
            // Если верхней группы нет - значит мы в самом верхнем меню, и дальше пути нет.
            if (temp == NULL)
                return;
            current = temp;
        }
        else
        {
            temp = current;
            // Находим целевой пункт
            while (input_num)
            {
                temp = temp->item_next;
                if (temp == NULL)
                {
                    return;
                }
                input_num--;
            }

            if (temp)
            {
                // Если он содержит внутри что-то, устанавливаем указатель на него, и рисуем
                if (temp->item_inner_group)
                {
                    current = temp->item_inner_group;
                    temp = current;
                }
                else
                {
                    temp = current;
                }
            }
        }
    }
}

uint8_t CheckErrors(menu_creation_res_s* str)
{
    if (str->error_ptr == 0 && str->value_error == NULL)
        return 0;
    else
    {
        // printf(str->value_error);
    }
}

int MenuParserDemo()
{
    gfx_printf("Reading ");
    gfx_printf("./kip21/kip21.json");
    // Шаг 1 - Читаем содержимое файла в главной директории в 1 огромный буфер
    char* json_data = ReadFile("sd:/kip21/kip21.json");
    
    // Вызываем эту функцию для парсинга JSON-а. Она не создает меню, но парсит все его элементы
    menu_creation_res_s* menu_skeleton = ReadJsonMenuFromText(json_data);

    // Проверяем на наличие ошибок при парсинге.
    if (CheckErrors(menu_skeleton))
    {
        // Тут логика обработки ошибок, к примеру.
    }
    free(json_data);
    // Если эта переменная отличается от нуля, то JSON имеет поле entries
    while (menu_skeleton->requered_jsons_size)
    {
        // Читаем с конца, что бы при наличии доп файлов они добавлялись в конец. В начале декрементируем переменную
        menu_skeleton->requered_jsons_size--;
        gfx_printf("Additional reading\n");
        // В массиве чаров будет лежать нуль-терминированный путь до файла, читаем его, опираясь на смещение menu_skeleton->requered_jsons_size
        gfx_printf("%s", (menu_skeleton->requered_jsons[menu_skeleton->requered_jsons_size]));
        
        json_data = ReadFile(menu_skeleton->requered_jsons[menu_skeleton->requered_jsons_size]);

        // После этого сразу же очищаем память и затираем указатель!!!!!!!!!!!!
        free(menu_skeleton->requered_jsons[menu_skeleton->requered_jsons_size]);
        menu_skeleton->requered_jsons[menu_skeleton->requered_jsons_size] = NULL;

        // С помощью новой команды дописываем новые элементы меню в список элементов
        menu_skeleton = AppendJsonMenuFromText(json_data, menu_skeleton);
        // Проверяем на наличие ошибок при парсинге.
        if (CheckErrors(menu_skeleton))
        {
            // Тут логика обработки ошибок, к примеру.
        }

        // Если и в нем будут вхождения - они добавятся в конец этого списка, и requered_jsons_size увеличится
        // В таком виде подобный цикл вычитает все необходимые файлы, сколько бы их ни было
        
        // Удаляем строковый буфер
        free(json_data);
    }
    
    // После того, как мы вычитали ВСЕ файлы JSON, собираем меню с помощью данной команды.
    menu_entry_s* menu = CreateMenu(menu_skeleton);
    // Проверяем на наличие ошибок при парсинге.
    if (CheckErrors(menu_skeleton))
    {
        // Тут логика обработки ошибок, к примеру.
    }

    // Если все ок - удаляем список, он не удалит меню, просто освободит память от уже ненужных элементов.
    DeleteMenuCreationRes(menu_skeleton);

    if (menu == NULL)
        return -1;

    // Работаем с меню
    MenuUsageExample(menu);

    // По окончанию работы удаляем меню.
    DeleteJsonMenu(menu);
    
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
