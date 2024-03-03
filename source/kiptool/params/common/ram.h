#pragma once

#include "../customize.h"
#include "../param.h"
#include "../table.h"

const FixedValues commonEmcMemVoltFV = {
    .valuesCount = 3, .values = {{.value = 1175000, .label = "ECO"}, {.value = 1275000}, {.value = 1375000, .label = "SRT"}}};
const FixedLimits commonEmcMemVoltFL = {.min = 950000, .max = 1400000, .stepSize = 12500};
// RAM VDD MODE
// 1175'000 ECO
// 1275'000 DEFAULT
// 1375'000 SRT
// MANUAL 950'000-1400'000 STEP 12'500uV
const Param commonEmcMemVolt = {
    .name = "RAM VDD MODE",
    .category = RAM,
    .platform = COMMON,
    .measure = "mV",
    .description = NULL,
    .offset = getOffset(custTable.commonEmcMemVolt),
    .length = 4,
    .defaultValue = custTable.commonEmcMemVolt,
    .limitsCount = 2,
    .limits = {{.type = EFixedValues, .values = &commonEmcMemVoltFV}, {.type = EFixedLimits, .values = &commonEmcMemVoltFL}}};

const FixedValues ramTiming1FV = {.valuesCount = 9,
                                  .values = {{.value = 0, .label = "Do not adjust"},
                                             {.value = 1},
                                             {.value = 2},
                                             {.value = 3},
                                             {.value = 4},
                                             {.value = 5},
                                             {.value = 6},
                                             {.value = 7},
                                             {.value = 8}}};
const Param ramTiming1 = {.name = "RAM Timing 1",
                          .category = RAM,
                          .platform = COMMON,
                          .measure = NULL,
                          .description = NULL,
                          .offset = getOffset(custTable.ramTimingPresetOne),
                          .length = 4,
                          .defaultValue = custTable.ramTimingPresetOne,
                          .limitsCount = 1,
                          .limits = {{.type = EFixedValues, .values = &ramTiming1FV}}};

const FixedValues ramTiming2FV = {.valuesCount = 9,
                                  .values = {{.value = 0, .label = "Do not adjust"},
                                             {.value = 1},
                                             {.value = 2},
                                             {.value = 3},
                                             {.value = 4},
                                             {.value = 5},
                                             {.value = 6},
                                             {.value = 7},
                                             {.value = 8}}};
const Param ramTiming2 = {.name = "RAM Timing 2",
                          .category = RAM,
                          .platform = COMMON,
                          .measure = NULL,
                          .description = NULL,
                          .offset = getOffset(custTable.ramTimingPresetTwo),
                          .length = 4,
                          .defaultValue = custTable.ramTimingPresetTwo,
                          .limitsCount = 1,
                          .limits = {{.type = EFixedValues, .values = &ramTiming2FV}}};

const FixedValues ramTiming3FV = {.valuesCount = 10,
                                  .values = {{.value = 0, .label = "Do not adjust"},
                                             {.value = 1},
                                             {.value = 2},
                                             {.value = 3},
                                             {.value = 4},
                                             {.value = 5},
                                             {.value = 6},
                                             {.value = 7},
                                             {.value = 8},
                                             {.value = 9}}};
const Param ramTiming3 = {.name = "RAM Timing 3",
                          .category = RAM,
                          .platform = COMMON,
                          .measure = NULL,
                          .description = NULL,
                          .offset = getOffset(custTable.ramTimingPresetThree),
                          .length = 4,
                          .defaultValue = custTable.ramTimingPresetThree,
                          .limitsCount = 1,
                          .limits = {{.type = EFixedValues, .values = &ramTiming3FV}}};

const FixedValues ramTiming4FV = {.valuesCount = 9,
                                  .values = {{.value = 0, .label = "Do not adjust"},
                                             {.value = 1},
                                             {.value = 2},
                                             {.value = 3},
                                             {.value = 4},
                                             {.value = 5},
                                             {.value = 6},
                                             {.value = 7},
                                             {.value = 8}}};
const Param ramTiming4 = {.name = "RAM Timing 4",
                          .category = RAM,
                          .platform = COMMON,
                          .measure = NULL,
                          .description = NULL,
                          .offset = getOffset(custTable.ramTimingPresetFour),
                          .length = 4,
                          .defaultValue = custTable.ramTimingPresetFour,
                          .limitsCount = 1,
                          .limits = {{.type = EFixedValues, .values = &ramTiming4FV}}};

