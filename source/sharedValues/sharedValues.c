#include "sharedValues.h"

const char* patchFilesPaths[PATCH_FILES_COUNT] = {[PAYLOAD] = "sd:/payload.bin", [FUSEE]"sd:/bootloader/payloads/fusee.bin", [ATM_REBOOT]"sd:/atmosphere/reboot_payload.bin",
                                                  [UPDATE] = "sd:/bootloader/update.bin"};
