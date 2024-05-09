#pragma once

#include "../defaultCustomize.h"
#include "../param.h"
#include "../table.h"

const FixedValues eristaGpuUVFV = {.valuesCount = 3,
                                   .values = {{.value = 0, .label = "ECO ST1"}, {.value = 1, .label = "ECO ST2"}, {.value = 2, .label = "ECO ST3"}}};
// GPU ECO LOGIC
// 0 AUTO ECO ST1
// 1 AUTO ECO ST2
// 2 AUTO ECO ST3
// ERISTA = eristaGpuDvfsTable uV - (12500 uV * marikoGpuUV)
const Param eristaGpuUV = {.name = "GPU ECO LOGIC",
                           .measure = NULL,
                           .description = NULL,
                           .offset = getOffset(defaultCustTable.marikoGpuUV),
                           .defaultValue = defaultCustTable.marikoGpuUV,
                           .limitsCount = 1,
                           .limits = {{.type = EFixedValues, .values = &eristaGpuUVFV}}};

const FixedValues eristaHGPUvFV = {.valuesCount = 1, .values = {{.value = 0, .label = "AUTO"}}};
const FixedLimits eristaHGPUvFL = {.min = 850, .max = 1300, .stepSize = 50, .measure = "mV"};
// GPU OVER LOGIC
// 0 AUTO
// ERISTA: 850-1300 MANUAL
const Param eristaHGPUv = {.name = "GPU OVER MODE",
                           .description = NULL,
                           .offset = getOffset(defaultCustTable.hGPUv),
                           .defaultValue = defaultCustTable.hGPUv,
                           .limitsCount = 2,
                           .limits = {{.type = EFixedValues, .values = &eristaHGPUvFV}, {.type = EFixedLimits, .values = &eristaHGPUvFL}}};

const FixedLimits eristaGpuDvfsTable192mhzFL = {.min = defaultCustTable.eristaGpuDvfsTable[0].cvb_pll_param.c0 - 75000,
                                                .max = defaultCustTable.eristaGpuDvfsTable[0].cvb_pll_param.c0 + 75000,
                                                .stepSize = 500};
const Param eristaGpuDvfsTable192mhz = {.name = "192mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.eristaGpuDvfsTable[0].cvb_pll_param.c0),
                                        .defaultValue = defaultCustTable.eristaGpuDvfsTable[0].cvb_pll_param.c0,
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &eristaGpuDvfsTable192mhzFL}}};
const FixedLimits eristaGpuDvfsTable230mhzFL = {.min = defaultCustTable.eristaGpuDvfsTable[1].cvb_pll_param.c0 - 75000,
                                                .max = defaultCustTable.eristaGpuDvfsTable[1].cvb_pll_param.c0 + 75000,
                                                .stepSize = 500};
const Param eristaGpuDvfsTable230mhz = {.name = "230mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.eristaGpuDvfsTable[1].cvb_pll_param.c0),
                                        .defaultValue = defaultCustTable.eristaGpuDvfsTable[1].cvb_pll_param.c0,
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &eristaGpuDvfsTable230mhzFL}}};
const FixedLimits eristaGpuDvfsTable307mhzFL = {.min = defaultCustTable.eristaGpuDvfsTable[2].cvb_pll_param.c0 - 75000,
                                                .max = defaultCustTable.eristaGpuDvfsTable[2].cvb_pll_param.c0 + 75000,
                                                .stepSize = 500};
const Param eristaGpuDvfsTable307mhz = {.name = "307mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.eristaGpuDvfsTable[2].cvb_pll_param.c0),
                                        .defaultValue = defaultCustTable.eristaGpuDvfsTable[2].cvb_pll_param.c0,
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &eristaGpuDvfsTable307mhzFL}}};
const FixedLimits eristaGpuDvfsTable384mhzFL = {.min = defaultCustTable.eristaGpuDvfsTable[3].cvb_pll_param.c0 - 75000,
                                                .max = defaultCustTable.eristaGpuDvfsTable[3].cvb_pll_param.c0 + 75000,
                                                .stepSize = 500};