const FixedValues ramTiming5FV = {.valuesCount = 9,
                                  .values = {{.value = 0, .label = "Do not adjust"},
                                             {.value = 1},
                                             {.value = 2},
                                             {.value = 3},
                                             {.value = 4},
                                             {.value = 5},
                                             {.value = 6},
                                             {.value = 7},
                                             {.value = 8}}};
const Param ramTiming5 = {.name = "RAM Timing 5",
                          .category = RAM,
                          .platform = COMMON,
                          .measure = NULL,
                          .description = NULL,
                          .offset = getOffset(custTable.ramTimingPresetFive),
                          .length = 4,
                          .defaultValue = custTable.ramTimingPresetFive,
                          .limitsCount = 1,
                          .limits = {{.type = EFixedValues, .values = &ramTiming5FV}}};

const FixedValues ramTiming6FV = {.valuesCount = 11,
                                  .values = {{.value = 0, .label = "Do not adjust"},
                                             {.value = 1},
                                             {.value = 2},
                                             {.value = 3},
                                             {.value = 4},
                                             {.value = 5},
                                             {.value = 6},
                                             {.value = 7},
                                             {.value = 8},
                                             {.value = 9},
                                             {.value = 10}}};
const Param ramTiming6 = {.name = "RAM Timing 6",
                          .category = RAM,
                          .platform = COMMON,
                          .measure = NULL,
                          .description = NULL,
                          .offset = getOffset(custTable.ramTimingPresetSix),
                          .length = 4,
                          .defaultValue = custTable.ramTimingPresetSix,
                          .limitsCount = 1,
                          .limits = {{.type = EFixedValues, .values = &ramTiming6FV}}};

const FixedValues ramTiming7FV = {.valuesCount = 15,
                                  .values = {{.value = 0, .label = "Do not adjust"},
                                             {.value = 1},
                                             {.value = 2},
                                             {.value = 3},
                                             {.value = 4},
                                             {.value = 5},
                                             {.value = 6},
                                             {.value = 7},
                                             {.value = 8},
                                             {.value = 9},
                                             {.value = 10},
                                             {.value = 11},
                                             {.value = 12},
                                             {.value = 13},
                                             {.value = 14}}};
const Param ramTiming7 = {.name = "RAM Timing 7",
                          .category = RAM,
                          .platform = COMMON,
                          .measure = NULL,
                          .description = NULL,
                          .offset = getOffset(custTable.ramTimingPresetSeven),
                          .length = 4,
                          .defaultValue = custTable.ramTimingPresetSeven,
                          .limitsCount = 1,
                          .limits = {{.type = EFixedValues, .values = &ramTiming7FV}}};

const FixedValues ramTiming8FV = {.valuesCount = 19,
                                  .values = {{.value = 0, .label = "Do not adjust"},
                                             {.value = 1},
                                             {.value = 2},
                                             {.value = 3},
                                             {.value = 4},
                                             {.value = 5},
                                             {.value = 6},
                                             {.value = 7},
                                             {.value = 8},
                                             {.value = 9},
                                             {.value = 10},
                                             {.value = 11},
                                             {.value = 12},
                                             {.value = 13},
                                             {.value = 14},
                                             {.value = 15},
                                             {.value = 16},
                                             {.value = 17},
                                             {.value = 18}}};
const Param ramTiming8 = {
    .name = "RAM Timing 8",
    .category = RAM,
    .platform = COMMON,
    .measure = NULL,
    .description = NULL,
    .offset = getOffset(custTable.ramTimingPresetEight),  // TODO Maybe change table offset logic without increment
    .length = 4,
    .defaultValue = custTable.ramTimingPresetEight,
    .limitsCount = 1,
    .limits = {{.type = EFixedValues, .values = &ramTiming8FV}}};

const Table ramTimingsTable = {
    .name = "RAM Timings Table",
    .description = NULL,
    .category = RAM,
    .platform = COMMON,
    .baseOffset = getOffset(custTable.ramTimingPresetOne),
    .paramsCount = 8,
    .params = {&ramTiming1, &ramTiming2, &ramTiming3, &ramTiming4, &ramTiming5, &ramTiming6, &ramTiming7, &ramTiming8}};

