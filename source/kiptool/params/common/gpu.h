#pragma once

#include "../param.h"
#include "../table.h"

const FixedValues GPUvFV = {.valuesCount = 3, .values = {{.value = 3, .label = "ECO ST1"}, {.value = 2, .label = "ECO ST2"}, {.value = 1, .label = "ECO ST3"}}};
const FixedLimits GPUvFL = {.min = 430, .max = 970, .stepSize = 5, .measure = "mV"};
// GPU UNDER LOGIC
// 3 AUTO ECO ST1
// 2 AUTO ECO ST2
// 1 AUTO ECO ST3
// MANUAL 430-970 STEP mV 5-10mV
// 610mV DEFAULT
// MARIKO GPU VOLT MIN = CPUv // ? GPUv
// ERISTA GPU VOLT MIN = CPUv + 100mV // ? GPUv
const Param GPUv = {.name = "UNDER LOGIC",
                    .measure = NULL,
                    .description = NULL,
                    .offset = getOffset(defaultCustTable.GPUv),
                    .defaultValue = defaultCustTable.GPUv,
                    .limitsCount = 2,
                    .limits = {{.type = EFixedValues, .values = &GPUvFV}, {.type = EFixedLimits, .values = &GPUvFL}}};

const Params cGPUParams = {.count = 1, .params = {&GPUv}};
const Tables cGPUTables = {};
