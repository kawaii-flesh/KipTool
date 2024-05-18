#pragma once

#include "../defaultCustomize.h"
#include "../param.h"
#include "../table.h"

const FixedValues commonCpuBoostClockFV = {.valuesCount = 6,
                                           .values = {{.value = eBAMATIC, .label = "eBAMATIC", .measure = ""},
                                                      {.value = 1428000, .label = "CPU-HI uV DEBUG"},
                                                      {.value = 1785000, .label = "CPU-LOW uV DEBUG"},
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
const Param commonCpuBoostClock = {.name = "CPU LAUNCH CONTROL TARGET",
                                   .measure = "MHz",
                                   .description = NULL,
                                   .offset = getOffset(defaultCustTable.commonCpuBoostClock),
                                   .defaultValue = defaultCustTable.commonCpuBoostClock,
                                   .limitsCount = 2,
                                   .limits = {{.type = EFixedValues, .values = &commonCpuBoostClockFV}, {.type = EFixedLimits, .values = &commonCpuBoostClockFL}}};

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
                          .description = NULL,
                          .offset = getOffset(defaultCustTable.SpeedShift),
                          .defaultValue = defaultCustTable.SpeedShift,
                          .limitsCount = 2,
                          .limits = {{.type = EFixedValues, .values = &SpeedShiftFV}, {.type = EFixedLimits, .values = &SpeedShiftFL}}};

const FixedValues marikoCpuHUVFV = {.valuesCount = 9,
                                    .values = {
                                        {.value = eBAMATIC, .label = "eBAMATIC"},
                                        {.value = 1, .label = "ECO ST1"},
                                        {.value = 2},
                                        {.value = 3, .label = "ECO ST2"},
                                        {.value = 4},
                                        {.value = 5, .label = "ECO ST3"},
                                        {.value = 6},
                                        {.value = 7},
                                        {.value = 8},
                                    }};
// MARIKO CPU-HI ECO LOGIC
// eBAMATIC
// 1 AUTO ECO ST1
// 3 AUTO ECO ST2
// 5 AUTO ECO ST3
// 1-8 MANUAL
const Param marikoCpuHUV = {.name = "CPU-HI ECO LOGIC",
                            .measure = NULL,
                            .description = NULL,
                            .offset = getOffset(defaultCustTable.marikoCpuHUV),
                            .defaultValue = defaultCustTable.marikoCpuHUV,
                            .limitsCount = 1,
                            .limits = {{.type = EFixedValues, .values = &marikoCpuHUVFV}}};

const FixedValues marikoCpuMaxVoltFV = {.valuesCount = 5,
                                        .values = {{.value = eBAMATIC, .label = "eBAMATIC", .measure = ""},
                                                   {.value = 1150, .label = "ECO"},
                                                   {.value = 1180, .label = "STAGE 1"},
                                                   {.value = 1215, .label = "STAGE 2"},
                                                   {.value = 1250, .label = "STAGE 3"}}};
const FixedLimits marikoCpuMaxVoltFL = {.min = 1130, .max = 1375, .stepSize = 5};
// MARIKO CPU VMAX MODE
// 1150 ECO
// 1180-1250 STAGE 1-3 STEP 35mV
// MANUAL 1130-1375 STEP 5mV
const Param marikoCpuMaxVolt = {.name = "CPU VMAX MODE",
                                .measure = "mV",
                                .description = NULL,
                                .offset = getOffset(defaultCustTable.marikoCpuMaxVolt),
                                .defaultValue = defaultCustTable.marikoCpuMaxVolt,
                                .limitsCount = 2,
                                .limits = {{.type = EFixedValues, .values = &marikoCpuMaxVoltFV}, {.type = EFixedLimits, .values = &marikoCpuMaxVoltFL}}};

const FixedValues marikoCpuUVFV = {.valuesCount = 7,
                                   .values = {{.value = 0, .label = "ECO ALT-MODE"},
                                              {.value = 1, .label = "ECO ST1"},
                                              {.value = 2},
                                              {.value = 3, .label = "ECO ST2"},
                                              {.value = 4},
                                              {.value = 5, .label = "ECO ST3"},
                                              {.value = 6}}};
// CPU-LOW ECO LOGIC
// 0 ECO ALT-MODE
// 1 AUTO ECO ST1
// 3 AUTO ECO ST2
// 5 AUTO ECO ST3
// MANUAL 1-6
const Param marikoCpuUV = {.name = "CPU-LOW ECO LOGIC",
                           .measure = NULL,
                           .description = NULL,
                           .offset = getOffset(defaultCustTable.marikoCpuUV),
                           .defaultValue = defaultCustTable.marikoCpuUV,
                           .limitsCount = 1,
                           .limits = {{.type = EFixedValues, .values = &marikoCpuUVFV}}};

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
const Param dCPUv = {.name = "CPU MIN-HIGH LOGIC",
                     .measure = NULL,
                     .description = NULL,
                     .offset = getOffset(defaultCustTable.dCPUv),
                     .defaultValue = defaultCustTable.dCPUv,
                     .limitsCount = 2,
                     .limits = {{.type = EFixedValues, .values = &dCPUvFV}, {.type = EFixedLimits, .values = &dCPUvFL}}};

const Params mCPUParams = {.count = 6, .params = {&commonCpuBoostClock, &SpeedShift, &marikoCpuMaxVolt, &marikoCpuUV, &dCPUv, &marikoCpuHUV}};
const Tables mCPUTables = {};
