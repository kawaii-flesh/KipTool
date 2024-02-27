#pragma once

#include "../customize.h"
#include "../param.h"

const FixedValues eristaCpuMaxVoltFV = {.valuesCount = 4,
                                        .values = {{.value = 1200, .label = "ECO"},
                                                   {.value = 1250, .label = "STAGE 1"},
                                                   {.value = 1300, .label = "STAGE 2"},
                                                   {.value = 1350, .label = "STAGE 3"}}};
const FixedLimits eristaCpuMaxVoltFL = {.min = 1180, .max = 1350, .stepSize = 5};
const Param eristaCpuMaxVolt = {
    .name = "CPU Max Volt",
    .measure = "mV",
    .description = NULL,
    .offset = getOffset(custTable.eristaCpuMaxVolt),
    .length = 4,
    .defaultValue = custTable.eristaCpuMaxVolt,
    .limitsCount = 2,
    .limits = {{.type = EFixedValues, .values = &eristaCpuMaxVoltFV}, {.type = EFixedLimits, .values = &eristaCpuMaxVoltFL}}};

const unsigned int eCPUParamsCount = 1;
const Param *eCPUParams[] = {&eristaCpuMaxVolt};