#include "kipWizard.h"

#include <mem/heap.h>
#include <stdlib.h>
#include <string.h>
#include <utils/util.h>

#include "../../err.h"
#include "../../fs/fsutils.h"
#include "../../gfx/gfx.h"
#include "../../hid/hid.h"
#include "../helpers/gfx.h"
#include "../helpers/kiprw.h"
#include "../helpers/param.h"
#include "../params/common/cpu.h"
#include "../params/common/general.h"
#include "../params/common/gpu.h"
#include "../params/common/ram.h"
#include "../params/customize.h"
#include "../params/erista/cpu.h"
#include "../params/erista/gpu.h"
#include "../params/erista/ram.h"
#include "../params/mariko/cpu.h"
#include "../params/mariko/gpu.h"
#include "../params/mariko/ram.h"


void printTable(const u8 *buff, const Table *table, char *displayBuff) {
    for (unsigned int i = 0; i < table->paramsCount; ++i) {
        const Param *param = table->params[i];
        const unsigned int paramValue = getParamValueByTable(buff, param, table);
        getDisplayValue(param, displayBuff, paramValue);
        gfx_printf("%s: %s\n", param->name, displayBuff);
    }
}

// void printModeTable(const u8 *buff, const ModeTable *table, char *displayBuff) {
//     const unsigned int mode = getParamValueFromBuffer(buff, table->tableModeParam);
//     const Table *currentTable = table->tables[mode];
//     printTable(buff, currentTable, displayBuff);
// }

void printParamByParam(const u8 *buff, const Param *param, char *displayBuff) {
    unsigned int paramValue = getParamValueFromBuffer(buff, param);
    getDisplayValue(param, displayBuff, paramValue);
    gfx_printf("%s: %s\n", param->name, displayBuff);
}

void printParamByValue(unsigned int value, const Param *param, char *displayBuff) {
    getDisplayValue(param, displayBuff, value);
    gfx_printf("%s: %s\n", param->name, displayBuff);
}

void printCPUParams(const u8 *buff, char *displayBuff, enum Platform platform) {
    gfx_clearscreenKT(platform);
    gfx_printf("--------CPU--------\n");
    for (unsigned int i = 0; i < cCPUParamsCount; ++i) printParamByParam(buff, cCPUParams[i], displayBuff);
    for (unsigned int i = 0; i < cCPUTablesCount; ++i) printTable(buff, cCPUTables[i], displayBuff);
    if (platform == MARIKO || platform == COMMON) {
        for (unsigned int i = 0; i < mCPUParamsCount; ++i) printParamByParam(buff, mCPUParams[i], displayBuff);
        for (unsigned int i = 0; i < mCPUTablesCount; ++i) printTable(buff, mCPUTables[i], displayBuff);
    }
    if (platform == ERISTA || platform == COMMON) {
        for (unsigned int i = 0; i < eCPUParamsCount; ++i) printParamByParam(buff, eCPUParams[i], displayBuff);
        for (unsigned int i = 0; i < eCPUTablesCount; ++i) printTable(buff, eCPUTables[i], displayBuff);
    }
}

void printGPUParams(const u8 *buff, char *displayBuff, enum Platform platform) {
    gfx_clearscreenKT(platform);
    gfx_printf("--------GPU--------\n");
    for (unsigned int i = 0; i < cGPUParamsCount; ++i) printParamByParam(buff, cGPUParams[i], displayBuff);
    for (unsigned int i = 0; i < cGPUTablesCount; ++i) printTable(buff, cGPUTables[i], displayBuff);
    if (platform == MARIKO || platform == COMMON) {
        for (unsigned int i = 0; i < mGPUParamsCount; ++i) printParamByParam(buff, mGPUParams[i], displayBuff);
        for (unsigned int i = 0; i < mGPUTablesCount; ++i) printTable(buff, mGPUTables[i], displayBuff);
    }
    if (platform == ERISTA || platform == COMMON) {
        for (unsigned int i = 0; i < eGPUParamsCount; ++i) printParamByParam(buff, eGPUParams[i], displayBuff);
        for (unsigned int i = 0; i < eGPUTablesCount; ++i) printTable(buff, eGPUTables[i], displayBuff);
    }
}

