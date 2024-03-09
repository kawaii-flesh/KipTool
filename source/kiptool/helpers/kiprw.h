#pragma once
#include <libs/fatfs/ff.h>

#include "../params/param.h"
#include "../params/table.h"

bool compareU8Arrays(const u8* a, const u8* b, const unsigned int size);

unsigned int u8ArrayToUnsignedInt(const u8* array, const unsigned int length);

unsigned int getParamValueFromBuffer(const u8* buffer, const Param* param);

int searchBytesArray(const u8* array, const unsigned int size, FIL* file);