#include "mem.h"

int compareU8Arrays(const u8* a, const u8* b, const unsigned int size) {
    int isEqual = 1;
    for (int i = 0; i < size; ++i) {
        isEqual = a[i] == b[i];
        if (!isEqual) return isEqual;
    }
    return isEqual;
}
