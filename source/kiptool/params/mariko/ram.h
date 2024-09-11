#pragma once

#include "../defaultCustomize.h"
#include "../param.h"
#include "../table.h"

const FixedValues marikoEmcMaxClockFV = {.valuesCount = 11,
                                         .values = {{.value = 1600000, .label = "S_LOH"},
                                                    {.value = 1734400, .label = "E_ST3"},
                                                    {.value = 1868800, .label = "E_ST2"},
                                                    {.value = 1996800, .label = "E_ST1"},
                                                    {.value = 2131200, .label = "D_ST1"},
                                                    {.value = 2265600, .label = "D_ST2"},
                                                    {.value = 2400000, .label = "D_ST3"},
                                                    {.value = 2534400, .label = "S_ST1"},
                                                    {.value = 2665600, .label = "S_ST2"},
                                                    {.value = 2800000, .label = "S_ST3"},
                                                    {.value = 2934400, .label = "L_C4C"}}};
const FixedLimits marikoEmcMaxClockFL = {.min = 1333000, .max = 2733000, .stepSize = 200};  // STEP GCD
// 4IFIR MODE ON MARIKO / VDQ / eBL1 / eBL2 / eBL3 / eBL4 / eBL5 /
// S_LOH 1600 / 1600000 / 500 / 1350 / 1200 / 1050	  900		 /
// E_ST3 1733 / 1734400 / 525 / 1400 / 1250 / 1100	  950	     /
// E_ST2 1866 / 1868800 / 550 / 	 / 1300 / 1150	 1000	     /
// E_ST1 2000 / 1996800 / 575 / 	 / 1350 / 1200	 1050	 900 /
// D_ST1 2133 / 2131200 / 600 / 	 / 1400 / 1250 / 1100    950 /
// D_ST2 2266 / 2265600 / 625 / 	   	    / 1300 / 1150   1000 /
// D_ST3 2400 / 2400000 / 650 / 	   		/ 1350 / 1200 / 1050 /
// S_ST1 2533 / 2534400 / 675 / 	  		/ 1400 / 1250 / 1100 /
// S_ST2 2666 / 2665600 / 700 / 	  			   / 1300 / 1150 /
// S_ST3 2800 / 2800000 / 725 / 	   	  		   / 1350 / 1200 /
// L_C4C 2933 / 2934400 / 750 / 	   	  		   / 1400 / 1250 /
// MICRON E/H eBAL 4 < 3.8GHz
// SAMSUNG B eBAL 4 < 3.9GHz
// HYNIX CJR/DJR eBAL 4 < 3.8GHz
// MANUAL 1333000-2733000 STEP 38.4MHz
const Param marikoEmcMaxClock = {.name = "EMC Max Clock",
                                 .measure = "MHz",
                                 .offset = getOffset(defaultCustTable.marikoEmcMaxClock),
                                 .defaultValue = defaultCustTable.marikoEmcMaxClock,
                                 .limitsCount = 2,
                                 .limits = {{.type = EFixedValues, .values = &marikoEmcMaxClockFV}, {.type = EFixedLimits, .values = &marikoEmcMaxClockFL}}};

const FixedValues marikoEmcVddqVoltFV = {.valuesCount = 3, .values = {{.value = 500000, .label = "ECO"}, {.value = 650000}, {.value = 700000, .label = "SRT"}}};
const FixedLimits marikoEmcVddqVoltFL = {.min = 300000, .max = 800000, .stepSize = 10000};
// RAM VDDQ MODE
// 500'000 ECO
// 650'000 DEFAULT
// 700'000 SRT
// MANUAL 300'000-800'000 STEP 10'000
const Param marikoEmcVddqVolt = {.name = "VDDQ MODE",
                                 .measure = "mV",
                                 .offset = getOffset(defaultCustTable.marikoEmcVddqVolt),
                                 .defaultValue = defaultCustTable.marikoEmcVddqVolt,
                                 .limitsCount = 2,
                                 .limits = {{.type = EFixedValues, .values = &marikoEmcVddqVoltFV}, {.type = EFixedLimits, .values = &marikoEmcVddqVoltFL}}};

const FixedValues marikoEmcDvbShiftFV = {
    .valuesCount = 4,
    .values = {{.value = eBAMATIC, .label = "eBAMATIC"}, {.value = 3, .label = "ECO ST1"}, {.value = 2, .label = "ECO ST2"}, {.value = 1, .label = "ECO ST3"}}};
const FixedLimits marikoEmcDvbShiftFL = {.min = 600, .max = 1150, .stepSize = 50, .measure = "mV"};  // TODO ? Step size
// EMB ECO LOGIC
// eBAMATIC
// 1 AUTO ECO ST3
// 2 AUTO ECO ST2
// 3 AUTO ECO ST1
// 600-1150 MANUAL mV
const Param marikoEmcDvbShift = {.name = "EMB ECO LOGIC",
                                 .measure = NULL,
                                 .offset = getOffset(defaultCustTable.marikoEmcDvbShift),
                                 .defaultValue = defaultCustTable.marikoEmcDvbShift,
                                 .limitsCount = 2,
                                 .limits = {{.type = EFixedValues, .values = &marikoEmcDvbShiftFV}, {.type = EFixedLimits, .values = &marikoEmcDvbShiftFL}}};

const Params mRAMParams = {.count = 3, .params = {&marikoEmcMaxClock, &marikoEmcVddqVolt, &marikoEmcDvbShift}};
const Tables mRAMTables = {};
