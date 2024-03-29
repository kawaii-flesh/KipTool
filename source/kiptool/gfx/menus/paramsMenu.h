#pragma once

#include "../../helpers/param.h"
#include "../../params/param.h"
#include "../../params/table.h"
#include "ktMenu.h"

typedef struct PrintParamAdditionalData {
    const u8* custTable;
    FormatingData* formatingData;
} PrintParamAdditionalData;

void printParamEntry(MenuEntry* entry, u32 maxLen, u8 highlighted, u32 bg, PrintParamAdditionalData* printParamAdditionalData);

void newParamsMenu(const u8* custTable, const char* sectionTitle, const Params* params[], const unsigned int paramsArraysCount, const Tables* tables[],
                   unsigned int tablesArraysCount);
