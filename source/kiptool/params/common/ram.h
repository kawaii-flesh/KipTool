#pragma once

#include "../customize.h"
#include "../param.h"
#include "../table.h"

const FixedValues commonEmcMemVoltFV = {
    .valuesCount = 3,
    .values = {{.value = 1175000, .label = "ECO"}, {.value = 1275000, .label = "DEFAULT"}, {.value = 1375000, .label = "SRT"}}};
const FixedLimits commonEmcMemVoltFL = {.min = 950000, .max = 1400000, .stepSize = 12500};
const Param commonEmcMemVolt = {
    .name = "EMC Mem Volt",
    .measure = "mV",
    .description = NULL,
    .offset = getOffset(custTable.commonEmcMemVolt),
    .length = 4,
    .defaultValue = custTable.commonEmcMemVolt,
    .limitsCount = 2,
    .limits = {{.type = EFixedValues, .values = &commonEmcMemVoltFV}, {.type = EFixedLimits, .values = &commonEmcMemVoltFL}}};

const FixedValues ramTiming1FV = {.valuesCount = 9,
                                  .values = {{.value = 0, .label = "Do not adjust"},
                                             {.value = 1},
                                             {.value = 2},
                                             {.value = 3},
                                             {.value = 4},
                                             {.value = 5},
                                             {.value = 6},
                                             {.value = 7},
                                             {.value = 8}}};
const Param ramTiming1 = {.name = "RAM Timing 1",
                          .measure = NULL,
                          .description = NULL,
                          .offset = 0,
                          .length = 4,
                          .defaultValue = custTable.ramTimingPresetOne,
                          .limitsCount = 1,
                          .limits = {{.type = EFixedValues, .values = &ramTiming1FV}}};

const FixedValues ramTiming2FV = {.valuesCount = 9,
                                  .values = {{.value = 0, .label = "Do not adjust"},
                                             {.value = 1},
                                             {.value = 2},
                                             {.value = 3},
                                             {.value = 4},
                                             {.value = 5},
                                             {.value = 6},
                                             {.value = 7},
                                             {.value = 8}}};
const Param ramTiming2 = {.name = "RAM Timing 2",
                          .measure = NULL,
                          .description = NULL,
                          .offset = 1,
                          .length = 4,
                          .defaultValue = custTable.ramTimingPresetTwo,
                          .limitsCount = 1,
                          .limits = {{.type = EFixedValues, .values = &ramTiming2FV}}};

const FixedValues ramTiming3FV = {.valuesCount = 10,
                                  .values = {{.value = 0, .label = "Do not adjust"},
                                             {.value = 1},
                                             {.value = 2},
                                             {.value = 3},
                                             {.value = 4},
                                             {.value = 5},
                                             {.value = 6},
                                             {.value = 7},
                                             {.value = 8},
                                             {.value = 9}}};
const Param ramTiming3 = {.name = "RAM Timing 3",
                          .measure = NULL,
                          .description = NULL,
                          .offset = 2,
                          .length = 4,
                          .defaultValue = custTable.ramTimingPresetThree,
                          .limitsCount = 1,
                          .limits = {{.type = EFixedValues, .values = &ramTiming3FV}}};

const FixedValues ramTiming4FV = {.valuesCount = 9,
                                  .values = {{.value = 0, .label = "Do not adjust"},
                                             {.value = 1},
                                             {.value = 2},
                                             {.value = 3},
                                             {.value = 4},
                                             {.value = 5},
                                             {.value = 6},
                                             {.value = 7},
                                             {.value = 8}}};
const Param ramTiming4 = {.name = "RAM Timing 4",
                          .measure = NULL,
                          .description = NULL,
                          .offset = 3,
                          .length = 4,
                          .defaultValue = custTable.ramTimingPresetFour,
                          .limitsCount = 1,
                          .limits = {{.type = EFixedValues, .values = &ramTiming4FV}}};

