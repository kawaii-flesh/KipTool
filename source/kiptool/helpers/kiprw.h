#pragma once
#include <libs/fatfs/ff.h>

#include "../params/customize.h"
#include "../params/param.h"
#include "../params/table.h"

int compareU8Arrays(const u8* a, const u8* b, const unsigned int size);

unsigned int getParamValueFromBuffer(const u8* buffer, const Param* param);

unsigned int getParamValueFromFile(FIL* file, const unsigned int baseOffset, const Param* param);

int checkVersionAndMagicFromBuffer(const CustomizeTable* customizeTable);

int searchBytesArray(const u8* array, const unsigned int size, FIL* file);

void setParamValue(const u8* buffer, const Param* param, unsigned int value);

void setParamValueWithoutSaveSession(const u8* buffer, const Param* param, unsigned int value);
