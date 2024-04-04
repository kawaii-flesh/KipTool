#pragma once
#include <libs/fatfs/ff.h>
#include <utils/types.h>

int searchBytesArray(const u8* array, const unsigned int size, FIL* file);
