#pragma once

#include <libs/fatfs/ff.h>

#include "../../fs/fstypes.h"
#include "../params/param.h"
#include "../params/table.h"

void printTable(const u8 *buff, const Table *table, char *displayBuff);

void printParamByParam(const u8 *buff, const Param *param, char *displayBuff);

void printParamByValue(unsigned int value, const Param *param, char *displayBuff);

void printCPUParams(const u8 *buff, char *displayBuff, enum Platform platform);

void printGPUParams(const u8 *buff, char *displayBuff, enum Platform platform);

void printRAMParams(const u8 *buff, char *displayBuff, enum Platform platform);

int kipWizard(char *path, FSEntry_t entry);