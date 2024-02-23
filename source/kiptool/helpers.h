#pragma once
#include <libs/fatfs/ff.h>

#include "params/param.h"

bool compareU8Arrays(u8 *a, u8 *b, unsigned int size);

unsigned int u8ArrayToUnsignedInt(u8 *array, unsigned int arraySize);

void getDisplayValue(const Param *param, char *displayBuff, unsigned int value);

unsigned int searchBytesArray(u8 *array, unsigned int size, FIL *file);

void addDefaultPostfix(const Param *param, char *displayBuff, unsigned int value);

bool addLabelToFixedValue(const Param *param, char *displayBuff, unsigned int value);

unsigned int getParamValueFromFile(FIL *file, unsigned int baseOffset, Param *param);