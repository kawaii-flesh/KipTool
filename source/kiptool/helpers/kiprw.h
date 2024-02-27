#pragma once
#include <libs/fatfs/ff.h>

#include "../params/param.h"
#include "../params/table.h"

bool compareU8Arrays(u8 *a, u8 *b, unsigned int size);

unsigned int u8ArrayToUnsignedInt(u8 *array, unsigned int arraySize);

unsigned int searchBytesArray(u8 *array, unsigned int size, FIL *file);