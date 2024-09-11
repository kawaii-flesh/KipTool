#pragma once

#include "../defaultCustomize.h"
#include "../param.h"
#include "../table.h"

const FixedValues eristaCpuMaxVoltFV = {
    .valuesCount = 4,
    .values = {{.value = 1200, .label = "ECO"}, {.value = 1250, .label = "STAGE 1"}, {.value = 1300, .label = "STAGE 2"}, {.value = 1350, .label = "STAGE 3"}}};
const FixedLimits eristaCpuMaxVoltFL = {.min = 1180, .max = 1375, .stepSize = 5};
// ERISTA CPU VMAX MODE
// 1200 ECO
// 1250-1350 STAGE 1-3
// MANUAL 1180-1375 STEP 5mV
const Param eristaCpuMaxVolt = {.name = "VMAX MODE",
                                .measure = "mV",
                                .offset = getOffset(defaultCustTable.eristaCpuMaxVolt),
                                .defaultValue = defaultCustTable.eristaCpuMaxVolt,
                                .limitsCount = 2,
                                .limits = {{.type = EFixedValues, .values = &eristaCpuMaxVoltFV}, {.type = EFixedLimits, .values = &eristaCpuMaxVoltFL}}};

const Params eCPUParams = {.count = 1, .params = {&eristaCpuMaxVolt}};
const Tables eCPUTables = {};
