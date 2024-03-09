#pragma once

#include "../../params/param.h"
#include "../../params/table.h"
#include "ktMenu.h"

void printParamEntry(MenuEntry* entry, u32 maxLen, u8 highlighted, u32 bg, u8* custTable);

void newParamsMenu(const u8* custTable, const char* sectionTitle, const Params* params[], const unsigned int paramsArraysCount,
                   const Tables* tables[], unsigned int tablesArraysCount);