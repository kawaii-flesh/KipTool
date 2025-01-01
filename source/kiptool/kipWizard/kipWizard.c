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
#include "../gfx/menus/tableMenu.h"
#include "../helpers/hw.h"
#include "../helpers/kiprw.h"
#include "../helpers/param.h"
#include "../params/common/cpu.h"
#include "../params/common/general.h"
#include "../params/common/gpu.h"
#include "../params/common/meh.h"
#include "../params/common/ram.h"
#include "../params/erista/cpu.h"
#include "../params/erista/gpu.h"
#include "../params/erista/ram.h"
#include "../params/mariko/cpu.h"
#include "../params/mariko/gpu.h"
#include "../params/mariko/ram.h"
#include "../service/kiptool.h"
#include "dashboard.h"

const Params* allCPUParams[] = {&cCPUParams, &mCPUParams, &eCPUParams};
const Tables* allCPUTables[] = {&cCPUTables, &mCPUTables, &eCPUTables};

const Params* allGPUParams[] = {&cGPUParams, &mGPUParams, &eGPUParams};
const Tables* allGPUTables[] = {&cGPUTables, &mGPUTables, &eGPUTables};

const Params* allRAMParams[] = {&cRAMParams, &mRAMParams, &eRAMParams};
const Tables* allRAMTables[] = {&cRAMTables, &mRAMTables, &eRAMTables};

void printParams(const CustomizeTable* custTable, char title[], const Params* params[], const Tables* tables[]) {
    gfx_clearscreenKT();
    newParamsMenu((const u8*)custTable, title, params, tables);
}

void printTable(const CustomizeTable* custTable, const Table* table) {
    gfx_clearscreenKT();
    newTableMenu((const u8*)custTable, table);
}

