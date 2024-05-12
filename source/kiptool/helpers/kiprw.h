#pragma once
#include <libs/fatfs/ff.h>

#include "../params/customize.h"
#include "../params/param.h"
#include "../params/table.h"

unsigned int getParamValueFromBuffer(const u8* buffer, const Param* param);

unsigned int getParamValueFromFile(FIL* file, const unsigned int baseOffset, const Param* param);

int checkVersionAndMagicFromBuffer(const CustomizeTable* customizeTable);

void setParamValue(const u8* buffer, const u8* ktSection, const Param* param, unsigned int value);

void setParamValueWithoutSaveSession(const u8* buffer, const Param* param, unsigned int value);
