#include "mainmenu.h"

#include <mem/heap.h>
#include <soc/fuse.h>
#include <storage/sd.h>
#include <string.h>
#include <utils/btn.h>
#include <utils/util.h>

#include "../4ekate/4ekate.h"
#include "../fs/fsutils.h"
#include "../fs/menus/explorer.h"
#include "../fs/menus/filemenu.h"
#include "../fs/readers/folderReader.h"
#include "../gfx/gfx.h"
#include "../gfx/gfxutils.h"
#include "../gfx/menu.h"
#include "../hid/hid.h"
#include "../hid/touchutils.h"
#include "../kiptool/gfx/dialogs/confirmationDialog.h"
#include "../utils/utils.h"
#include "tconf.h"
#include "tools.h"

enum {
    MainExplore = 0,
    MainKipWizard,
    MainBrowseSd,
    MainMountSd,
    MainViewCredits,
    MainMisc,
    MainActivateTouchMode,
    Main4EKATE,
    MainExit,
    MainPowerOff,
    MainRebootRCM,
    MainRebootNormal,
    MainRebootUpdate,
    MainRebootAMS,
    MainReboot4EKATE
};

MenuEntry_t mainMenuEntries[] = {
    [MainExplore] = {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .name = "-- Explore --"},
    [MainKipWizard] = {.optionUnion = COLORTORGB(COLOR_GREEN), .name = "KIP Wizard atmosphere/kips/loader.kip"},
    [MainBrowseSd] = {.optionUnion = COLORTORGB(COLOR_GREEN), .name = "Browse SD"},
    [MainMountSd] = {.optionUnion = COLORTORGB(COLOR_YELLOW)},  // To mount/unmount the SD
    [MainViewCredits] = {.optionUnion = COLORTORGB(COLOR_YELLOW), .name = "Credits"},
    [MainMisc] = {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .name = "\n-- Misc --"},
    [MainActivateTouchMode] = {.optionUnion = COLORTORGB(COLOR_BLUE)},
    [Main4EKATE] = {.optionUnion = COLORTORGB(COLOR_BLUE)},
    [MainExit] = {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .name = "\n-- Exit --"},
    [MainPowerOff] = {.optionUnion = COLORTORGB(COLOR_VIOLET), .name = "Power off"},
    [MainRebootRCM] = {.optionUnion = COLORTORGB(COLOR_VIOLET), .name = "Reboot to RCM"},
    [MainRebootNormal] = {.optionUnion = COLORTORGB(COLOR_VIOLET), .name = "Reboot normally"},
    [MainRebootUpdate] = {.optionUnion = COLORTORGB(COLOR_VIOLET), .name = "Reboot to bootloader/update.bin"},
    [MainRebootAMS] = {.optionUnion = COLORTORGB(COLOR_VIOLET), .name = "Reboot to atmosphere/reboot_payload.bin"},
    [MainReboot4EKATE] = {.optionUnion = COLORTORGB(COLOR_VIOLET), .name = "Reboot to 4EKATE - /payload.bin"},
};

void HandleSD() {
    gfx_clearscreen();
    TConf.curExplorerLoc = LOC_SD;
    if (!sd_mount() || sd_get_card_removed()) {
        gfx_printf("Sd is not mounted!");
        hidWait();
    } else {
        const char loaderKipPath[] = "sd:/atmosphere/kips";
        FileExplorer(DirExists(loaderKipPath) ? loaderKipPath : "sd:/");
    }
}

void OpenKipWizard() {
    gfx_clearscreen();
    FSEntry_t loaderKip = {.name = "loader.kip"};
    kipWizard("sd:/atmosphere/kips", loaderKip);
}

void ViewCredits() {
    gfx_clearscreen();
    gfx_printf(
        "\nTegraexplorer v%d.%d.%d\nBy SuchMemeManySkill Based on Lockpick_RCM & Hekate, from shchmue & CTCaern\n\nKip Tool "
        "v%d.%d.%d-%d by kawaii-flesh\n\n",
        LP_VER_MJ, LP_VER_MN, LP_VER_BF, KT_VER_MJ, KT_VER_MN, KT_VER_BF, KT_CUST_VER);

    if (hidRead()->r)
        gfx_printf("%k\"I'm not even sure if it works\" - meme", COLOR_ORANGE);
    else if (hidRead()->l)
        gfx_printf("%k\"And you don't seem to understand ...\"", COLOR_BLUE);

    hidWait();
}

extern bool is_sd_inited;
extern int launch_payload(char* path);

void RebootToAMS() { launch_payload("sd:/atmosphere/reboot_payload.bin"); }

