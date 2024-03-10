#pragma once

#include "../defaultCustomize.h"
#include "../param.h"

const FixedOneValue gKipVersionFOV = {19};
const Param gKipVersion = {.name = "Kip version",
                           .category = GENERAL,
                           .platform = COMMON,
                           .measure = NULL,
                           .description = NULL,
                           .offset = getOffset(defaultCustTable.custRev),
                           .length = 4,
                           .defaultValue = CURRENT_VERSION,
                           .limitsCount = 1,
                           .limits = {{.type = EFixedOneValue, .values = &gKipVersionFOV}}};