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
// 4IFIR MODE / eBAMATIC STAGE 0-1-2-3
// S-LOH 1600 / 1600000 / eBAL 2 2 2 2
// E ST2 1733 / 1734400 / eBAL 3 2 2 2
// E ST1 1866 / 1868800 / eBAL 3 3 2 2
// D ST1 2000 / 1996800 / eBAL 3 3 3 2
// D ST2 2133 / 2131200 / eBAL 3 4 3 3
// S ST1 2266 / 2265600 / eBAL 4 4 4 3
// L-C4C 2366 / 2361600 / eBAL 4 4 4 4
// 1600000-2366000 MANUAL 38.4MHz STEP
// 2278400 2240000 2201600 2163200 2124800 TODO Is actual min-max for manual?
const Param eristaEmcMaxClock = {.name = "EMC Max Clock",
                                 .measure = "MHz",
                                 .description = NULL,
                                 .offset = getOffset(defaultCustTable.eristaEmcMaxClock),
                                 .defaultValue = defaultCustTable.eristaEmcMaxClock,
                                 .limitsCount = 2,
                                 .limits = {{.type = EFixedValues, .values = &eristaEmcMaxClockFV}, {.type = EFixedLimits, .values = &eristaEmcMaxClockFL}}};

const Params eRAMParams = {.count = 1, .params = {&eristaEmcMaxClock}};
const Tables eRAMTables = {};
