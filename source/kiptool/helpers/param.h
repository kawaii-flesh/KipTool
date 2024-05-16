#pragma once

#include <utils/types.h>

#include "../params/param.h"

typedef struct FormatingData {
    unsigned int nameLen;
    unsigned int valueLen;
    unsigned int labelLen;
} FormatingData;

void addDefaultPostfix(const Param* param, char* displayBuff, unsigned int value, int isParam);

void addLabel(const Value* value, char* displayBuff);

bool addLabelToFixedValue(const Param* param, char* displayBuff, unsigned int value);

void formatValueDiv(char* displayBuff, const unsigned int value, bool div);

void getDisplayValue(const Param* param, char* displayBuff, unsigned int value, int isParam);
// A waste of time, but a beautiful print TODO rewrite (╯°□°)╯ (┻━┻)
void getFormatingData(FormatingData* formatingData, const u8* custTable, const unsigned int paramsCount, const Param* params[]);
char* getFormattedBuff(FormatingData* formatingData, char* buff);
