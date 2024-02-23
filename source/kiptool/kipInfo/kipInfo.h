#pragma once

#include <libs/fatfs/ff.h>

#include "../../fs/fstypes.h"
#include "../params/param.h"

int kipInfo(char *path, FSEntry_t entry);

void printParamFromFile(FIL *file, unsigned int baseOffset, const Param *param, char *displayBuff);

void printParamByValue(unsigned int value, const Param *param, char *displayBuff);