void RebootTo4EKATE() { launch_payload(CHEKATE_PAYLOAD_PATH); }

void RebootToUpdate() { launch_payload("sd:/bootloader/update.bin"); }

void MountOrUnmountSD() {
    gfx_clearscreen();
    if (sd_get_card_mounted())
        sd_unmount();
    else if (!sd_mount())
        hidWait();
}

void ActivateTouchMode() {
    if (*isTouchEnabled()) {
        const char* message[] = {"Do you want to deactivate touch mode?", NULL};
        if (confirmationDialog(message, EYES) == EYES) {
            *isTouchEnabled() = 0;
        }
    } else {
        const char* message[] = {"Do you want to activate touch mode?", NULL};
        if (confirmationDialog(message, EYES) == EYES) {
            *isTouchEnabled() = touch_power_on();
        }
    }
}

menuPaths mainMenuPaths[] = {
    [MainBrowseSd] = HandleSD,    [MainKipWizard] = OpenKipWizard, [MainMountSd] = MountOrUnmountSD,   [MainActivateTouchMode] = ActivateTouchMode,
    [Main4EKATE] = chekate,       [MainViewCredits] = ViewCredits, [MainRebootAMS] = RebootToAMS,      [MainRebootUpdate] = RebootToUpdate,
    [MainRebootRCM] = reboot_rcm, [MainPowerOff] = power_off,      [MainRebootNormal] = reboot_normal, [MainReboot4EKATE] = RebootTo4EKATE};

void EnterMainMenu() {
    const char* message1[] = {"Text on Page 1", "Text", "Large teeeeeeeeeeeeeeeeeeeeext", NULL};
    const char* message2[] = {"Text on Page 2", "Text2", "Larger teeeeeeeeeeeeeeeeeeeeext11111", NULL};
    const char* message3[] = {"Text on Page 3", "Text3", "Text3", "Text3", "Text3", "Text3", "Text3", "Text3", "Larger teeeeeee11", NULL};
    const char** message[] = {message1, message2, message3, NULL};
    int res = 0;
    while (1) {
        informationDialog(message);
        if (sd_get_card_removed()) sd_unmount();
        bool sd_mounted = sd_get_card_mounted();
        mainMenuEntries[MainBrowseSd].hide = !sd_mounted;
        mainMenuEntries[MainKipWizard].hide = !sd_mounted || !FileExists("sd:/atmosphere/kips/loader.kip");
        mainMenuEntries[MainMountSd].name = (sd_mounted) ? "Unmount SD" : "Mount SD";

        // -- Exit --
        mainMenuEntries[MainReboot4EKATE].hide = (!sd_mounted || !FileExists(CHEKATE_PAYLOAD_PATH));
        mainMenuEntries[MainRebootAMS].hide = (!sd_mounted || !FileExists("sd:/atmosphere/reboot_payload.bin"));
        mainMenuEntries[MainRebootUpdate].hide = (!sd_mounted || !FileExists("sd:/bootloader/update.bin"));
        mainMenuEntries[MainRebootRCM].hide = TConf.isMariko;
        if (TConf.isMariko && sd_mounted) {
            const char* stageTitle = getCurrentStageTitle();
            mainMenuEntries[Main4EKATE].name = stageTitle;
            if (strcmp(stageTitle, CHEKATE_UNKNOWN_STAGE) == 0)
                mainMenuEntries[Main4EKATE].optionUnion = COLORTORGB(COLOR_GREY) | SKIPBIT;
            else
                mainMenuEntries[Main4EKATE].optionUnion = COLORTORGB(COLOR_BLUE);
        } else
            mainMenuEntries[Main4EKATE].hide = 1;
        mainMenuEntries[MainActivateTouchMode].name = (*isTouchEnabled()) ? "Deactivate touch mode" : "Activate touch mode";
        Vector_t ent = newVec(sizeof(MenuEntry_t), ARRAY_SIZE(mainMenuEntries));
        ent.count = ARRAY_SIZE(mainMenuEntries);
        memcpy(ent.data, mainMenuEntries, sizeof(MenuEntry_t) * ARRAY_SIZE(mainMenuEntries));

        gfx_clearscreen();
        gfx_putc('\n');

        res = newMenu(&ent, res, 79, 30, (ent.count == ARRAY_SIZE(mainMenuEntries)) ? ALWAYSREDRAW : ALWAYSREDRAW | ENABLEPAGECOUNT,
                      ent.count - ARRAY_SIZE(mainMenuEntries));
        if (res < 16 && mainMenuPaths[res] != NULL && res != -1) mainMenuPaths[res]();

        free(ent.data);
    }
}
