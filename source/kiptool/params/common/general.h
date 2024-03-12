#pragma once

#include "../defaultCustomize.h"
#include "../param.h"

const FixedOneValue cKipVersionFOV = {19};
const Param cKipVersion = {.name = "Kip version",
                           .measure = NULL,
                           .description = NULL,
                           .offset = getOffset(defaultCustTable.custRev),
                           .defaultValue = KT_CUST_VER,
                           .limitsCount = 1,
                           .limits = {{.type = EFixedOneValue, .values = &cKipVersionFOV}}};