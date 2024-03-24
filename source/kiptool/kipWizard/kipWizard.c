// #include "kipWizard.h"

// #include <mem/heap.h>
// #include <stdlib.h>
// #include <string.h>
// #include <utils/util.h>

// #include "../../err.h"
// #include "../../fs/fsutils.h"
// #include "../../gfx/gfx.h"
// #include "../../gfx/gfxutils.h"
// #include "../../gfx/menu.h"
// #include "../../hid/hid.h"
// #include "../gfx/dialogs/confirmationDialog.h"
// #include "../gfx/gfx.h"
// #include "../gfx/menus/ktMenu.h"
// #include "../gfx/menus/paramsMenu.h"
// #include "../helpers/hw.h"
// #include "../helpers/kiprw.h"
// #include "../helpers/param.h"
// #include "../params/common/cpu.h"
// #include "../params/common/general.h"
// #include "../params/common/gpu.h"
// #include "../params/common/ram.h"
// #include "../params/erista/cpu.h"
// #include "../params/erista/gpu.h"
// #include "../params/erista/ram.h"
// #include "../params/mariko/cpu.h"
// #include "../params/mariko/gpu.h"
// #include "../params/mariko/ram.h"
// #include "../service/kiptool.h"
// #include "../service/session.h"

// const Params* allCPUParams[] = {&cCPUParams, &mCPUParams, &eCPUParams};
// const Tables* allCPUTables[] = {&cCPUTables, &mCPUTables, &eCPUTables};
// void printCPUParams(const CustomizeTable* custTable, enum Platform platform) {
//     gfx_clearscreenKT();
//     const Params* allParams[] = {&cCPUParams, platform == MARIKO ? &mCPUParams : &eCPUParams};
//     const Tables* allTables[] = {&cCPUTables, platform == MARIKO ? &mCPUTables : &eCPUTables};
//     if (platform == COMMON)
//         newParamsMenu((const u8*)custTable, "CPU", allCPUParams, 3, allCPUTables, 3);
//     else
//         newParamsMenu((const u8*)custTable, "CPU", allParams, 2, allTables, 2);
// }

// const Params* allGPUParams[] = {&cGPUParams, &mGPUParams, &eGPUParams};
// const Tables* allGPUTables[] = {&cGPUTables, &mGPUTables, &eGPUTables};
// void printGPUParams(const CustomizeTable* custTable, enum Platform platform) {
//     gfx_clearscreenKT();
//     const Params* allParams[] = {&cGPUParams, platform == MARIKO ? &mGPUParams : &eGPUParams};
//     const Tables* allTables[] = {&cGPUTables, platform == MARIKO ? &mGPUTables : &eGPUTables};
//     if (platform == COMMON)
//         newParamsMenu((const u8*)custTable, "GPU", allGPUParams, 3, allGPUTables, 3);
//     else
//         newParamsMenu((const u8*)custTable, "GPU", allParams, 2, allTables, 2);
// }

// const Params* allRAMParams[] = {&cRAMParams, &mRAMParams, &eRAMParams};
// const Tables* allRAMTables[] = {&cRAMTables, &mRAMTables, &eRAMTables};
// void printRAMParams(const CustomizeTable* custTable, enum Platform platform) {
//     gfx_clearscreenKT();
//     const Params* allParams[] = {&cRAMParams, platform == MARIKO ? &mRAMParams : &eRAMParams};
//     const Tables* allTables[] = {&cRAMTables, platform == MARIKO ? &mRAMTables : &eRAMTables};
//     if (platform == COMMON)
//         newParamsMenu((const u8*)custTable, "RAM", allRAMParams, 3, allRAMTables, 3);
//     else
//         newParamsMenu((const u8*)custTable, "RAM", allParams, 2, allTables, 2);
// }

// void memcpy_kt(u8* dst, const u8* src, const unsigned int size) {
//     for (unsigned int i = 0; i < size; ++i) dst[i] = src[i];
// }

// int kipWizard(char* path, FSEntry_t entry) {
//     char* filePath = CombinePaths(path, entry.name);

//     FIL kipFile;
//     int res;
//     Input_t* input = hidRead();
//     if (input->l) {
//         if (input->r)
//             setHWType(MARIKO);
//         else if (input->zr)
//             setHWType(ERISTA);
//         else if (input->zl)
//             setHWType(COMMON);
//     }

//     gfx_clearscreenKT();
//     gfx_printf("Loading CUST table ...");

//     if ((res = f_open(&kipFile, filePath, FA_READ | FA_WRITE | FA_OPEN_EXISTING))) {
//         DrawError(newErrCode(res));
//         return 1;
//     }

