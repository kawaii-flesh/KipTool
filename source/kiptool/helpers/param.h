#pragma once
#include "../params/param.h"
#include <stdbool.h>

void getDisplayValue(const Param *param, char *displayBuff, unsigned int value);

void addDefaultPostfix(const Param *param, char *displayBuff, unsigned int value);

bool addLabelToFixedValue(const Param *param, char *displayBuff, unsigned int value);