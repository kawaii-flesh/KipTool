#include "editorMenu.h"

#include <mem/heap.h>
#include <stdlib.h>
#include <string.h>
#include <utils/sprintf.h>

#include "../../helpers/kiprw.h"
#include "../../helpers/param.h"
#include "../dialogs/manualValueDialog.h"
#include "../gfx.h"
#include "ktMenu.h"

bool validateValueByFixedLimits(const FixedLimits* fixedLimits, const unsigned int value) {
    return fixedLimits->min <= value && value <= fixedLimits->max && value % fixedLimits->stepSize == 0;
}

void printValueEntry(MenuEntry* entry, u32 maxLen, u8 highlighted, u32 bg, const EditorAdditionalData* editorAdditionalData) {
    if (entry->hide) return;

    (highlighted) ? SETCOLOR(bg, RGBUnionToU32(entry->optionUnion)) : SETCOLOR(RGBUnionToU32(entry->optionUnion), bg);

    u32 curX = 0, curY = 0;
    gfx_con_getpos(&curX, &curY);
    char* displayBuff = malloc(256);
    if (entry->type == ETReset) {
        s_printf(displayBuff, "%s", "Reset to the default value - ");
        formatValueDiv(displayBuff + strlen(displayBuff), editorAdditionalData->param->defaultValue, editorAdditionalData->param->defaultValue > 1500);
    } else if (entry->type == ETFixedRange) {
        getDisplayValue(editorAdditionalData->param, displayBuff, (unsigned int)entry->entry);
        addPostfix(editorAdditionalData->param, displayBuff, (unsigned int)entry->entry, 0, 1);
    } else if (entry->type == ETValue) {
        const Value* value = entry->entry;
        getDisplayValue(editorAdditionalData->param, displayBuff, value->value);
        addPostfix(editorAdditionalData->param, displayBuff, value->value, 0, 1);
    } else if (entry->type == ETLimits) {
        const FixedLimits* fixedLimits = entry->entry;
        int min = fixedLimits->min;
        int max = fixedLimits->max;
        int stepSize = fixedLimits->stepSize;
        bool div = min > 1500 || editorAdditionalData->currentValue > 1500 || max > 1500 || stepSize > 1500;
        char* minStr = malloc(8);
        formatValueDiv(minStr, min, div);
        char* curValStr = malloc(8);
        formatValueDiv(curValStr, editorAdditionalData->currentValue, div);
        char* maxStr = malloc(8);
        formatValueDiv(maxStr, max, div);
        char* stepStr = malloc(8);
        formatValueDiv(stepStr, stepSize, div);
        const char* measure = editorAdditionalData->param->measure != NULL ? editorAdditionalData->param->measure : fixedLimits->measure;
        s_printf(displayBuff, "Manual value - min: %s curVal: %s max: %s step: %s%s", minStr,
                 validateValueByFixedLimits(fixedLimits, editorAdditionalData->currentValue) ? curValStr : "preset", maxStr, stepStr,
                 measure != NULL ? measure : "");
        free(minStr);
        free(curValStr);
        free(maxStr);
        free(stepStr);
    }
    if (entry->type == ETLabel)
        gfx_puts_limit((const char*)entry->entry, maxLen);
    else
        gfx_puts_limit(displayBuff, maxLen);
    free(displayBuff);
    gfx_putc('\n');
}

