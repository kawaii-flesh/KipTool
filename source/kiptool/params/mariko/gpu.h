#pragma once

#include "../defaultCustomize.h"
#include "../param.h"
#include "../table.h"

const FixedValues GPUvFV = {
    .valuesCount = 3,
    .values = {{.value = 3, .label = "ECO ST1"}, {.value = 2, .label = "ECO ST2"}, {.value = 1, .label = "ECO ST3"}}};
const FixedLimits GPUvFL = {.min = 430, .max = 770, .stepSize = 5, .measure = "mV"};
// GPU UNDER LOGIC
// 3 AUTO ECO ST1
// 2 AUTO ECO ST2
// 1 AUTO ECO ST3
// MANUAL 430-770 mV 5-10mV STEP
const Param GPUv = {.name = "GPU UNDER LOGIC",
                    .category = GPU,
                    .platform = MARIKO,
                    .measure = NULL,
                    .description = NULL,
                    .offset = getOffset(defaultCustTable.GPUv),
                    .length = 4,
                    .defaultValue = defaultCustTable.GPUv,
                    .limitsCount = 2,
                    .limits = {{.type = EFixedValues, .values = &GPUvFV}, {.type = EFixedLimits, .values = &GPUvFL}}};

const FixedValues marikoGpuUVFV = {.valuesCount = 4,
                                   .values = {{.value = 0, .label = "ECO ST1"},
                                              {.value = 1, .label = "ECO ST2"},
                                              {.value = 2, .label = "ECO ST3"},
                                              {.value = 3, .label = "MANUAL"}}};
// GPU ECO LOGIC
// 0 ECO ST1
// 1 ECO ST2
// 2 ECO ST3
// 3 MANUAL ( -75mV << marikoGpuVoltArray ECO ST2 >> +75mV ) STEP 5mV
const Param marikoGpuUV = {.name = "GPU ECO LOGIC ",
                           .category = GPU,
                           .platform = MARIKO,
                           .measure = NULL,
                           .description = NULL,
                           .offset = getOffset(defaultCustTable.marikoGpuUV),
                           .length = 4,
                           .defaultValue = defaultCustTable.marikoGpuUV,
                           .limitsCount = 1,
                           .limits = {{.type = EFixedValues, .values = &marikoGpuUVFV}}};

const FixedLimits marikoGpuVoltArray192mhzFL = {
    .min = defaultCustTable.marikoGpuVoltArray[0] - 75, .max = defaultCustTable.marikoGpuVoltArray[0] + 75, .stepSize = 5};
const Param marikoGpuVoltArray192mhz = {.name = "192mhz",
                                        .category = GPU,
                                        .platform = MARIKO,
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[0]),
                                        .length = 4,
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[0],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray192mhzFL}}};
const FixedLimits marikoGpuVoltArray230mhzFL = {
    .min = defaultCustTable.marikoGpuVoltArray[1] - 75, .max = defaultCustTable.marikoGpuVoltArray[1] + 75, .stepSize = 5};
const Param marikoGpuVoltArray230mhz = {.name = "230mhz",
                                        .category = GPU,
                                        .platform = MARIKO,
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[1]),
                                        .length = 4,
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[1],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray230mhzFL}}};
const FixedLimits marikoGpuVoltArray307mhzFL = {
    .min = defaultCustTable.marikoGpuVoltArray[2] - 75, .max = defaultCustTable.marikoGpuVoltArray[2] + 75, .stepSize = 5};
const Param marikoGpuVoltArray307mhz = {.name = "307mhz",
                                        .category = GPU,
                                        .platform = MARIKO,
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[2]),
                                        .length = 4,
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[2],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray307mhzFL}}};
const FixedLimits marikoGpuVoltArray384mhzFL = {
    .min = defaultCustTable.marikoGpuVoltArray[3] - 75, .max = defaultCustTable.marikoGpuVoltArray[3] + 75, .stepSize = 5};
const Param marikoGpuVoltArray384mhz = {.name = "384mhz",
                                        .category = GPU,
                                        .platform = MARIKO,
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[3]),
                                        .length = 4,
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[3],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray384mhzFL}}};
const FixedLimits marikoGpuVoltArray460mhzFL = {
    .min = defaultCustTable.marikoGpuVoltArray[4] - 75, .max = defaultCustTable.marikoGpuVoltArray[4] + 75, .stepSize = 5};
