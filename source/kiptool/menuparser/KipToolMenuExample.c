#include <mem/heap.h>
#include <stdlib.h>
#include <string.h>
#include <utils/util.h>

#include "../../err.h"
#include "../../fs/fsutils.h"
#include "../../gfx/gfx.h"
#include "../../gfx/gfxutils.h"
#include "../../gfx/menu.h"
#include "../../hid/hid.h"
#include "../gfx/dialogs/confirmationDialog.h"
#include "../gfx/gfx.h"
#include "../gfx/menus/ktMenu.h"
#include "../gfx/menus/paramsMenu.h"
#include "../helpers/hw.h"
#include "../helpers/kiprw.h"
#include "../helpers/param.h"
#include "../service/kiptool.h"
#include "../service/session.h"
#include "draw_helper.h"
#include "menu_json_tools.h"
#include "../../../bdk/utils/sprintf.h"

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

    json_data[file_size] = '\0';  // Null-terminate the string
    f_close(&file);
    return json_data;
}

uint8_t CheckErrors(menu_creation_res_s* str) {
    if (str->error_ptr == 0 && str->value_error == NULL)
        return 0;
    else {
        gfx_printf(str->value_error);
    }
}

void MenuDrawingLogic(menu_entry_s* menu) {
    menu_entry_s* current = menu;
    menu_entry_s* nav_temp = menu;
    uint32_t start_index = 1;
    while (1) {  // TODO Leaks fix on return 0
    drawMenu:    // TODO Remove plz, only study purpose
        uint32_t menu_elements;
        MenuEntry* curr_menu = CreateMenuEntity(current, &menu_elements);
        while (1) {
            gfx_clearscreenKT();
            int res = newMenuKT(curr_menu, menu_elements, start_index, NULL, printEntry);
            gfx_printf("Selected: %d", res);
            DeleteMenuEntry(curr_menu, menu_elements, curr_menu);
            if (res == -1) {
                nav_temp = LocateUpperSelectionMenu(current, &start_index);
                if (nav_temp) {
                    current = nav_temp;
                    goto drawMenu;
                } else {
                    return 0;
                }
            }
            nav_temp = LocateChoosenMenu(current, res);
            if (nav_temp == NULL) {
                nav_temp = current;
                start_index = 1;
                goto drawMenu;
            }
            if (nav_temp->item_inner_group) {
                current = nav_temp->item_inner_group;
                nav_temp = current;
                start_index = 1;
                goto drawMenu;
            }
        }
    }
}