const FixedValues eBALFV = {.valuesCount = 5,
                            .values = {{.value = 1, .label = "SYK-LOH"},
                                       {.value = 2, .label = "ECO ST1"},
                                       {.value = 3},
                                       {.value = 4, .label = "SRT ST1"},
                                       {.value = 5, .label = "SRT ST2"}}};
// EMC BALLANCE ADVANCED LOGIC
// 0 RESERVED
// 1 SYK-LOH
// 2 ECO ST1
// 3 DEFAULT
// 4 SRT ST1
// 5 SRT ST2
const Param eBAL = {.name = "EMC BALLANCE ADVANCED LOGIC",
                    .category = RAM,
                    .platform = COMMON,
                    .measure = NULL,
                    .description = NULL,
                    .offset = getOffset(custTable.eBAL),
                    .length = 4,
                    .defaultValue = custTable.eBAL,
                    .limitsCount = 2,
                    .limits = {{.type = EFixedValues, .values = &eBALFV}}};

const FixedValues eBASFV = {.valuesCount = 5,
                            .values = {{.value = 0, .label = "SYK-LOH"},
                                       {.value = 1, .label = "ECO ST1"},
                                       {.value = 2, .label = "SYK-LOH"},
                                       {.value = 5, .label = "LOH-C4C"}}};
// EBA-SHIFT
// 0 DEFAULT
// 1 ECO ST1
// 2 SYK-LOH
// 3 RESERVED
// 4 RESERVED
// 5 LOH-C4C
const Param eBAS = {.name = "EBA-SHIFT",
                    .category = RAM,
                    .platform = COMMON,
                    .measure = NULL,
                    .description = NULL,
                    .offset = getOffset(custTable.eBAS),
                    .length = 4,
                    .defaultValue = custTable.eBAS,
                    .limitsCount = 2,
                    .limits = {{.type = EFixedValues, .values = &eBASFV}}};

const FixedValues pMeh0FV = {.valuesCount = 2, .values = {{.value = 0}, {.value = 1}}};
// 0 eBAS Sub-Zero 0-1
const Param pMeh0 = {.name = "pMeh 0",
                     .category = RAM,
                     .platform = COMMON,
                     .measure = NULL,
                     .description = NULL,
                     .offset = getOffset(custTable.pMEH[0]),
                     .length = 4,
                     .defaultValue = custTable.pMEH[0],
                     .limitsCount = 1,
                     .limits = {{.type = EFixedValues, .values = &pMeh0FV}}};
const FixedValues pMeh1FV = {.valuesCount = 5,
                             .values = {{.value = 0}, {.value = 1}, {.value = 2}, {.value = 3}, {.value = 4}}};
// 1 divMB Supressor 0-4
const Param pMeh1 = {.name = "pMeh 1",
                     .category = RAM,
                     .platform = COMMON,
                     .measure = NULL,
                     .description = NULL,
                     .offset = getOffset(custTable.pMEH[1]),
                     .length = 4,
                     .defaultValue = custTable.pMEH[1],
                     .limitsCount = 1,
                     .limits = {{.type = EFixedValues, .values = &pMeh1FV}}};
const FixedValues pMeh2FV = {.valuesCount = 3, .values = {{.value = 0}, {.value = 1}, {.value = 2}}};
// 2 1333>1065>800
const Param pMeh2 = {.name = "pMeh 2",
                     .category = RAM,
                     .platform = COMMON,
                     .measure = NULL,
                     .description = NULL,
                     .offset = getOffset(custTable.pMEH[2]),
                     .length = 4,
                     .defaultValue = custTable.pMEH[2],
                     .limitsCount = 1,
                     .limits = {{.type = EFixedValues, .values = &pMeh2FV}}};
const FixedValues pMeh3FV = {.valuesCount = 5,
                             .values = {{.value = 0}, {.value = 1}, {.value = 2}, {.value = 3}, {.value = 4}}};
// 3 eBAW Shift 0-4
const Param pMeh3 = {.name = "pMeh 3",
                     .category = RAM,
                     .platform = COMMON,
                     .measure = NULL,
                     .description = NULL,
                     .offset = getOffset(custTable.pMEH[3]),
                     .length = 4,
                     .defaultValue = custTable.pMEH[3],
                     .limitsCount = 1,
                     .limits = {{.type = EFixedValues, .values = &pMeh3FV}}};
const FixedValues pMeh4FV = {.valuesCount = 5,
                             .values = {{.value = 0}, {.value = 1}, {.value = 2}, {.value = 3}, {.value = 4}}};
