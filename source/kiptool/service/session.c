#include "session.h"

#include <string.h>

#include "idStorage.h"
#include "kiptool.h"

bool _isSessionsSupported = false;
bool isSessionsSupported() { return _isSessionsSupported; }
void setSessionSupported(bool value) { _isSessionsSupported = value; }

const char* getSessionPath(const KTSection* ktSection) {
    const char* numBuffer = malloc(16);
    utoa(ktSection->idSession, numBuffer, 10);
    char* buffer = calloc(strlen(KT_SESSIONS_DIR) + strlen(numBuffer), 1);
    strcat(buffer, KT_SESSIONS_DIR);
    strcat(buffer, "/");
    strcat(buffer, numBuffer);
    free(numBuffer);
    return buffer;
}

bool sessionIsExist(const KTSection* ktSection) {
    const char* sessionPath = getSessionPath(ktSection);
    bool fileExists = FileExists(sessionPath);
    free(sessionPath);
    return fileExists;
}
// TODO errors check
bool loadSession(const KTSection* ktSection, CustomizeTable* customizeTable) {
    const char* sessionPath = getSessionPath(ktSection);
    FIL file;
    FRESULT res;
    res = f_open(&file, sessionPath, FA_READ);
    free(sessionPath);
    if (res != FR_OK) {
        f_close(&file);
        return false;
    }
    unsigned int bytesRead;
    f_read(&file, customizeTable, sizeof(CustomizeTable), &bytesRead);
    f_close(&file);
    return bytesRead == sizeof(CustomizeTable);
}

bool saveSession(const KTSection* ktSection, const CustomizeTable* customizeTable) {
    const char* sessionPath = getSessionPath(ktSection);
    FRESULT res = writeData(sessionPath, -1, customizeTable, sizeof(CustomizeTable), FA_CREATE_ALWAYS);
    free(sessionPath);
    if (res != FR_OK) return false;
    return true;
}

bool removeSession(const KTSection* ktSection) {
    const char* sessionPath = getSessionPath(ktSection);
    FRESULT res = f_unlink(sessionPath);
    free(ktSection);
    if (res != FR_OK) return false;

    return true;
}

u32 getSessionId() {
    createDirIfNotExist(KT_SESSIONS_DIR);
    return getId(KT_SESSIONS_IDSTORAGE);
}