const Param eristaGpuDvfsTable384mhz = {.name = "384mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.eristaGpuDvfsTable[3].cvb_pll_param.c0),
                                        .defaultValue = defaultCustTable.eristaGpuDvfsTable[3].cvb_pll_param.c0,
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &eristaGpuDvfsTable384mhzFL}}};
const FixedLimits eristaGpuDvfsTable460mhzFL = {.min = defaultCustTable.eristaGpuDvfsTable[4].cvb_pll_param.c0 - 75000,
                                                .max = defaultCustTable.eristaGpuDvfsTable[4].cvb_pll_param.c0 + 75000,
                                                .stepSize = 500};
const Param eristaGpuDvfsTable460mhz = {.name = "460mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.eristaGpuDvfsTable[4].cvb_pll_param.c0),
                                        .defaultValue = defaultCustTable.eristaGpuDvfsTable[4].cvb_pll_param.c0,
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &eristaGpuDvfsTable460mhzFL}}};
const FixedLimits eristaGpuDvfsTable537mhzFL = {.min = defaultCustTable.eristaGpuDvfsTable[5].cvb_pll_param.c0 - 75000,
                                                .max = defaultCustTable.eristaGpuDvfsTable[5].cvb_pll_param.c0 + 75000,
                                                .stepSize = 500};
const Param eristaGpuDvfsTable537mhz = {.name = "537mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.eristaGpuDvfsTable[5].cvb_pll_param.c0),
                                        .defaultValue = defaultCustTable.eristaGpuDvfsTable[5].cvb_pll_param.c0,
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &eristaGpuDvfsTable537mhzFL}}};
const FixedLimits eristaGpuDvfsTable614mhzFL = {.min = defaultCustTable.eristaGpuDvfsTable[6].cvb_pll_param.c0 - 75000,
                                                .max = defaultCustTable.eristaGpuDvfsTable[6].cvb_pll_param.c0 + 75000,
                                                .stepSize = 500};
const Param eristaGpuDvfsTable614mhz = {.name = "614mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.eristaGpuDvfsTable[6].cvb_pll_param.c0),
                                        .defaultValue = defaultCustTable.eristaGpuDvfsTable[6].cvb_pll_param.c0,
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &eristaGpuDvfsTable614mhzFL}}};
const FixedLimits eristaGpuDvfsTable691mhzFL = {.min = defaultCustTable.eristaGpuDvfsTable[7].cvb_pll_param.c0 - 75000,
                                                .max = defaultCustTable.eristaGpuDvfsTable[7].cvb_pll_param.c0 + 75000,
                                                .stepSize = 500};
const Param eristaGpuDvfsTable691mhz = {.name = "691mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.eristaGpuDvfsTable[7].cvb_pll_param.c0),
                                        .defaultValue = defaultCustTable.eristaGpuDvfsTable[7].cvb_pll_param.c0,
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &eristaGpuDvfsTable691mhzFL}}};
const FixedLimits eristaGpuDvfsTable768mhzFL = {.min = defaultCustTable.eristaGpuDvfsTable[8].cvb_pll_param.c0 - 75000,
                                                .max = defaultCustTable.eristaGpuDvfsTable[8].cvb_pll_param.c0 + 75000,
                                                .stepSize = 500};
const Param eristaGpuDvfsTable768mhz = {.name = "768mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.eristaGpuDvfsTable[8].cvb_pll_param.c0),
                                        .defaultValue = defaultCustTable.eristaGpuDvfsTable[8].cvb_pll_param.c0,
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &eristaGpuDvfsTable768mhzFL}}};
const FixedLimits eristaGpuDvfsTable844mhzFL = {.min = defaultCustTable.eristaGpuDvfsTable[9].cvb_pll_param.c0 - 75000,
                                                .max = defaultCustTable.eristaGpuDvfsTable[9].cvb_pll_param.c0 + 75000,
                                                .stepSize = 500};