// 4 eBAR Shift 0-4
const Param pMeh4 = {.name = "pMeh 4",
                     .category = RAM,
                     .platform = COMMON,
                     .measure = NULL,
                     .description = NULL,
                     .offset = getOffset(custTable.pMEH[4]),
                     .length = 4,
                     .defaultValue = custTable.pMEH[4],
                     .limitsCount = 1,
                     .limits = {{.type = EFixedValues, .values = &pMeh4FV}}};
const FixedValues pMeh5FV = {.valuesCount = 9,
                             .values = {{.value = 0},
                                        {.value = 1},
                                        {.value = 2},
                                        {.value = 3},
                                        {.value = 4},
                                        {.value = 5},
                                        {.value = 6},
                                        {.value = 7},
                                        {.value = 8}}};
// 5 RTW Shift 0-8
const Param pMeh5 = {.name = "pMeh 5",
                     .category = RAM,
                     .platform = COMMON,
                     .measure = NULL,
                     .description = NULL,
                     .offset = getOffset(custTable.pMEH[5]),
                     .length = 4,
                     .defaultValue = custTable.pMEH[5],
                     .limitsCount = 1,
                     .limits = {{.type = EFixedValues, .values = &pMeh5FV}}};
const FixedValues pMeh6FV = {.valuesCount = 9,
                             .values = {{.value = 0},
                                        {.value = 1},
                                        {.value = 2},
                                        {.value = 3},
                                        {.value = 4},
                                        {.value = 5},
                                        {.value = 6},
                                        {.value = 7},
                                        {.value = 8}}};
// 6 WTR Shift 0-8
const Param pMeh6 = {.name = "pMeh 6",
                     .category = RAM,
                     .platform = COMMON,
                     .measure = NULL,
                     .description = NULL,
                     .offset = getOffset(custTable.pMEH[6]),
                     .length = 4,
                     .defaultValue = custTable.pMEH[6],
                     .limitsCount = 1,
                     .limits = {{.type = EFixedValues, .values = &pMeh6FV}}};
const FixedValues pMeh7FV = {.valuesCount = 9,
                             .values = {{.value = 0},
                                        {.value = 1},
                                        {.value = 2},
                                        {.value = 3},
                                        {.value = 4},
                                        {.value = 5},
                                        {.value = 6},
                                        {.value = 7},
                                        {.value = 8}}};
// 7 WTP Shift
const Param pMeh7 = {.name = "pMeh 7",
                     .category = RAM,
                     .platform = COMMON,
                     .measure = NULL,
                     .description = NULL,
                     .offset = getOffset(custTable.pMEH[7]),
                     .length = 4,
                     .defaultValue = custTable.pMEH[7],
                     .limitsCount = 1,
                     .limits = {{.type = EFixedValues, .values = &pMeh7FV}}};
const FixedValues pMeh8FV = {.valuesCount = 5,
                             .values = {{.value = 0}, {.value = 1}, {.value = 2}, {.value = 3}, {.value = 4}}};
// 8 RCD Reduct 0-4
const Param pMeh8 = {.name = "pMeh 8",
                     .category = RAM,
                     .platform = COMMON,
                     .measure = NULL,
                     .description = NULL,
                     .offset = getOffset(custTable.pMEH[8]),
                     .length = 4,
                     .defaultValue = custTable.pMEH[8],
                     .limitsCount = 1,
                     .limits = {{.type = EFixedValues, .values = &pMeh8FV}}};
const FixedValues pMeh9FV = {.valuesCount = 5,
                             .values = {{.value = 0}, {.value = 1}, {.value = 2}, {.value = 3}, {.value = 4}}};
// 9 RP Reduct 0-4
const Param pMeh9 = {.name = "pMeh 9",
                     .category = RAM,
                     .platform = COMMON,
                     .measure = NULL,
                     .description = NULL,
                     .offset = getOffset(custTable.pMEH[9]),
                     .length = 4,
                     .defaultValue = custTable.pMEH[9],
                     .limitsCount = 1,
                     .limits = {{.type = EFixedValues, .values = &pMeh9FV}}};
const FixedValues pMeh10FV = {.valuesCount = 17,
                              .values = {{.value = 0},
                                         {.value = 1},
                                         {.value = 2},
                                         {.value = 3},
                                         {.value = 4},
                                         {.value = 5},
                                         {.value = 6},
                                         {.value = 7},
                                         {.value = 8},
                                         {.value = 9},
                                         {.value = 10},
                                         {.value = 11},
                                         {.value = 12},
                                         {.value = 13},
                                         {.value = 14},
                                         {.value = 15},
                                         {.value = 16}}};
