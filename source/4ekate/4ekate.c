#include "4ekate.h"

#include <libs/fatfs/ff.h>
#include <mem/heap.h>
#include <string.h>

#include "../err.h"
#include "../fs/fscopy.h"
#include "../fs/fsutils.h"
#include "../helpers/fs.h"
#include "../helpers/mem.h"
#include "../hid/hid.h"
#include "../kiptool/gfx/gfx.h"
#include "../kiptool/gfx/menus/ktMenu.h"
#include "../kiptool/helpers/rw.h"

const char* chekateFilesPaths[CHEKATE_FILES_COUNT] = {"sd:/payload.bin", "sd:/bootloader/payloads/fusee.bin", "sd:/atmosphere/reboot_payload.bin",
                                                      "sd:/bootloader/update.bin"};
int paramsOffsets[CHEKATE_FILES_COUNT] = {0, 0, 0, 0};

const CHEKATEParams stages[CHEKATE_STAGES_COUNT] = {
    // DEFAULT
    {.mc_emem_adr_cfg_channel_mask = 0xFFFF2400,
     .mc_emem_adr_cfg_bank_mask0 = 0x6E574400,
     .mc_emem_adr_cfg_bank_mask1 = 0x39722800,
     .mc_emem_adr_cfg_bank_mask2 = 0x4B9C1000},
    // ST1
    {.mc_emem_adr_cfg_channel_mask = 0x00002400,
     .mc_emem_adr_cfg_bank_mask0 = 0x6E574400,
     .mc_emem_adr_cfg_bank_mask1 = 0x39722800,
     .mc_emem_adr_cfg_bank_mask2 = 0x4B9C1000},
    // ST2
    {.mc_emem_adr_cfg_channel_mask = 0x00002400,
     .mc_emem_adr_cfg_bank_mask0 = 0x00004400,
     .mc_emem_adr_cfg_bank_mask1 = 0x00002800,
     .mc_emem_adr_cfg_bank_mask2 = 0x00001000}};
const char* stagesTitles[CHEKATE_STAGES_COUNT] = {"4EKATE Stage - Default", "4EKATE Stage - ST1", "4EKATE Stage - ST2"};

const char* chifixTitle = "4EKATE - 4IFIX";
const u8 chifixPattern[4] = {0x46, 0x38, 0x02, 0x40};

int getParamsOffset(const char filePath[], int start) {
    FIL file;
    FRESULT res = f_open(&file, filePath, FA_READ);
    if (res != FR_OK) {
        f_close(&file);
        return -1;
    }
    f_lseek(&file, start);
    for (int i = 0; i < CHEKATE_STAGES_COUNT; ++i) {
        int offset = searchBytesArray((const u8*)(&stages[i]), sizeof(CHEKATEParams), &file);
        if (offset != -1) {
            f_close(&file);
            return offset;
        }
    }
    f_close(&file);
    return -1;
}

void set4ekateStagesOffsets() {
    for (int i = 0; i < CHEKATE_FILES_COUNT; ++i)
        if (paramsOffsets[i] == 0) paramsOffsets[i] = getParamsOffset(chekateFilesPaths[i], 0x00015000);
}

void load4EKATEParams(CHEKATEParams* params) {
    for (int i = 0; i < CHEKATE_FILES_COUNT; ++i)
        if (paramsOffsets[i] == -1) return;
    FIL file;
    FRESULT res = f_open(&file, chekateFilesPaths[0], FA_READ);
    if (res != FR_OK) {
        f_close(&file);
        return;
    }
    unsigned int bytesRead;

    f_lseek(&file, paramsOffsets[0]);
    f_read(&file, params, sizeof(CHEKATEParams), &bytesRead);
    f_close(&file);
}

bool chekateFilesExists() {
    for (int i = 0; i < CHEKATE_FILES_COUNT; ++i)
        if (!FileExists(chekateFilesPaths[i])) return false;
    return true;
}

bool chekateStageWasChanged = false;
bool set4EKATEParams(const CHEKATEParams* params) {
    gfx_clearscreenKT();
    gfx_printf("Patching files. Please wait ...");
    for (int i = 0; i < CHEKATE_FILES_COUNT; ++i)
        if (paramsOffsets[i] == -1) return false;
    for (int i = 0; i < CHEKATE_FILES_COUNT; ++i) {
        FIL file;
        FRESULT res;
        unsigned int bytesWritten;

        if (FileExists(chekateFilesPaths[i])) {
            res = f_open(&file, chekateFilesPaths[i], FA_WRITE);
            if (res != FR_OK) {
                return false;
            }
            f_lseek(&file, paramsOffsets[i]);
            res = f_write(&file, params, sizeof(CHEKATEParams), &bytesWritten);
            f_close(&file);
            if (res != FR_OK || bytesWritten != sizeof(CHEKATEParams)) return false;
        }
    }
    if (!chekateStageWasChanged) chekateStageWasChanged = true;
    return true;
}

int getCurrentStageId() {
    bool unknown = false;
    for (int i = 0; i < CHEKATE_FILES_COUNT; ++i) {
        if (paramsOffsets[i] == -1) {
            unknown = true;
            break;
        }
    }
    if (unknown) {
        u8 buff[4];
        readData(chekateFilesPaths[0], buff, 4, CHIFIX_DETECT_OFFSET);
        if (compareU8Arrays(buff, chifixPattern, 4)) return -2;
        return -1;
    }
    CHEKATEParams* params = malloc(sizeof(CHEKATEParams));
    load4EKATEParams(params);
    for (int i = 0; i < CHEKATE_STAGES_COUNT; ++i)
        if (compareU8Arrays((u8*)params, (u8*)&stages[i], sizeof(CHEKATEParams))) {
            free(params);
            return i;
        }
    free(params);
    return -1;
}

const char* getCurrentStageTitle() {
    const int stageId = getCurrentStageId();
    if (stageId == -1)
        return CHEKATE_UNKNOWN_STAGE;
    else if (stageId == -2)
        return chifixTitle;
    return stagesTitles[stageId];
}

void chekate() {
    createDirIfNotExist(KT_DIR);
    MenuEntry* menuEntries = calloc(1 + CHEKATE_STAGES_COUNT, sizeof(MenuEntry));
    int currentStageId = getCurrentStageId();
    int startIndex = currentStageId + 1;
    menuEntries[0].optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT;
    menuEntries[0].type = ETLabel;
    menuEntries[0].entry = "4EKATE Stages";
    while (1) {
        gfx_clearscreenKT();
        for (int i = 1; i != CHEKATE_STAGES_COUNT + 1; ++i) {
            menuEntries[i].type = ETLabel;
            menuEntries[i].entry = (void*)stagesTitles[i - 1];
            if (i - 1 == currentStageId)
                menuEntries[i].optionUnion = COLORTORGB(COLOR_BLUE);
            else if (i == 1)
                menuEntries[i].optionUnion = COLORTORGB(COLOR_VIOLET);
            else
                menuEntries[i].optionUnion = COLORTORGB(COLOR_ORANGE);
        }
        MenuResult menuResult = newMenuKT(menuEntries, CHEKATE_STAGES_COUNT + 1, startIndex, JoyA, NULL, printEntry);
        if (menuResult.buttons & JoyA) startIndex = menuResult.index;
        if (menuResult.buttons & JoyB || currentStageId == -1) {
            free(menuEntries);
            break;
        }
        set4EKATEParams(&stages[menuResult.selectableIndex]);

        currentStageId = getCurrentStageId();
    }
}
