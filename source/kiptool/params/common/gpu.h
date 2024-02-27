#pragma once

#include "../customize.h"
#include "../param.h"

const FixedValues GPUvFV = {
    .valuesCount = 3,
    .values = {
        {.value = 3, .label = "AUTO ECO ST1"}, {.value = 2, .label = "AUTO ECO ST2"}, {.value = 1, .label = "AUTO ECO ST3"}}};
const FixedLimits GPUvFL = {.min = 430, .max = 770, .stepSize = 5, .measure = "mV"};
const Param GPUv = {.name = "GPUv",
                    .measure = NULL,
                    .description = NULL,
                    .offset = getOffset(custTable.GPUv),
                    .length = 4,
                    .defaultValue = custTable.GPUv,
                    .limitsCount = 2,
                    .limits = {{.type = EFixedValues, .values = &GPUvFV}, {.type = EFixedLimits, .values = &GPUvFL}}};

const unsigned int cGPUParamsCount = 1;
const Param *cGPUParams[] = {&GPUv};