// 10 RAS Shift 0-16
const Param pMeh10 = {.name = "pMeh 10",
                      .category = RAM,
                      .platform = COMMON,
                      .measure = NULL,
                      .description = NULL,
                      .offset = getOffset(custTable.pMEH[10]),
                      .length = 4,
                      .defaultValue = custTable.pMEH[10],
                      .limitsCount = 1,
                      .limits = {{.type = EFixedValues, .values = &pMeh10FV}}};
const FixedValues pMeh11FV = {.valuesCount = 4, .values = {{.value = 0}, {.value = 1}, {.value = 2}, {.value = 3}}};
// 11 SRPD 0-3
const Param pMeh11 = {.name = "pMeh 11",
                      .category = RAM,
                      .platform = COMMON,
                      .measure = NULL,
                      .description = NULL,
                      .offset = getOffset(custTable.pMEH[11]),
                      .length = 4,
                      .defaultValue = custTable.pMEH[11],
                      .limitsCount = 1,
                      .limits = {{.type = EFixedValues, .values = &pMeh11FV}}};
const FixedValues pMeh12FV = {.valuesCount = 2, .values = {{.value = 0}, {.value = 1}}};
// 12 E-Enhance P
const Param pMeh12 = {.name = "pMeh 12",
                      .category = RAM,
                      .platform = COMMON,
                      .measure = NULL,
                      .description = NULL,
                      .offset = getOffset(custTable.pMEH[12]),
                      .length = 4,
                      .defaultValue = custTable.pMEH[12],
                      .limitsCount = 1,
                      .limits = {{.type = EFixedValues, .values = &pMeh12FV}}};
const FixedValues pMeh13FV = {.valuesCount = 5,
                              .values = {{.value = 0}, {.value = 1}, {.value = 2}, {.value = 3}, {.value = 4}}};
// 13 DR Debug 0-4
const Param pMeh13 = {.name = "pMeh 13",
                      .category = RAM,
                      .platform = COMMON,
                      .measure = NULL,
                      .description = NULL,
                      .offset = getOffset(custTable.pMEH[13]),
                      .length = 4,
                      .defaultValue = custTable.pMEH[13],
                      .limitsCount = 1,
                      .limits = {{.type = EFixedValues, .values = &pMeh13FV}}};
const FixedValues pMeh14FV = {
    .valuesCount = 25,
    .values = {{.value = 0},  {.value = 1},  {.value = 2},  {.value = 3},  {.value = 4},  {.value = 5},  {.value = 6},
               {.value = 7},  {.value = 8},  {.value = 9},  {.value = 10}, {.value = 11}, {.value = 12}, {.value = 13},
               {.value = 14}, {.value = 15}, {.value = 16}, {.value = 17}, {.value = 18}, {.value = 19}, {.value = 20},
               {.value = 21}, {.value = 22}, {.value = 23}, {.value = 24}}};
// 14 GameChanger 0-24
const Param pMeh14 = {.name = "pMeh 14",
                      .category = RAM,
                      .platform = COMMON,
                      .measure = NULL,
                      .description = NULL,
                      .offset = getOffset(custTable.pMEH[14]),
                      .length = 4,
                      .defaultValue = custTable.pMEH[14],
                      .limitsCount = 1,
                      .limits = {{.type = EFixedValues, .values = &pMeh14FV}}};
const FixedValues pMeh15FV = {.valuesCount = 2, .values = {{.value = 0}, {.value = 1}}};
// 15 Eri-Bump 0-1
const Param pMeh15 = {.name = "pMeh 15",
                      .category = RAM,
                      .platform = COMMON,
                      .measure = NULL,
                      .description = NULL,
                      .offset = getOffset(custTable.pMEH[15]),
                      .length = 4,
                      .defaultValue = custTable.pMEH[15],
                      .limitsCount = 1,
                      .limits = {{.type = EFixedValues, .values = &pMeh15FV}}};

const Table pMehTable = {.name = "pMeh Table",
                         .description = NULL,
                         .category = RAM,
                         .platform = COMMON,
                         .baseOffset = getOffset(custTable.pMEH),
                         .paramsCount = 16,  // 16-23 RESERVED
                         .params = {&pMeh0, &pMeh1, &pMeh2, &pMeh3, &pMeh4, &pMeh5, &pMeh6, &pMeh7, &pMeh8, &pMeh9, &pMeh10,
                                    &pMeh11, &pMeh12, &pMeh13, &pMeh14, &pMeh15}};

