#pragma once
#include "param.h"

typedef struct {
    const char* name;
    const char* description;
    const unsigned int baseOffset;
    const unsigned int paramsCount;
    const Param* params[];
} Table;

typedef struct Tables {
    const unsigned int count;
    const Table* tables[];
} Tables;

#define RAM_TIMINGS_TABLE_NAME "RAM Timings Table"
// typedef struct {
//     const Param *tableModeParam;
//     const Table *tables[];
// } ModeTable;
