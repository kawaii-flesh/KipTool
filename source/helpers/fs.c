#include "fs.h"

#include <mem/heap.h>

#include "mem.h"

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
        endOfFile = size >= currentBuffSize;
        ++offset;
    }
}
