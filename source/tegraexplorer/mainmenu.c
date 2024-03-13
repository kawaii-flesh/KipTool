#include "mainmenu.h"

#include <mem/heap.h>
#include <soc/fuse.h>
#include <storage/nx_sd.h>
#include <string.h>
#include <utils/btn.h>
#include <utils/util.h>

#include "../config.h"
#include "../fs/fsutils.h"
#include "../fs/menus/explorer.h"
#include "../fs/menus/filemenu.h"
#include "../fs/readers/folderReader.h"
#include "../gfx/gfx.h"
#include "../gfx/gfxutils.h"
#include "../gfx/menu.h"
#include "../hid/hid.h"
#include "../utils/utils.h"
#include "tconf.h"
#include "tools.h"

extern hekate_config h_cfg;

enum {
    MainExplore = 0,
    MainBrowseSd,
    MainMountSd,
    MainViewCredits,
    MainExit,
    MainPowerOff,
    MainRebootRCM,
    MainRebootNormal,
    MainRebootHekate,
    MainRebootAMS,
};

MenuEntry_t mainMenuEntries[] = {
    [MainExplore] = {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .name = "-- Explore --"},
    [MainBrowseSd] = {.optionUnion = COLORTORGB(COLOR_GREEN), .name = "Browse SD"},
    [MainMountSd] = {.optionUnion = COLORTORGB(COLOR_YELLOW)},  // To mount/unmount the SD
    [MainViewCredits] = {.optionUnion = COLORTORGB(COLOR_YELLOW), .name = "Credits"},
    [MainExit] = {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .name = "\n-- Exit --"},
    [MainPowerOff] = {.optionUnion = COLORTORGB(COLOR_VIOLET), .name = "Power off"},
    [MainRebootRCM] = {.optionUnion = COLORTORGB(COLOR_VIOLET), .name = "Reboot to RCM"},
    [MainRebootNormal] = {.optionUnion = COLORTORGB(COLOR_VIOLET), .name = "Reboot normally"},
    [MainRebootHekate] = {.optionUnion = COLORTORGB(COLOR_VIOLET), .name = "Reboot to bootloader/update.bin"},
    [MainRebootAMS] = {.optionUnion = COLORTORGB(COLOR_VIOLET), .name = "Reboot to atmosphere/reboot_payload.bin"},
};

void HandleSD() {
    gfx_clearscreen();
    TConf.curExplorerLoc = LOC_SD;
    if (!sd_mount() || sd_get_card_removed()) {
        gfx_printf("Sd is not mounted!");
        hidWait();
    } else {
        const loaderKipPath = "sd:/atmosphere/kips";
        FileExplorer(DirExists(loaderKipPath) ? loaderKipPath : "sd:/");
    }
}

void ViewCredits() {
    gfx_clearscreen();
    gfx_printf(
        "\nTegraexplorer v%d.%d.%d\nBy SuchMemeManySkill\Based on Lockpick_RCM & Hekate, from shchmue & CTCaern\n\nKip Tool "
        "v%d.%d.%d-%d by kawaii-flesh\n\n",
        LP_VER_MJ, LP_VER_MN, LP_VER_BF, KT_VER_MJ, KT_VER_MN, KT_VER_BF, KT_CUST_VER);

    if (hidRead()->r)
        gfx_printf("%k\"I'm not even sure if it works\" - meme", COLOR_ORANGE);
    else if (hidRead()->l)
        gfx_printf("%k\"And you don't seem to understand ...\"", COLOR_BLUE);

    hidWait();
}

extern bool sd_mounted;
extern bool is_sd_inited;
extern int launch_payload(char* path);

void RebootToAMS() { launch_payload("sd:/atmosphere/reboot_payload.bin"); }

void RebootToHekate() { launch_payload("sd:/bootloader/update.bin"); }

void MountOrUnmountSD() {
    gfx_clearscreen();
    if (sd_mounted)
        sd_unmount();
    else if (!sd_mount())
        hidWait();
}

menuPaths mainMenuPaths[] = {
    [MainBrowseSd] = HandleSD,     [MainMountSd] = MountOrUnmountSD,    [MainViewCredits] = ViewCredits,
    [MainRebootAMS] = RebootToAMS, [MainRebootHekate] = RebootToHekate, [MainRebootRCM] = reboot_rcm,
    [MainPowerOff] = power_off,    [MainRebootNormal] = reboot_normal,
};

void EnterMainMenu() {
    int res = 0;
    while (1) {
        if (sd_get_card_removed()) sd_unmount();

        mainMenuEntries[MainBrowseSd].hide = !sd_mounted;
        mainMenuEntries[MainMountSd].name = (sd_mounted) ? "Unmount SD" : "Mount SD";

        // -- Exit --
        mainMenuEntries[MainRebootAMS].hide = (!sd_mounted || !FileExists("sd:/atmosphere/reboot_payload.bin"));
        mainMenuEntries[MainRebootHekate].hide = (!sd_mounted || !FileExists("sd:/bootloader/update.bin"));
        mainMenuEntries[MainRebootRCM].hide = h_cfg.t210b01;
        Vector_t ent = newVec(sizeof(MenuEntry_t), ARRAY_SIZE(mainMenuEntries));
        ent.count = ARRAY_SIZE(mainMenuEntries);
        memcpy(ent.data, mainMenuEntries, sizeof(MenuEntry_t) * ARRAY_SIZE(mainMenuEntries));

        gfx_clearscreen();
        gfx_putc('\n');

        res = newMenu(&ent, res, 79, 30,
                      (ent.count == ARRAY_SIZE(mainMenuEntries)) ? ALWAYSREDRAW : ALWAYSREDRAW | ENABLEPAGECOUNT,
                      ent.count - ARRAY_SIZE(mainMenuEntries));
        if (res < 10 && mainMenuPaths[res] != NULL && res != -1) mainMenuPaths[res]();

        free(ent.data);
    }
}
