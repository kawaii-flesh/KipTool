#pragma once

#include "../customize.h"
#include "../param.h"

const FixedValues marikoEmcMaxClockFV = {.valuesCount = 11,
                                         .values = {{.value = 1600000, .label = "S-LOH"},
                                                    {.value = 1734400, .label = "E ST3"},
                                                    {.value = 1862400, .label = "E ST2"},
                                                    {.value = 1996800, .label = "E ST1"},
                                                    {.value = 2131200, .label = "D ST1"},
                                                    {.value = 2265600, .label = "D ST2"},
                                                    {.value = 2400000, .label = "D ST3"},
                                                    {.value = 2534400, .label = "S ST1"},
                                                    {.value = 2665600, .label = "S ST2"},
                                                    {.value = 2800000, .label = "S ST3"},
                                                    {.value = 2934400, .label = "L-C4C"}}};
const FixedLimits marikoEmcMaxClockFL = {.min = 1333000, .max = 2733000, .stepSize = 38400};
const Param marikoEmcMaxClock = {
    .name = "EMC Max Clock",
    .measure = "mHz",
    .description = NULL,
    .offset = getOffset(custTable.marikoEmcMaxClock),
    .length = 4,
    .defaultValue = custTable.marikoEmcMaxClock,
    .limitsCount = 2,
    .limits = {{.type = EFixedValues, .values = &marikoEmcMaxClockFV}, {.type = EFixedLimits, .values = &marikoEmcMaxClockFL}}};

    const FixedValues marikoEmcVddqVoltFV = {
    .valuesCount = 3, .values = {{.value = 550000, .label = "ECO"}, {.value = 650000}, {.value = 750000, .label = "SRT"}}};
const FixedLimits marikoEmcVddqVoltFL = {.min = 300000, .max = 800000, .stepSize = 100000};
const Param marikoEmcVddqVolt = {
    .name = "EMC VDDq Volt",
    .measure = "mV",
    .description = NULL,
    .offset = getOffset(custTable.marikoEmcVddqVolt),
    .length = 4,
    .defaultValue = custTable.marikoEmcVddqVolt,
    .limitsCount = 2,
    .limits = {{.type = EFixedValues, .values = &marikoEmcVddqVoltFV}, {.type = EFixedLimits, .values = &marikoEmcVddqVoltFL}}};

const FixedValues marikoEmcDvbShiftFV = {.valuesCount = 4,
                                         .values = {{.value = 3, .label = "AUTO"},
                                                    {.value = 2, .label = "AUTO ECO ST1"},
                                                    {.value = 1, .label = "AUTO ECO ST2"},
                                                    {.value = 0, .label = "AUTO ECO ST3"}}};
const FixedLimits marikoEmcDvbShiftFL = {.min = 300, .max = 1150, .stepSize = 10, .measure = "mV"};  // TODO ? Step size
const Param marikoEmcDvbShift = {
    .name = "EMC DVB Shift",
    .measure = NULL,
    .description = NULL,
    .offset = getOffset(custTable.marikoEmcDvbShift),
    .length = 4,
    .defaultValue = custTable.marikoEmcDvbShift,
    .limitsCount = 2,
    .limits = {{.type = EFixedValues, .values = &marikoEmcDvbShiftFV}, {.type = EFixedLimits, .values = &marikoEmcDvbShiftFL}}};

const unsigned int mRAMParamsCount = 3;
const Param *mRAMParams[] = {&marikoEmcMaxClock,&marikoEmcVddqVolt,&marikoEmcDvbShift};