const Param eristaGpuDvfsTable844mhz = {.name = "844mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.eristaGpuDvfsTable[9].cvb_pll_param.c0),
                                        .defaultValue = defaultCustTable.eristaGpuDvfsTable[9].cvb_pll_param.c0,
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &eristaGpuDvfsTable844mhzFL}}};
const FixedLimits eristaGpuDvfsTable921mhzFL = {.min = defaultCustTable.eristaGpuDvfsTable[10].cvb_pll_param.c0 - 75000,
                                                .max = defaultCustTable.eristaGpuDvfsTable[10].cvb_pll_param.c0 + 75000,
                                                .stepSize = 500};
const Param eristaGpuDvfsTable921mhz = {.name = "921mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.eristaGpuDvfsTable[10].cvb_pll_param.c0),
                                        .defaultValue = defaultCustTable.eristaGpuDvfsTable[10].cvb_pll_param.c0,
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &eristaGpuDvfsTable921mhzFL}}};
const FixedLimits eristaGpuDvfsTable998mhzFL = {.min = defaultCustTable.eristaGpuDvfsTable[11].cvb_pll_param.c0 - 75000,
                                                .max = defaultCustTable.eristaGpuDvfsTable[11].cvb_pll_param.c0 + 75000,
                                                .stepSize = 500};
const Param eristaGpuDvfsTable998mhz = {.name = "998mhz",
                                        .measure = "mV",
                                        .description = NULL,
                                        .offset = getOffset(defaultCustTable.eristaGpuDvfsTable[11].cvb_pll_param.c0),
                                        .defaultValue = defaultCustTable.eristaGpuDvfsTable[11].cvb_pll_param.c0,
                                        .limitsCount = 1,
                                        .limits = {{.type = EFixedLimits, .values = &eristaGpuDvfsTable998mhzFL}}};
const FixedLimits eristaGpuDvfsTable1075mhzFL = {.min = defaultCustTable.eristaGpuDvfsTable[12].cvb_pll_param.c0 - 75000,
                                                 .max = defaultCustTable.eristaGpuDvfsTable[12].cvb_pll_param.c0 + 75000,
                                                 .stepSize = 500};
const Param eristaGpuDvfsTable1075mhz = {.name = "1075mhz",
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = getOffset(defaultCustTable.eristaGpuDvfsTable[12].cvb_pll_param.c0),
                                         .defaultValue = defaultCustTable.eristaGpuDvfsTable[12].cvb_pll_param.c0,
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedLimits, .values = &eristaGpuDvfsTable1075mhzFL}}};
const FixedLimits eristaGpuDvfsTable1152mhzFL = {.min = defaultCustTable.eristaGpuDvfsTable[13].cvb_pll_param.c0 - 75000,
                                                 .max = defaultCustTable.eristaGpuDvfsTable[13].cvb_pll_param.c0 + 75000,
                                                 .stepSize = 500};
const Param eristaGpuDvfsTable1152mhz = {.name = "1152mhz",
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = getOffset(defaultCustTable.eristaGpuDvfsTable[13].cvb_pll_param.c0),
                                         .defaultValue = defaultCustTable.eristaGpuDvfsTable[13].cvb_pll_param.c0,
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedLimits, .values = &eristaGpuDvfsTable1152mhzFL}}};
const FixedLimits eristaGpuDvfsTable1228mhzFL = {.min = defaultCustTable.eristaGpuDvfsTable[14].cvb_pll_param.c0 - 75000,
                                                 .max = defaultCustTable.eristaGpuDvfsTable[14].cvb_pll_param.c0 + 75000,
                                                 .stepSize = 500};
const Param eristaGpuDvfsTable1228mhz = {.name = "1228mhz",
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = getOffset(defaultCustTable.eristaGpuDvfsTable[14].cvb_pll_param.c0),
                                         .defaultValue = defaultCustTable.eristaGpuDvfsTable[14].cvb_pll_param.c0,
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedLimits, .values = &eristaGpuDvfsTable1228mhzFL}}};
const FixedLimits eristaGpuDvfsTable1305mhzFL = {.min = defaultCustTable.eristaGpuDvfsTable[15].cvb_pll_param.c0 - 75000,
                                                 .max = defaultCustTable.eristaGpuDvfsTable[15].cvb_pll_param.c0 + 75000,
                                                 .stepSize = 500};
