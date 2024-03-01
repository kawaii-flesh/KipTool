#pragma once

#include "../customize.h"
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
                    .offset = getOffset(custTable.GPUv),
                    .length = 4,
                    .defaultValue = custTable.GPUv,
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
                           .offset = getOffset(custTable.marikoGpuUV),
                           .length = 4,
                           .defaultValue = custTable.marikoGpuUV,
                           .limitsCount = 1,
                           .limits = {{.type = EFixedValues, .values = &marikoGpuUVFV}}};

const FixedOneValue marikoGpuVoltArray192mhzFOV = {.value = custTable.marikoGpuVoltArray[0]};
const Param marikoGpuVoltArray192mhz = {.name = "192mhz",
                                        .category = GPU,
                                        .platform = MARIKO,
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = 0,
                                        .length = 4,
                                        .defaultValue = custTable.marikoGpuVoltArray[0],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedOneValue, .values = &marikoGpuVoltArray192mhzFOV}}};
const FixedOneValue marikoGpuVoltArray230mhzFOV = {.value = custTable.marikoGpuVoltArray[1]};
const Param marikoGpuVoltArray230mhz = {.name = "230mhz",
                                        .category = GPU,
                                        .platform = MARIKO,
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = 1,
                                        .length = 4,
                                        .defaultValue = custTable.marikoGpuVoltArray[1],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedOneValue, .values = &marikoGpuVoltArray230mhzFOV}}};
const FixedOneValue marikoGpuVoltArray307mhzFOV = {.value = custTable.marikoGpuVoltArray[2]};
const Param marikoGpuVoltArray307mhz = {.name = "307mhz",
                                        .category = GPU,
                                        .platform = MARIKO,
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = 2,
                                        .length = 4,
                                        .defaultValue = custTable.marikoGpuVoltArray[2],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedOneValue, .values = &marikoGpuVoltArray307mhzFOV}}};
const FixedOneValue marikoGpuVoltArray384mhzFOV = {.value = custTable.marikoGpuVoltArray[3]};
const Param marikoGpuVoltArray384mhz = {.name = "384mhz",
                                        .category = GPU,
                                        .platform = MARIKO,
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = 3,
                                        .length = 4,
                                        .defaultValue = custTable.marikoGpuVoltArray[3],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedOneValue, .values = &marikoGpuVoltArray384mhzFOV}}};
const FixedOneValue marikoGpuVoltArray460mhzFOV = {.value = custTable.marikoGpuVoltArray[4]};
const Param marikoGpuVoltArray460mhz = {.name = "460mhz",
                                        .category = GPU,
                                        .platform = MARIKO,
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = 4,
                                        .length = 4,
                                        .defaultValue = custTable.marikoGpuVoltArray[4],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedOneValue, .values = &marikoGpuVoltArray460mhzFOV}}};
const FixedOneValue marikoGpuVoltArray537mhzFOV = {.value = custTable.marikoGpuVoltArray[5]};
const Param marikoGpuVoltArray537mhz = {.name = "537mhz",
                                        .category = GPU,
                                        .platform = MARIKO,
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = 5,
                                        .length = 4,
                                        .defaultValue = custTable.marikoGpuVoltArray[5],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedOneValue, .values = &marikoGpuVoltArray537mhzFOV}}};
const FixedOneValue marikoGpuVoltArray614mhzFOV = {.value = custTable.marikoGpuVoltArray[6]};
const Param marikoGpuVoltArray614mhz = {.name = "614mhz",
                                        .category = GPU,
                                        .platform = MARIKO,
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = 6,
                                        .length = 4,
                                        .defaultValue = custTable.marikoGpuVoltArray[6],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedOneValue, .values = &marikoGpuVoltArray614mhzFOV}}};
const FixedOneValue marikoGpuVoltArray691mhzFOV = {.value = custTable.marikoGpuVoltArray[7]};
const Param marikoGpuVoltArray691mhz = {.name = "691mhz",
                                        .category = GPU,
                                        .platform = MARIKO,
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = 7,
                                        .length = 4,
                                        .defaultValue = custTable.marikoGpuVoltArray[7],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedOneValue, .values = &marikoGpuVoltArray691mhzFOV}}};
