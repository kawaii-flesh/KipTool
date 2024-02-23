#include "helpers.h"

#include <mem/heap.h>
#include <stdlib.h>
#include <string.h>

#include "params/param.h"

bool compareU8Arrays(u8 *a, u8 *b, unsigned int size) {
    bool isEqual = true;
    for (int i = 0; i < size; ++i) {
        isEqual = a[i] == b[i];
        if (!isEqual) return isEqual;
    }
    return isEqual;
}

unsigned int u8ArrayToUnsignedInt(u8 *array, unsigned int arraySize) {
    unsigned int num = 0;
    for (unsigned int i = arraySize - 1; i != -1; --i) {
        num <<= 8;
        num += array[i];
    }
    return num;
}

extern const Param gKipVersion;
void addDefaultPostfix(const Param *param, char *displayBuff, unsigned int value) {
    if (param != &gKipVersion && param->defaultValue == value)
        strcpy(displayBuff + strlen(displayBuff), " - Default");
}

bool addLabelToFixedValue(const Param *param, char *displayBuff, unsigned int value) {
    const FixedValues *limits = (FixedValues *)(param->limits);
    for (unsigned int i = 0; i < limits->valuesCount; ++i) {
        if (limits->values[i].value == value) {
            if (limits->values[i].label == NULL) return;
            strcpy(displayBuff + strlen(displayBuff), " - ");
            strcpy(displayBuff + strlen(displayBuff), limits->values[i].label);
            return;
        }
    }
}

void getDisplayValue(const Param *param, char *displayBuff, unsigned int value) {
    utoa(value > 1500 ? value / 1000 : value, displayBuff, 10);
    if (param->limitsType == EFixedValues) {
        if (!addLabelToFixedValue(param, displayBuff, value)) {
            strcpy(displayBuff, "Unknown value");
            return;
        }
    }
    if (param->measure != NULL) strcpy(displayBuff + strlen(displayBuff), param->measure);
    addDefaultPostfix(param, displayBuff, value);
    return;
}

unsigned int getParamValueFromFile(FIL *file, unsigned int baseOffset, Param *param) {
    unsigned int paramLength = param->length;
    u8 *valueBytes = calloc(paramLength, 1);
    unsigned int bytesReaded = 0;
    f_lseek(file, baseOffset + param->offset);
    f_read(file, valueBytes, paramLength, &bytesReaded);
    return u8ArrayToUnsignedInt(valueBytes, paramLength);
}

unsigned int searchBytesArray(u8 *array, unsigned int size, FIL *file) {
    const unsigned int BUFF_SIZE = 2048;
    unsigned int offset = 0;
    unsigned int fileOffset = 0;
    u8 *buff = calloc(BUFF_SIZE, 1);
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