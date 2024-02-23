#include "kipInfo.h"

#include <mem/heap.h>
#include <stdlib.h>
#include <string.h>

#include "../../err.h"
#include "../../hid/hid.h"
#include "../helpers.h"
#include "../kip.h"
#include "../params/general.h"
#include "../params/mariko/cpu.h"
#include "../params/mariko/ram.h"

void printParamFromFile(FIL *file, unsigned int baseOffset, const Param *param, char *displayBuff) {
    unsigned int paramValue = getParamValueFromFile(file, baseOffset, param);
    getDisplayValue(param, displayBuff, paramValue);
    gfx_printf("%s: %s\n", param->name, displayBuff, param->measure);
}

void printParamByValue(unsigned int value, const Param *param, char *displayBuff) {
    getDisplayValue(param, displayBuff, value);
    gfx_printf("%s: %s\n", param->name, displayBuff);
}

int kipInfo(char *path, FSEntry_t entry) {
    char *filePath = CombinePaths(path, entry.name);

    FIL kipFile;
    int res;
    Input_t *input = hidRead();

    while (input->buttons & (BtnPow | JoyB)) hidRead();

    gfx_clearscreen();

    if ((res = f_open(&kipFile, filePath, FA_READ | FA_OPEN_EXISTING))) {
        DrawError(newErrCode(res));
        return 1;
    }

    u8 cust[] = CUST;
    unsigned int baseOffset = searchBytesArray(cust, 4, &kipFile);
    unsigned int kipVersion = getParamValueFromFile(&kipFile, baseOffset, &gKipVersion);
    if (kipVersion == CURRENT_VERSION) {
        char *displayBuff = calloc(1024, 1);

        printParamByValue(kipVersion, &gKipVersion, displayBuff);
        gfx_printf("--------CPU--------\n");
        for (unsigned int i = 0; i < mCPUParamsCount; ++i)
            printParamFromFile(&kipFile, baseOffset, mCPUParams[i], displayBuff);
        gfx_printf("--------RAM--------\n");
        for (unsigned int i = 0; i < mRAMParamsCount; ++i)
            printParamFromFile(&kipFile, baseOffset, mRAMParams[i], displayBuff);
        // gfx_printf("--------GPU--------\n");
        // for (unsigned int i = 0; i < mGPUParamsCount; ++i)
        //     printParamFromFile(&kipFile, baseOffset, mGPUParams[i], displayBuff);

        while (1) {
            input = hidRead();

            if (!(input->buttons)) input = hidWait();
            if (input->buttons & (BtnPow | JoyB)) break;
        }

        f_close(&kipFile);
        free(filePath);
        free(displayBuff);
        return 0;
    }
    gfx_printf("Kip version %d is unsupported. Supported version is %d", kipVersion,
               CURRENT_VERSION);
    while (1) {
        input = hidRead();

        if (!(input->buttons)) input = hidWait();
        if (input->buttons & (BtnPow | JoyB)) break;
    }
    return 0;
}