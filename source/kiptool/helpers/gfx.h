#pragma once
#include "../../gfx/gfx.h"
#include "../../gfx/gfxutils.h"
#include "../params/param.h"
#include "../params/table.h"

enum MenuEntryType { ELabel, EParam, ETable };

typedef struct ParamsMenuEntry {
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
    void *entry;
    u8 icon;
} ParamsMenuEntry;

void gfx_printTopInfoKT();

void gfx_clearscreenKT();
int newMenuKT(ParamsMenuEntry entries[], const u8 *custTable, const unsigned int entriesCount, unsigned int startIndex);
void newParamsMenu(const u8 *custTable, const char *sectionTitle, const Params *params[], const unsigned int paramsArraysCount,
                   const Tables *tables[], unsigned int tablesArraysCount);
void printParamEntry(ParamsMenuEntry entry, const u8 *custTable, u32 maxLen, u8 highlighted, u32 bg);