const FixedValues sMeh0FV = {.valuesCount = 9,
                             .values = {{.value = 1},
                                        {.value = 2},
                                        {.value = 3},
                                        {.value = 4},
                                        {.value = 5},
                                        {.value = 6},
                                        {.value = 7},
                                        {.value = 8},
                                        {.value = 9}}};
// 0 ARB-Boost 1-9
const Param sMeh0 = {.name = "sMeh 0",
                     .category = RAM,
                     .platform = COMMON,
                     .measure = NULL,
                     .description = NULL,
                     .offset = getOffset(custTable.sMEH[0]),
                     .length = 4,
                     .defaultValue = custTable.sMEH[0],
                     .limitsCount = 1,
                     .limits = {{.type = EFixedValues, .values = &sMeh0FV}}};
const FixedValues sMeh1FV = {.valuesCount = 5,
                             .values = {{.value = 0}, {.value = 1}, {.value = 2}, {.value = 3}, {.value = 4}}};
// 1 ARB-BCD 0-4
const Param sMeh1 = {.name = "sMeh 1",
                     .category = RAM,
                     .platform = COMMON,
                     .measure = NULL,
                     .description = NULL,
                     .offset = getOffset(custTable.sMEH[1]),
                     .length = 4,
                     .defaultValue = custTable.sMEH[1],
                     .limitsCount = 1,
                     .limits = {{.type = EFixedValues, .values = &sMeh1FV}}};
const FixedValues sMeh2FV = {.valuesCount = 5,
                             .values = {{.value = 0}, {.value = 1}, {.value = 2}, {.value = 3}, {.value = 4}}};
// 2 ARB-BRP 0-4
const Param sMeh2 = {.name = "sMeh 2",
                     .category = RAM,
                     .platform = COMMON,
                     .measure = NULL,
                     .description = NULL,
                     .offset = getOffset(custTable.sMEH[2]),
                     .length = 4,
                     .defaultValue = custTable.sMEH[2],
                     .limitsCount = 1,
                     .limits = {{.type = EFixedValues, .values = &sMeh2FV}}};
const FixedValues sMeh3FV = {.valuesCount = 5,
                             .values = {{.value = 0}, {.value = 1}, {.value = 2}, {.value = 3}, {.value = 4}}};
// 3 ARB-RTR 0-4
const Param sMeh3 = {.name = "sMeh 3",
                     .category = RAM,
                     .platform = COMMON,
                     .measure = NULL,
                     .description = NULL,
                     .offset = getOffset(custTable.sMEH[3]),
                     .length = 4,
                     .defaultValue = custTable.sMEH[3],
                     .limitsCount = 1,
                     .limits = {{.type = EFixedValues, .values = &sMeh3FV}}};
const FixedValues sMeh4FV = {.valuesCount = 5,
                             .values = {{.value = 0}, {.value = 1}, {.value = 2}, {.value = 3}, {.value = 4}}};
// 4 ARB-RTW 0-4
const Param sMeh4 = {.name = "sMeh 4",
                     .category = RAM,
                     .platform = COMMON,
                     .measure = NULL,
                     .description = NULL,
                     .offset = getOffset(custTable.sMEH[4]),
                     .length = 4,
                     .defaultValue = custTable.sMEH[4],
                     .limitsCount = 1,
                     .limits = {{.type = EFixedValues, .values = &sMeh4FV}}};
const FixedValues sMeh5FV = {.valuesCount = 5,
                             .values = {{.value = 0}, {.value = 1}, {.value = 2}, {.value = 3}, {.value = 4}}};
// 5 ARB-WTR 0-4
const Param sMeh5 = {.name = "sMeh 5",
                     .category = RAM,
                     .platform = COMMON,
                     .measure = NULL,
                     .description = NULL,
                     .offset = getOffset(custTable.sMEH[5]),
                     .length = 4,
                     .defaultValue = custTable.sMEH[5],
                     .limitsCount = 1,
                     .limits = {{.type = EFixedValues, .values = &sMeh5FV}}};
const FixedValues sMeh6FV = {
    .valuesCount = 8,
    .values = {{.value = 0}, {.value = 1}, {.value = 2}, {.value = 3}, {.value = 4}, {.value = 5}, {.value = 6}, {.value = 7}}};
