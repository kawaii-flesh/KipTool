#pragma once
#include <stdbool.h>

#include "../params/param.h"

void addDefaultPostfix(const Param* param, char* displayBuff, unsigned int value, int isParam);

void addLabel(const Param* param, const Value* value, char* displayBuff);

bool addLabelToFixedValue(const Param* param, char* displayBuff, unsigned int value);

void getDisplayValue(const Param* param, char* displayBuff, unsigned int value, int isParam);