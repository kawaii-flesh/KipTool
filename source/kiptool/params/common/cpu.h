#pragma once

#include "../defaultCustomize.h"
#include "../param.h"
#include "../table.h"

const FixedValues commonCpuBoostClockFV = {.valuesCount = 6,
                                           .values = {{.value = eBAMATIC, .label = "eBAMATIC", .measure = ""},
                                                      {.value = 1428000, .label = "HI uV DBG"},
                                                      {.value = 1785000, .label = "LOW uV DBG"},
                                                      {.value = 2000000, .label = "E"},
                                                      {.value = 2500000, .label = "D"},
                                                      {.value = 3000000, .label = "S"}}};
const FixedLimits commonCpuBoostClockFL = {.min = 1400000, .max = 3000000, .stepSize = 1000};  // STEP GCD
// CPU LAUNCH CONTROL TARGET
// 1428000 CPU-HI uV DEBUG
// 1785000 CPU-LOW uV DEBUG
// 2000000 E
// 2500000 D
// 3000000 S
// MANUAL 1400000-3000000 STEP 100000
// eBAMATIC
const Param commonCpuBoostClock = {.name = "LAUNCH CONTROL TARGET",
                                   .measure = "MHz",
                                   .offset = getOffset(defaultCustTable.commonCpuBoostClock),
                                   .defaultValue = defaultCustTable.commonCpuBoostClock,
                                   .limitsCount = 2,
                                   .limits = {{.type = EFixedValues, .values = &commonCpuBoostClockFV}, {.type = EFixedLimits, .values = &commonCpuBoostClockFL}}};

const FixedValues CPUvFV = {
    .valuesCount = 4,
    .values = {{.value = 620, .measure = "mV"}, {.value = 3, .label = "ECO ST1"}, {.value = 2, .label = "ECO ST2"}, {.value = 1, .label = "ECO ST3"}}};
const FixedLimits CPUvFL = {.min = 430, .max = 670, .stepSize = 5, .measure = "mV"};
// CPU UNDER LOGIC
// 3 AUTO ECO ST1
// 2 AUTO ECO ST2
// 1 AUTO ECO ST3
// MANUAL 430-670 STEP 5-10mV
// 620mV DEFAULT
// MARIKO CPU VOLT MIN = CPUv
// ERISTA CPU VOLT MIN = CPUv + 205mV
const Param CPUv = {.name = "UNDER LOGIC",
                    .measure = NULL,
                    .offset = getOffset(defaultCustTable.CPUv),
                    .defaultValue = defaultCustTable.CPUv,
                    .limitsCount = 2,
                    .limits = {{.type = EFixedValues, .values = &CPUvFV}, {.type = EFixedLimits, .values = &CPUvFL}}};

const FixedValues dCPUvFV = {
    .valuesCount = 4,
    .values = {{.value = eBAMATIC, .label = "eBAMATIC"}, {.value = 1, .label = "ECO ST1"}, {.value = 2, .label = "ECO ST2"}, {.value = 3, .label = "ECO ST3"}}};
const FixedLimits dCPUvFL = {.min = 750, .max = 850, .stepSize = 5, .measure = "mV"};
// MARIKO CPU MIN-HIGH LOGIC
// eBAMATIC
// 1 AUTO ECO ST1
// 2 AUTO ECO ST2
// 3 AUTO ECO ST3
// MANUAL 750-850
const Param dCPUv = {.name = "MIN-HIGH LOGIC",
                     .measure = NULL,
                     .offset = getOffset(defaultCustTable.dCPUv),
                     .defaultValue = defaultCustTable.dCPUv,
                     .limitsCount = 2,
                     .limits = {{.type = EFixedValues, .values = &dCPUvFV}, {.type = EFixedLimits, .values = &dCPUvFL}}};

const FixedValues SpeedShiftFV = {.valuesCount = 6,
                                  .values = {
                                      {.value = eBAMATIC, .label = "eBAMATIC"},
                                      {.value = 1, .label = "AUTO"},
                                      {.value = 50, .label = "SRT ST1"},
                                      {.value = 100, .label = "ECO ST1"},
                                      {.value = 125, .label = "ECO ST2"},
                                      {.value = 150, .label = "ECO ST3"},
                                  }};
const FixedLimits SpeedShiftFL = {.min = 25, .max = 175, .stepSize = 25};
// SPEEDSHIFT ECO LOGIC
// eBAMATIC
// 1 DEFAULT
// 50 SRT ST1
// 100 ECO ST1
// 125 ECO ST2
// 150 ECO ST3
// 25-175 MANUAL
// Ov << 100 >> uV
const Param SpeedShift = {.name = "SPEEDSHIFT",
                          .measure = NULL,
                          .offset = getOffset(defaultCustTable.SpeedShift),
                          .defaultValue = defaultCustTable.SpeedShift,
                          .limitsCount = 2,
                          .limits = {{.type = EFixedValues, .values = &SpeedShiftFV}, {.type = EFixedLimits, .values = &SpeedShiftFL}}};

const Params cCPUParams = {.count = 4, .params = {&commonCpuBoostClock, &CPUv, &dCPUv, &SpeedShift}};
const Tables cCPUTables = {};
