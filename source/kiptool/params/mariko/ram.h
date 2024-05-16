#pragma once

#include "../defaultCustomize.h"
#include "../param.h"
#include "../table.h"

const FixedValues marikoEmcMaxClockFV = {.valuesCount = 11,
                                         .values = {{.value = 1600000, .label = "S-LOH"},
                                                    {.value = 1734400, .label = "E ST3"},
                                                    {.value = 1868800, .label = "E ST2"},
                                                    {.value = 1996800, .label = "E ST1"},
                                                    {.value = 2131200, .label = "D ST1"},
                                                    {.value = 2265600, .label = "D ST2"},
                                                    {.value = 2400000, .label = "D ST3"},
                                                    {.value = 2534400, .label = "S ST1"},
                                                    {.value = 2665600, .label = "S ST2"},
                                                    {.value = 2800000, .label = "S ST3"},
                                                    {.value = 2934400, .label = "L-C4C"}}};
const FixedLimits marikoEmcMaxClockFL = {.min = 1333000, .max = 2733000, .stepSize = 200};  // STEP GCD
// 4IFIR MODE ON MARIKO / VDQ / eBL2 / eBL3 / eBL4 / eBL5 /
// S-LOH 1600 / 1600000 / 370 / 1050 /  975				  /
// E ST3 1733 / 1734400 / 400 / 1100 / 1025				  /
// E ST2 1866 / 1868800 / 430 / 1150 / 1075	   900		  /
// E ST1 2000 / 1996800 / 460 / 1200 / 1125	   950		  /
// D ST1 2133 / 2131200 / 490 / 1250 / 1175 / 1000    925 /
// D ST2 2266 / 2265600 / 520 / 1300 / 1225 / 1050    975 /
// D ST3 2400 / 2400000 / 550 / 1350 / 1275 / 1100 / 1025 /
// S ST1 2533 / 2534400 / 580 /		   1325 / 1150 / 1075 /
// S ST2 2666 / 2665600 / 610 /		   1375 / 1200 / 1125 /
// S ST3 2800 / 2800000 / 640 / 	  		  1250 / 1175 /
// L-C4C 2933 / 2934400 / 670 / 	  		  1300 / 1225 /
// MICRON E/H eBAL 4 < 3.8GHz
// SAMSUNG B eBAL 4 < 3.9GHz
// HYNIX CJR/DJR eBAL 4 < 3.8GHz
// MANUAL 1333000-2733000 STEP 38.4MHz
const Param marikoEmcMaxClock = {.name = "EMC Max Clock",
                                 .measure = "MHz",
                                 .description = NULL,
                                 .offset = getOffset(defaultCustTable.marikoEmcMaxClock),
                                 .defaultValue = defaultCustTable.marikoEmcMaxClock,
                                 .limitsCount = 2,
                                 .limits = {{.type = EFixedValues, .values = &marikoEmcMaxClockFV}, {.type = EFixedLimits, .values = &marikoEmcMaxClockFL}}};

const FixedValues marikoEmcVddqVoltFV = {.valuesCount = 3, .values = {{.value = 500000, .label = "ECO"}, {.value = 650000}, {.value = 700000, .label = "SRT"}}};
const FixedLimits marikoEmcVddqVoltFL = {.min = 300000, .max = 800000, .stepSize = 100000};
// RAM VDDQ MODE
// 500'000 ECO
// 650'000 DEFAULT
// 700'000 SRT
// MANUAL 300'000-800'000
const Param marikoEmcVddqVolt = {.name = "RAM VDDQ MODE",
                                 .measure = "mV",
                                 .description = NULL,
                                 .offset = getOffset(defaultCustTable.marikoEmcVddqVolt),
                                 .defaultValue = defaultCustTable.marikoEmcVddqVolt,
                                 .limitsCount = 2,
                                 .limits = {{.type = EFixedValues, .values = &marikoEmcVddqVoltFV}, {.type = EFixedLimits, .values = &marikoEmcVddqVoltFL}}};

const FixedValues marikoEmcDvbShiftFV = {
    .valuesCount = 4,
    .values = {{.value = 3, .label = "AUTO"}, {.value = 2, .label = "ECO ST1"}, {.value = 1, .label = "ECO ST2"}, {.value = 0, .label = "ECO ST3"}}};
const FixedLimits marikoEmcDvbShiftFL = {.min = 300, .max = 1150, .stepSize = 50, .measure = "mV"};  // TODO ? Step size
// EMB ECO LOGIC
// 3 AUTO
// 2 AUTO ECO ST1
// 1 AUTO ECO ST2
// 0 AUTO ECO ST3
// MANUAL 300-1150 mV
const Param marikoEmcDvbShift = {.name = "EMB ECO LOGIC",
                                 .measure = NULL,
                                 .description = NULL,
                                 .offset = getOffset(defaultCustTable.marikoEmcDvbShift),
                                 .defaultValue = defaultCustTable.marikoEmcDvbShift,
                                 .limitsCount = 2,
                                 .limits = {{.type = EFixedValues, .values = &marikoEmcDvbShiftFV}, {.type = EFixedLimits, .values = &marikoEmcDvbShiftFL}}};

const Params mRAMParams = {.count = 3, .params = {&marikoEmcMaxClock, &marikoEmcVddqVolt, &marikoEmcDvbShift}};
const Tables mRAMTables = {};
