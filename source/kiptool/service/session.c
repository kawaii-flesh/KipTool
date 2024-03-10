#include "session.h"

#include "kiptool.h"

// TODO errors check
bool loadSession(Session* session) {
    FIL file;
    FRESULT res;
    res = f_open(&file, KTSESSION, FA_READ);
    if (res != FR_OK) {
        f_close(&file);
        return false;
    }
    unsigned int bytesRead;
    f_read(&file, session, sizeof(Session), &bytesRead);
    f_close(&file);
    return bytesRead == sizeof(Session);
}

bool saveSession(const u8* customizeTable) {
    FIL file;
    FRESULT res;
    unsigned int bytesWritten;

    res = f_open(&file, KTSESSION, FA_WRITE | FA_CREATE_ALWAYS);
    if (res != FR_OK) {
        return false;
    }

    const Session session = {.magic = KTMAGIC, .kipVersion = CURRENT_VERSION};
    const unsigned int sessionHeaderSize = ((void*)&session.customizeTable - (void*)&session.magic);
    res = f_write(&file, &session, sessionHeaderSize, &bytesWritten);
    if (res != FR_OK || bytesWritten != sessionHeaderSize) {
        f_close(&file);
        return false;
    }
    f_lseek(&file, sessionHeaderSize);
    res = f_write(&file, customizeTable, sizeof(CustomizeTable), &bytesWritten);
    if (res != FR_OK || bytesWritten != sizeof(CustomizeTable)) {
        f_close(&file);
        return false;
    }
    f_close(&file);

    return true;
}

bool isSessionExist() {
    FILINFO finfo;
    FRESULT res;
    res = f_stat(KTSESSION, &finfo);
    return res == FR_OK && !(finfo.fattrib & AM_DIR);
}