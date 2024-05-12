#include "4ekate.h"

#include <libs/fatfs/ff.h>
#include <mem/heap.h>

#include "../err.h"
#include "../fs/fscopy.h"
#include "../fs/fsutils.h"
#include "../helpers/mem.h"
#include "../kiptool/gfx/gfx.h"
#include "../kiptool/gfx/menus/ktMenu.h"
#include "../kiptool/helpers/rw.h"

#define CHEKATE_STAGES_COUNT 3

const CHEKATEParams stages[CHEKATE_STAGES_COUNT] = {
    {.p0 = 0xFFFF2400, .p1 = 0x6E574400, .p2 = 0x39722800, .p3 = 0x4B9C1000},  // DEFAULT
    {.p0 = 0x00002400, .p1 = 0x6E574400, .p2 = 0x39722800, .p3 = 0x4B9C1000},  // ST1
    {.p0 = 0x00002400, .p1 = 0x00004400, .p2 = 0x00002800, .p3 = 0x00001000}   // ST2
};
const char* stagesTitles[CHEKATE_STAGES_COUNT] = {"4EKATE Stage - Default", "4EKATE Stage - ST1", "4EKATE Stage - ST2"};

bool load4EKATEParams(CHEKATEParams* params) {
    FIL file;
    FRESULT res;
    res = f_open(&file, CHEKATE_PAYLOAD_PATH, FA_READ);
    if (res != FR_OK) {
        f_close(&file);
        return false;
    }
    unsigned int bytesRead;
    f_lseek(&file, CHEKATE_PARAMS_ABSOLUTE_OFFSET);
    f_read(&file, params, sizeof(CHEKATEParams), &bytesRead);
    f_close(&file);
    return bytesRead == sizeof(CHEKATEParams);
}

bool set4EKATEParams(const CHEKATEParams* params) {
    FIL file;
    FRESULT res;
    unsigned int bytesWritten;

    res = f_open(&file, CHEKATE_PAYLOAD_PATH, FA_WRITE);
    if (res != FR_OK) {
        return false;
    }
    f_lseek(&file, CHEKATE_PARAMS_ABSOLUTE_OFFSET);
    res = f_write(&file, params, sizeof(CHEKATEParams), &bytesWritten);
    f_close(&file);
    if (res != FR_OK || bytesWritten != sizeof(CHEKATEParams)) return false;

    return true;
}

int getCurrentStageId() {
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
    if (stageId == -1) return CHEKATE_UNKNOWN_STAGE;
    return stagesTitles[stageId];
}

bool createPayloadBackup() {
    ErrCode_t res = FileCopy(CHEKATE_PAYLOAD_PATH, CHEKATE_PAYLOAD_BACKUP_PATH, 0);
    if (res.err != 0) return false;
    return true;
}

void chekate() {
    createDirIfNotExist(KT_DIR);
    if (!FileExists(CHEKATE_PAYLOAD_BACKUP_PATH)) {
        gfx_clearscreenKT();
        gfx_printf("Creating a backup ...");
        createPayloadBackup();
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
        int res = newMenuKT(menuEntries, CHEKATE_STAGES_COUNT + 1, startIndex, NULL, printEntry);
        startIndex = res + 1;
        if (res == -1 || currentStageId == -1) {
            free(menuEntries);
            break;
        }
        set4EKATEParams(&stages[res]);

        currentStageId = getCurrentStageId();
    }
}
