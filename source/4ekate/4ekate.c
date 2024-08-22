#include "4ekate.h"

#include <libs/fatfs/ff.h>
#include <mem/heap.h>
#include <stdbool.h>
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
const u8 chifixPattern[4] = {0x8a, 0x1e, 0x02, 0x40};

int payloadOffset = 0;
int fuseeOffset = 0;

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
    if (payloadOffset == 0) payloadOffset = getParamsOffset(CHEKATE_PAYLOAD_PATH, 0x00010000);
    if (fuseeOffset == 0) fuseeOffset = getParamsOffset(CHEKATE_FUSEE_PATH, 0x00010000);
}

void load4EKATEParams(CHEKATEParams* params) {
    if (payloadOffset != -1 && fuseeOffset != 1) {
        FIL file;
        FRESULT res = f_open(&file, CHEKATE_PAYLOAD_PATH, FA_READ);
        if (res != FR_OK) {
            f_close(&file);
            return;
        }
        unsigned int bytesRead;

        f_lseek(&file, payloadOffset);
        f_read(&file, params, sizeof(CHEKATEParams), &bytesRead);
        f_close(&file);
    }
}

bool set4EKATEParams(const CHEKATEParams* params) {
    if (payloadOffset != -1 && fuseeOffset != -1) {
        FIL file;
        FRESULT res;
        unsigned int bytesWritten;

        if (FileExists(CHEKATE_PAYLOAD_PATH)) {
            res = f_open(&file, CHEKATE_PAYLOAD_PATH, FA_WRITE);
            if (res != FR_OK) {
                return false;
            }
            f_lseek(&file, payloadOffset);
            res = f_write(&file, params, sizeof(CHEKATEParams), &bytesWritten);
            f_close(&file);
            if (res != FR_OK || bytesWritten != sizeof(CHEKATEParams)) return false;
        }
        if (FileExists(CHEKATE_FUSEE_PATH)) {
            res = f_open(&file, CHEKATE_FUSEE_PATH, FA_WRITE);
            if (res != FR_OK) {
                return false;
            }
            f_lseek(&file, fuseeOffset);
            res = f_write(&file, params, sizeof(CHEKATEParams), &bytesWritten);
            f_close(&file);
            if (res != FR_OK || bytesWritten != sizeof(CHEKATEParams)) return false;
        }

        return true;
    }
    return false;
}

int getCurrentStageId() {
    if (payloadOffset == -1 || fuseeOffset == -1) {
        u8 buff[4];
        readData(CHEKATE_PAYLOAD_PATH, buff, 4, CHIFIX_DETECT_OFFSET);
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

bool createPayloadBackup() {
    ErrCode_t res = FileCopy(CHEKATE_PAYLOAD_PATH, CHEKATE_PAYLOAD_BACKUP_PATH, 0);
    if (res.err != 0) return false;
    return true;
}

bool createPayloadFusee() {
    ErrCode_t res = FileCopy(CHEKATE_FUSEE_PATH, CHEKATE_FUSEE_BACKUP_PATH, 0);
    if (res.err != 0) return false;
    return true;
}

void chekate() {
    createDirIfNotExist(KT_DIR);
    if (!FileExists(CHEKATE_PAYLOAD_BACKUP_PATH)) {
        gfx_clearscreenKT();
        gfx_printf("Creating a paylaod backup ...");
        createPayloadBackup();
    }
    if (!FileExists(CHEKATE_FUSEE_BACKUP_PATH)) {
        gfx_clearscreenKT();
        gfx_printf("Creating a fusee backup ...");
        createPayloadFusee();
    }
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
