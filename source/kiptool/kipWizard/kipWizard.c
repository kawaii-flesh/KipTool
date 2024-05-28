#include "kipWizard.h"

#include <mem/heap.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <utils/util.h>

#include "../../err.h"
#include "../../fs/fsutils.h"
#include "../../gfx/gfx.h"
#include "../../gfx/gfxutils.h"
#include "../../gfx/menu.h"
#include "../../helpers/fs.h"
#include "../../hid/hid.h"
#include "../../kiptool/helpers/rw.h"
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
void printCPUParams(const CustomizeTable* custTable, const KTSection* ktSection, enum Platform platform) {
    gfx_clearscreenKT();
    const Params* allParams[] = {&cCPUParams, platform == MARIKO ? &mCPUParams : &eCPUParams};
    const Tables* allTables[] = {&cCPUTables, platform == MARIKO ? &mCPUTables : &eCPUTables};
    if (platform == COMMON)
        newParamsMenu((const u8*)custTable, (const u8*)ktSection, "CPU", allCPUParams, 3, allCPUTables, 3);
    else
        newParamsMenu((const u8*)custTable, (const u8*)ktSection, "CPU", allParams, 2, allTables, 2);
}

const Params* allGPUParams[] = {&cGPUParams, &mGPUParams, &eGPUParams};
const Tables* allGPUTables[] = {&cGPUTables, &mGPUTables, &eGPUTables};
void printGPUParams(const CustomizeTable* custTable, const KTSection* ktSection, enum Platform platform) {
    gfx_clearscreenKT();
    const Params* allParams[] = {&cGPUParams, platform == MARIKO ? &mGPUParams : &eGPUParams};
    const Tables* allTables[] = {&cGPUTables, platform == MARIKO ? &mGPUTables : &eGPUTables};
    if (platform == COMMON)
        newParamsMenu((const u8*)custTable, (const u8*)ktSection, "GPU", allGPUParams, 3, allGPUTables, 3);
    else
        newParamsMenu((const u8*)custTable, (const u8*)ktSection, "GPU", allParams, 2, allTables, 2);
}

const Params* allRAMParams[] = {&cRAMParams, &mRAMParams, &eRAMParams};
const Tables* allRAMTables[] = {&cRAMTables, &mRAMTables, &eRAMTables};
void printRAMParams(const CustomizeTable* custTable, const KTSection* ktSection, enum Platform platform) {
    gfx_clearscreenKT();
    const Params* allParams[] = {&cRAMParams, platform == MARIKO ? &mRAMParams : &eRAMParams};
    const Tables* allTables[] = {&cRAMTables, platform == MARIKO ? &mRAMTables : &eRAMTables};
    if (platform == COMMON)
        newParamsMenu((const u8*)custTable, (const u8*)ktSection, "RAM", allRAMParams, 3, allRAMTables, 3);
    else
        newParamsMenu((const u8*)custTable, (const u8*)ktSection, "RAM", allParams, 2, allTables, 2);
}