const FixedOneValue marikoGpuVoltArray768mhzFOV = {.value = custTable.marikoGpuVoltArray[8]};
const Param marikoGpuVoltArray768mhz = {.name = "768mhz",
                                        .category = GPU,
                                        .platform = MARIKO,
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = 8,
                                        .length = 4,
                                        .defaultValue = custTable.marikoGpuVoltArray[8],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedOneValue, .values = &marikoGpuVoltArray768mhzFOV}}};
const FixedOneValue marikoGpuVoltArray844mhzFOV = {.value = custTable.marikoGpuVoltArray[9]};
const Param marikoGpuVoltArray844mhz = {.name = "844mhz",
                                        .category = GPU,
                                        .platform = MARIKO,
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = 9,
                                        .length = 4,
                                        .defaultValue = custTable.marikoGpuVoltArray[9],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedOneValue, .values = &marikoGpuVoltArray844mhzFOV}}};
const FixedOneValue marikoGpuVoltArray921mhzFOV = {.value = custTable.marikoGpuVoltArray[10]};
const Param marikoGpuVoltArray921mhz = {.name = "921mhz",
                                        .category = GPU,
                                        .platform = MARIKO,
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = 10,
                                        .length = 4,
                                        .defaultValue = custTable.marikoGpuVoltArray[10],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedOneValue, .values = &marikoGpuVoltArray921mhzFOV}}};
const FixedOneValue marikoGpuVoltArray998mhzFOV = {.value = custTable.marikoGpuVoltArray[11]};
const Param marikoGpuVoltArray998mhz = {.name = "998mhz",
                                        .category = GPU,
                                        .platform = MARIKO,
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = 11,
                                        .length = 4,
                                        .defaultValue = custTable.marikoGpuVoltArray[11],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedOneValue, .values = &marikoGpuVoltArray998mhzFOV}}};
