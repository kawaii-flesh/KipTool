#pragma once
#include "../../gfx/gfx.h"
#include "../../gfx/gfxutils.h"
#include "../params/param.h"
#include "../params/table.h"

enum MenuEntryType { ELabel, EParam, ETable, EValue, ELimits };

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
    void *entry;
    u8 icon;
} MenuEntry;

enum ConfirmationDialogResult { EYES, ENO, ENOT_SELECTED };

enum ManualValueStatus { EMVS_GOOD, EMVS_EXIT, EMVS_ITS_NOT_FIXEDLIMITS, EMVS_INVALID_VALUE };
typedef struct ManualValueResult {
    unsigned int value;
    enum ManualValueStatus status;
} ManualValueResult;

void gfx_printTopInfoKT();

void gfx_clearscreenKT();
void printEntry(MenuEntry *entry, u32 maxLen, u8 highlighted, u32 bg, void *additionalData);
int newMenuKT(MenuEntry entries[], const unsigned int entriesCount, unsigned int startIndex, void *additionalData,
              void (*printMenuEntryFunc)(MenuEntry *entry, u32 maxLen, u8 highlighted, u32 bg, void *data));
void printParamEntry(MenuEntry *entry, u32 maxLen, u8 highlighted, u32 bg, u8 *custTable);
void newTableMenu(const u8 *custTable, const Table *table);
void newParamsMenu(const u8 *custTable, const char *sectionTitle, const Params *params[], const unsigned int paramsArraysCount,
                   const Tables *tables[], unsigned int tablesArraysCount);
enum ConfirmationDialogResult confirmationDialog(const char *message, const enum ConfirmationDialogResult defaultValue);
ManualValueResult manualValueDialog(const Param *param, int defaultValue);