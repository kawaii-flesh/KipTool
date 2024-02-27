#pragma once

#include "../customize.h"
#include "../param.h"

const FixedValues commonCpuBoostClockFV = {.valuesCount = 5,
                                           .values = {{.value = 1428000, .label = "CPU-HI uV DEBUG"},
                                                      {.value = 1785000, .label = "CPU-LOW uV DEBUG"},
                                                      {.value = 2000000, .label = "E"},
                                                      {.value = 2500000, .label = "D"},
                                                      {.value = 3000000, .label = "S"}}};
const FixedLimits commonCpuBoostClockFL = {.min = 1400000, .max = 3000000, .stepSize = 100000};
const Param commonCpuBoostClock = {.name = "Cpu Boost Clock",
                                   .measure = "MHz",
                                   .description = NULL,
                                   .offset = getOffset(custTable.commonCpuBoostClock),
                                   .length = 4,
                                   .defaultValue = custTable.commonCpuBoostClock,
                                   .limitsCount = 2,
                                   .limits = {{.type = EFixedValues, .values = &commonCpuBoostClockFV},
                                              {.type = EFixedLimits, .values = &commonCpuBoostClockFL}}};


const FixedValues CPUvFV = {.valuesCount = 4,
                            .values = {{.value = 620},
                                       {.value = 590, .label = "ECO ST1"},
                                       {.value = 560, .label = "ECO ST2"},
                                       {.value = 530, .label = "ECO ST3"}}};
const FixedLimits CPUvFL = {.min = 430, .max = 670, .stepSize = 5};
const Param CPUv = {.name = "CPUv",
                    .measure = "mV",
                    .description = NULL,
                    .offset = getOffset(custTable.CPUv),
                    .length = 4,
                    .defaultValue = custTable.CPUv,
                    .limitsCount = 2,
                    .limits = {{.type = EFixedValues, .values = &CPUvFV}, {.type = EFixedLimits, .values = &CPUvFL}}};

const unsigned int cCPUParamsCount = 2;
const Param *cCPUParams[] = {&commonCpuBoostClock, &CPUv};
