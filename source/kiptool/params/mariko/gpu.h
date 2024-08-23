#pragma once

#include "../defaultCustomize.h"
#include "../param.h"
#include "../table.h"

const FixedValues marikoGpuUVFV = {
    .valuesCount = 4,
    .values = {{.value = 0, .label = "ECO ST1"}, {.value = 1, .label = "ECO ST2"}, {.value = 2, .label = "ECO ST3"}, {.value = 3, .label = "MANUAL"}}};
// GPU ECO LOGIC
// 0 AUTO ECO ST1
// 1 AUTO ECO ST2
// 2 AUTO ECO ST3
// 3 MANUAL ( -75mV << marikoGpuVoltArray ECO ST2 >> +75mV ) 5mV STEP
const Param marikoGpuUV = {.name = "ECO LOGIC",
                           .measure = NULL,
                           .description = NULL,
                           .offset = getOffset(defaultCustTable.marikoGpuUV),
                           .defaultValue = defaultCustTable.marikoGpuUV,
                           .limitsCount = 1,
                           .limits = {{.type = EFixedValues, .values = &marikoGpuUVFV}}};

const FixedLimits marikoGpuVoltArray307mhzFL = {.min = 150, .max = defaultCustTable.marikoGpuVoltArray[0] + 75, .stepSize = 5};
const Param marikoGpuVoltArray307mhz = {.name = "307mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[0]),
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[0],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray307mhzFL}}};
const FixedLimits marikoGpuVoltArray345mhzFL = {.min = 150, .max = defaultCustTable.marikoGpuVoltArray[1] + 75, .stepSize = 5};
const Param marikoGpuVoltArray345mhz = {.name = "345mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[1]),
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[1],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray345mhzFL}}};
const FixedLimits marikoGpuVoltArray384mhzFL = {.min = 150, .max = defaultCustTable.marikoGpuVoltArray[2] + 75, .stepSize = 5};
const Param marikoGpuVoltArray384mhz = {.name = "384mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[2]),
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[2],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray384mhzFL}}};
const FixedLimits marikoGpuVoltArray422mhzFL = {.min = 150, .max = defaultCustTable.marikoGpuVoltArray[3] + 75, .stepSize = 5};
const Param marikoGpuVoltArray422mhz = {.name = "422mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[3]),
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[3],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray422mhzFL}}};
const FixedLimits marikoGpuVoltArray460mhzFL = {.min = 150, .max = defaultCustTable.marikoGpuVoltArray[4] + 75, .stepSize = 5};
const Param marikoGpuVoltArray460mhz = {.name = "460mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[4]),
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[4],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray460mhzFL}}};
const FixedLimits marikoGpuVoltArray499mhzFL = {.min = 200, .max = defaultCustTable.marikoGpuVoltArray[5] + 75, .stepSize = 5};
const Param marikoGpuVoltArray499mhz = {.name = "499mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[5]),
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[5],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray499mhzFL}}};
const FixedLimits marikoGpuVoltArray537mhzFL = {.min = 200, .max = defaultCustTable.marikoGpuVoltArray[6] + 75, .stepSize = 5};
const Param marikoGpuVoltArray537mhz = {.name = "537mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[6]),
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[6],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray537mhzFL}}};
const FixedLimits marikoGpuVoltArray576mhzFL = {.min = 200, .max = defaultCustTable.marikoGpuVoltArray[7] + 75, .stepSize = 5};
const Param marikoGpuVoltArray576mhz = {.name = "576mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[7]),
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[7],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray576mhzFL}}};
const FixedLimits marikoGpuVoltArray614mhzFL = {.min = 200, .max = defaultCustTable.marikoGpuVoltArray[8] + 75, .stepSize = 5};
const Param marikoGpuVoltArray614mhz = {.name = "614mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[8]),
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[8],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray614mhzFL}}};
const FixedLimits marikoGpuVoltArray652mhzFL = {.min = 200, .max = defaultCustTable.marikoGpuVoltArray[9] + 75, .stepSize = 5};
const Param marikoGpuVoltArray652mhz = {.name = "652mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[9]),
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[9],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray652mhzFL}}};
const FixedLimits marikoGpuVoltArray691mhzFL = {.min = 200, .max = defaultCustTable.marikoGpuVoltArray[10] + 75, .stepSize = 5};
const Param marikoGpuVoltArray691mhz = {.name = "691mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[10]),
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[10],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray691mhzFL}}};
const FixedLimits marikoGpuVoltArray729mhzFL = {.min = 200, .max = defaultCustTable.marikoGpuVoltArray[11] + 75, .stepSize = 5};
const Param marikoGpuVoltArray729mhz = {.name = "729mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[11]),
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[11],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray729mhzFL}}};
const FixedLimits marikoGpuVoltArray768mhzFL = {.min = 200, .max = defaultCustTable.marikoGpuVoltArray[12] + 75, .stepSize = 5};
const Param marikoGpuVoltArray768mhz = {.name = "768mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[12]),
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[12],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray768mhzFL}}};
const FixedLimits marikoGpuVoltArray806mhzFL = {.min = 200, .max = defaultCustTable.marikoGpuVoltArray[13] + 75, .stepSize = 5};
const Param marikoGpuVoltArray806mhz = {.name = "806mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[13]),
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[13],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray806mhzFL}}};
const FixedLimits marikoGpuVoltArray845mhzFL = {.min = 200, .max = defaultCustTable.marikoGpuVoltArray[14] + 75, .stepSize = 5};
const Param marikoGpuVoltArray845mhz = {.name = "845mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[14]),
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[14],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray845mhzFL}}};
const FixedLimits marikoGpuVoltArray883mhzFL = {.min = 200, .max = defaultCustTable.marikoGpuVoltArray[15] + 75, .stepSize = 5};
const Param marikoGpuVoltArray883mhz = {.name = "883mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[15]),
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[15],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray883mhzFL}}};
const FixedLimits marikoGpuVoltArray921mhzFL = {.min = 200, .max = defaultCustTable.marikoGpuVoltArray[16] + 75, .stepSize = 5};
const Param marikoGpuVoltArray921mhz = {.name = "921mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[16]),
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[16],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray921mhzFL}}};
const FixedLimits marikoGpuVoltArray960mhzFL = {.min = 200, .max = defaultCustTable.marikoGpuVoltArray[17] + 75, .stepSize = 5};
const Param marikoGpuVoltArray960mhz = {.name = "960mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[17]),
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[17],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray960mhzFL}}};
const FixedLimits marikoGpuVoltArray998mhzFL = {.min = 200, .max = defaultCustTable.marikoGpuVoltArray[18] + 75, .stepSize = 5};
const Param marikoGpuVoltArray998mhz = {.name = "998mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.marikoGpuVoltArray[18]),
                                        .defaultValue = defaultCustTable.marikoGpuVoltArray[18],
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray998mhzFL}}};
const FixedLimits marikoGpuVoltArray1036mhzFL = {.min = 200, .max = defaultCustTable.marikoGpuVoltArray[19] + 75, .stepSize = 5};
const Param marikoGpuVoltArray1036mhz = {.name = "1036mhz",
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = getOffset(defaultCustTable.marikoGpuVoltArray[19]),
                                         .defaultValue = defaultCustTable.marikoGpuVoltArray[19],
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray1036mhzFL}}};
const FixedLimits marikoGpuVoltArray1075mhzFL = {.min = 200, .max = defaultCustTable.marikoGpuVoltArray[20] + 75, .stepSize = 5};
const Param marikoGpuVoltArray1075mhz = {.name = "1075mhz",
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = getOffset(defaultCustTable.marikoGpuVoltArray[20]),
                                         .defaultValue = defaultCustTable.marikoGpuVoltArray[20],
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray1075mhzFL}}};
const FixedLimits marikoGpuVoltArray1113mhzFL = {.min = 200, .max = defaultCustTable.marikoGpuVoltArray[21] + 75, .stepSize = 5};
const Param marikoGpuVoltArray1113mhz = {.name = "1113mhz",
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = getOffset(defaultCustTable.marikoGpuVoltArray[21]),
                                         .defaultValue = defaultCustTable.marikoGpuVoltArray[21],
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray1113mhzFL}}};
const FixedLimits marikoGpuVoltArray1152mhzFL = {.min = 200, .max = defaultCustTable.marikoGpuVoltArray[22] + 75, .stepSize = 5};
const Param marikoGpuVoltArray1152mhz = {.name = "1152mhz",
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = getOffset(defaultCustTable.marikoGpuVoltArray[22]),
                                         .defaultValue = defaultCustTable.marikoGpuVoltArray[22],
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray1152mhzFL}}};
const FixedLimits marikoGpuVoltArray1190mhzFL = {.min = 200, .max = defaultCustTable.marikoGpuVoltArray[23] + 75, .stepSize = 5};
const Param marikoGpuVoltArray1190mhz = {.name = "1190mhz",
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = getOffset(defaultCustTable.marikoGpuVoltArray[23]),
                                         .defaultValue = defaultCustTable.marikoGpuVoltArray[23],
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedLimits, .values = &marikoGpuVoltArray1190mhzFL}}};