const Param marikoGpuVoltArray460mhz = {.name = "460mhz",
                                        .category = GPU,
                                        .platform = MARIKO,
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[4]),
                                        .length = 4,
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[4],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray460mhzFL}}};
const FixedLimits marikoGpuVoltArray537mhzFL = {
    .min = defaultCustTable.marikoGpuVoltArray[5] - 75, .max = defaultCustTable.marikoGpuVoltArray[5] + 75, .stepSize = 5};
const Param marikoGpuVoltArray537mhz = {.name = "537mhz",
                                        .category = GPU,
                                        .platform = MARIKO,
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[5]),
                                        .length = 4,
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[5],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray537mhzFL}}};
const FixedLimits marikoGpuVoltArray614mhzFL = {
    .min = defaultCustTable.marikoGpuVoltArray[6] - 75, .max = defaultCustTable.marikoGpuVoltArray[6] + 75, .stepSize = 5};
const Param marikoGpuVoltArray614mhz = {.name = "614mhz",
                                        .category = GPU,
                                        .platform = MARIKO,
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[6]),
                                        .length = 4,
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[6],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray614mhzFL}}};
const FixedLimits marikoGpuVoltArray691mhzFL = {
    .min = defaultCustTable.marikoGpuVoltArray[7] - 75, .max = defaultCustTable.marikoGpuVoltArray[7] + 75, .stepSize = 5};
const Param marikoGpuVoltArray691mhz = {.name = "691mhz",
                                        .category = GPU,
                                        .platform = MARIKO,
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[7]),
                                        .length = 4,
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[7],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray691mhzFL}}};
const FixedLimits marikoGpuVoltArray768mhzFL = {
    .min = defaultCustTable.marikoGpuVoltArray[8] - 75, .max = defaultCustTable.marikoGpuVoltArray[8] + 75, .stepSize = 5};
const Param marikoGpuVoltArray768mhz = {.name = "768mhz",
                                        .category = GPU,
                                        .platform = MARIKO,
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[8]),
                                        .length = 4,
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[8],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray768mhzFL}}};
const FixedLimits marikoGpuVoltArray844mhzFL = {
    .min = defaultCustTable.marikoGpuVoltArray[9] - 75, .max = defaultCustTable.marikoGpuVoltArray[9] + 75, .stepSize = 5};
const Param marikoGpuVoltArray844mhz = {.name = "844mhz",
                                        .category = GPU,
                                        .platform = MARIKO,
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[9]),
                                        .length = 4,
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[9],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray844mhzFL}}};
const FixedLimits marikoGpuVoltArray921mhzFL = {
    .min = defaultCustTable.marikoGpuVoltArray[10] - 75, .max = defaultCustTable.marikoGpuVoltArray[10] + 75, .stepSize = 5};
const Param marikoGpuVoltArray921mhz = {.name = "921mhz",
                                        .category = GPU,
                                        .platform = MARIKO,
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[10]),
                                        .length = 4,
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[10],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray921mhzFL}}};
const FixedLimits marikoGpuVoltArray998mhzFL = {
    .min = defaultCustTable.marikoGpuVoltArray[11] - 75, .max = defaultCustTable.marikoGpuVoltArray[11] + 75, .stepSize = 5};
const Param marikoGpuVoltArray998mhz = {.name = "998mhz",
                                        .category = GPU,
                                        .platform = MARIKO,
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[11]),
                                        .length = 4,
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[11],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray998mhzFL}}};
const FixedLimits marikoGpuVoltArray1075mhzFL = {
    .min = defaultCustTable.marikoGpuVoltArray[12] - 75, .max = defaultCustTable.marikoGpuVoltArray[12] + 75, .stepSize = 5};
const Param marikoGpuVoltArray1075mhz = {.name = "1075mhz",
                                         .category = GPU,
                                         .platform = MARIKO,
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = getOffset(defaultCustTable.marikoGpuVoltArray[12]),
                                         .length = 4,
                                         .defaultValue = defaultCustTable.marikoGpuVoltArray[12],
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray1075mhzFL}}};
const FixedLimits marikoGpuVoltArray1152mhzFL = {
    .min = defaultCustTable.marikoGpuVoltArray[13] - 75, .max = defaultCustTable.marikoGpuVoltArray[13] + 75, .stepSize = 5};
