#include "gfx.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../../hid/hid.h"
#include "../params/table.h"
#include "hw.h"
#include "kiprw.h"
#include "param.h"

void gfx_printTopInfoKT() {
    SETCOLOR(COLOR_DEFAULT, COLOR_WHITE);
    gfx_con_setpos(0, 0);
    gfx_printf("Kip Tool %d.%d.%d | SoC: %s | Battery: %d%% %c\n", KT_VER_MJ, KT_VER_MN, KT_VER_BF,
               getHWType() == COMMON   ? COMMON
               : getHWType() == MARIKO ? "Mariko"
                                       : "Erista",
               getBatteryValue(), (getCurrentChargeState() ? 129 : 32));
    RESETCOLOR;
}

void gfx_clearscreenKT() {
    gfx_boxGrey(0, 16, 1279, 703, 0x1b);

    gfx_boxGrey(0, 703, 1279, 719, 0xFF);
    gfx_boxGrey(0, 0, 1279, 15, 0xFF);

    gfx_printTopInfoKT();
}

int newMenuKT(ParamsMenuEntry entries[], const u8 *custTable, const unsigned int entriesCount, unsigned int startIndex) {
    int screenLenX = 60;
    int screenLenY = 42;
    int selected = startIndex;

    bool haveSelectable = false;
    for (unsigned int i = 0; i < entriesCount; ++i) {
        haveSelectable = !(entries[i].optionUnion & SKIPHIDEBITS);
        if (haveSelectable == true) break;
    }
    if (!haveSelectable) return -1;
    while (entries[selected].optionUnion & SKIPHIDEBITS) {
        selected++;
        if (selected >= entriesCount) selected = 0;
    }
    int lastIndex = selected;
    u32 startX = 0, startY = 0;
    gfx_con_getpos(&startX, &startY);

    u32 bgColor = COLOR_DEFAULT;

    bool redrawScreen = true;
    Input_t *input = hidRead();

    u32 lastPress = 1000 + get_tmr_ms();
    u32 holdTimer = 300;
    int totalPageCount = ((entriesCount - 1) / screenLenY) + 1;

    while (1) {
        int currentPage = (selected / screenLenY) + 1;
        u32 lastDraw = get_tmr_ms();
        if (redrawScreen) {
            SETCOLOR(COLOR_DEFAULT, COLOR_WHITE);
            char temp[40] = "";
            s_printf(temp, " Page %d / %d | Total %d entries", currentPage, totalPageCount, entriesCount - 1);
            gfx_con_setpos(YLEFT - strlen(temp) * 18, 0);
            gfx_printf(temp);

            gfx_con_setpos(startX, startY);

            if (redrawScreen) {
                minerva_periodic_training();
                gfx_boxGrey(startX, startY, startX + screenLenX * 16, startY + screenLenY * 16, 0x1B);
            }

            int start = selected / screenLenY * screenLenY;
            gfx_con_setpos(startX, startY);
            gfx_printf("%b", startX);
            for (int i = start; i < MIN(entriesCount, start + screenLenY); i++) {
                printParamEntry(entries[i], custTable, screenLenX, (i == selected), bgColor);
            }
            gfx_printf("%b", 0);
        } else if (lastIndex != selected) {
            u32 minLastCur = MIN(lastIndex, selected);
            u32 maxLastCur = MAX(lastIndex, selected);
            gfx_con_setpos(startX, startY + ((minLastCur % screenLenY) * 16));
            printParamEntry(entries[minLastCur], custTable, screenLenX, (minLastCur == selected), bgColor);
            gfx_con_setpos(startX, startY + ((maxLastCur % screenLenY) * 16));
            printParamEntry(entries[maxLastCur], custTable, screenLenX, (minLastCur != selected), bgColor);
        }

        lastIndex = selected;

        SETCOLOR(COLOR_DEFAULT, COLOR_WHITE);
        gfx_con_setpos(0, 704);
        gfx_printf("Time taken for screen draw: %dms  ", get_tmr_ms() - lastDraw);

        while (hidRead()) {
            if (!(input->buttons)) {
                holdTimer = 300;
                break;
            }

            if (input->buttons & (JoyRUp | JoyRDown)) holdTimer = 40;

            if ((lastPress + holdTimer) < get_tmr_ms()) {
                if (holdTimer > 50) holdTimer -= 50;
                break;
            }
        }

        int currentPageFirstIndex = (currentPage - 1) * screenLenY;
        int nextPageFirstIndex = currentPageFirstIndex + screenLenY;
        bool pageTurn = false;
        while (1) {
            if (hidRead()->a) {
                int skipableBefore = 0;
                int tmp = selected;
                while (tmp != -1)
                    if (entries[--tmp].optionUnion & SKIPHIDEBITS) ++skipableBefore;
                return selected - skipableBefore;
            } else if (input->b)
                return -1;
            else if (input->down || input->rDown) {  // Rdown should probs not trigger a page change. Same for RUp
                ++selected;
                break;
            } else if (input->right) {
                if (totalPageCount == 1) {
                    selected = entriesCount - 1;
                    break;
                } else if (totalPageCount > 1) {
                    if (currentPage == totalPageCount)
                        selected = 0;
                    else
                        selected = nextPageFirstIndex;
                    while (selected < entriesCount && entries[selected].optionUnion & SKIPHIDEBITS) ++selected;
                    pageTurn = true;
                    break;
                }
            } else if (input->up || input->rUp) {
                --selected;
                break;
            } else if (input->left) {
                if (totalPageCount == 1) {
                    selected = currentPageFirstIndex;
                    while (selected < entriesCount - 1 && entries[selected].optionUnion & SKIPHIDEBITS) ++selected;
                    break;
                } else if (totalPageCount > 1) {
                    if (currentPage == 1)
                        selected = (totalPageCount - 1) * screenLenY;
                    else
                        selected = (currentPage - 2) * screenLenY;
                    while (selected < entriesCount && entries[selected].optionUnion & SKIPHIDEBITS) ++selected;
                    pageTurn = true;
                    break;
                }
            } else {
                holdTimer = 300;
                gfx_printTopInfoKT();
            }
        }

        lastPress = get_tmr_ms();

        if (selected < lastIndex && !pageTurn || selected == entriesCount - 1) {
            while (selected > currentPageFirstIndex - 1 && entries[selected].optionUnion & SKIPHIDEBITS) --selected;
            if (selected < currentPageFirstIndex) {
                selected = totalPageCount == 1 ? entriesCount - 1 : MIN(nextPageFirstIndex - 1, entriesCount - 1);
                while (selected != 0 && entries[selected].optionUnion & SKIPHIDEBITS) --selected;
            }
        } else if (selected > lastIndex && !pageTurn) {
            while (selected < entriesCount && entries[selected].optionUnion & SKIPHIDEBITS) ++selected;
            if (selected >= nextPageFirstIndex || selected >= entriesCount) {
                selected = currentPageFirstIndex;
                while (selected < entriesCount - 1 && entries[selected].optionUnion & SKIPHIDEBITS) ++selected;
            }
        }

        redrawScreen = (selected / screenLenY != lastIndex / screenLenY);
    }
}

