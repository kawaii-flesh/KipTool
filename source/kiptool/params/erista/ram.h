#pragma once

#include "../customize.h"
#include "../param.h"

const FixedValues eristaEmcMaxClockFV = {.valuesCount = 4,
                                         .values = {{.value = 1868800, .label = "E"},
                                                    {.value = 1996800, .label = "D"},
                                                    {.value = 2131200, .label = "STAGE 1"},
                                                    {.value = 2265600, .label = "STAGE 2"}}};
const FixedLimits eristaEmcMaxClockFL = {.min = 1600000, .max = 2366000, .stepSize = 38400};
const Param eristaEmcMaxClock = {
    .name = "EMC Max Clock",
    .measure = "mV",
    .description = NULL,
    .offset = getOffset(custTable.eristaEmcMaxClock),
    .length = 4,
    .defaultValue = custTable.eristaEmcMaxClock,
    .limitsCount = 2,
    .limits = {{.type = EFixedValues, .values = &eristaEmcMaxClockFV}, {.type = EFixedLimits, .values = &eristaEmcMaxClockFL}}};

const unsigned int eRAMParamsCount = 1;
const Param *eRAMParams[] = {&eristaEmcMaxClock};