void newEditorMenu(const u8* custTable, const Param* param) {
    const unsigned int limitsCount = param->limitsCount;
    const FixedValues* fixedValues = NULL;
    const FixedLimits* fixedLimits = NULL;
    const FixedRange* fixedRange = NULL;
    unsigned int totalEntriesCount = 2;
    for (unsigned int i = 0; i < limitsCount; ++i) {
        if (param->limits[i].type == EFixedLimits) {
            fixedLimits = param->limits[i].values;
            ++totalEntriesCount;
        } else if (param->limits[i].type == EFixedValues) {
            fixedValues = param->limits[i].values;
            totalEntriesCount += fixedValues->valuesCount;
        } else if (param->limits[i].type == EFixedRange) {
            fixedRange = param->limits[i].values;
            totalEntriesCount += (fixedRange->end - fixedRange->start);
            ++totalEntriesCount;
        }
    }

    MenuEntry* menuEntries = calloc(sizeof(MenuEntry), totalEntriesCount);
    menuEntries[0].optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT;
    menuEntries[0].type = ETLabel;
    menuEntries[0].entry = (void*)param->name;
    while (1) {
        gfx_clearscreenKT();
        unsigned int startIndex = 0;
        unsigned int menuEntriesIndex = 1;
        unsigned int paramCurrentValue = getParamValueFromBuffer(custTable, param);
        bool canBeManualValue = validateValueByFixedLimits(fixedLimits, paramCurrentValue);
        if (fixedValues != NULL)
            for (unsigned int valueI = 0; valueI < fixedValues->valuesCount; ++valueI) {
                const Value* fixedValue = &fixedValues->values[valueI];
                menuEntries[menuEntriesIndex].type = ETValue;
                menuEntries[menuEntriesIndex].entry = fixedValue;
                if (paramCurrentValue == fixedValue->value) {
                    startIndex = menuEntriesIndex;
                    menuEntries[menuEntriesIndex].optionUnion = COLORTORGB(COLOR_BLUE);
                } else
                    menuEntries[menuEntriesIndex].optionUnion =
                        param->defaultValue == fixedValue->value ? COLORTORGB(COLOR_DEFAULT_PARAM) : COLORTORGB(COLOR_CHANGED_PARAM);
                ++menuEntriesIndex;
            }
        if (fixedLimits != NULL) {
            menuEntries[menuEntriesIndex].type = ETLimits;
            menuEntries[menuEntriesIndex].entry = fixedLimits;
            if (canBeManualValue && startIndex == 0) {
                startIndex = menuEntriesIndex;
                menuEntries[menuEntriesIndex].optionUnion = COLORTORGB(COLOR_BLUE);
            } else
                menuEntries[menuEntriesIndex].optionUnion = COLORTORGB(COLOR_YELLOW);
            ++menuEntriesIndex;
        }
        if (fixedRange != NULL)
            for (unsigned int i = fixedRange->start; i <= fixedRange->end; ++i) {
                menuEntries[menuEntriesIndex].type = ETFixedRange;
                menuEntries[menuEntriesIndex].entry = (const void*)i;  // It is not a bug. Although the pointer is waiting, we assign an unsigned int
                if (paramCurrentValue == i) {
                    startIndex = menuEntriesIndex;
                    menuEntries[menuEntriesIndex].optionUnion = COLORTORGB(COLOR_BLUE);
                } else
                    menuEntries[menuEntriesIndex].optionUnion = param->defaultValue == i ? COLORTORGB(COLOR_DEFAULT_PARAM) : COLORTORGB(COLOR_CHANGED_PARAM);
                ++menuEntriesIndex;
            }
        menuEntries[menuEntriesIndex].optionUnion = COLORTORGB(COLOR_WHITE);
        menuEntries[menuEntriesIndex].type = ETReset;

        EditorAdditionalData editorAdditionalData = {.param = param, .currentValue = paramCurrentValue};
        MenuResult menuResult =
            newMenuKT(menuEntries, totalEntriesCount, startIndex, JoyA, &editorAdditionalData, (void (*)(MenuEntry*, u32, u8, u32, const void*))printValueEntry);
        if (menuResult.buttons & JoyB) {
            break;
        }
        const MenuEntry selectedEntry = menuEntries[menuResult.index];
        if (selectedEntry.type == ETLimits) {
            const ManualValueResult manualValueResult = manualValueDialog(param, canBeManualValue ? paramCurrentValue : -1);
            if (manualValueResult.status == EMVS_GOOD) setParamValue(custTable, param, manualValueResult.value);
        } else if (selectedEntry.type == ETValue) {
            const Value* value = selectedEntry.entry;
            setParamValue(custTable, param, value->value);
        } else if (selectedEntry.type == ETFixedRange) {
            setParamValue(custTable, param, (unsigned int)selectedEntry.entry);  // It is not a bug
        } else if (selectedEntry.type == ETReset) {
            const char* message[] = {"Do you want to reset param?", NULL};
            if (confirmationDialog(message, ENO) == EYES) {
                setParamValue(custTable, param, param->defaultValue);
                char* message = calloc(256, 1);
                s_printf(message, "[Session] Param: %s has been reset", param->name);
                gfx_printBottomInfoKT(message);
                free(message);
            }
        }
    }
    free(menuEntries);
    return;
}