enum MenuElements { TITLE = 0, CPU, GPU, RAM, PMEH, SMEH, NEW_LINE, APPLY_CHANGES, DASHBOARD, RESET_ALL };

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
        while (!(hidRead()->buttons & JoyB));
        return -1;
    }

    unsigned int kipVersion = getParamValueFromFile(&kipFile, baseOffset, &cKipVersion);
    unsigned int startIndex = 0;
    if (kipVersion == KT_CUST_VER) {
        const enum Platform platform = getHWType();
        const Params* CPUParams[] = {&cCPUParams, platform == MARIKO ? &mCPUParams : &eCPUParams, NULL};
        const Tables* CPUTables[] = {&cCPUTables, platform == MARIKO ? &mCPUTables : &eCPUTables, NULL};
        const Params* GPUParams[] = {&cGPUParams, platform == MARIKO ? &mGPUParams : &eGPUParams, NULL};
        const Tables* GPUTables[] = {&cGPUTables, platform == MARIKO ? &mGPUTables : &eGPUTables, NULL};
        const Params* RAMParams[] = {&cRAMParams, platform == MARIKO ? &mRAMParams : &eRAMParams, NULL};
        const Tables* RAMTables[] = {&cRAMTables, platform == MARIKO ? &mRAMTables : &eRAMTables, NULL};
        const Tables* MEHTables[] = {&cMEHTables, NULL};

        const unsigned int custTableSize = sizeof(CustomizeTable);
        CustomizeTable* custTable = malloc(custTableSize);
        f_lseek(&kipFile, baseOffset);
        int bytesReaded;
        f_read(&kipFile, custTable, custTableSize, &bytesReaded);
        if (checkVersionAndMagicFromBuffer(custTable)) {
            char* displayBuff = malloc(1024);
            MenuEntry entries[] = {[TITLE] = {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .type = ETLabel, .entry = "-- Kip Wizard --"},
                                   [CPU] = {.optionUnion = COLORTORGB(COLOR_GREEN), .type = ETLabel, .entry = "CPU Params"},
                                   [GPU] = {.optionUnion = COLORTORGB(COLOR_ORANGE), .type = ETLabel, .entry = "GPU Params"},
                                   [RAM] = {.optionUnion = COLORTORGB(COLOR_BLUE), .type = ETLabel, .entry = "RAM Params"},
                                   [PMEH] = {.optionUnion = COLORTORGB(COLOR_YELLOW), .type = ETLabel, .entry = "pMeh Table"},
                                   [SMEH] = {.optionUnion = COLORTORGB(COLOR_YELLOW), .type = ETLabel, .entry = "sMeh Table"},
                                   [NEW_LINE] = {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .type = ETLabel, .entry = ""},
                                   [APPLY_CHANGES] = {.optionUnion = COLORTORGB(COLOR_WHITE), .type = ETLabel, .entry = "Apply changes"},
                                   [DASHBOARD] = {.optionUnion = COLORTORGB(COLOR_YELLOW), .type = ETLabel, .entry = "Dashboard"},
                                   [RESET_ALL] = {.optionUnion = COLORTORGB(COLOR_WHITE), .type = ETLabel, .entry = "Reset all params to default values"}};
            while (1) {
                gfx_clearscreenKT();
                entries[APPLY_CHANGES].optionUnion = isChangesApplied() ? (COLORTORGB(COLOR_GREY) | SKIPBIT) : COLORTORGB(COLOR_WHITE);
                MenuResult menuResult = newMenuKT(entries, 10, startIndex, JoyA, NULL, printEntry);
                startIndex = menuResult.index;
                if (menuResult.buttons & JoyB) {
                    if (isChangesApplied()) break;
                    const char* message[] = {"You have not applied the last changes you made", "After exiting, all changes that",
                                             "have not been applied will be lost", "Are you sure you want to exit?", NULL};
                    if (confirmationDialog(message, ENO) == EYES) {
                        setIsChangesApplied(1);
                        break;
                    }
                    continue;
                }
                if (menuResult.index == APPLY_CHANGES) {
                    const char* message[] = {"Do you want to apply changes?", "This will change your kip file", NULL};
                    if (confirmationDialog(message, ENO) == EYES) {
                        writeData(filePath, baseOffset, custTable, sizeof(CustomizeTable), 0);
                        gfx_printBottomInfoKT("[KIP File] Changes have been applied");
                        setIsChangesApplied(1);
                    }
                } else if (menuResult.index == DASHBOARD) {
                    gfx_clearscreenKT();
                    showDashboard(custTable, CPUParams, CPUTables, GPUParams, GPUTables, RAMParams, RAMTables, MEHTables);
                } else if (menuResult.index == RESET_ALL) {
                    const char* message[] = {"Do you want to reset all params?", NULL};
                    if (confirmationDialog(message, ENO) == EYES) {
                        memcpy((u8*)custTable, (const u8*)&defaultCustTable, sizeof(CustomizeTable));
                        gfx_printBottomInfoKT("[Session] All params have been reset");
                        setIsChangesApplied(0);
                    }
                } else if (menuResult.index <= RAM) {
                    char* title;
                    const Params** params;
                    const Tables** tables;
                    switch (menuResult.index) {
                        case CPU:
                            title = "CPU";
                            if (platform == COMMON) {
                                params = allCPUParams;
                                tables = allCPUTables;
                            } else {
                                params = CPUParams;
                                tables = CPUTables;
                            }
                            break;
                        case GPU:
                            title = "GPU";
                            if (platform == COMMON) {
                                params = allGPUParams;
                                tables = allGPUTables;
                            } else {
                                params = GPUParams;
                                tables = GPUTables;
                            }
                            break;
                        case RAM:
                            title = "RAM";
                            if (platform == COMMON) {
                                params = allRAMParams;
                                tables = allRAMTables;
                            } else {
                                params = RAMParams;
                                tables = RAMTables;
                            }
                            break;
                    }
                    printParams(custTable, title, params, tables);
                } else if (menuResult.index > RAM && menuResult.index <= SMEH) {
                    const Table* table;
                    switch (menuResult.index) {
                        case PMEH:
                            table = &pMehTable;
                            break;
                        case SMEH:
                            table = &sMehTable;
                            break;
                    }
                    printTable(custTable, table);
                }
            }
            free(displayBuff);
        }
        f_close(&kipFile);
        free(filePath);
        free(custTable);
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
    return 0;
}