const FixedOneValue marikoGpuVoltArray1075mhzFOV = {.value = custTable.marikoGpuVoltArray[12]};
const Param marikoGpuVoltArray1075mhz = {.name = "1075mhz",
                                         .category = GPU,
                                         .platform = MARIKO,
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = 12,
                                         .length = 4,
                                         .defaultValue = custTable.marikoGpuVoltArray[12],
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedOneValue, .values = &marikoGpuVoltArray1075mhzFOV}}};
const FixedOneValue marikoGpuVoltArray1152mhzFOV = {.value = custTable.marikoGpuVoltArray[13]};
const Param marikoGpuVoltArray1152mhz = {.name = "1152mhz",
                                         .category = GPU,
                                         .platform = MARIKO,
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = 13,
                                         .length = 4,
                                         .defaultValue = custTable.marikoGpuVoltArray[13],
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedOneValue, .values = &marikoGpuVoltArray1152mhzFOV}}};
const FixedOneValue marikoGpuVoltArray1228mhzFOV = {.value = custTable.marikoGpuVoltArray[14]};
const Param marikoGpuVoltArray1228mhz = {.name = "1228mhz",
                                         .category = GPU,
                                         .platform = MARIKO,
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = 14,
                                         .length = 4,
                                         .defaultValue = custTable.marikoGpuVoltArray[14],
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedOneValue, .values = &marikoGpuVoltArray1228mhzFOV}}};
const FixedOneValue marikoGpuVoltArray1305mhzFOV = {.value = custTable.marikoGpuVoltArray[15]};
const Param marikoGpuVoltArray1305mhz = {.name = "1305mhz",
                                         .category = GPU,
                                         .platform = MARIKO,
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = 15,
                                         .length = 4,
                                         .defaultValue = custTable.marikoGpuVoltArray[15],
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedOneValue, .values = &marikoGpuVoltArray1305mhzFOV}}};
const FixedOneValue marikoGpuVoltArray1344mhzFOV = {.value = custTable.marikoGpuVoltArray[16]};
const Param marikoGpuVoltArray1344mhz = {.name = "1344mhz",
                                         .category = GPU,
                                         .platform = MARIKO,
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = 16,
                                         .length = 4,
                                         .defaultValue = custTable.marikoGpuVoltArray[16],
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedOneValue, .values = &marikoGpuVoltArray1344mhzFOV}}};
const FixedOneValue marikoGpuVoltArray1382mhzFOV = {.value = custTable.marikoGpuVoltArray[17]};
const Param marikoGpuVoltArray1382mhz = {.name = "1382mhz",
                                         .category = GPU,
                                         .platform = MARIKO,
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = 17,
                                         .length = 4,
                                         .defaultValue = custTable.marikoGpuVoltArray[17],
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedOneValue, .values = &marikoGpuVoltArray1382mhzFOV}}};
const FixedOneValue marikoGpuVoltArray1420mhzFOV = {.value = custTable.marikoGpuVoltArray[18]};
const Param marikoGpuVoltArray1420mhz = {.name = "1420mhz",
                                         .category = GPU,
                                         .platform = MARIKO,
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = 18,
                                         .length = 4,
                                         .defaultValue = custTable.marikoGpuVoltArray[18],
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedOneValue, .values = &marikoGpuVoltArray1420mhzFOV}}};
const FixedOneValue marikoGpuVoltArray1459mhzFOV = {.value = custTable.marikoGpuVoltArray[19]};
const Param marikoGpuVoltArray1459mhz = {.name = "1459mhz",
                                         .category = GPU,
                                         .platform = MARIKO,
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = 19,
                                         .length = 4,
                                         .defaultValue = custTable.marikoGpuVoltArray[19],
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedOneValue, .values = &marikoGpuVoltArray1459mhzFOV}}};
const FixedOneValue marikoGpuVoltArray1497mhzFOV = {.value = custTable.marikoGpuVoltArray[20]};
const Param marikoGpuVoltArray1497mhz = {.name = "1497mhz",
                                         .category = GPU,
                                         .platform = MARIKO,
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = 20,
                                         .length = 4,
                                         .defaultValue = custTable.marikoGpuVoltArray[20],
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedOneValue, .values = &marikoGpuVoltArray1497mhzFOV}}};
const FixedOneValue marikoGpuVoltArray1536mhzFOV = {.value = custTable.marikoGpuVoltArray[21]};
const Param marikoGpuVoltArray1536mhz = {.name = "1536mhz",
                                         .category = GPU,
                                         .platform = MARIKO,
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = 21,
                                         .length = 4,
                                         .defaultValue = custTable.marikoGpuVoltArray[21],
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedOneValue, .values = &marikoGpuVoltArray1536mhzFOV}}};
const FixedOneValue marikoGpuVoltArray1574mhzFOV = {.value = custTable.marikoGpuVoltArray[22]};
const Param marikoGpuVoltArray1574mhz = {.name = "1574mhz",
                                         .category = GPU,
                                         .platform = MARIKO,
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = 22,
                                         .length = 4,
                                         .defaultValue = custTable.marikoGpuVoltArray[22],
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedOneValue, .values = &marikoGpuVoltArray1574mhzFOV}}};
const FixedOneValue marikoGpuVoltArray1612mhzFOV = {.value = custTable.marikoGpuVoltArray[23]};
const Param marikoGpuVoltArray1612mhz = {.name = "1612mhz",
                                         .category = GPU,
                                         .platform = MARIKO,
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = 23,
                                         .length = 4,
                                         .defaultValue = custTable.marikoGpuVoltArray[23],
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedOneValue, .values = &marikoGpuVoltArray1612mhzFOV}}};

const Table marikoGpuVoltArray = {
    .baseOffset = getOffset(custTable.marikoGpuVoltArray),
    .increment = 4,
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
                     .offset = getOffset(custTable.hGPUv),
                     .length = 4,
                     .defaultValue = custTable.hGPUv,
                     .limitsCount = 2,
                     .limits = {{.type = EFixedValues, .values = &hGPUvFV}, {.type = EFixedLimits, .values = &hGPUvFL}}};

const unsigned int mGPUParamsCount = 3;
const Param *mGPUParams[] = {&GPUv, &marikoGpuUV, &hGPUv};
const unsigned int mGPUTablesCount = 1;
const Table *mGPUTables[] = {&marikoGpuVoltArray};