const Param *newTableMenu(const u8 *custTable, const Table *table) {
    const unsigned int paramsCount = table->paramsCount;
    unsigned int totalEntriesCount = 1 + table->paramsCount;
    ParamsMenuEntry *menuEntries = calloc(sizeof(ParamsMenuEntry), totalEntriesCount);
    menuEntries[0].optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT;
    menuEntries[0].type = ELabel;
    menuEntries[0].entry = table->name;
    unsigned int menuEntriesIndex = 1;
    for (unsigned int paramI = 0; paramI < paramsCount; ++paramI) {
        menuEntries[menuEntriesIndex].optionUnion = COLORTORGB(COLOR_BLUE);
        menuEntries[menuEntriesIndex].type = EParam;
        menuEntries[menuEntriesIndex].entry = table->params[paramI];
        ++menuEntriesIndex;
    }
    int res = newMenuKT(menuEntries, custTable, totalEntriesCount, 0);
    if (res == -1) {
        free(menuEntries);
        return NULL;
    }
    const ParamsMenuEntry selectedEntry = menuEntries[res + 1];
    free(menuEntries);
    return selectedEntry.entry;
}
void newParamsMenu(const u8 *custTable, const char *sectionTitle, const Params *params[], const unsigned int paramsArraysCount,
                   const Tables *tables[], unsigned int tablesArraysCount) {
    unsigned int totalEntriesCount = 1;
    unsigned int startIndex = 0;
    for (unsigned int i = 0; i < paramsArraysCount; ++i) totalEntriesCount += params[i]->count;
    for (unsigned int i = 0; i < tablesArraysCount; ++i) totalEntriesCount += tables[i]->count;
    ParamsMenuEntry *menuEntries = calloc(sizeof(ParamsMenuEntry), totalEntriesCount);
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
        int res = newMenuKT(menuEntries, custTable, totalEntriesCount, startIndex);
        if (res == -1) {
            free(menuEntries);
            return NULL;
        }
        const ParamsMenuEntry selectedEntry = menuEntries[res + 1];
        if (selectedEntry.type == ETable) {
            startIndex = res + 1;
            const Table *table = selectedEntry.entry;
            const Param *selectedParam = newTableMenu(custTable, table);
            if (selectedParam == NULL) continue;
            return selectedParam;  // TODO Open edit dialog
        }
        free(menuEntries);
        return selectedEntry.entry;  // TODO Open edit dialog
    }
}

