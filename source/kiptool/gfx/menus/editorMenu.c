#include "editorMenu.h"

#include <mem/heap.h>
#include <string.h>
#include <utils/sprintf.h>

#include "../../helpers/kiprw.h"
#include "../../helpers/param.h"
#include "../dialogs/manualValueDialog.h"

bool validateValueByFixedLimits(const FixedLimits* fixedLimits, const unsigned int value) {
    return fixedLimits->min <= value && value <= fixedLimits->max && value % fixedLimits->stepSize == 0;
}

void printValueEntry(MenuEntry* entry, u32 maxLen, u8 highlighted, u32 bg, const Param* param) {
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
    else if (entry->type == EValue) {
        char* displayBuff = calloc(1024, 1);
        const Value* value = entry->entry;
        getDisplayValue(param, displayBuff + strlen(displayBuff), value->value);
        gfx_puts_limit(displayBuff, maxLen);
        free((void*)displayBuff);
    } else if (entry->type == ELimits) {
        char* displayBuff = calloc(1024, 1);
        const FixedLimits* fixedLimits = entry->entry;
        int min = fixedLimits->min;
        if (min > 1500) min /= 1000;
        int max = fixedLimits->max;
        if (max > 1500) max /= 1000;
        int stepSize = fixedLimits->stepSize;
        if (stepSize > 1500) stepSize /= 1000;
        const char* measure = param->measure != NULL ? param->measure : fixedLimits->measure;
        s_printf(displayBuff, "Manual value - min: %d max: %d step: %d", min, max, stepSize, measure != NULL ? measure : "");
        gfx_puts_limit(displayBuff, maxLen);
        free((void*)displayBuff);
    }

    gfx_putc('\n');
}

void newEditorMenu(const u8* custTable, const Param* param) {
    const unsigned int limitsCount = param->limitsCount;
    const FixedValues* fixedValues = NULL;
    const FixedLimits* fixedLimits = NULL;
    unsigned int totalEntriesCount = 1;
    for (unsigned int i = 0; i < limitsCount; ++i)
        if (param->limits[i].type == EFixedLimits) {
            fixedLimits = param->limits[i].values;
            ++totalEntriesCount;
        } else if (param->limits[i].type == EFixedValues) {
            fixedValues = param->limits[i].values;
            totalEntriesCount += fixedValues->valuesCount;
        }

    MenuEntry* menuEntries = calloc(sizeof(MenuEntry), totalEntriesCount);
    menuEntries[0].optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT;
    menuEntries[0].type = ELabel;
    menuEntries[0].entry = (void*)param->name;
    unsigned int menuEntriesIndex = 1;
    unsigned int paramCurrentValue = getParamValueFromBuffer(custTable, param);
    unsigned int startIndex = 0;
    bool canBeManualValue = validateValueByFixedLimits(fixedLimits, paramCurrentValue);
    if (fixedValues != NULL)
        for (unsigned int valueI = 0; valueI < fixedValues->valuesCount; ++valueI) {
            const Value* fixedValue = &fixedValues->values[valueI];
            menuEntries[menuEntriesIndex].type = EValue;
            menuEntries[menuEntriesIndex].entry = fixedValue;
            if (paramCurrentValue == fixedValue->value) {
                startIndex = menuEntriesIndex;
                menuEntries[menuEntriesIndex].optionUnion = COLORTORGB(COLOR_BLUE);
            } else
                menuEntries[menuEntriesIndex].optionUnion = COLORTORGB(COLOR_VIOLET);
            ++menuEntriesIndex;
        }
    if (fixedLimits != NULL) {
        menuEntries[menuEntriesIndex].type = ELimits;
        menuEntries[menuEntriesIndex].entry = fixedLimits;
        if (canBeManualValue && startIndex == 0) {
            startIndex = menuEntriesIndex;
            menuEntries[menuEntriesIndex].optionUnion = COLORTORGB(COLOR_BLUE);
        } else
            menuEntries[menuEntriesIndex].optionUnion = COLORTORGB(COLOR_YELLOW);
    }

    while (1) {
        int res = newMenuKT(menuEntries, totalEntriesCount, startIndex, param, printValueEntry);
        if (res == -1) {
            break;
        }
        const MenuEntry selectedEntry = menuEntries[res + 1];
        if (selectedEntry.type == ELimits) {
            const ManualValueResult manualValueResult = manualValueDialog(param, canBeManualValue ? paramCurrentValue : -1);
        }
    }
    free(menuEntries);
    return;  // selectedEntry.entry;
}