const Param marikoGpuVoltArray1152mhz = {.name = "1152mhz",
                                         .category = GPU,
                                         .platform = MARIKO,
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = getOffset(defaultCustTable.marikoGpuVoltArray[13]),
                                         .length = 4,
                                         .defaultValue = defaultCustTable.marikoGpuVoltArray[13],
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray1152mhzFL}}};
const FixedLimits marikoGpuVoltArray1228mhzFL = {
    .min = defaultCustTable.marikoGpuVoltArray[14] - 75, .max = defaultCustTable.marikoGpuVoltArray[14] + 75, .stepSize = 5};
const Param marikoGpuVoltArray1228mhz = {.name = "1228mhz",
                                         .category = GPU,
                                         .platform = MARIKO,
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = getOffset(defaultCustTable.marikoGpuVoltArray[14]),
                                         .length = 4,
                                         .defaultValue = defaultCustTable.marikoGpuVoltArray[14],
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray1228mhzFL}}};
const FixedLimits marikoGpuVoltArray1305mhzFL = {
    .min = defaultCustTable.marikoGpuVoltArray[15] - 75, .max = defaultCustTable.marikoGpuVoltArray[15] + 75, .stepSize = 5};
const Param marikoGpuVoltArray1305mhz = {.name = "1305mhz",
                                         .category = GPU,
                                         .platform = MARIKO,
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = getOffset(defaultCustTable.marikoGpuVoltArray[15]),
                                         .length = 4,
                                         .defaultValue = defaultCustTable.marikoGpuVoltArray[15],
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray1305mhzFL}}};
const FixedLimits marikoGpuVoltArray1344mhzFL = {
    .min = defaultCustTable.marikoGpuVoltArray[16] - 75, .max = defaultCustTable.marikoGpuVoltArray[16] + 75, .stepSize = 5};
const Param marikoGpuVoltArray1344mhz = {.name = "1344mhz",
                                         .category = GPU,
                                         .platform = MARIKO,
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = getOffset(defaultCustTable.marikoGpuVoltArray[16]),
                                         .length = 4,
                                         .defaultValue = defaultCustTable.marikoGpuVoltArray[16],
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray1344mhzFL}}};
const FixedLimits marikoGpuVoltArray1382mhzFL = {
    .min = defaultCustTable.marikoGpuVoltArray[17] - 75, .max = defaultCustTable.marikoGpuVoltArray[17] + 75, .stepSize = 5};
const Param marikoGpuVoltArray1382mhz = {.name = "1382mhz",
                                         .category = GPU,
                                         .platform = MARIKO,
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = getOffset(defaultCustTable.marikoGpuVoltArray[17]),
                                         .length = 4,
                                         .defaultValue = defaultCustTable.marikoGpuVoltArray[17],
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray1382mhzFL}}};
const FixedLimits marikoGpuVoltArray1420mhzFL = {
    .min = defaultCustTable.marikoGpuVoltArray[18] - 75, .max = defaultCustTable.marikoGpuVoltArray[18] + 75, .stepSize = 5};
const Param marikoGpuVoltArray1420mhz = {.name = "1420mhz",
                                         .category = GPU,
                                         .platform = MARIKO,
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = getOffset(defaultCustTable.marikoGpuVoltArray[18]),
                                         .length = 4,
                                         .defaultValue = defaultCustTable.marikoGpuVoltArray[18],
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray1420mhzFL}}};
const FixedLimits marikoGpuVoltArray1459mhzFL = {
    .min = defaultCustTable.marikoGpuVoltArray[19] - 75, .max = defaultCustTable.marikoGpuVoltArray[19] + 75, .stepSize = 5};
const Param marikoGpuVoltArray1459mhz = {.name = "1459mhz",
                                         .category = GPU,
                                         .platform = MARIKO,
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = getOffset(defaultCustTable.marikoGpuVoltArray[19]),
                                         .length = 4,
                                         .defaultValue = defaultCustTable.marikoGpuVoltArray[19],
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray1459mhzFL}}};
const FixedLimits marikoGpuVoltArray1497mhzFL = {
    .min = defaultCustTable.marikoGpuVoltArray[20] - 75, .max = defaultCustTable.marikoGpuVoltArray[20] + 75, .stepSize = 5};
