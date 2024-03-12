#pragma once

#include "../defaultCustomize.h"
#include "../param.h"
#include "../table.h"

const FixedValues eristaEmcMaxClockFV = {.valuesCount = 4,
                                         .values = {{.value = 1868800, .label = "E"},
                                                    {.value = 1996800, .label = "D"},
                                                    {.value = 2131200, .label = "STAGE 1"},
                                                    {.value = 2265600, .label = "STAGE 2"}}};
const FixedLimits eristaEmcMaxClockFL = {.min = 1600000, .max = 2366000, .stepSize = 400};  // step = GCD
// 4IFIR MODE / RAM VDD MODE
// E 1866 1868800 / 1150'000
// D 2000 1996800 / 1250'000
// S 2133 2131200 / 1350'000
// S 2266 2265600 / 1350'000
// MANUAL 1600000-2366000 STEP 38400KHz
const Param eristaEmcMaxClock = {
    .name = "EMC Max Clock",
    .measure = "MHz",
    .description = NULL,
    .offset = getOffset(defaultCustTable.eristaEmcMaxClock),
    .defaultValue = defaultCustTable.eristaEmcMaxClock,
    .limitsCount = 2,
    .limits = {{.type = EFixedValues, .values = &eristaEmcMaxClockFV}, {.type = EFixedLimits, .values = &eristaEmcMaxClockFL}}};

const Params eRAMParams = {.count = 1, .params = {&eristaEmcMaxClock}};
const Tables eRAMTables = {};