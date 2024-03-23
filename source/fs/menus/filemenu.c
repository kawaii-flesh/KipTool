#include "filemenu.h"

#include <libs/fatfs/ff.h>
#include <mem/heap.h>
#include <storage/nx_sd.h>
#include <string.h>
#include <utils/sprintf.h>

#include "../../err.h"
#include "../../gfx/gfxutils.h"
#include "../../gfx/menu.h"
#include "../../hid/hid.h"
#include "../../kiptool/menuparser/KipToolMenuExample.h"
#include "../../tegraexplorer/tconf.h"
#include "../../utils/utils.h"
#include "../fsutils.h"

MenuEntry_t FileMenuEntries[] = {
    {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .name = "-- File menu --"},
    {.optionUnion = COLORTORGB(COLOR_GREEN) | SKIPBIT},   // For the file name and size
    {.optionUnion = COLORTORGB(COLOR_VIOLET) | SKIPBIT},  // For the file Attribs
    {.optionUnion = HIDEBIT},
    {.optionUnion = COLORTORGB(COLOR_WHITE), .name = "<- Back"},
    {.optionUnion = COLORTORGB(COLOR_BLUE), .name = "\nCopy to clipboard"},
    {.optionUnion = COLORTORGB(COLOR_BLUE), .name = "Move to clipboard"},
    {.optionUnion = COLORTORGB(COLOR_BLUE), .name = "Rename file\n"},
    {.optionUnion = COLORTORGB(COLOR_RED), .name = "Delete file"},
    {.optionUnion = COLORTORGB(COLOR_ORANGE), .name = "Launch Payload"},
    {.optionUnion = COLORTORGB(COLOR_WHITE), .name = "\nKip tool"},
};

void UnimplementedException(char* path, FSEntry_t entry) { DrawError(newErrCode(TE_ERR_UNIMPLEMENTED)); }

extern int launch_payload(char* path);

void LaunchPayload(char* path, FSEntry_t entry) { launch_payload(CombinePaths(path, entry.name)); }

void KipTool(char* path, FSEntry_t entry) { drawKipToolMenu(path, entry); }

void CopyClipboard(char* path, FSEntry_t entry) {
    char* thing = CombinePaths(path, entry.name);
    SetCopyParams(thing, CMODE_Copy);
    free(thing);
}

void MoveClipboard(char* path, FSEntry_t entry) {
    char* thing = CombinePaths(path, entry.name);
    SetCopyParams(thing, CMODE_Move);
    free(thing);
}

void DeleteFile(char* path, FSEntry_t entry) {
    gfx_con_setpos(384 + 16, 200 + 16 + 10 * 16);
    SETCOLOR(COLOR_RED, COLOR_DARKGREY);
    gfx_printf("Are you sure?      ");

    WaitFor(500);
    if (!MakeYesNoHorzMenu(3, COLOR_DARKGREY)) return;

    char* thing = CombinePaths(path, entry.name);
    int res = f_unlink(thing);
    if (res) DrawError(newErrCode(res));
    free(thing);
}

void RenameFile(char* path, FSEntry_t entry) {
    gfx_clearscreen();
    char* renameTo = ShowKeyboard(entry.name, false);
    if (renameTo == NULL || !(*renameTo))  // smol memory leak but eh
        return;

    char* src = CombinePaths(path, entry.name);
    char* dst = CombinePaths(path, renameTo);

    int res = f_rename(src, dst);
    if (res) {
        DrawError(newErrCode(res));
    }

    free(src);
    free(dst);
    free(renameTo);
}

fileMenuPath FileMenuPaths[] = {CopyClipboard, MoveClipboard, RenameFile, DeleteFile, LaunchPayload, MenuParserDemo};

void FileMenu(char* path, FSEntry_t entry) {
    FileMenuEntries[1].name = entry.name;
    FileMenuEntries[0].sizeUnion = entry.sizeUnion;
    char attribs[16];
    char* attribList = GetFileAttribs(entry);
    s_printf(attribs, "Attribs:%s\n", attribList);
    free(attribList);
    FileMenuEntries[2].name = attribs;

    FileMenuEntries[9].hide = !StrEndsWith(entry.name, ".bin");
    FileMenuEntries[10].hide = !StrEndsWith(entry.name, ".kip");

    Vector_t ent = vecFromArray(FileMenuEntries, ARR_LEN(FileMenuEntries), sizeof(MenuEntry_t));
    gfx_boxGrey(384, 200, 384 + 512, 200 + 320, 0x33);
    gfx_con_setpos(384 + 16, 200 + 16);
    int res = newMenu(&ent, 0, 30, 19, ENABLEB | ALWAYSREDRAW | USELIGHTGREY, ent.count);

    if (res <= 4 || res == -1) return;

    FileMenuPaths[res - 5](path, entry);
}
