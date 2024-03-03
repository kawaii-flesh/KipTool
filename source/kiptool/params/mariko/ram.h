#pragma once

#include "../customize.h"
#include "../param.h"
#include "../table.h"

const FixedValues marikoEmcMaxClockFV = {.valuesCount = 11,
                                         .values = {{.value = 1600000, .label = "S-LOH"},
                                                    {.value = 1734400, .label = "E ST3"},
                                                    {.value = 1862400, .label = "E ST2"},
                                                    {.value = 1996800, .label = "E ST1"},
                                                    {.value = 2131200, .label = "D ST1"},
                                                    {.value = 2265600, .label = "D ST2"},
                                                    {.value = 2400000, .label = "D ST3"},
                                                    {.value = 2534400, .label = "S ST1"},
                                                    {.value = 2665600, .label = "S ST2"},
                                                    {.value = 2800000, .label = "S ST3"},
                                                    {.value = 2934400, .label = "L-C4C"}}};
const FixedLimits marikoEmcMaxClockFL = {.min = 1333000, .max = 2733000, .stepSize = 38400};
// 4IFIR MODE / eBAMATIC STAGE: 1-2-3
// S-LOH 1600 / 1600000 / eBAL: 1 1 2
// E ST3 1733 / 1734400 / eBAL: 1 2 2
// E ST2 1866 / 1862400 / eBAL: 2 2 2
// E ST1 2000 / 1996800 / eBAL: 2 2 3
// D ST1 2133 / 2131200 / eBAL: 2 3 3
// D ST2 2266 / 2265600 / eBAL: 3 3 3
// D ST3 2400 / 2400000 / eBAL: 3 3 4
// S ST1 2533 / 2534400 / eBAL: 3 4 4
// S ST2 2666 / 2665600 / eBAL: 4 4 4
// S ST3 2800 / 2800000 / eBAL: 4 4 5
// L-C4C 2933 / 2934400 / eBAL: 4 5 5
// MANUAL 1333000-2733000 STEP 38400 KHz
const Param marikoEmcMaxClock = {
    .name = "EMC Max Clock",
    .category = RAM,
    .platform = MARIKO,
    .measure = "MHz",
    .description = NULL,
    .offset = getOffset(custTable.marikoEmcMaxClock),
    .length = 4,
    .defaultValue = custTable.marikoEmcMaxClock,
    .limitsCount = 2,
    .limits = {{.type = EFixedValues, .values = &marikoEmcMaxClockFV}, {.type = EFixedLimits, .values = &marikoEmcMaxClockFL}}};

const FixedValues marikoEmcVddqVoltFV = {
    .valuesCount = 3, .values = {{.value = 550000, .label = "ECO"}, {.value = 650000}, {.value = 750000, .label = "SRT"}}};
const FixedLimits marikoEmcVddqVoltFL = {.min = 300000, .max = 800000, .stepSize = 100000};
// RAM VDDQ MODE
// 550'000 ECO
// 650'000 DEFAULT
// 750'000 SRT
// MANUAL 300'000-800'000
const Param marikoEmcVddqVolt = {
    .name = "RAM VDDQ MODE",
    .category = RAM,
    .platform = MARIKO,
    .measure = "mV",
    .description = NULL,
    .offset = getOffset(custTable.marikoEmcVddqVolt),
    .length = 4,
    .defaultValue = custTable.marikoEmcVddqVolt,
    .limitsCount = 2,
    .limits = {{.type = EFixedValues, .values = &marikoEmcVddqVoltFV}, {.type = EFixedLimits, .values = &marikoEmcVddqVoltFL}}};

const FixedValues marikoEmcDvbShiftFV = {.valuesCount = 4,
                                         .values = {{.value = 3, .label = "AUTO"},
                                                    {.value = 2, .label = "ECO ST1"},
                                                    {.value = 1, .label = "ECO ST2"},
                                                    {.value = 0, .label = "ECO ST3"}}};
const FixedLimits marikoEmcDvbShiftFL = {.min = 300, .max = 1150, .stepSize = 50, .measure = "mV"};  // TODO ? Step size
// EMB ECO LOGIC
// 3 AUTO
// 2 AUTO ECO ST1
// 1 AUTO ECO ST2
// 0 AUTO ECO ST3
// MANUAL 300-1150 mV
const Param marikoEmcDvbShift = {
    .name = "EMB ECO LOGIC",
    .category = RAM,
    .platform = MARIKO,
    .measure = NULL,
    .description = NULL,
    .offset = getOffset(custTable.marikoEmcDvbShift),
    .length = 4,
    .defaultValue = custTable.marikoEmcDvbShift,
    .limitsCount = 2,
    .limits = {{.type = EFixedValues, .values = &marikoEmcDvbShiftFV}, {.type = EFixedLimits, .values = &marikoEmcDvbShiftFL}}};

const Params mRAMParams = {.count = 3, .params = {&marikoEmcMaxClock, &marikoEmcVddqVolt, &marikoEmcDvbShift}};
const Tables mRAMTables = {};