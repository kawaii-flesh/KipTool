#include "kiprw.h"

#include <mem/heap.h>

#include "../params/param.h"
#include "../service/session.h"

int compareU8Arrays(const u8* a, const u8* b, const unsigned int size) {
    int isEqual = 1;
    for (int i = 0; i < size; ++i) {
        isEqual = a[i] == b[i];
        if (!isEqual) return isEqual;
    }
    return isEqual;
}

unsigned int getParamValueFromBuffer(const u8* buffer, const Param* param) { return *(unsigned int*)(buffer + param->offset); }

unsigned int getParamValueFromFile(FIL* file, const unsigned int baseOffset, const Param* param) {
    u32 value;
    unsigned int bytesReaded = 0;
    f_lseek(file, baseOffset + param->offset);
    f_read(file, &value, 4, &bytesReaded);
    return value;
}

int checkVersionAndMagicFromBuffer(const CustomizeTable* customizeTable) {
    return customizeTable->custRev == KT_CUST_VER && compareU8Arrays(customizeTable->cust, "CUST", 4);
}

int searchBytesArray(const u8* array, const unsigned int size, FIL* file) {
    const unsigned int BUFF_SIZE = 2048;
    unsigned int offset = 0;
    unsigned int fileOffset = 0;
    u8* buff = calloc(BUFF_SIZE, 1);
    unsigned int currentBuffSize = 0;

    f_lseek(file, offset);
    f_read(file, buff, BUFF_SIZE, &currentBuffSize);
    f_lseek(file, BUFF_SIZE);
    int endOfFile = 0;
    while (true) {
        if (endOfFile) {
            free(buff);
            return -1;
        }
        if (offset == currentBuffSize) {
            unsigned int skipPartSize = (size - 1);
            fileOffset += currentBuffSize - skipPartSize;
            f_lseek(file, fileOffset);
            f_read(file, buff, BUFF_SIZE, &currentBuffSize);
            f_lseek(file, fileOffset + BUFF_SIZE);
            offset = 0;
        }
        if (compareU8Arrays(array, buff + offset, size)) {
            free(buff);
            return fileOffset + offset;
        }
        endOfFile = BUFF_SIZE != currentBuffSize;
        ++offset;
    }
}

void setParamValue(const u8* buffer, const Param* param, unsigned int value) {
    *(unsigned int*)(buffer + param->offset) = value;
    saveSession(buffer);
    char* message = calloc(256, 1);
    s_printf(message, "[Session] Param: %s has been changed", param->name);
    gfx_printBottomInfoKT(message);
    free(message);
}

void setParamValueWithoutSaveSession(const u8* buffer, const Param* param, unsigned int value) {
    *(unsigned int*)(buffer + param->offset) = value;
}