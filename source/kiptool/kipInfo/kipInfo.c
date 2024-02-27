#include "kipInfo.h"

#include <mem/heap.h>
#include <stdlib.h>
#include <string.h>

#include "../../err.h"
#include "../../hid/hid.h"
#include "../helpers/kiprw.h"
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

// void printTableFromFile(FIL *file, unsigned int baseOffset, const Table *table, char *displayBuff) {
//     unsigned int tableMode = getParamValueFromFile(file, baseOffset, table->tableModeParam);
//     for (unsigned int i = 0; i < table->paramsCount; ++i) {
//         const Param *param = &table->params[i];
//         const paramValue = getParamValueFromFileByTable(file, baseOffset, param, table, tableMode);
//         getDisplayValue(param, displayBuff, paramValue);
//         gfx_printf("%s: %s\n", param->name, displayBuff, param->measure);
//     }
// }

void printTable(const u8 *buff, const Table *table, char *displayBuff) {
    for (unsigned int i = 0; i < table->paramsCount; ++i) {
        const Param *param = table->params[i];
        const paramValue = getParamValueByTable(buff, param, table);
        getDisplayValue(param, displayBuff, paramValue);
        gfx_printf("%s: %s\n", param->name, displayBuff);
    }
}

void printModeTable(const u8 *buff, const ModeTable *table, char *displayBuff) {
    const unsigned int mode = getParamValueFromBuffer(buff, table->tableModeParam);
    const Table *currentTable = table->tables[mode];
    printTable(buff, currentTable, displayBuff);
}

void printParamByParam(const u8 *buff, const Param *param, char *displayBuff) {
    unsigned int paramValue = getParamValueFromBuffer(buff, param);
    getDisplayValue(param, displayBuff, paramValue);
    gfx_printf("%s: %s\n", param->name, displayBuff);
}

void printParamByValue(unsigned int value, const Param *param, char *displayBuff) {
    getDisplayValue(param, displayBuff, value);
    gfx_printf("%s: %s\n", param->name, displayBuff);
}

void printCPUParams(const u8 *buff, char *displayBuff) {
    gfx_clearscreenKT();
    gfx_printf("--------CPU--------\n");
    for (unsigned int i = 0; i < cCPUParamsCount; ++i) printParamByParam(buff, cCPUParams[i], displayBuff);
    const Param **pCPUParams = isMarikoHWType() ? &mCPUParams : &eCPUParams;
    const unsigned int paramsCount = isMarikoHWType() ? mCPUParamsCount : eCPUParamsCount;
    for (unsigned int i = 0; i < paramsCount; ++i) printParamByParam(buff, pCPUParams[i], displayBuff);
}

void printGPUParams(const u8 *buff, char *displayBuff) {
    gfx_clearscreenKT();
    gfx_printf("--------GPU--------\n");
    for (unsigned int i = 0; i < cGPUParamsCount; ++i) printParamByParam(buff, cGPUParams[i], displayBuff);
    const Param **pGPUParams = isMarikoHWType() ? &mGPUParams : &eGPUParams;
    const unsigned int paramsCount = isMarikoHWType() ? mGPUParamsCount : eGPUParamsCount;
    for (unsigned int i = 0; i < paramsCount; ++i) printParamByParam(buff, pGPUParams[i], displayBuff);
    const ModeTable **modeTables = isMarikoHWType() ? &mGPUModeTables : &eGPUModeTables;
    const unsigned int modeTablesCount = isMarikoHWType() ? mGPUModeTablesCount : eGPUModeTablesCount;
    for (unsigned int i = 0; i < modeTablesCount; ++i) printModeTable(buff, modeTables[i], displayBuff);
}

void printRAMParams(const u8 *buff, char *displayBuff) {
    gfx_clearscreenKT();
    gfx_printf("--------RAM--------\n");
    for (unsigned int i = 0; i < cRAMFixedTablesCount; ++i) printTable(buff, cRAMTables[i], displayBuff);
    for (unsigned int i = 0; i < cRAMParamsCount; ++i) printParamByParam(buff, cRAMParams[i], displayBuff);
    const Param **pRAMParams = isMarikoHWType() ? &mRAMParams : &eRAMParams;
    const unsigned int paramsCount = isMarikoHWType() ? mRAMParamsCount : eRAMParamsCount;
    for (unsigned int i = 0; i < paramsCount; ++i) printParamByParam(buff, pRAMParams[i], displayBuff);
}

int kipInfo(char *path, FSEntry_t entry) {
    char *filePath = CombinePaths(path, entry.name);

    FIL kipFile;
    int res;
    Input_t *input = hidRead();

    gfx_clearscreenKT();

    if ((res = f_open(&kipFile, filePath, FA_READ | FA_OPEN_EXISTING))) {
        DrawError(newErrCode(res));
        return 1;
    }

    u8 cust[] = CUST;
    const unsigned int baseOffset = searchBytesArray(cust, 4, &kipFile);
    const unsigned int custSecionSize = sizeof(CustomizeTable);
    const u8 *custSection = calloc(custSecionSize, 1);
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
        const void (*pageFunctions[])(const u8 *, char *) = {printCPUParams, printGPUParams, printRAMParams};
        pageFunctions[currentPage](custSection, displayBuff);
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
                pageFunctions[currentPage](custSection, displayBuff);
            } else if (input->buttons & (JoyLLeft)) {
                --currentPage;
                if (currentPage < 0) currentPage = lastPage;
                pageFunctions[currentPage](custSection, displayBuff);
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