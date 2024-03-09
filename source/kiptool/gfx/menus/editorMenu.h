#pragma once

#include "../../params/param.h"
#include "../dialogs/manualValueDialog.h"
#include "ktMenu.h"

void printValueEntry(MenuEntry* entry, u32 maxLen, u8 highlighted, u32 bg, const Param* param);

void newEditorMenu(const u8* custTable, const Param* param);