#pragma once

#include "../../../gfx/gfxutils.h"
#include "../../../hid/hid.h"
#include "../../params/param.h"
#include "confirmationDialog.h"

enum ManualValueStatus { EMVS_GOOD, EMVS_EXIT, EMVS_ITS_NOT_FIXEDLIMITS, EMVS_INVALID_VALUE };
typedef struct ManualValueResult {
    unsigned int value;
    enum ManualValueStatus status;
} ManualValueResult;

ManualValueResult manualValueDialog(const Param* param, int defaultValue);
