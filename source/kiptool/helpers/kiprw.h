#pragma once
#include <libs/fatfs/ff.h>

#include "../params/param.h"
#include "../params/table.h"

int compareU8Arrays(const u8* a, const u8* b, const unsigned int size);

unsigned int getParamValueFromBuffer(const u8* buffer, const Param* param);

int searchBytesArray(const u8* array, const unsigned int size, FIL* file);

void setParamValue(const u8* buffer, const Param* param, unsigned int value);