int MenuParserDemo(char* path, FSEntry_t entry) {
    char* filePath = CombinePaths(path, entry.name);

    Input_t* input = hidRead();
    if (input->l) {
        if (input->r)
            setHWType(MARIKO);
        else if (input->zr)
            setHWType(ERISTA);
        else if (input->zl)
            setHWType(COMMON);
    }

    gfx_clearscreenKT();
    char* displayBuff = malloc(1024);

    gfx_printf("Reading ");
    gfx_printf("sd:/kip21/kip21.json\r\n");
    // Шаг 1 - Читаем содержимое файла в главной директории в 1 огромный буфер
    char* json_data = ReadFile("sd:/kip21/kip21.json");
    if (json_data == NULL) {
        gfx_printf("Can`t open file!");
        while (1) {
            input = hidRead();

            if (!(input->buttons)) input = hidWait();
            if (input->buttons & (BtnPow | JoyB)) break;
        }
        return 0;
    }
    // Вызываем эту функцию для парсинга JSON-а. Она не создает меню, но парсит все его элементы
    menu_creation_res_s* menu_skeleton = ReadJsonMenuFromText(json_data);

    // Проверяем на наличие ошибок при парсинге.
    if (CheckErrors(menu_skeleton)) {
        while (1) {
            input = hidRead();

            if (!(input->buttons)) input = hidWait();
            if (input->buttons & (BtnPow | JoyB)) break;
        }
        return 0;
    }
    free(json_data);
    // Если эта переменная отличается от нуля, то JSON имеет поле entries
    while (menu_skeleton->requered_jsons_size) {
        // Читаем с конца, что бы при наличии доп файлов они добавлялись в конец. В начале декрементируем переменную
        menu_skeleton->requered_jsons_size--;
        gfx_printf("Additional reading");
        // В массиве чаров будет лежать нуль-терминированный путь до файла, читаем его, опираясь на смещение
        // menu_skeleton->requered_jsons_size
        gfx_printf("%s", (menu_skeleton->requered_jsons[menu_skeleton->requered_jsons_size]));
        gfx_printf("\r\n");
        json_data = ReadFile(menu_skeleton->requered_jsons[menu_skeleton->requered_jsons_size]);

        // После этого сразу же очищаем память и затираем указатель!!!!!!!!!!!!
        free(menu_skeleton->requered_jsons[menu_skeleton->requered_jsons_size]);
        menu_skeleton->requered_jsons[menu_skeleton->requered_jsons_size] = NULL;

        // С помощью новой команды дописываем новые элементы меню в список элементов
        menu_skeleton = AppendJsonMenuFromText(json_data, menu_skeleton);
        // Проверяем на наличие ошибок при парсинге.
        if (CheckErrors(menu_skeleton)) {
            while (1) {
                input = hidRead();

                if (!(input->buttons)) input = hidWait();
                if (input->buttons & (BtnPow | JoyB)) break;
            }
            return 0;
        }

        // Если и в нем будут вхождения - они добавятся в конец этого списка, и requered_jsons_size увеличится
        // В таком виде подобный цикл вычитает все необходимые файлы, сколько бы их ни было

        // Удаляем строковый буфер
        free(json_data);
    }

    // После того, как мы вычитали ВСЕ файлы JSON, собираем меню с помощью данной команды.
    gfx_printf("Creating menu based on KIP%d\n", menu_skeleton->kip_version);
    menu_entry_s* menu = CreateMenu(menu_skeleton);
    // Проверяем на наличие ошибок при парсинге.
    if (CheckErrors(menu_skeleton)) {
        while (1) {
            input = hidRead();

            if (!(input->buttons)) input = hidWait();
            if (input->buttons & (BtnPow | JoyB)) break;
        }
        return 0;
    }

    // Если все ок - удаляем список, он не удалит меню, просто освободит память от уже ненужных элементов.
    DeleteMenuCreationRes(menu_skeleton);

    if (menu == NULL) return -1;
    gfx_printf("Drawing menu...\n", menu_skeleton->kip_version);
    MenuDrawingLogic(menu);

    DeleteJsonMenu(menu);

    // MenuEntry entries[] = {
    //     {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .type = ETLabel, .entry = "-- Kip Wizard --"},
    //     {.optionUnion = COLORTORGB(COLOR_GREEN), .type = ETLabel, .entry = "CPU Params"},
    //     {.optionUnion = COLORTORGB(COLOR_ORANGE), .type = ETLabel, .entry = "GPU Params"},
    //     {.optionUnion = COLORTORGB(COLOR_BLUE), .type = ETLabel, .entry = "RAM Params"},
    //     {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .type = ETLabel, .entry = ""},
    //     {.optionUnion = COLORTORGB(COLOR_WHITE), .type = ETLabel, .entry = "Apply changes"},
    //     {.optionUnion = COLORTORGB(COLOR_GREY), .type = ETLabel, .entry = "Reset all params to default values"}};
    // void (*functions[])(const CustomizeTable*, enum Platform) = {printCPUParams, printGPUParams, printRAMParams};
    // while (1) {
    //     gfx_clearscreenKT();
    //     int res = newMenuKT(entries, 7, startIndex, NULL, printEntry);
    //     startIndex = res + 1;
    //     if (res == -1)
    //         break;
    //     else if (res == 3) {
    //         const char* message[] = {"Do you want to apply changes?", "This will change your kip file", NULL};
    //         if (confirmationDialog(message, ENO) == EYES) {
    //             overwriteCUST(&kipFile, baseOffset, (const u8*)custTable);
    //             gfx_printBottomInfoKT("[KIP File] Changes have been applied");
    //         }
    //     } else if (res == 4) {
    //         ++startIndex;
    //         const char* message[] = {"Do you want to reset all params?", NULL};
    //         if (confirmationDialog(message, ENO) == EYES) {
    //             memcpy_kt((u8*)custTable, (const u8*)&defaultCustTable, sizeof(CustomizeTable));
    //             saveSession(custTable);
    //             gfx_printBottomInfoKT("[Session] All params have been reset");
    //         }
    //     } else if (res <= 2)
    //         functions[res](custTable, getHWType());
    // }
    free(displayBuff);
    return 0;
}
