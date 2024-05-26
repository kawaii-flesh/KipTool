#pragma once
#include "kipWizard/kipWizard.h"
#include "service/kiptool.h"
#include "service/profile.h"

enum { KTMenu = 0, KTWizard, AddToProfiles };

MenuEntry_t kipToolMenuEntries[] = {
    {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .name = "-- Kip Tool Menu --"},
    {.optionUnion = COLORTORGB(COLOR_GREEN), .name = "Kip Wizard"},
    {.optionUnion = COLORTORGB(COLOR_GREEN), .name = "Add to Profiles"},
};

const int (*kipToolMenuPaths[])(char*, FSEntry_t) = {[KTWizard] = kipWizard, [AddToProfiles] = addFileToProfiles};

void drawKipToolMenu(char* path, FSEntry_t entry) {
    Vector_t ent = vecFromArray(kipToolMenuEntries, ARR_LEN(kipToolMenuEntries), sizeof(MenuEntry_t));
    gfx_boxGrey(384, 200, 384 + 512, 200 + 320, 0x33);
    gfx_con_setpos(384 + 16, 200 + 16);
    int res = newMenu(&ent, 0, 30, 19, ENABLEB | ALWAYSREDRAW | USELIGHTGREY, ent.count);
    if (res < 3 && res != -1) kipToolMenuPaths[res](path, entry);
}
