#include "paramsMenu.h"

#include <stdlib.h>
#include <string.h>
#include <utils/sprintf.h>

#include "../../../gfx/gfxutils.h"
#include "../../../utils/utils.h"
#include "../../helpers/kiprw.h"
#include "../../helpers/param.h"
#include "../../service/kiptool.h"
#include "../gfx.h"
#include "editorMenu.h"
#include "ktMenu.h"
#include "tableMenu.h"

void printParamEntry(MenuEntry* entry, u32 maxLen, u8 highlighted, u32 bg, PrintParamAdditionalData* printParamAdditionalData) {
    if (entry->hide) return;

    (highlighted) ? SETCOLOR(bg, RGBUnionToU32(entry->optionUnion)) : SETCOLOR(RGBUnionToU32(entry->optionUnion), bg);

    u32 curX = 0, curY = 0;
    gfx_con_getpos(&curX, &curY);
    if (entry->type == ETLabel || entry->type == ETReset)
        gfx_puts_limit((const char*)entry->entry, maxLen);
    else if (entry->type == ETParam) {
        char* displayBuff = malloc(1024);
        const Param* param = (const Param*)entry->entry;
        s_printf(displayBuff, "%s - ", param->name);
        u32 value = getParamValueFromBuffer(printParamAdditionalData->custTable, param);
        getDisplayValue(param, displayBuff + strlen(displayBuff), value);
        addPostfix(param, displayBuff, value, 1, 1);
        const char* formattedBuff = getFormattedBuff(printParamAdditionalData->formatingData, displayBuff);
        gfx_puts_limit(formattedBuff, maxLen);
        free((void*)formattedBuff);
        free((void*)displayBuff);
    } else if (entry->type == ETTable) {
        const Table* table = (const Table*)entry->entry;
        gfx_puts_limit(table->name, maxLen);
    }
    gfx_putc('\n');
}

void newParamsMenu(const u8* custTable, const char* sectionTitle, const Params* params[], const Tables* tables[]) {
    unsigned int totalEntriesCount = 2;
    unsigned int startIndex = 0;
    for (unsigned int i = 0; params[i] != NULL; ++i) totalEntriesCount += params[i]->count;
    for (unsigned int i = 0; tables[i] != NULL; ++i) totalEntriesCount += tables[i]->count;
    MenuEntry* menuEntries = calloc(sizeof(MenuEntry), totalEntriesCount);
    menuEntries[0].optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT;
    menuEntries[0].type = ETLabel;
    menuEntries[0].entry = sectionTitle;
    while (1) {
        FormatingData formatingData = {0, 0, 0};
        unsigned int menuEntriesIndex = 1;
        for (unsigned int paramArrayIndex = 0; params[paramArrayIndex] != NULL; ++paramArrayIndex) {
            for (unsigned int paramI = 0; paramI < params[paramArrayIndex]->count; ++paramI) {
                const Param* param = params[paramArrayIndex]->params[paramI];
                menuEntries[menuEntriesIndex].optionUnion =
                    param->defaultValue == getParamValueFromBuffer(custTable, param) ? COLORTORGB(COLOR_DEFAULT_PARAM) : COLORTORGB(COLOR_CHANGED_PARAM);
                menuEntries[menuEntriesIndex].type = ETParam;
                menuEntries[menuEntriesIndex].entry = param;
                ++menuEntriesIndex;
            }
            FormatingData tmp;
            getFormatingData(&tmp, custTable, params[paramArrayIndex]->count, params[paramArrayIndex]->params);
            if (tmp.nameLen > formatingData.nameLen) formatingData.nameLen = tmp.nameLen;
            if (tmp.valueLen > formatingData.valueLen) formatingData.valueLen = tmp.valueLen;
            if (tmp.labelLen > formatingData.labelLen) formatingData.labelLen = tmp.labelLen;
        }
        for (unsigned int tableArrayIndex = 0; tables[tableArrayIndex] != NULL; ++tableArrayIndex) {
            for (unsigned int tableI = 0; tableI < tables[tableArrayIndex]->count; ++tableI) {
                menuEntries[menuEntriesIndex].optionUnion = COLORTORGB(COLOR_YELLOW);
                menuEntries[menuEntriesIndex].type = ETTable;
                menuEntries[menuEntriesIndex].entry = tables[tableArrayIndex]->tables[tableI];
                ++menuEntriesIndex;
            }
        }
        menuEntries[menuEntriesIndex].optionUnion = COLORTORGB(COLOR_WHITE);
        menuEntries[menuEntriesIndex].type = ETReset;
        menuEntries[menuEntriesIndex].entry = "Reset all values for this category";
        PrintParamAdditionalData printParamAdditionalData = {.custTable = custTable, .formatingData = &formatingData};
        MenuResult menuResult = newMenuKT(menuEntries, totalEntriesCount, startIndex, JoyA, &printParamAdditionalData,
                                          (void (*)(MenuEntry*, u32, u8, u32, const void*))printParamEntry);
        if (menuResult.buttons & JoyB) {
            free(menuEntries);
            return;
        }
        const MenuEntry selectedEntry = menuEntries[menuResult.index];
        if (selectedEntry.type == ETTable) {
            const Table* table = selectedEntry.entry;
            newTableMenu(custTable, table);
        } else if (selectedEntry.type == ETParam) {
#ifdef KT_DEBUG
            Input_t* input = hidRead();
            if (input->l || input->r) {
                gfx_clearscreenKT();
                unsigned int currentValue = getParamValueFromBuffer(custTable, selectedEntry.entry);
                char* currentValueStr = malloc(256);
                utoa(currentValue, currentValueStr, 10);
                char* oldValue = malloc(256);
                strcpy(oldValue, currentValueStr);
                char* value = ShowKeyboard(currentValueStr, false);
                if (value != NULL) {
                    const unsigned int newValue = atoi(value);
                    formatValueDiv(currentValueStr, newValue, newValue > 1500);
                    const char* message[] = {"Do you want to set a new value?", strcat(strcat(strcat(strcat(currentValueStr, " <- "), value), " <- "), oldValue),
                                             NULL};
                    if (confirmationDialog(message, ENO) == EYES) setParamValue(custTable, selectedEntry.entry, atoi(value));
                    free(value);
                }
                free(currentValueStr);
                free(oldValue);
                gfx_clearscreenKT();
            } else
                newEditorMenu(custTable, selectedEntry.entry);
#else
            newEditorMenu(custTable, selectedEntry.entry);
#endif
        } else if (selectedEntry.type == ETReset) {
            const char* message[] = {"Do you want to reset all params in this category?", NULL};
            if (confirmationDialog(message, ENO) == EYES) {
                for (unsigned int i = 0; params[i] != NULL; ++i) {
                    for (unsigned int j = 0; j < params[i]->count; ++j) {
                        setParamValueWithoutSaveSession(custTable, params[i]->params[j], params[i]->params[j]->defaultValue);
                    }
                }
                for (unsigned int i = 0; tables[i] != NULL; ++i) {
                    for (unsigned int j = 0; j < tables[i]->count; ++j) {
                        for (unsigned int k = 0; k < tables[i]->tables[j]->paramsCount; ++k)
                            setParamValueWithoutSaveSession(custTable, tables[i]->tables[j]->params[k], tables[i]->tables[j]->params[k]->defaultValue);
                    }
                }
                char* message = calloc(256, 1);
                s_printf(message, "[Session] Category: %s has been reset", sectionTitle);
                gfx_printBottomInfoKT(message);
                setIsChangesApplied(0);
                free(message);
            }
        }
        startIndex = menuResult.index;
    }
}
