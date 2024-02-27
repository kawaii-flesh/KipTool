#pragma once

#include "../customize.h"
#include "../param.h"

#define getOffset(param) (const void *)&param - (const void *)custTable.cust

const FixedOneValue gKipVersionFOV = {19};
const Param gKipVersion = {.name = "Kip version",
                           .measure = NULL,
                           .description = NULL,
                           .offset = getOffset(custTable.custRev),
                           .length = 4,
                           .defaultValue = CURRENT_VERSION,
                           .limitsCount = 1,
                           .limits = {{.type = EFixedOneValue, .values = &gKipVersionFOV}}};