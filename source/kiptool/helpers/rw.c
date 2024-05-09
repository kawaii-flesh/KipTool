#include "rw.h"

FRESULT writeData(const char *path, const int offset, const void *data, u32 dataSize, BYTE flags) {
    FIL fil;
    UINT bw;
    FRESULT res;

    res = f_open(&fil, path, FA_WRITE | FA_OPEN_ALWAYS | flags);
    if (res != FR_OK) return res;

    if (offset != -1) f_lseek(&fil, offset);
    res = f_write(&fil, data, dataSize, &bw);
    if (res != FR_OK) {
        f_close(&fil);
        return res;
    }

    if (bw != dataSize) {
        f_close(&fil);
        return FR_INT_ERR;
    }

    f_close(&fil);

    return FR_OK;
}

FRESULT readData(const char *path, void *buffer, u32 bufferSize) {
    FIL fil;
    UINT br;
    FRESULT res;

    res = f_open(&fil, path, FA_READ);
    if (res != FR_OK) return res;

    res = f_read(&fil, buffer, bufferSize, &br);
    if (res != FR_OK) {
        f_close(&fil);
        return res;
    }

    if (br != bufferSize) {
        f_close(&fil);
        return FR_INT_ERR;
    }

    f_close(&fil);

    return FR_OK;
}

FRESULT createDirIfNotExist(const char path[]) {
    FRESULT res;
    if (!DirExists(path)) {
        res = f_mkdir(path);
        return res;
    }
    return FR_OK;
}