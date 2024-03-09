#include "kiprw.h"

#include <mem/heap.h>

#include "../params/param.h"

bool compareU8Arrays(const u8* a, const u8* b, const unsigned int size) {
    bool isEqual = true;
    for (int i = 0; i < size; ++i) {
        isEqual = a[i] == b[i];
        if (!isEqual) return isEqual;
    }
    return isEqual;
}

unsigned int u8ArrayToUnsignedInt(const u8* array, const unsigned int length) {
    unsigned int num = 0;
    for (unsigned int i = length - 1; i != -1; --i) {
        num <<= 8;
        num += array[i];
    }
    return num;
}

unsigned int getParamValueFromBuffer(const u8* buffer, const Param* param) {
    return u8ArrayToUnsignedInt(buffer + param->offset, param->length);
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
    while (true) {
        if (offset == currentBuffSize) {
            unsigned int skipPartSize = (size - 1);
            fileOffset += currentBuffSize - skipPartSize;
            f_lseek(file, fileOffset);
            f_read(file, buff, BUFF_SIZE, &currentBuffSize);
            f_lseek(file, fileOffset + BUFF_SIZE);
            offset = 0;
        }
        if (currentBuffSize == 0) {
            free(buff);
            return -1;
        }
        if (compareU8Arrays(array, buff + offset, size)) {
            free(buff);
            return fileOffset + offset;
        }
        ++offset;
    }
}