void printRAMParams(const u8 *buff, char *displayBuff, enum Platform platform) {
    gfx_clearscreenKT(platform);
    gfx_printf("--------RAM--------\n");
    for (unsigned int i = 0; i < cRAMParamsCount; ++i) printParamByParam(buff, cRAMParams[i], displayBuff);
    for (unsigned int i = 0; i < cRAMTablesCount; ++i) printTable(buff, cRAMTables[i], displayBuff);
    if (platform == MARIKO || platform == COMMON) {
        for (unsigned int i = 0; i < mRAMParamsCount; ++i) printParamByParam(buff, mRAMParams[i], displayBuff);
        for (unsigned int i = 0; i < mRAMTablesCount; ++i) printTable(buff, mRAMTables[i], displayBuff);
    }
    if (platform == ERISTA || platform == COMMON) {
        for (unsigned int i = 0; i < eRAMParamsCount; ++i) printParamByParam(buff, eRAMParams[i], displayBuff);
        for (unsigned int i = 0; i < eRAMTablesCount; ++i) printTable(buff, eRAMTables[i], displayBuff);
    }
}

int kipWizard(char *path, FSEntry_t entry) {
    char *filePath = CombinePaths(path, entry.name);

    FIL kipFile;
    int res;
    Input_t *input = hidRead();
    const enum Platform platform = COMMON;  // DEBUG

    gfx_clearscreenKT();

    if ((res = f_open(&kipFile, filePath, FA_READ | FA_OPEN_EXISTING))) {
        DrawError(newErrCode(res));
        return 1;
    }

    u8 cust[] = CUST;
    const unsigned int baseOffset = searchBytesArray(cust, 4, &kipFile);
    const unsigned int custSecionSize = sizeof(CustomizeTable);
    u8 *custSection = calloc(custSecionSize, 1);
    unsigned int bytesReaded;
    f_lseek(&kipFile, baseOffset);
    f_read(&kipFile, custSection, custSecionSize, &bytesReaded);
    unsigned int kipVersion = getParamValueFromBuffer(custSection, &gKipVersion);
    if (kipVersion == CURRENT_VERSION) {
        char *displayBuff = calloc(1024, 1);
        // printParamByValue(kipVersion, &gKipVersion, displayBuff);
        int currentPage = 0;
        int lastPage = 2;
        u32 lastPress = 0;
        u32 holdTimer = 300;
        u32 lastTopUpdate = 0;
        u32 topUpdateTimer = 10000;
        const void (*pageFunctions[])(const u8 *, char *, enum Platform) = {printCPUParams, printGPUParams, printRAMParams};
        pageFunctions[currentPage](custSection, displayBuff, platform);
        while (1) {
            if ((lastTopUpdate + topUpdateTimer) < get_tmr_ms()) {
                gfx_printTopInfoKT();
                lastTopUpdate = get_tmr_ms();
            }
            while (1) {
                hidRead();
                if ((lastTopUpdate + topUpdateTimer) < get_tmr_ms()) {
                    gfx_printTopInfoKT();
                    lastTopUpdate = get_tmr_ms();
                }
                if (input->buttons) {
                    if ((lastPress + holdTimer) < get_tmr_ms()) {
                        lastPress = get_tmr_ms();
                        break;
                    }
                }
            }

            if (input->buttons & (JoyLRight)) {
                ++currentPage;
                if (currentPage > lastPage) currentPage = 0;
                pageFunctions[currentPage](custSection, displayBuff, platform);
            } else if (input->buttons & (JoyLLeft)) {
                --currentPage;
                if (currentPage < 0) currentPage = lastPage;
                pageFunctions[currentPage](custSection, displayBuff, platform);
            } else if (input->buttons & (BtnPow | JoyB))
                break;
        }

        f_close(&kipFile);
        free(filePath);
        free(displayBuff);
        free(custSection);
        return 0;
    }
    gfx_printf("Kip version %d is unsupported. Supported version is %d", kipVersion, CURRENT_VERSION);
    while (1) {
        input = hidRead();

        if (!(input->buttons)) input = hidWait();
        if (input->buttons & (BtnPow | JoyB)) break;
    }
    return 0;
}