const Param marikoGpuVoltArray1497mhz = {.name = "1497mhz",
                                         .category = GPU,
                                         .platform = MARIKO,
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = getOffset(defaultCustTable.marikoGpuVoltArray[20]),
                                         .length = 4,
                                         .defaultValue = defaultCustTable.marikoGpuVoltArray[20],
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray1497mhzFL}}};
const FixedLimits marikoGpuVoltArray1536mhzFL = {
    .min = defaultCustTable.marikoGpuVoltArray[21] - 75, .max = defaultCustTable.marikoGpuVoltArray[21] + 75, .stepSize = 5};
const Param marikoGpuVoltArray1536mhz = {.name = "1536mhz",
                                         .category = GPU,
                                         .platform = MARIKO,
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = getOffset(defaultCustTable.marikoGpuVoltArray[21]),
                                         .length = 4,
                                         .defaultValue = defaultCustTable.marikoGpuVoltArray[21],
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray1536mhzFL}}};
const FixedLimits marikoGpuVoltArray1574mhzFL = {
    .min = defaultCustTable.marikoGpuVoltArray[22] - 75, .max = defaultCustTable.marikoGpuVoltArray[22] + 75, .stepSize = 5};
const Param marikoGpuVoltArray1574mhz = {.name = "1574mhz",
                                         .category = GPU,
                                         .platform = MARIKO,
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = getOffset(defaultCustTable.marikoGpuVoltArray[22]),
                                         .length = 4,
                                         .defaultValue = defaultCustTable.marikoGpuVoltArray[22],
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray1574mhzFL}}};
const FixedLimits marikoGpuVoltArray1612mhzFL = {
    .min = defaultCustTable.marikoGpuVoltArray[23] - 75, .max = defaultCustTable.marikoGpuVoltArray[23] + 75, .stepSize = 5};
const Param marikoGpuVoltArray1612mhz = {.name = "1612mhz",
                                         .category = GPU,
                                         .platform = MARIKO,
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = getOffset(defaultCustTable.marikoGpuVoltArray[23]),
                                         .length = 4,
                                         .defaultValue = defaultCustTable.marikoGpuVoltArray[23],
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray1612mhzFL}}};

const Table marikoGpuVoltArray = {
    .name = "GPU Volt Table",
    .description = NULL,
    .baseOffset = getOffset(defaultCustTable.marikoGpuVoltArray),
    .paramsCount = 24,
    .params = {&marikoGpuVoltArray192mhz,  &marikoGpuVoltArray230mhz,  &marikoGpuVoltArray307mhz,  &marikoGpuVoltArray384mhz,
               &marikoGpuVoltArray460mhz,  &marikoGpuVoltArray537mhz,  &marikoGpuVoltArray614mhz,  &marikoGpuVoltArray691mhz,
               &marikoGpuVoltArray768mhz,  &marikoGpuVoltArray844mhz,  &marikoGpuVoltArray921mhz,  &marikoGpuVoltArray998mhz,
               &marikoGpuVoltArray1075mhz, &marikoGpuVoltArray1152mhz, &marikoGpuVoltArray1228mhz, &marikoGpuVoltArray1305mhz,
               &marikoGpuVoltArray1344mhz, &marikoGpuVoltArray1382mhz, &marikoGpuVoltArray1420mhz, &marikoGpuVoltArray1459mhz,
               &marikoGpuVoltArray1497mhz, &marikoGpuVoltArray1536mhz, &marikoGpuVoltArray1574mhz, &marikoGpuVoltArray1612mhz}};

const FixedValues hGPUvFV = {.valuesCount = 3,
                             .values = {{.value = 1000, .label = "ECO"}, {.value = 1050}, {.value = 1100, .label = "SRT"}}};
const FixedLimits hGPUvFL = {.min = 750, .max = 1200, .stepSize = 50};
// MARIKO GPU OVER MODE
// 1000 4IFIR ECO
// 1050 DEFAULT
// 1100 4IFIR SRT
// MANUAL 750-1200
const Param hGPUv = {.name = "GPU OVER MODE",
                     .measure = "mV",
                     .description = NULL,
                     .offset = getOffset(defaultCustTable.hGPUv),
                     .length = 4,
                     .defaultValue = defaultCustTable.hGPUv,
                     .limitsCount = 2,
                     .limits = {{.type = EFixedValues, .values = &hGPUvFV}, {.type = EFixedLimits, .values = &hGPUvFL}}};

const Params mGPUParams = {.count = 3, .params = {&GPUv, &marikoGpuUV, &hGPUv}};
const Tables mGPUTables = {.count = 1, .tables = {&marikoGpuVoltArray}};