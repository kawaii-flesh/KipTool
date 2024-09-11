#pragma once

#include "../defaultCustomize.h"
#include "../param.h"
#include "../table.h"

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
const Param marikoCpuHUV = {.name = "HI ECO LOGIC",
                            .measure = NULL,
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
const Param marikoCpuMaxVolt = {.name = "VMAX MODE",
                                .measure = "mV",
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
const Param marikoCpuUV = {.name = "LOW ECO LOGIC",
                           .measure = NULL,
                           .offset = getOffset(defaultCustTable.marikoCpuUV),
                           .defaultValue = defaultCustTable.marikoCpuUV,
                           .limitsCount = 1,
                           .limits = {{.type = EFixedValues, .values = &marikoCpuUVFV}}};

const Params mCPUParams = {.count = 3, .params = {&marikoCpuMaxVolt, &marikoCpuUV, &marikoCpuHUV}};
const Tables mCPUTables = {};