//     u8 cust[] = CUST;
//     const int baseOffset = searchBytesArray(cust, 4, &kipFile);
//     if (baseOffset == -1) {
//         gfx_clearscreenKT();
//         gfx_printf("CUST section was not found! Press B to exit");
//         free(filePath);
//         while (!(hidRead()->buttons & JoyB))
//             ;
//         return -1;
//     }

//     unsigned int kipVersion = getParamValueFromFile(&kipFile, baseOffset, &cKipVersion);
//     unsigned int startIndex = 0;
//     if (kipVersion == KT_CUST_VER) {
//         const unsigned int custTableSize = sizeof(CustomizeTable);
//         CustomizeTable* custTable = malloc(custTableSize);

//         unsigned int bytesReaded;
//         bool goToExit = false;
//         bool loadedFromSession = false;
//         const char* messageLoadSession[] = {"Do you want to load a session file?", NULL};
//         if (!FileExists(KTSESSION)) {
//             f_lseek(&kipFile, baseOffset);
//             f_read(&kipFile, custTable, custTableSize, &bytesReaded);
//         } else if (confirmationDialog(messageLoadSession, EYES) == ENO) {
//             f_lseek(&kipFile, baseOffset);
//             f_read(&kipFile, custTable, custTableSize, &bytesReaded);
//         } else {
//             loadSession(custTable);
//             if (!checkVersionAndMagicFromBuffer(custTable)) {
//                 const char* message[] = {"Session file is corrupted or does not match the current version",
//                                          "Do you want to overwrite the session file by values from kip file?", NULL};
//                 if (confirmationDialog(message, EYES) == EYES) {
//                     f_lseek(&kipFile, baseOffset);
//                     f_read(&kipFile, custTable, custTableSize, &bytesReaded);
//                 } else
//                     goToExit = true;
//             } else {
//                 gfx_printBottomInfoKT("Session was loaded");
//                 loadedFromSession = true;
//             }
//         }

//         if (checkVersionAndMagicFromBuffer(custTable)) {
//             if (!loadedFromSession) saveSession(custTable);
//         } else
//             goToExit = true;

//         if (!goToExit) {
//             char* displayBuff = malloc(1024);
//             MenuEntry entries[] = {
//                 {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .type = ETLabel, .entry = "-- Kip Wizard --"},
//                 {.optionUnion = COLORTORGB(COLOR_GREEN), .type = ETLabel, .entry = "CPU Params"},
//                 {.optionUnion = COLORTORGB(COLOR_ORANGE), .type = ETLabel, .entry = "GPU Params"},
//                 {.optionUnion = COLORTORGB(COLOR_BLUE), .type = ETLabel, .entry = "RAM Params"},
//                 {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .type = ETLabel, .entry = ""},
//                 {.optionUnion = COLORTORGB(COLOR_WHITE), .type = ETLabel, .entry = "Apply changes"},
//                 {.optionUnion = COLORTORGB(COLOR_GREY), .type = ETLabel, .entry = "Reset all params to default values"}};
//             void (*functions[])(const CustomizeTable*, enum Platform) = {printCPUParams, printGPUParams, printRAMParams};
//             while (1) {
//                 gfx_clearscreenKT();
//                 int res = newMenuKT(entries, 7, startIndex, NULL, printEntry);
//                 startIndex = res + 1;
//                 if (res == -1)
//                     break;
//                 else if (res == 3) {
//                     const char* message[] = {"Do you want to apply changes?", "This will change your kip file", NULL};
//                     if (confirmationDialog(message, ENO) == EYES) {
//                         overwriteCUST(&kipFile, baseOffset, (const u8*)custTable);
//                         gfx_printBottomInfoKT("[KIP File] Changes have been applied");
//                     }
//                 } else if (res == 4) {
//                     ++startIndex;
//                     const char* message[] = {"Do you want to reset all params?", NULL};
//                     if (confirmationDialog(message, ENO) == EYES) {
//                         memcpy_kt((u8*)custTable, (const u8*)&defaultCustTable, sizeof(CustomizeTable));
//                         saveSession(custTable);
//                         gfx_printBottomInfoKT("[Session] All params have been reset");
//                     }
//                 } else if (res <= 2)
//                     functions[res](custTable, getHWType());
//             }
//             free(displayBuff);
//         }
//         free(filePath);
//         f_close(&kipFile);
//         free(custTable);
//         return 0;
//     }
//     free(filePath);
//     gfx_clearscreenKT();
//     gfx_printf("Kip version %d is unsupported. Supported version is %d", kipVersion, KT_CUST_VER);
//     while (1) {
//         input = hidRead();

//         if (!(input->buttons)) input = hidWait();
//         if (input->buttons & (BtnPow | JoyB)) break;
//     }
//     return 0;
// }
