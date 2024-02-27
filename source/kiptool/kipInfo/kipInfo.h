#pragma once

#include <libs/fatfs/ff.h>

#include "../../fs/fstypes.h"
#include "../params/param.h"
#include "../params/table.h"

int kipInfo(char *path, FSEntry_t entry);

void printParamByValue(unsigned int value, const Param *param, char *displayBuff);