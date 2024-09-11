#pragma once

#define PATCH_FILES_COUNT 4

enum PAYLOADS_NAME {
    PAYLOAD = 0,
    FUSEE,
    ATM_REBOOT,
    UPDATE
};
extern const char* patchFilesPaths[PATCH_FILES_COUNT];
