#pragma once
#include "param.h"

typedef struct {
    const enum Category category;
    const enum Platform platform;
    const unsigned int baseOffset;
    const unsigned int increment;
    const unsigned int paramsCount;
    const Param *params[];
} Table;

// typedef struct {
//     const Param *tableModeParam;
//     const Table *tables[];
// } ModeTable;