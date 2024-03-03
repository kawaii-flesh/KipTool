#pragma once
#include "param.h"

typedef struct {
    const char *name;
    const char *description;
    const enum Category category;
    const enum Platform platform;
    const unsigned int baseOffset;
    const unsigned int paramsCount;
    const Param *params[];
} Table;

typedef struct Tables {
    const unsigned int count;
    const Table *tables[];
} Tables;

// typedef struct {
//     const Param *tableModeParam;
//     const Table *tables[];
// } ModeTable;