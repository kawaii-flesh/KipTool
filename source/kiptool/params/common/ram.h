#pragma once

#include "../param.h"
#include "../table.h"

const FixedValues commonEmcMemVoltFV = {.valuesCount = 3, .values = {{.value = 1175000, .label = "ECO"}, {.value = 1275000}, {.value = 1375000, .label = "SRT"}}};
const FixedLimits commonEmcMemVoltFL = {.min = 950000, .max = 1400000, .stepSize = 12500};
// RAM VDD MODE
// 1175'000 ECO
// 1275'000 DEFAULT
// 1375'000 SRT
// MANUAL 950'000-1400'000 STEP 12'500uV
const Param commonEmcMemVolt = {.name = "VDD MODE",
                                .measure = "mV",
                                .description = NULL,
                                .offset = getOffset(defaultCustTable.commonEmcMemVolt),
                                .defaultValue = defaultCustTable.commonEmcMemVolt,
                                .limitsCount = 2,
                                .limits = {{.type = EFixedValues, .values = &commonEmcMemVoltFV}, {.type = EFixedLimits, .values = &commonEmcMemVoltFL}}};

const FixedRange drochr01FR = {.start = 0, .end = 9};
// 0 DEBUG // 1 AUTO SAFE // 2-9 AUTO STAGE
const Param drochr01 = {.name = "DROCHR01",
                        .measure = NULL,
                        .description = NULL,
                        .offset = getOffset(defaultCustTable.drochr01),
                        .defaultValue = defaultCustTable.drochr01,
                        .limitsCount = 1,
                        .limits = {{.type = EFixedRange, .values = &drochr01FR}}};

const FixedRange drochr02FR = {.start = 0, .end = 9};
// 0 DEBUG // 1 AUTO SAFE // 2-8 AUTO STAGE // 9 ALT LOGIC
const Param drochr02 = {.name = "DROCHR02",
                        .measure = NULL,
                        .description = NULL,
                        .offset = getOffset(defaultCustTable.drochr02),
                        .defaultValue = defaultCustTable.drochr02,
                        .limitsCount = 1,
                        .limits = {{.type = EFixedRange, .values = &drochr02FR}}};

const FixedValues drochr03FV = {.valuesCount = 1, .values = {{.value = eBAMATIC, .label = "eBAMATIC"}}};
const FixedRange drochr03FR = {.start = 1, .end = 10};
// 1 AUTO SAFE // 2-9 AUTO STAGE // 10 ALT LOGIC
const Param drochr03 = {.name = "DROCHR03",
                        .measure = NULL,
                        .description = NULL,
                        .offset = getOffset(defaultCustTable.drochr03),
                        .defaultValue = defaultCustTable.drochr03,
                        .limitsCount = 2,
                        .limits = {{.type = EFixedValues, .values = &drochr03FV}, {.type = EFixedRange, .values = &drochr03FR}}};

const FixedRange drochr04FR = {.start = 0, .end = 9};
// 0 DEBUG // 1 AUTO SAFE // 2-9 AUTO STAGE
const Param drochr04 = {.name = "DROCHR04",
                        .measure = NULL,
                        .description = NULL,
                        .offset = getOffset(defaultCustTable.drochr04),
                        .defaultValue = defaultCustTable.drochr04,
                        .limitsCount = 1,
                        .limits = {{.type = EFixedRange, .values = &drochr04FR}}};

const FixedRange drochr05FR = {.start = 0, .end = 9};
// 0 DEBUG // 1 AUTO SAFE // 2-9 AUTO STAGE // ! drochr05 = drochr01 + drochr05
const Param drochr05 = {.name = "DROCHR05",
                        .measure = NULL,
                        .description = NULL,
                        .offset = getOffset(defaultCustTable.drochr05),
                        .defaultValue = defaultCustTable.drochr05,
                        .limitsCount = 1,
                        .limits = {{.type = EFixedRange, .values = &drochr05FR}}};