void printParamEntry(ParamsMenuEntry entry, const u8 *custTable, u32 maxLen, u8 highlighted, u32 bg) {
    if (entry.hide) return;

    (highlighted) ? SETCOLOR(bg, RGBUnionToU32(entry.optionUnion)) : SETCOLOR(RGBUnionToU32(entry.optionUnion), bg);

    if (entry.icon) {
        gfx_putc(entry.icon);
        gfx_putc(' ');
        maxLen -= 2;
    }

    u32 curX = 0, curY = 0;
    gfx_con_getpos(&curX, &curY);
    if (entry.type == ELabel)
        gfx_puts_limit((const char *)entry.entry, maxLen);
    else if (entry.type == EParam) {
        const char *displayBuff = calloc(1024, 1);
        const Param *param = (const Param *)entry.entry;
        s_printf(displayBuff, "%s - ", param->name);
        getDisplayValue(param, displayBuff + strlen(displayBuff), getParamValueFromBuffer(custTable, param));
        gfx_puts_limit(displayBuff, maxLen);
        free(displayBuff);
    } else if (entry.type == ETable) {
        const Table *table = (const Table *)entry.entry;
        gfx_puts_limit(table->name, maxLen);
    }

    gfx_putc('\n');
}

enum ConfirmationDialogResult confirmationDialog(const char *message, const enum ConfirmationDialogResult defaultValue) {
    unsigned int selected = defaultValue == EYES ? 0 : 1;
    unsigned int holdTimer = 300;
    unsigned int linesCount = 0;
    unsigned int maxStringLen = 7; // YES__NO
    unsigned tmp = 0;
    for (unsigned int i = 0;; ++i) {
        ++tmp;
        if (message[i] == 0) {
            ++linesCount;
            --tmp;
            if (tmp > maxStringLen) maxStringLen = tmp;
            break;
        } else if (message[i] == '\n') {
            ++linesCount;
            --tmp;
            if (tmp > maxStringLen) maxStringLen = tmp;
            tmp = 0;
        }
    }
    unsigned int fontSize = gfx_con.fntsz;
    unsigned int boxWidth = (maxStringLen * fontSize) + fontSize * 2;
    unsigned int boxHeight = (linesCount * fontSize) + fontSize * 4;
    unsigned int boxX0Position = 1280 / 2 - boxWidth / 2;
    unsigned int boxX1Position = 1280 / 2 + boxWidth / 2;
    unsigned int boxY0Position = 720 / 2 - boxHeight / 2;
    unsigned int boxY1Position = 720 / 2 + boxHeight / 2;
    unsigned int yesX0Position = boxX0Position + (boxWidth / 2 - (3 + (maxStringLen % 2 ? 0 : 1)) * fontSize);
    unsigned int yesY0Position = boxY1Position - 2 * fontSize;
    unsigned int noX0Position = yesX0Position + (5 + (maxStringLen % 2 ? 0 : 1)) * fontSize;
    unsigned int noLastXPosition = noX0Position + 2 * fontSize;
    unsigned int noLastYPosition = yesY0Position + 1 * fontSize;

    unsigned int lastPress = 1000 + get_tmr_ms();
    unsigned int lastResult = selected;
    bool redraw = true;
    Input_t *input = hidRead();
    Input_t oldButtons = *input;
    gfx_box(boxX0Position, boxY0Position, boxX1Position, boxY1Position, COLOR_GREY);
    gfx_con_setpos(boxX0Position + fontSize, boxY0Position + fontSize);
    SETCOLOR(RGBUnionToU32(COLOR_WHITE), COLOR_GREY);
    gfx_puts(message);
    while (1) {
        if (redraw) {
            redraw = false;
            gfx_printTopInfoKT();
            gfx_box(yesX0Position, yesY0Position, noLastXPosition, noLastYPosition, COLOR_GREY);
            SETCOLOR(RGBUnionToU32(COLOR_WHITE), COLOR_GREY);
            if (selected == 0) SETCOLOR(COLOR_GREY, RGBUnionToU32(COLOR_WHITE));
            gfx_con_setpos(yesX0Position, yesY0Position);
            gfx_puts("YES");
            SETCOLOR(RGBUnionToU32(COLOR_WHITE), COLOR_GREY);
            if (selected == 1) SETCOLOR(COLOR_GREY, RGBUnionToU32(COLOR_WHITE));
            gfx_con_setpos(noX0Position, yesY0Position);
            gfx_puts("NO");
        }

        while (!hidRead()->buttons || oldButtons.buttons == input->buttons) {
            if ((lastPress + holdTimer) < get_tmr_ms() && oldButtons.buttons == input->buttons) break;
        }
        while (1) {
            if (input->buttons) oldButtons = *input;
            if (oldButtons.a)
                return selected == 0 ? EYES : ENO;
            else if (oldButtons.b)
                return ENOT_SELECTED;
            else if (!(hidRead()->buttons))
                break;
            else if ((lastPress + holdTimer) < get_tmr_ms())
                break;
        }

        if (oldButtons.right) {
            if (selected == 1)
                selected = 0;
            else
                ++selected;
        } else if (oldButtons.left) {
            if (selected == 0)
                selected = 1;
            else
                --selected;
        }
        if (selected != lastResult) {
            lastResult = selected;
            redraw = true;
        }
        lastPress = get_tmr_ms();
    }
}