const Table marikoGpuVoltArray = {
    .name = "GPU Manual Mode Volt Table",
    .description = NULL,
    .baseOffset = getOffset(defaultCustTable.marikoGpuVoltArray),
    .paramsCount = 24,
    .params = {&marikoGpuVoltArray307mhz,  &marikoGpuVoltArray345mhz,  &marikoGpuVoltArray384mhz,  &marikoGpuVoltArray422mhz, &marikoGpuVoltArray460mhz,
               &marikoGpuVoltArray499mhz,  &marikoGpuVoltArray537mhz,  &marikoGpuVoltArray576mhz,  &marikoGpuVoltArray614mhz, &marikoGpuVoltArray652mhz,
               &marikoGpuVoltArray691mhz,  &marikoGpuVoltArray729mhz,  &marikoGpuVoltArray768mhz,  &marikoGpuVoltArray806mhz, &marikoGpuVoltArray845mhz,
               &marikoGpuVoltArray883mhz,  &marikoGpuVoltArray921mhz,  &marikoGpuVoltArray960mhz,  &marikoGpuVoltArray998mhz, &marikoGpuVoltArray1036mhz,
               &marikoGpuVoltArray1075mhz, &marikoGpuVoltArray1113mhz, &marikoGpuVoltArray1152mhz, &marikoGpuVoltArray1190mhz}};

const FixedValues marikoHGPUvFV = {.valuesCount = 1, .values = {{.value = eBAMATIC, .label = "eBAMATIC"}}};
const FixedLimits marikoHGPUvFL = {.min = 750, .max = 1200, .stepSize = 50, .measure = "mV"};
// GPU OVER LOGIC
// eBAMATIC
// MARIKO: 750-1200 MANUAL
const Param marikoHGPUv = {.name = "OVER MODE",
                           .description = NULL,
                           .offset = getOffset(defaultCustTable.hGPUv),
                           .defaultValue = defaultCustTable.hGPUv,
                           .limitsCount = 2,
                           .limits = {{.type = EFixedValues, .values = &marikoHGPUvFV}, {.type = EFixedLimits, .values = &marikoHGPUvFL}}};

const Params mGPUParams = {.count = 2, .params = {&marikoGpuUV, &marikoHGPUv}};
const Tables mGPUTables = {.count = 1, .tables = {&marikoGpuVoltArray}};