const FixedValues ramTiming5FV = {.valuesCount = 9,
                                  .values = {{.value = 0, .label = "Do not adjust"},
                                             {.value = 1},
                                             {.value = 2},
                                             {.value = 3},
                                             {.value = 4},
                                             {.value = 5},
                                             {.value = 6},
                                             {.value = 7},
                                             {.value = 8}}};
const Param ramTiming5 = {.name = "RAM Timing 5",
                          .measure = NULL,
                          .description = NULL,
                          .offset = 4,
                          .length = 4,
                          .defaultValue = custTable.ramTimingPresetFive,
                          .limitsCount = 1,
                          .limits = {{.type = EFixedValues, .values = &ramTiming5FV}}};

const FixedValues ramTiming6FV = {.valuesCount = 11,
                                  .values = {{.value = 0, .label = "Do not adjust"},
                                             {.value = 1},
                                             {.value = 2},
                                             {.value = 3},
                                             {.value = 4},
                                             {.value = 5},
                                             {.value = 6},
                                             {.value = 7},
                                             {.value = 8},
                                             {.value = 9},
                                             {.value = 10}}};
const Param ramTiming6 = {.name = "RAM Timing 6",
                          .measure = NULL,
                          .description = NULL,
                          .offset = 5,
                          .length = 4,
                          .defaultValue = custTable.ramTimingPresetSix,
                          .limitsCount = 1,
                          .limits = {{.type = EFixedValues, .values = &ramTiming6FV}}};

const FixedValues ramTiming7FV = {.valuesCount = 15,
                                  .values = {{.value = 0, .label = "Do not adjust"},
                                             {.value = 1},
                                             {.value = 2},
                                             {.value = 3},
                                             {.value = 4},
                                             {.value = 5},
                                             {.value = 6},
                                             {.value = 7},
                                             {.value = 8},
                                             {.value = 9},
                                             {.value = 10},
                                             {.value = 11},
                                             {.value = 12},
                                             {.value = 13},
                                             {.value = 14}}};
const Param ramTiming7 = {.name = "RAM Timing 7",
                          .measure = NULL,
                          .description = NULL,
                          .offset = 6,
                          .length = 4,
                          .defaultValue = custTable.ramTimingPresetSeven,
                          .limitsCount = 1,
                          .limits = {{.type = EFixedValues, .values = &ramTiming7FV}}};

const FixedValues ramTiming8FV = {.valuesCount = 19,
                                  .values = {{.value = 0, .label = "Do not adjust"},
                                             {.value = 1},
                                             {.value = 2},
                                             {.value = 3},
                                             {.value = 4},
                                             {.value = 5},
                                             {.value = 6},
                                             {.value = 7},
                                             {.value = 8},
                                             {.value = 9},
                                             {.value = 10},
                                             {.value = 11},
                                             {.value = 12},
                                             {.value = 13},
                                             {.value = 14},
                                             {.value = 15},
                                             {.value = 16},
                                             {.value = 17},
                                             {.value = 18}}};
const Param ramTiming8 = {.name = "RAM Timing 8",
                          .measure = NULL,
                          .description = NULL,
                          .offset = getOffset(custTable.ramTimingPresetEight),
                          .length = 4,
                          .defaultValue = custTable.ramTimingPresetEight,
                          .limitsCount = 1,
                          .limits = {{.type = EFixedValues, .values = &ramTiming8FV}}};

const Table ramTimingsTable = {
    .editable = true,
    .baseOffset = getOffset(custTable.ramTimingPresetOne),
    .increment = 4,
    .paramsCount = 7,
    .params = {&ramTiming1, &ramTiming2, &ramTiming3, &ramTiming4, &ramTiming5, &ramTiming6, &ramTiming7}};

const unsigned int cRAMParamsCount = 2;
const Param *cRAMParams[] = {&ramTiming8, &commonEmcMemVolt};

const unsigned int cRAMFixedTablesCount = 1;
const Table *cRAMTables[] = {&ramTimingsTable};