const Param eristaGpuDvfsTable1305mhz = {.name = "1305mhz",
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = getOffset(defaultCustTable.eristaGpuDvfsTable[15].cvb_pll_param.c0),
                                         .defaultValue = defaultCustTable.eristaGpuDvfsTable[15].cvb_pll_param.c0,
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedLimits, .values = &eristaGpuDvfsTable1305mhzFL}}};
const FixedLimits eristaGpuDvfsTable1344mhzFL = {.min = defaultCustTable.eristaGpuDvfsTable[16].cvb_pll_param.c0 - 75000,
                                                 .max = defaultCustTable.eristaGpuDvfsTable[16].cvb_pll_param.c0 + 75000,
                                                 .stepSize = 500};
const Param eristaGpuDvfsTable1344mhz = {.name = "1344mhz",
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = getOffset(defaultCustTable.eristaGpuDvfsTable[16].cvb_pll_param.c0),
                                         .defaultValue = defaultCustTable.eristaGpuDvfsTable[16].cvb_pll_param.c0,
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedLimits, .values = &eristaGpuDvfsTable1344mhzFL}}};
const FixedLimits eristaGpuDvfsTable1382mhzFL = {.min = defaultCustTable.eristaGpuDvfsTable[17].cvb_pll_param.c0 - 75000,
                                                 .max = defaultCustTable.eristaGpuDvfsTable[17].cvb_pll_param.c0 + 75000,
                                                 .stepSize = 500};
const Param eristaGpuDvfsTable1382mhz = {.name = "1382mhz",
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = getOffset(defaultCustTable.eristaGpuDvfsTable[17].cvb_pll_param.c0),
                                         .defaultValue = defaultCustTable.eristaGpuDvfsTable[17].cvb_pll_param.c0,
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedLimits, .values = &eristaGpuDvfsTable1382mhzFL}}};
const FixedLimits eristaGpuDvfsTable1420mhzFL = {.min = defaultCustTable.eristaGpuDvfsTable[18].cvb_pll_param.c0 - 75000,
                                                 .max = defaultCustTable.eristaGpuDvfsTable[18].cvb_pll_param.c0 + 75000,
                                                 .stepSize = 500};
const Param eristaGpuDvfsTable1420mhz = {.name = "1420mhz",
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = getOffset(defaultCustTable.eristaGpuDvfsTable[18].cvb_pll_param.c0),
                                         .defaultValue = defaultCustTable.eristaGpuDvfsTable[18].cvb_pll_param.c0,
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedLimits, .values = &eristaGpuDvfsTable1420mhzFL}}};
const FixedLimits eristaGpuDvfsTable1459mhzFL = {.min = defaultCustTable.eristaGpuDvfsTable[19].cvb_pll_param.c0 - 75000,
                                                 .max = defaultCustTable.eristaGpuDvfsTable[19].cvb_pll_param.c0 + 75000,
                                                 .stepSize = 500};
const Param eristaGpuDvfsTable1459mhz = {.name = "1459mhz",
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = getOffset(defaultCustTable.eristaGpuDvfsTable[19].cvb_pll_param.c0),
                                         .defaultValue = defaultCustTable.eristaGpuDvfsTable[19].cvb_pll_param.c0,
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedLimits, .values = &eristaGpuDvfsTable1459mhzFL}}};
const FixedLimits eristaGpuDvfsTable1497mhzFL = {.min = defaultCustTable.eristaGpuDvfsTable[20].cvb_pll_param.c0 - 75000,
                                                 .max = defaultCustTable.eristaGpuDvfsTable[20].cvb_pll_param.c0 + 75000,
                                                 .stepSize = 500};
const Param eristaGpuDvfsTable1497mhz = {.name = "1497mhz",
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = getOffset(defaultCustTable.eristaGpuDvfsTable[20].cvb_pll_param.c0),
                                         .defaultValue = defaultCustTable.eristaGpuDvfsTable[20].cvb_pll_param.c0,
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedLimits, .values = &eristaGpuDvfsTable1497mhzFL}}};
const FixedLimits eristaGpuDvfsTable1536mhzFL = {.min = defaultCustTable.eristaGpuDvfsTable[21].cvb_pll_param.c0 - 75000,
                                                 .max = defaultCustTable.eristaGpuDvfsTable[21].cvb_pll_param.c0 + 75000,
                                                 .stepSize = 500};
