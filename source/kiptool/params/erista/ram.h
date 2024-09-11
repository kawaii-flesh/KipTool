#pragma once

#include "../defaultCustomize.h"
#include "../param.h"
#include "../table.h"

const FixedValues eristaEmcMaxClockFV = {.valuesCount = 7,
                                         .values = {{.value = 1600000, .label = "S-LOH"},
                                                    {.value = 1734400, .label = "E ST2"},
                                                    {.value = 1868800, .label = "E ST1"},
                                                    {.value = 1996800, .label = "D ST1"},
                                                    {.value = 2131200, .label = "D ST2"},
                                                    {.value = 2265600, .label = "S ST1"},
                                                    {.value = 2361600, .label = "L-C4C"}}};
const FixedLimits eristaEmcMaxClockFL = {.min = 1600000, .max = 2366000, .stepSize = 400};  // step = GCD
// 4IFIR MODE ON ERISTA
// S-LOH 1600 / 1600000
// E ST2 1733 / 1734400
// E ST1 1866 / 1868800
// D ST1 2000 / 1996800
// D ST2 2133 / 2131200
// S ST1 2266 / 2265600
// L-C4C 2366 / 2361600
// MANUAL 1600000-2366000 STEP 38.4MHz
// 2278400 2240000 2201600 2163200 2124800
const Param eristaEmcMaxClock = {.name = "EMC Max Clock",
                                 .measure = "MHz",
                                 .offset = getOffset(defaultCustTable.eristaEmcMaxClock),
                                 .defaultValue = defaultCustTable.eristaEmcMaxClock,
                                 .limitsCount = 2,
                                 .limits = {{.type = EFixedValues, .values = &eristaEmcMaxClockFV}, {.type = EFixedLimits, .values = &eristaEmcMaxClockFL}}};

const Params eRAMParams = {.count = 1, .params = {&eristaEmcMaxClock}};
const Tables eRAMTables = {};
