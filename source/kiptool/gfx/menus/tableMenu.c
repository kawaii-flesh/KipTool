#include "tableMenu.h"

#include <mem/heap.h>
#include <string.h>
#include <utils/sprintf.h>

#include "../../helpers/kiprw.h"
#include "../../service/session.h"
#include "../gfx.h"
#include "editorMenu.h"
#include "ktMenu.h"
#include "paramsMenu.h"

void newTableMenu(const u8* custTable, const Table* table) {
    const unsigned int paramsCount = table->paramsCount;
    unsigned int totalEntriesCount = 2 + table->paramsCount;
    MenuEntry* menuEntries = calloc(sizeof(MenuEntry), totalEntriesCount);
    menuEntries[0].optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT;
    menuEntries[0].type = ETLabel;
    menuEntries[0].entry = table->name;
    unsigned int menuEntriesIndex = 1;
    for (unsigned int paramI = 0; paramI < paramsCount; ++paramI) {
        const Param* param = table->params[paramI];
        menuEntries[menuEntriesIndex].optionUnion =
            param->defaultValue == getParamValueFromBuffer(custTable, param) ? COLORTORGB(COLOR_DEFAULT_PARAM) : COLORTORGB(COLOR_CHANGED_PARAM);
        menuEntries[menuEntriesIndex].type = ETParam;
        menuEntries[menuEntriesIndex].entry = param;
        ++menuEntriesIndex;
    }
    menuEntries[menuEntriesIndex].optionUnion = COLORTORGB(COLOR_GREY);
    menuEntries[menuEntriesIndex].type = ETReset;
    menuEntries[menuEntriesIndex].entry = "Reset the table to default values";
    unsigned int startIndex = 0;
    unsigned int maxParamNameLen = 0;
    FormatingData formatingData;
    while (1) {
        menuEntriesIndex = 1;
        for (unsigned int paramI = 0; paramI < paramsCount; ++paramI) {
            const Param* param = table->params[paramI];
            menuEntries[menuEntriesIndex].optionUnion =
                param->defaultValue == getParamValueFromBuffer(custTable, param) ? COLORTORGB(COLOR_DEFAULT_PARAM) : COLORTORGB(COLOR_CHANGED_PARAM);
            menuEntries[menuEntriesIndex].type = ETParam;
            menuEntries[menuEntriesIndex].entry = param;
            const unsigned int paramNameLen = strlen(param->name);
            if (paramNameLen > maxParamNameLen) maxParamNameLen = paramNameLen;
            ++menuEntriesIndex;
        }
        getFormatingData(&formatingData, custTable, table->paramsCount, table->params);
        const PrintParamAdditionalData printParamAdditionalData = {.custTable = custTable, .formatingData = &formatingData};
        int res = newMenuKT(menuEntries, totalEntriesCount, startIndex, &printParamAdditionalData, printParamEntry);
        if (res == -1) {
            free(menuEntries);
            return;
        } else {
            const MenuEntry selectedEntry = menuEntries[res + 1];
            startIndex = res + 1;
            if (selectedEntry.type == ETReset) {
                const char* message[] = {"Do you want to reset tables params?", NULL};
                if (confirmationDialog(message, ENO) == EYES) {
                    for (unsigned int i = 0; i < table->paramsCount; ++i)
                        setParamValueWithoutSaveSession(custTable, table->params[i], table->params[i]->defaultValue);
                    saveSession((const CustomizeTable*)custTable);
                    char* message = calloc(256, 1);
                    s_printf(message, "[Session] Table: %s has been reset", table->name);
                    gfx_printBottomInfoKT(message);
                    free(message);
                }
            } else
                newEditorMenu(custTable, selectedEntry.entry);
        }
    }
}
