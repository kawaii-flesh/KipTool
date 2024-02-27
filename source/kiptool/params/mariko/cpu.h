#pragma once

#include "../customize.h"
#include "../param.h"

const FixedValues marikoCpuMaxVoltFV = {.valuesCount = 4,
                                        .values = {{.value = 1150, .label = "ECO"},
                                                   {.value = 1180, .label = "STAGE 1"},
                                                   {.value = 1210, .label = "STAGE 2"},
                                                   {.value = 1250, .label = "STAGE 3"}}};
const FixedLimits marikoCpuMaxVoltFL = {.min = 1130, .max = 1280, .stepSize = 5};
const Param marikoCpuMaxVolt = {
    .name = "CPU Max Volt",
    .measure = "mV",
    .description = NULL,
    .offset = getOffset(custTable.marikoCpuMaxVolt),
    .length = 4,
    .defaultValue = custTable.marikoCpuMaxVolt,
    .limitsCount = 2,
    .limits = {{.type = EFixedValues, .values = &marikoCpuMaxVoltFV}, {.type = EFixedLimits, .values = &marikoCpuMaxVoltFL}}};

const FixedValues marikoCpuUVFV = {.valuesCount = 4,
                                   .values = {{.value = 0},
                                              {.value = 1, .label = "ECO ST1"},
                                              {.value = 2},
                                              {.value = 3, .label = "ECO ST2"},
                                              {.value = 4},
                                              {.value = 5, .label = "ECO ST3"},
                                              {.value = 6}}};
const Param marikoCpuUV = {.name = "CPU UV",
                           .measure = NULL,
                           .description = NULL,
                           .offset = getOffset(custTable.marikoCpuUV),
                           .length = 4,
                           .defaultValue = custTable.marikoCpuUV,
                           .limitsCount = 1,
                           .limits = {{.type = EFixedValues, .values = &marikoCpuUVFV}}};

const unsigned int mCPUParamsCount = 2;
const Param *mCPUParams[] = {&marikoCpuMaxVolt, &marikoCpuUV};