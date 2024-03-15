#pragma once

#include "../defaultCustomize.h"
#include "../param.h"
#include "../table.h"

const FixedValues CPUvFV = {
    .valuesCount = 4,
    .values = {
        {.value = 620}, {.value = 3, .label = "ECO ST1"}, {.value = 2, .label = "ECO ST2"}, {.value = 1, .label = "ECO ST3"}}};
const FixedLimits CPUvFL = {.min = 430, .max = 670, .stepSize = 5, .measure = "mV"};
// CPU UNDER LOGIC
// 3 AUTO ECO ST1
// 2 AUTO ECO ST2
// 1 AUTO ECO ST3
// MANUAL 430-670 STEP 5-10mV
// 620mV DEFAULT
// MARIKO CPU VOLT MIN = CPUv
const Param CPUv = {.name = "CPU UNDER LOGIC",
                    .measure = NULL,
                    .description = NULL,
                    .offset = getOffset(defaultCustTable.CPUv),
                    .defaultValue = defaultCustTable.CPUv,
                    .limitsCount = 2,
                    .limits = {{.type = EFixedValues, .values = &CPUvFV}, {.type = EFixedLimits, .values = &CPUvFL}}};

const Params cCPUParams = {.count = 1, .params = {&CPUv}};
const Tables cCPUTables = {};