int kipWizard(char* path, FSEntry_t entry) {
    createDirIfNotExist(KT_DIR);
    char* filePath = CombinePaths(path, entry.name);

    FIL kipFile;
    int resFile;
    Input_t* input = hidRead();
#ifdef KT_DEBUG
    if (input->l) {
        if (input->r)
            setHWType(MARIKO);
        else if (input->zr)
            setHWType(ERISTA);
        else if (input->zl)
            setHWType(COMMON);
    }
#endif

    gfx_clearscreenKT();
    gfx_printf("Loading CUST table ...");

    if ((resFile = f_open(&kipFile, filePath, FA_READ | FA_OPEN_EXISTING))) {
        DrawError(newErrCode(resFile));
        free(filePath);
        return 1;
    }

    const u8 cust[] = CUST;
    const int baseOffset = searchBytesArray(cust, 4, &kipFile);
    if (baseOffset == -1) {
        gfx_clearscreenKT();
        gfx_printf("CUST section was not found! Press B to exit");
        free(filePath);
        while (!(hidRead()->buttons & JoyB))
            ;
        return -1;
    }

    unsigned int kipVersion = getParamValueFromFile(&kipFile, baseOffset, &cKipVersion);
    unsigned int startIndex = 0;
    if (kipVersion == KT_CUST_VER) {
        const unsigned int custTableSize = sizeof(CustomizeTable);
        CustomizeTable* custTable = malloc(custTableSize);
        KTSection* ktSection = malloc(sizeof(KTSection));

        unsigned int bytesReaded;
        bool goToExit = false;
        bool loadedFromSession = false;
        const u8 ktMagic[] = KT_MAGIC;
        int ktSectionOffset = searchBytesArray(ktMagic, 8, &kipFile);
        if (ktSectionOffset == -1) {
            setSessionSupported(false);
            const char* ktSectionCreatingMessage[] = {"Do you want to enable the mechanism of sessions?",
                                                      "This will add a service section at the end of your kip file", NULL};
            if (confirmationDialog(ktSectionCreatingMessage, EYES) == EYES) {
                if (addKTSection(filePath, ktSection) == FR_OK) setSessionSupported(true);
            }
            f_lseek(&kipFile, baseOffset);
            f_read(&kipFile, custTable, custTableSize, &bytesReaded);
        } else {
            f_lseek(&kipFile, ktSectionOffset);
            f_read(&kipFile, ktSection, sizeof(KTSection), &bytesReaded);
            setSessionSupported(true);
            const char* messageLoadSession[] = {"Do you want to load a session file?", NULL};
            if (!sessionIsExist(ktSection)) {
                f_lseek(&kipFile, baseOffset);
                f_read(&kipFile, custTable, custTableSize, &bytesReaded);
            } else if (confirmationDialog(messageLoadSession, EYES) != EYES) {
                f_lseek(&kipFile, baseOffset);
                f_read(&kipFile, custTable, custTableSize, &bytesReaded);
            } else {
                loadSession(ktSection, custTable);
                if (!checkVersionAndMagicFromBuffer(custTable)) {
                    const char* message[] = {"Session file is corrupted or does not match the current version",
                                             "Do you want to overwrite the session file by values from kip file?", NULL};
                    if (confirmationDialog(message, EYES) == EYES) {
                        f_lseek(&kipFile, baseOffset);
                        f_read(&kipFile, custTable, custTableSize, &bytesReaded);
                    } else
                        goToExit = true;
                } else {
                    gfx_printBottomInfoKT("Session was loaded");
                    loadedFromSession = true;
                }
            }
        }

        if (checkVersionAndMagicFromBuffer(custTable)) {
            if (!loadedFromSession && isSessionsSupported()) saveSession(ktSection, custTable);
        } else
            goToExit = true;

        if (!goToExit) {
            char* displayBuff = malloc(1024);
            MenuEntry entries[] = {{.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .type = ETLabel, .entry = "-- Kip Wizard --"},
                                   {.optionUnion = COLORTORGB(COLOR_GREEN), .type = ETLabel, .entry = "CPU Params"},
                                   {.optionUnion = COLORTORGB(COLOR_ORANGE), .type = ETLabel, .entry = "GPU Params"},
                                   {.optionUnion = COLORTORGB(COLOR_BLUE), .type = ETLabel, .entry = "RAM Params"},
                                   {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .type = ETLabel, .entry = ""},
                                   {.optionUnion = COLORTORGB(COLOR_WHITE), .type = ETLabel, .entry = "Apply changes"},
                                   {.optionUnion = COLORTORGB(COLOR_GREY), .type = ETLabel, .entry = "Reset all params to default values"}};
            void (*functions[])(const CustomizeTable*, const KTSection*, enum Platform) = {printCPUParams, printGPUParams, printRAMParams};
            while (1) {
                gfx_clearscreenKT();
                MenuResult result = newMenuKT(entries, 7, startIndex, JoyA, NULL, printEntry);
                startIndex = result.selectableIndex + 1;
                if (result.buttons & JoyB) {
                    if (isSessionsSupported()) {
                        break;
                    } else {
                        const char* message[] = {"The session mechanism is not activated", "Changes that have not been applied will be lost",
                                                 "Are you sure you want to exit?", NULL};
                        if (confirmationDialog(message, ENO) == EYES) {
                            break;
                        }
                    }
                    continue;
                    ;
                }
                if (result.selectableIndex == 3) {
                    const char* message[] = {"Do you want to apply changes?", "This will change your kip file", NULL};
                    if (confirmationDialog(message, ENO) == EYES) {
                        writeData(filePath, baseOffset, custTable, sizeof(CustomizeTable), 0);
                        removeSession(ktSection);
                        gfx_printBottomInfoKT("[KIP File] Changes have been applied");
                    }
                } else if (result.selectableIndex == 4) {
                    ++startIndex;
                    const char* message[] = {"Do you want to reset all params?", NULL};
                    if (confirmationDialog(message, ENO) == EYES) {
                        memcpy((u8*)custTable, (const u8*)&defaultCustTable, sizeof(CustomizeTable));
                        saveSession(ktSection, custTable);
                        gfx_printBottomInfoKT("[Session] All params have been reset");
                    }
                } else if (result.selectableIndex <= 2)
                    functions[result.selectableIndex](custTable, ktSection, getHWType());
            }
            free(displayBuff);
        }
        f_close(&kipFile);
        free(filePath);
        free(custTable);
        free(ktSection);
        return 0;
    }
    free(filePath);
    gfx_clearscreenKT();
    gfx_printf("Kip version %d is unsupported. Supported version is %d", kipVersion, KT_CUST_VER);
    while (1) {
        input = hidRead();

        if (!(input->buttons)) input = hidWait();
        if (input->buttons & (BtnPow | JoyB)) break;
    }
    free(filePath);
    return 0;
}