const Param eristaGpuDvfsTable1536mhz = {.name = "1536mhz",
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = getOffset(defaultCustTable.eristaGpuDvfsTable[21].cvb_pll_param.c0),
                                         .defaultValue = defaultCustTable.eristaGpuDvfsTable[21].cvb_pll_param.c0,
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedLimits, .values = &eristaGpuDvfsTable1536mhzFL}}};
const FixedLimits eristaGpuDvfsTable1574mhzFL = {.min = defaultCustTable.eristaGpuDvfsTable[22].cvb_pll_param.c0 - 75000,
                                                 .max = defaultCustTable.eristaGpuDvfsTable[22].cvb_pll_param.c0 + 75000,
                                                 .stepSize = 500};
const Param eristaGpuDvfsTable1574mhz = {.name = "1574mhz",
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = getOffset(defaultCustTable.eristaGpuDvfsTable[22].cvb_pll_param.c0),
                                         .defaultValue = defaultCustTable.eristaGpuDvfsTable[22].cvb_pll_param.c0,
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedLimits, .values = &eristaGpuDvfsTable1574mhzFL}}};
const FixedLimits eristaGpuDvfsTable1612mhzFL = {.min = defaultCustTable.eristaGpuDvfsTable[23].cvb_pll_param.c0 - 75000,
                                                 .max = defaultCustTable.eristaGpuDvfsTable[23].cvb_pll_param.c0 + 75000,
                                                 .stepSize = 500};
const Param eristaGpuDvfsTable1612mhz = {.name = "1612mhz",
                                         .measure = "mV",
                                         .description = NULL,
                                         .offset = getOffset(defaultCustTable.eristaGpuDvfsTable[23].cvb_pll_param.c0),
                                         .defaultValue = defaultCustTable.eristaGpuDvfsTable[23].cvb_pll_param.c0,
                                         .limitsCount = 1,
                                         .limits = {{.type = EFixedLimits, .values = &eristaGpuDvfsTable1612mhzFL}}};
// ERISTA GPU ECO LOGIC
// ECO ST1 = -12500uV
// ECO ST2 = -25000uV
// ECO ST3 = -37500uV
// MANUAL = -75000uV << Default >> +75000uV
const Table eristaGpuDvfsTable = {
    .name = "GPU Volt Table",
    .description = NULL,
    .baseOffset = getOffset(defaultCustTable.eristaGpuDvfsTable[0].cvb_pll_param.c0),
    .paramsCount = 24,
    .params = {&eristaGpuDvfsTable192mhz,  &eristaGpuDvfsTable230mhz,  &eristaGpuDvfsTable307mhz,  &eristaGpuDvfsTable384mhz,  &eristaGpuDvfsTable460mhz,
               &eristaGpuDvfsTable537mhz,  &eristaGpuDvfsTable614mhz,  &eristaGpuDvfsTable691mhz,  &eristaGpuDvfsTable768mhz,  &eristaGpuDvfsTable844mhz,
               &eristaGpuDvfsTable921mhz,  &eristaGpuDvfsTable998mhz,  &eristaGpuDvfsTable1075mhz, &eristaGpuDvfsTable1152mhz, &eristaGpuDvfsTable1228mhz,
               &eristaGpuDvfsTable1305mhz, &eristaGpuDvfsTable1344mhz, &eristaGpuDvfsTable1382mhz, &eristaGpuDvfsTable1420mhz, &eristaGpuDvfsTable1459mhz,
               &eristaGpuDvfsTable1497mhz, &eristaGpuDvfsTable1536mhz, &eristaGpuDvfsTable1574mhz, &eristaGpuDvfsTable1612mhz}};

const Params eGPUParams = {.count = 2, .params = {&eristaGpuUV, &eristaHGPUv}};
const Tables eGPUTables = {.count = 1, .tables = {&eristaGpuDvfsTable}};
