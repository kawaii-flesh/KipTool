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
#include "../helpers/hw.h"
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
        const unsigned int paramValue = getParamValueFromBuffer(buff, param);
        getDisplayValue(param, displayBuff, paramValue);
        gfx_printf("%s: %s\n", param->name, displayBuff);
    }
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

void printCPUParams(const u8 *buff, enum Platform platform) {
    gfx_clearscreenKT();
    const Params *allParams[] = {&cCPUParams, platform == MARIKO ? &mCPUParams : &eCPUParams};
    const Tables *allTables[] = {&cCPUTables, platform == MARIKO ? &mCPUTables : &eCPUTables};
    newParamsMenu(buff, "--------CPU--------", allParams, 2, allTables, 2);
}

void printGPUParams(const u8 *buff, enum Platform platform) {
    gfx_clearscreenKT();
    const Params *allParams[] = {&cGPUParams, platform == MARIKO ? &mGPUParams : &eGPUParams};
    const Tables *allTables[] = {&cGPUTables, platform == MARIKO ? &mGPUTables : &eGPUTables};
    newParamsMenu(buff, "--------GPU--------", allParams, 2, allTables, 2);
}

void printRAMParams(const u8 *buff, enum Platform platform) {
    gfx_clearscreenKT();
    const Params *allParams[] = {&cRAMParams, platform == MARIKO ? &mRAMParams : &eRAMParams};
    const Tables *allTables[] = {&cRAMTables, platform == MARIKO ? &mRAMTables : &eRAMTables};
    newParamsMenu(buff, "--------RAM--------", allParams, 2, allTables, 2);
}

int kipWizard(char *path, FSEntry_t entry) {
    char *filePath = CombinePaths(path, entry.name);

    FIL kipFile;
    int res;
    Input_t *input = hidRead();
    if (input->l) {
        if (input->r)
            setHWType(MARIKO);
        else if (input->zr)
            setHWType(ERISTA);
        else if (input->zl)
            setHWType(COMMON);
    }

    gfx_clearscreenKT();
    gfx_printf("Loading CUST table ...");
    confirmationDialog("Hello, User?", ENO);

    if ((res = f_open(&kipFile, filePath, FA_READ | FA_OPEN_EXISTING))) {
        DrawError(newErrCode(res));
        return 1;
    }

    u8 cust[] = CUST;
    const int baseOffset = searchBytesArray(cust, 4, &kipFile);
    if (baseOffset == -1) {
        gfx_printf("CUST section was not found! Press B to exit");
        while (!(hidRead()->buttons & JoyB))
            ;
        return -1;
    }
    const unsigned int custTableSize = sizeof(CustomizeTable);
    u8 *custTable = calloc(custTableSize, 1);
    unsigned int bytesReaded;
    f_lseek(&kipFile, baseOffset);
    f_read(&kipFile, custTable, custTableSize, &bytesReaded);
    unsigned int kipVersion = getParamValueFromBuffer(custTable, &gKipVersion);
    unsigned int startIndex = 0;
    if (kipVersion == CURRENT_VERSION) {
        gfx_clearscreenKT();
        char *displayBuff = calloc(1024, 1);
        ParamsMenuEntry entries[] = {
            {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .type = ELabel, .entry = "-- Kip Wizard --"},
            {.optionUnion = COLORTORGB(COLOR_GREEN), .type = ELabel, .entry = "CPU Params"},
            {.optionUnion = COLORTORGB(COLOR_ORANGE), .type = ELabel, .entry = "GPU Params"},
            {.optionUnion = COLORTORGB(COLOR_BLUE), .type = ELabel, .entry = "RAM Params"}};
        void (*functions[])(const u8 *, enum Platform) = {printCPUParams, printGPUParams, printRAMParams};
        while (1) {
            int res = newMenuKT(entries, custTable, 4, startIndex);
            startIndex = res + 1;
            if (res == -1)
                break;
            else if (res <= 2)
                functions[res](custTable, getHWType());
        }

        f_close(&kipFile);
        free(filePath);
        free(displayBuff);
        free(custTable);
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