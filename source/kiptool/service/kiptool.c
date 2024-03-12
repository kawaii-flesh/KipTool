#include "kiptool.h"

#include <libs/fatfs/ff.h>
#include <stdbool.h>

#include "../params/customize.h"

bool isDirExist(const char* path) {
    FILINFO finfo;
    FRESULT res;
    res = f_stat(path, &finfo);
    return res == FR_OK && (finfo.fattrib & AM_DIR);
}

void createKTDirIfNotExist() {
    FRESULT res;
    if (!isDirExist(KTDIR)) res = f_mkdir(KTDIR);
}

// TODO errors check
void overwriteCUST(FIL* kipFile, const unsigned int custOffset, const u8* custTable) {
    f_lseek(kipFile, custOffset);
    FRESULT res;
    unsigned int bytesWritten;

    res = f_write(kipFile, custTable, sizeof(CustomizeTable), &bytesWritten);
}