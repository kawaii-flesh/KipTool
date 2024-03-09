#include "paramsMenu.h"

#include "../../../gfx/gfxutils.h"
#include "../../helpers/kiprw.h"
#include "editorMenu.h"
#include "ktMenu.h"
#include "tableMenu.h"

void printParamEntry(MenuEntry* entry, u32 maxLen, u8 highlighted, u32 bg, u8* custTable) {
    if (entry->hide) return;

    (highlighted) ? SETCOLOR(bg, RGBUnionToU32(entry->optionUnion)) : SETCOLOR(RGBUnionToU32(entry->optionUnion), bg);

    if (entry->icon) {
        gfx_putc(entry->icon);
        gfx_putc(' ');
        maxLen -= 2;
    }

    u32 curX = 0, curY = 0;
    gfx_con_getpos(&curX, &curY);
    if (entry->type == ELabel)
        gfx_puts_limit((const char*)entry->entry, maxLen);
    else if (entry->type == EParam) {
        const char* displayBuff = calloc(1024, 1);
        const Param* param = (const Param*)entry->entry;
        s_printf(displayBuff, "%s - ", param->name);
        getDisplayValue(param, displayBuff + strlen(displayBuff), getParamValueFromBuffer(custTable, param));
        gfx_puts_limit(displayBuff, maxLen);
        free(displayBuff);
    } else if (entry->type == ETable) {
        const Table* table = (const Table*)entry->entry;
        gfx_puts_limit(table->name, maxLen);
    }

    gfx_putc('\n');
}

void newParamsMenu(const u8* custTable, const char* sectionTitle, const Params* params[], const unsigned int paramsArraysCount,
                   const Tables* tables[], unsigned int tablesArraysCount) {
    unsigned int totalEntriesCount = 1;
    unsigned int startIndex = 0;
    for (unsigned int i = 0; i < paramsArraysCount; ++i) totalEntriesCount += params[i]->count;
    for (unsigned int i = 0; i < tablesArraysCount; ++i) totalEntriesCount += tables[i]->count;
    MenuEntry* menuEntries = calloc(sizeof(MenuEntry), totalEntriesCount);
    menuEntries[0].optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT;
    menuEntries[0].type = ELabel;
    menuEntries[0].entry = sectionTitle;
    unsigned int menuEntriesIndex = 1;
    for (unsigned int paramArrayIndex = 0; paramArrayIndex < paramsArraysCount; ++paramArrayIndex) {
        for (unsigned int paramI = 0; paramI < params[paramArrayIndex]->count; ++paramI) {
            menuEntries[menuEntriesIndex].optionUnion = COLORTORGB(COLOR_VIOLET);
            menuEntries[menuEntriesIndex].type = EParam;
            menuEntries[menuEntriesIndex].entry = params[paramArrayIndex]->params[paramI];
            ++menuEntriesIndex;
        }
    }
    for (unsigned int tableArrayIndex = 0; tableArrayIndex < tablesArraysCount; ++tableArrayIndex) {
        for (unsigned int tableI = 0; tableI < tables[tableArrayIndex]->count; ++tableI) {
            menuEntries[menuEntriesIndex].optionUnion = COLORTORGB(COLOR_YELLOW);
            menuEntries[menuEntriesIndex].type = ETable;
            menuEntries[menuEntriesIndex].entry = tables[tableArrayIndex]->tables[tableI];
            ++menuEntriesIndex;
        }
    }
    while (1) {
        int res = newMenuKT(menuEntries, totalEntriesCount, startIndex, custTable, printParamEntry);
        if (res == -1) {
            free(menuEntries);
            return;
        }
        const MenuEntry selectedEntry = menuEntries[res + 1];
        if (selectedEntry.type == ETable) {
            const Table* table = selectedEntry.entry;
            newTableMenu(custTable, table);
            continue;
        }
        newEditorMenu(custTable, selectedEntry.entry);
        startIndex = res + 1;
    }
}