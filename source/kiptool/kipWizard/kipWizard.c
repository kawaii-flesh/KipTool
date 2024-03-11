#include "kipWizard.h"

#include <mem/heap.h>
#include <stdlib.h>
#include <string.h>
#include <utils/util.h>

#include "../../err.h"
#include "../../fs/fsutils.h"
#include "../../gfx/gfx.h"
#include "../../gfx/gfxutils.h"
#include "../../gfx/menu.h"
#include "../../hid/hid.h"
#include "../gfx/dialogs/confirmationDialog.h"
#include "../gfx/gfx.h"
#include "../gfx/menus/ktMenu.h"
#include "../gfx/menus/paramsMenu.h"
#include "../helpers/hw.h"
#include "../helpers/kiprw.h"
#include "../helpers/param.h"
#include "../params/common/cpu.h"
#include "../params/common/general.h"
#include "../params/common/gpu.h"
#include "../params/common/ram.h"
#include "../params/erista/cpu.h"
#include "../params/erista/gpu.h"
#include "../params/erista/ram.h"
#include "../params/mariko/cpu.h"
#include "../params/mariko/gpu.h"
#include "../params/mariko/ram.h"
#include "../service/kiptool.h"
#include "../service/session.h"

const Params* allCPUParams[] = {&cCPUParams, &mCPUParams, &eCPUParams};
const Tables* allCPUTables[] = {&cCPUTables, &mCPUTables, &eCPUTables};
void printCPUParams(const u8* custTable, enum Platform platform) {
    gfx_clearscreenKT();
    const Params* allParams[] = {&cCPUParams, platform == MARIKO ? &mCPUParams : &eCPUParams};
    const Tables* allTables[] = {&cCPUTables, platform == MARIKO ? &mCPUTables : &eCPUTables};
    if (platform == COMMON)
        newParamsMenu(custTable, "--------CPU--------", allCPUParams, 3, allCPUTables, 3);
    else
        newParamsMenu(custTable, "--------CPU--------", allParams, 2, allTables, 2);
}

const Params* allGPUParams[] = {&cGPUParams, &mGPUParams, &eGPUParams};
const Tables* allGPUTables[] = {&cGPUTables, &mGPUTables, &eGPUTables};
void printGPUParams(const u8* custTable, enum Platform platform) {
    gfx_clearscreenKT();
    const Params* allParams[] = {&cGPUParams, platform == MARIKO ? &mGPUParams : &eGPUParams};
    const Tables* allTables[] = {&cGPUTables, platform == MARIKO ? &mGPUTables : &eGPUTables};
    if (platform == COMMON)
        newParamsMenu(custTable, "--------GPU--------", allGPUParams, 3, allGPUTables, 3);
    else
        newParamsMenu(custTable, "--------GPU--------", allParams, 2, allTables, 2);
}

const Params* allRAMParams[] = {&cRAMParams, &mRAMParams, &eRAMParams};
const Tables* allRAMTables[] = {&cRAMTables, &mRAMTables, &eRAMTables};
void printRAMParams(const u8* custTable, enum Platform platform) {
    gfx_clearscreenKT();
    const Params* allParams[] = {&cRAMParams, platform == MARIKO ? &mRAMParams : &eRAMParams};
    const Tables* allTables[] = {&cRAMTables, platform == MARIKO ? &mRAMTables : &eRAMTables};
    if (platform == COMMON)
        newParamsMenu(custTable, "--------RAM--------", allRAMParams, 3, allRAMTables, 32);
    else
        newParamsMenu(custTable, "--------RAM--------", allParams, 2, allTables, 2);
}

void memcpy_kt(u8* dst, u8* src, const unsigned int size) {
    for(unsigned int i = 0; i < size; ++i)
        dst[i] = src[i];
}

int kipWizard(char* path, FSEntry_t entry) {
    char* filePath = CombinePaths(path, entry.name);

    FIL kipFile;
    int res;
    Input_t* input = hidRead();
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

    if ((res = f_open(&kipFile, filePath, FA_READ | FA_WRITE | FA_OPEN_EXISTING))) {
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
    CustomizeTable* custTable = calloc(custTableSize, 1);
    unsigned int bytesReaded;
    f_lseek(&kipFile, baseOffset);
    f_read(&kipFile, custTable, custTableSize, &bytesReaded);
    unsigned int kipVersion = getParamValueFromBuffer(custTable, &gKipVersion);
    unsigned int startIndex = 0;
    if (kipVersion == CURRENT_VERSION) {
        if (!isSessionExist())
            saveSession(custTable);
        else if (confirmationDialog("Load a session file?", EYES) == ENO)
            saveSession(custTable);
        else {
            Session session;
            loadSession(&session);
            memcpy_kt(custTable, &session.customizeTable, sizeof(CustomizeTable));
        }

        char* displayBuff = malloc(1024);
        MenuEntry entries[] = {
            {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .type = ELabel, .entry = "-- Kip Wizard --"},
            {.optionUnion = COLORTORGB(COLOR_GREEN), .type = ELabel, .entry = "CPU Params"},
            {.optionUnion = COLORTORGB(COLOR_ORANGE), .type = ELabel, .entry = "GPU Params"},
            {.optionUnion = COLORTORGB(COLOR_BLUE), .type = ELabel, .entry = "RAM Params"},
            {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .type = ELabel, .entry = ""},
            {.optionUnion = COLORTORGB(COLOR_WHITE), .type = ELabel, .entry = "Apply changes"},
            {.optionUnion = COLORTORGB(COLOR_GREY), .type = ELabel, .entry = "Reset all parameters to default values"}};
        void (*functions[])(const u8*, enum Platform) = {printCPUParams, printGPUParams, printRAMParams};
        while (1) {
            gfx_clearscreenKT();
            int res = newMenuKT(entries, 7, startIndex, NULL, printEntry);
            startIndex = res + 1;
            if (res == -1)
                break;
            else if (res == 3) {
                if (confirmationDialog("Apply changes?", EYES) == EYES) {
                    overwriteCUST(&kipFile, baseOffset, custTable);
                }
            } else if (res == 4) {
                if (confirmationDialog("Reset all parameters?", ENO) == EYES) {
                    memcpy_kt(custTable, &defaultCustTable, sizeof(CustomizeTable));
                    saveSession(custTable);
                }
            } else if (res <= 2)
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