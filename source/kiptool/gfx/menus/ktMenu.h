#pragma once

#include "../../../gfx/gfxutils.h"
#include "ktMenu.h"

enum MenuEntryType { ETLabel, ETParam, ETTable, ETValue, ETLimits, ETReset, ETFixedRange };

typedef struct MenuEntry {
    union {
        struct {
            u32 B : 8;
            u32 G : 8;
            u32 R : 8;
            u32 skip : 1;
            u32 hide : 1;
        };
        u32 optionUnion;
    };
    enum MenuEntryType type;
    const void* entry;
    u8 icon;
} MenuEntry;

int newMenuKT(MenuEntry entries[], const unsigned int entriesCount, unsigned int startIndex, const void* additionalData,
              void (*printMenuEntryFunc)(MenuEntry* entry, u32 maxLen, u8 highlighted, u32 bg, const void* additionalData));

void printEntry(MenuEntry* entry, u32 maxLen, u8 highlighted, u32 bg, const void* additionalData);
