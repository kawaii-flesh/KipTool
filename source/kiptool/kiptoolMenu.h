#pragma once
#include "kipInfo/kipInfo.h"
#include "kipWizard/kipWizard.h"

MenuEntry_t kipToolMenuEntries[] = {
    {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .name = "-- Kip tool menu --"},
    {.optionUnion = COLORTORGB(COLOR_BLUE), .name = "Kip info"},
    {.optionUnion = COLORTORGB(COLOR_GREEN), .name = "Kip wizard"},
};

const int (*kipToolMenuPaths[])(char *, FSEntry_t) = {kipInfo, kipWizard};

void drawKipToolMenu(char *path, FSEntry_t entry) {
    Vector_t ent =
        vecFromArray(kipToolMenuEntries, ARR_LEN(kipToolMenuEntries), sizeof(MenuEntry_t));
    gfx_boxGrey(384, 200, 384 + 512, 200 + 320, 0x33);
    gfx_con_setpos(384 + 16, 200 + 16);
    int res = newMenu(&ent, 0, 30, 19, ENABLEB | ALWAYSREDRAW | USELIGHTGREY, ent.count);

    if (res == 0) return;
    kipToolMenuPaths[res - 1](path, entry);
}
