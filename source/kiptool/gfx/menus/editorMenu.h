#pragma once

#include "../../params/param.h"
#include "../dialogs/manualValueDialog.h"
#include "ktMenu.h"

typedef struct EditorAdditionalData {
    const Param* param;
    const unsigned int currentValue;
} EditorAdditionalData;

void printValueEntry(MenuEntry* entry, u32 maxLen, u8 highlighted, u32 bg, const EditorAdditionalData* editorAdditionalData);

void newEditorMenu(const u8* custTable, const Param* param);