const FixedRange drochr06FR = {.start = 0, .end = 14};
// 0 DEBUG // 1 AUTO SAFE // 2-14 AUTO STAGE
const Param drochr06 = {.name = "DROCHR06",
                        .measure = NULL,
                        .description = NULL,
                        .offset = getOffset(defaultCustTable.drochr06),
                        .defaultValue = defaultCustTable.drochr06,
                        .limitsCount = 1,
                        .limits = {{.type = EFixedRange, .values = &drochr06FR}}};

const FixedRange drochr07FR = {.start = 0, .end = 10};
// 0 DEBUG // 1 AUTO SAFE // 2-10 AUTO STAGE
const Param drochr07 = {.name = "DROCHR07",
                        .measure = NULL,
                        .description = NULL,
                        .offset = getOffset(defaultCustTable.drochr07),
                        .defaultValue = defaultCustTable.drochr07,
                        .limitsCount = 1,
                        .limits = {{.type = EFixedRange, .values = &drochr07FR}}};
const FixedRange drochr08FR = {.start = 0, .end = 12};
// 0 DEBUG // 1 AUTO SAFE // 2-12 AUTO STAGE
const Param drochr08 = {.name = "DROCHR08",
                        .measure = NULL,
                        .description = NULL,
                        .offset = getOffset(defaultCustTable.drochr08),
                        .defaultValue = defaultCustTable.drochr08,
                        .limitsCount = 1,
                        .limits = {{.type = EFixedRange, .values = &drochr08FR}}};

const Table drochrsTable = {.name = RAM_TIMINGS_TABLE_NAME,
                            .description = NULL,
                            .baseOffset = getOffset(defaultCustTable.drochr01),
                            .paramsCount = 8,
                            .params = {&drochr01, &drochr02, &drochr03, &drochr04, &drochr05, &drochr06, &drochr07, &drochr08}};

const FixedValues eBALFV = {.valuesCount = 6,
                            .values = {{.value = eBAMATIC, .label = "eBAMATIC"},
                                       {.value = 1, .label = "SYK-LOH"},
                                       {.value = 2, .label = "ECO ST1"},
                                       {.value = 3},
                                       {.value = 4, .label = "SRT ST1"},
                                       {.value = 5, .label = "SRT ST2"}}};
// EMC BALLANCE ADVANCED LOGIC
// eBAMATIC
// 1 SYK-LOH
// 2 ECO ST1
// 3 DEFAULT
// 4 SRT ST1
// 5 SRT ST2
// TRADE MAX FREQ FOR EFFICIENCY
// EFFICIENCY << PRIORITY >> FREQUENCY
const Param eBAL = {.name = "EMC BALLANCE ADVANCED LOGIC",
                    .measure = NULL,
                    .description = NULL,
                    .offset = getOffset(defaultCustTable.eBAL),
                    .defaultValue = defaultCustTable.eBAL,
                    .limitsCount = 1,
                    .limits = {{.type = EFixedValues, .values = &eBALFV}}};

const FixedValues eBASFV = {.valuesCount = 6,
                            .values = {{.value = 0},
                                       {.value = 1, .label = "ST1"},
                                       {.value = 2, .label = "SYK-LOH"},
                                       {.value = 3, .label = "ST3"},
                                       {.value = 4, .label = "ST4"},
                                       {.value = 5, .label = "LOH-C4C"}}};
// EBA-SHIFT
// 0 DEFAULT
// 1 AUTO ST1
// 2 SYK-LOH
// 3 AUTO ST3
// 4 AUTO ST4
// 5 LOH-C4C
// TRADE MAX FREQ FOR EFFICIENCY
// FREQUENCY << PRIORITY >> EFFICIENCY
const Param eBAS = {.name = "EBA-SHIFT",
                    .measure = NULL,
                    .description = NULL,
                    .offset = getOffset(defaultCustTable.eBAS),
                    .defaultValue = defaultCustTable.eBAS,
                    .limitsCount = 1,
                    .limits = {{.type = EFixedValues, .values = &eBASFV}}};

const Params cRAMParams = {.count = 3, .params = {&commonEmcMemVolt, &eBAL, &eBAS}};
const Tables cRAMTables = {.count = 1, .tables = {&drochrsTable}};
