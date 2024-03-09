#pragma once

#include "../../../gfx/gfxutils.h"
#include "../../../hid/hid.h"

enum ConfirmationDialogResult { EYES, ENO, ENOT_SELECTED };

enum ConfirmationDialogResult confirmationDialog(const char* message, const enum ConfirmationDialogResult defaultValue);