#include "kiptool.h"

#include <libs/fatfs/ff.h>
#include <stdbool.h>

#include "../../fs/fsutils.h"
#include "../params/customize.h"

FRESULT createKTDirIfNotExist() {
    FRESULT res;
    if (!DirExists(KTDIR)) {
        res = f_mkdir(KTDIR);
        return res;
    }
    return FR_OK;
}

// TODO errors check
FRESULT overwriteCUST(FIL* kipFile, const unsigned int custOffset, const u8* custTable) {
    f_lseek(kipFile, custOffset);
    FRESULT res;
    unsigned int bytesWritten;

    res = f_write(kipFile, custTable, sizeof(CustomizeTable), &bytesWritten);
    return res;
}
