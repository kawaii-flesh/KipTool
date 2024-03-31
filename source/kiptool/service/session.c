#include "session.h"

#include "kiptool.h"

// TODO errors check
bool loadSession(CustomizeTable* customizeTable) {
    FIL file;
    FRESULT res;
    res = f_open(&file, KTSESSION, FA_READ);
    if (res != FR_OK) {
        f_close(&file);
        return false;
    }
    unsigned int bytesRead;
    f_read(&file, customizeTable, sizeof(CustomizeTable), &bytesRead);
    f_close(&file);
    return bytesRead == sizeof(CustomizeTable);
}

bool saveSession(const CustomizeTable* customizeTable) {
    FIL file;
    FRESULT res;
    unsigned int bytesWritten;

    res = f_open(&file, KTSESSION, FA_WRITE | FA_CREATE_ALWAYS);
    if (res != FR_OK) {
        return false;
    }

    res = f_write(&file, customizeTable, sizeof(CustomizeTable), &bytesWritten);
    if (res != FR_OK || bytesWritten != sizeof(CustomizeTable)) {
        f_close(&file);
        return false;
    }
    f_close(&file);

    return true;
}

bool removeSession() {
    FIL file;

    FRESULT res = f_unlink(KTSESSION);
    if (res != FR_OK) return false;

    return true;
}
