#pragma once
#include "service/kiptool.h"
#include "menuparser/KipToolMenuExample.h"

enum { KTMenu = 0, MenuParser };

MenuEntry_t kipToolMenuEntries[] = {
    {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .name = "-- Kip Tool Menu --"},
    {.optionUnion = COLORTORGB(COLOR_GREEN), .name = "Menu Parser"},
};

const int (*kipToolMenuPaths[])(char*, FSEntry_t) = {[MenuParser] = MenuParserDemo};

void drawKipToolMenu(char* path, FSEntry_t entry) {
    createKTDirIfNotExist();
    Vector_t ent = vecFromArray(kipToolMenuEntries, ARR_LEN(kipToolMenuEntries), sizeof(MenuEntry_t));
    gfx_boxGrey(384, 200, 384 + 512, 200 + 320, 0x33);
    gfx_con_setpos(384 + 16, 200 + 16);
    int res = newMenu(&ent, 0, 30, 19, ENABLEB | ALWAYSREDRAW | USELIGHTGREY, ent.count);
    if (res < 2 && res != -1) kipToolMenuPaths[res](path, entry);
}