// 6 ??? 0-7
const Param sMeh6 = {.name = "sMeh 6",
                     .category = RAM,
                     .platform = COMMON,
                     .measure = NULL,
                     .description = NULL,
                     .offset = getOffset(custTable.sMEH[6]),
                     .length = 4,
                     .defaultValue = custTable.sMEH[6],
                     .limitsCount = 1,
                     .limits = {{.type = EFixedValues, .values = &sMeh6FV}}};
const FixedValues sMeh7FV = {.valuesCount = 2, .values = {{.value = 0}, {.value = 1}}};
// 7 trDVFS 0-1
const Param sMeh7 = {.name = "sMeh 7",
                     .category = RAM,
                     .platform = COMMON,
                     .measure = NULL,
                     .description = NULL,
                     .offset = getOffset(custTable.sMEH[7]),
                     .length = 4,
                     .defaultValue = custTable.sMEH[7],
                     .limitsCount = 1,
                     .limits = {{.type = EFixedValues, .values = &sMeh7FV}}};
const FixedValues sMeh8FV = {.valuesCount = 2, .values = {{.value = 0}, {.value = 1}}};
// 8 E-Boost 0-1
const Param sMeh8 = {.name = "sMeh 8",
                     .category = RAM,
                     .platform = COMMON,
                     .measure = NULL,
                     .description = NULL,
                     .offset = getOffset(custTable.sMEH[8]),
                     .length = 4,
                     .defaultValue = custTable.sMEH[8],
                     .limitsCount = 1,
                     .limits = {{.type = EFixedValues, .values = &sMeh8FV}}};
const FixedValues sMeh9FV = {.valuesCount = 2, .values = {{.value = 0}, {.value = 1}}};
// 9 SSC Logic 0-1
const Param sMeh9 = {.name = "sMeh 9",
                     .category = RAM,
                     .platform = COMMON,
                     .measure = NULL,
                     .description = NULL,
                     .offset = getOffset(custTable.sMEH[9]),
                     .length = 4,
                     .defaultValue = custTable.sMEH[9],
                     .limitsCount = 1,
                     .limits = {{.type = EFixedValues, .values = &sMeh9FV}}};
const FixedValues sMeh10FV = {.valuesCount = 9,
                              .values = {{.value = 0},
                                         {.value = 1},
                                         {.value = 2},
                                         {.value = 3},
                                         {.value = 4},
                                         {.value = 5},
                                         {.value = 6},
                                         {.value = 7},
                                         {.value = 8}}};
// 10 Latent 0-8
const Param sMeh10 = {.name = "sMeh 10",
                      .category = RAM,
                      .platform = COMMON,
                      .measure = NULL,
                      .description = NULL,
                      .offset = getOffset(custTable.sMEH[10]),
                      .length = 4,
                      .defaultValue = custTable.sMEH[10],
                      .limitsCount = 1,
                      .limits = {{.type = EFixedValues, .values = &sMeh10FV}}};

const FixedValues sMeh11FV = {.valuesCount = 5,
                              .values = {{.value = 0}, {.value = 1}, {.value = 2}, {.value = 3}, {.value = 4}}};
// 11 CP-THM 0-4
const Param sMeh11 = {.name = "sMeh 11",
                      .category = RAM,
                      .platform = COMMON,
                      .measure = NULL,
                      .description = NULL,
                      .offset = getOffset(custTable.sMEH[11]),
                      .length = 4,
                      .defaultValue = custTable.sMEH[11],
                      .limitsCount = 1,
                      .limits = {{.type = EFixedValues, .values = &sMeh11FV}}};
const Table sMehTable = {
    .name = "sMeh Table",
    .description = NULL,
    .category = RAM,
    .platform = COMMON,
    .baseOffset = getOffset(custTable.sMEH),
    .paramsCount = 12,  // 12-23 RESERVED
    .params = {&sMeh0, &sMeh1, &sMeh2, &sMeh3, &sMeh4, &sMeh5, &sMeh6, &sMeh7, &sMeh8, &sMeh9, &sMeh10, &sMeh11}};

const Params cRAMParams = {.count = 3, .params = {&commonEmcMemVolt, &eBAL, &eBAS}};
const Tables cRAMTables = {.count = 3, .tables = {&ramTimingsTable, &pMehTable, &sMehTable}};