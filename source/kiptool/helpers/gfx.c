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

int newMenuKT(MenuEntry entries[], const unsigned int entriesCount, unsigned int startIndex, void *additionalData,
              void (*printMenuEntryFunc)(MenuEntry *entry, u32 maxLen, u8 highlighted, u32 bg, void *additionalData)) {
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
    gfx_con_setpos(0, 24);
    gfx_boxGrey(0, 16, 160, 31, 0x1B);
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

            minerva_periodic_training();
            gfx_boxGrey(startX, startY, startX + screenLenX * 16, startY + screenLenY * 16, 0x1B);

            int start = selected / screenLenY * screenLenY;
            gfx_con_setpos(startX, startY);
            gfx_printf("%b", startX);
            for (int i = start; i < MIN(entriesCount, start + screenLenY); i++) {
                printMenuEntryFunc(&entries[i], screenLenX, (i == selected), bgColor, additionalData);
            }
            gfx_printf("%b", 0);
        } else if (lastIndex != selected) {
            u32 minLastCur = MIN(lastIndex, selected);
            u32 maxLastCur = MAX(lastIndex, selected);
            gfx_con_setpos(startX, startY + ((minLastCur % screenLenY) * 16));
            printMenuEntryFunc(&entries[minLastCur], screenLenX, (minLastCur == selected), bgColor, additionalData);
            gfx_con_setpos(startX, startY + ((maxLastCur % screenLenY) * 16));
            printMenuEntryFunc(&entries[maxLastCur], screenLenX, (minLastCur != selected), bgColor, additionalData);
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

void printEntry(MenuEntry *entry, u32 maxLen, u8 highlighted, u32 bg, void *additionalData) {
    if (entry->hide) return;

    (highlighted) ? SETCOLOR(bg, RGBUnionToU32(entry->optionUnion)) : SETCOLOR(RGBUnionToU32(entry->optionUnion), bg);

    if (entry->icon) {
        gfx_putc(entry->icon);
        gfx_putc(' ');
        maxLen -= 2;
    }

    u32 curX = 0, curY = 0;
    gfx_con_getpos(&curX, &curY);
    if (entry->type == ELabel) gfx_puts_limit((const char *)entry->entry, maxLen);

    gfx_putc('\n');
}

enum ConfirmationDialogResult confirmationDialog(const char *message, const enum ConfirmationDialogResult defaultValue) {
    unsigned int selected = defaultValue == EYES ? 0 : 1;
    unsigned int holdTimer = 300;
    unsigned int linesCount = 0;
    unsigned int maxStringLen = 7;  // YES__NO
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
            minerva_periodic_training();
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
            if ((lastPress + holdTimer) < get_tmr_ms() && oldButtons.buttons == input->buttons)
                break;
            else if (oldButtons.buttons != input->buttons)
                oldButtons = *input;
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

unsigned int numPlaces(unsigned int n) {
    unsigned int r = 1;
    while (n > 9) {
        n /= 10;
        r++;
    }
    return r;
}

bool validateValueByFixedLimits(const FixedLimits *fixedLimits, const unsigned int value) {
    return fixedLimits->min <= value && value <= fixedLimits->max && value % fixedLimits->stepSize == 0;
}
bool validateValue(unsigned int min, unsigned int max, unsigned int stepSize, const unsigned int value) {
    return min <= value && value <= max && value % stepSize == 0;
}

ManualValueResult manualValueDialog(const Param *param, int defaultValue) {
    const FixedLimits *fixedLimits = NULL;
    for (unsigned int i = 0; i < param->limitsCount; ++i)
        if (param->limits[i].type == EFixedLimits) fixedLimits = param->limits[i].values;
    if (fixedLimits == NULL) {
        const ManualValueResult notFixedLimits = {.status = EMVS_ITS_NOT_FIXEDLIMITS};
        return notFixedLimits;
    }

    int min = fixedLimits->min;
    if (min > 1500) min /= 1000;
    int max = fixedLimits->max;
    if (max > 1500) max /= 1000;
    int stepSize = fixedLimits->stepSize;
    if (stepSize > 1500) stepSize /= 1000;
    int currentValue = defaultValue;
    if (currentValue == -1) {
        currentValue = min + (max - min) / 2;
        if (currentValue % stepSize != 0) currentValue += currentValue % stepSize;
    } else if (currentValue > 1500)
        currentValue /= 1000;
    unsigned int holdTimer = 200;
    const unsigned int linesCount = 5;
    const char template[] = "min=>%d %k%d%k %d<=max step=%d%s";
    const char help[] = "dec(<) inc(>) apply(A) back(B)";
    const char *measure = param->measure != NULL ? param->measure : fixedLimits->measure != NULL ? fixedLimits->measure : NULL;
    const unsigned int minMaxDif = numPlaces(max) - numPlaces(min);
    unsigned int maxStringLen = 18 + numPlaces(min) + numPlaces(max) + numPlaces(max) + numPlaces(stepSize) +
                                (measure != NULL ? strlen(measure) : 0) + minMaxDif;
    unsigned int fontSize = gfx_con.fntsz;
    unsigned int boxWidth = (maxStringLen * fontSize) + fontSize * 2;
    unsigned int boxHeight = (linesCount * fontSize) + fontSize * 2;
    unsigned int boxX0Position = 1280 / 2 - boxWidth / 2;
    unsigned int boxX1Position = 1280 / 2 + boxWidth / 2;
    unsigned int boxY0Position = 720 / 2 - boxHeight / 2;
    unsigned int boxY1Position = 720 / 2 + boxHeight / 2;
    unsigned int boxXMid = boxX0Position + boxWidth / 2;
    unsigned int paramNameXPosition = boxXMid - (strlen(param->name) / 2) * fontSize;
    unsigned int helpXPosition = boxXMid - 15 * fontSize;
    unsigned int selectorX0Position = boxXMid - (maxStringLen / 2) * fontSize;
    unsigned int selectorX1Position = boxXMid + (maxStringLen / 2) * fontSize;

    unsigned int paramNameYPosition = boxY0Position + 1 * fontSize;
    unsigned int helpYPosition = boxY0Position + 3 * fontSize;
    unsigned int selectorY0Position = boxY0Position + 5 * fontSize;

    unsigned int lastPress = 1000 + get_tmr_ms();
    unsigned int lastResult = currentValue;
    const int mult = 10;
    bool redraw = true;
    bool fullRedraw = true;
    bool redrawSelector = false;
    Input_t *input = hidRead();
    Input_t oldButtons = *input;

    while (1) {
        if (redraw) {
            gfx_printTopInfoKT();
            SETCOLOR(COLOR_WHITE, COLOR_GREY);
            if (fullRedraw) {
                minerva_periodic_training();
                gfx_box(boxX0Position, boxY0Position, boxX1Position, boxY1Position, COLOR_GREY);
                gfx_con_setpos(paramNameXPosition, paramNameYPosition);
                gfx_puts(param->name);
                gfx_con_setpos(helpXPosition, helpYPosition);
                gfx_puts(help);
                fullRedraw = false;
            }
            if (redrawSelector && !fullRedraw) {
                gfx_box(selectorX0Position, selectorY0Position, selectorX1Position, selectorY0Position + fontSize, COLOR_GREY);
                redrawSelector = false;
            }
            redraw = false;
            gfx_con_setpos(selectorX0Position, selectorY0Position);
            gfx_printf(template, min, COLOR_ORANGE, currentValue, COLOR_WHITE, max, stepSize, measure);
        }
        while (!hidRead()->buttons || oldButtons.buttons == input->buttons) {
            if ((lastPress + holdTimer) < get_tmr_ms() && oldButtons.buttons == input->buttons)
                break;
            else if (oldButtons.buttons != input->buttons)
                oldButtons = *input;
        }
        while (1) {
            if (input->buttons) oldButtons = *input;
            if (oldButtons.a) {
                if (validateValue(min, max, stepSize, currentValue)) {
                    const ManualValueResult good = {.value = currentValue, .status = EMVS_GOOD};
                    if (confirmationDialog("Set new value?", EYES) == EYES)
                        return good;
                    else {
                        oldButtons = *hidRead();
                        fullRedraw = true;
                        redraw = true;
                        break;
                    }
                } else {
                    const ManualValueResult invalidValue = {.status = EMVS_INVALID_VALUE};
                    return invalidValue;
                }
            } else if (oldButtons.b) {
                const ManualValueResult exit = {.status = EMVS_EXIT};
                if (confirmationDialog("Close?", EYES) == EYES)
                    return exit;
                else {
                    oldButtons = *hidRead();
                    fullRedraw = true;
                    redraw = true;
                    break;
                }
                return exit;
            } else if (!(hidRead()->buttons))
                break;
            else if ((lastPress + holdTimer) < get_tmr_ms())
                break;
        }

        if (oldButtons.right) {
            if (currentValue + stepSize < max)
                currentValue += stepSize;
            else
                currentValue = max;
        } else if (oldButtons.left) {
            if (min < currentValue - stepSize)
                currentValue -= stepSize;
            else
                currentValue = min;
        } else if (oldButtons.up) {
            if (currentValue + stepSize * mult < max)
                currentValue += stepSize * mult;
            else
                currentValue = max;
        } else if (oldButtons.down) {
            if (min < currentValue - stepSize * mult)
                currentValue -= stepSize * mult;
            else
                currentValue = min;
        }
        if (currentValue != lastResult) {
            if (currentValue % stepSize != 0) currentValue += currentValue % stepSize;
            redrawSelector = numPlaces(currentValue) != numPlaces(lastResult);
            lastResult = currentValue;
            redraw = true;
        }
        lastPress = get_tmr_ms();
    }
}

void printParamEntry(MenuEntry *entry, u32 maxLen, u8 highlighted, u32 bg, u8 *custTable) {
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
        gfx_puts_limit((const char *)entry->entry, maxLen);
    else if (entry->type == EParam) {
        const char *displayBuff = calloc(1024, 1);
        const Param *param = (const Param *)entry->entry;
        s_printf(displayBuff, "%s - ", param->name);
        getDisplayValue(param, displayBuff + strlen(displayBuff), getParamValueFromBuffer(custTable, param));
        gfx_puts_limit(displayBuff, maxLen);
        free(displayBuff);
    } else if (entry->type == ETable) {
        const Table *table = (const Table *)entry->entry;
        gfx_puts_limit(table->name, maxLen);
    }

    gfx_putc('\n');
}

void newTableMenu(const u8 *custTable, const Table *table) {
    const unsigned int paramsCount = table->paramsCount;
    unsigned int totalEntriesCount = 1 + table->paramsCount;
    MenuEntry *menuEntries = calloc(sizeof(MenuEntry), totalEntriesCount);
    menuEntries[0].optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT;
    menuEntries[0].type = ELabel;
    menuEntries[0].entry = table->name;
    unsigned int menuEntriesIndex = 1;
    for (unsigned int paramI = 0; paramI < paramsCount; ++paramI) {
        menuEntries[menuEntriesIndex].optionUnion = COLORTORGB(COLOR_VIOLET);
        menuEntries[menuEntriesIndex].type = EParam;
        menuEntries[menuEntriesIndex].entry = table->params[paramI];
        ++menuEntriesIndex;
    }
    int res = newMenuKT(menuEntries, totalEntriesCount, 0, custTable, printParamEntry);
    if (res == -1) {
        free(menuEntries);
        return;
    }
    const MenuEntry selectedEntry = menuEntries[res + 1];
    free(menuEntries);
    newEditorMenu(custTable, selectedEntry.entry);
    return;
}

void newParamsMenu(const u8 *custTable, const char *sectionTitle, const Params *params[], const unsigned int paramsArraysCount,
                   const Tables *tables[], unsigned int tablesArraysCount) {
    unsigned int totalEntriesCount = 1;
    unsigned int startIndex = 0;
    for (unsigned int i = 0; i < paramsArraysCount; ++i) totalEntriesCount += params[i]->count;
    for (unsigned int i = 0; i < tablesArraysCount; ++i) totalEntriesCount += tables[i]->count;
    MenuEntry *menuEntries = calloc(sizeof(MenuEntry), totalEntriesCount);
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
            const Table *table = selectedEntry.entry;
            newTableMenu(custTable, table);
            continue;
        }
        newEditorMenu(custTable, selectedEntry.entry);
        startIndex = res + 1;
    }
}

void printValueEntry(MenuEntry *entry, u32 maxLen, u8 highlighted, u32 bg, Param *param) {
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
        gfx_puts_limit((const char *)entry->entry, maxLen);
    else if (entry->type == EValue) {
        const char *displayBuff = calloc(1024, 1);
        const Value *value = entry->entry;
        getDisplayValue(param, displayBuff + strlen(displayBuff), value->value);
        gfx_puts_limit(displayBuff, maxLen);
        free(displayBuff);
    } else if (entry->type == ELimits) {
        const char *displayBuff = calloc(1024, 1);
        const FixedLimits *fixedLimits = entry->entry;
        int min = fixedLimits->min;
        if (min > 1500) min /= 1000;
        int max = fixedLimits->max;
        if (max > 1500) max /= 1000;
        int stepSize = fixedLimits->stepSize;
        if (stepSize > 1500) stepSize /= 1000;
        int currentValue = min + (max - min) / 2;
        const char *measure = param->measure != NULL ? param->measure : fixedLimits->measure;
        s_printf(displayBuff, "Manual value - min: %d max: %d step: %d", min, max, stepSize, measure != NULL ? measure : "");
        gfx_puts_limit(displayBuff, maxLen);
        free(displayBuff);
    }

    gfx_putc('\n');
}

void newEditorMenu(const u8 *custTable, const Param *param) {
    const unsigned int limitsCount = param->limitsCount;
    const FixedValues *fixedValues = NULL;
    const FixedLimits *fixedLimits = NULL;
    unsigned int totalEntriesCount = 1;
    for (unsigned int i = 0; i < limitsCount; ++i)
        if (param->limits[i].type == EFixedLimits) {
            fixedLimits = param->limits[i].values;
            ++totalEntriesCount;
        } else if (param->limits[i].type == EFixedValues) {
            fixedValues = param->limits[i].values;
            totalEntriesCount += fixedValues->valuesCount;
        }

    MenuEntry *menuEntries = calloc(sizeof(MenuEntry), totalEntriesCount);
    menuEntries[0].optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT;
    menuEntries[0].type = ELabel;
    menuEntries[0].entry = param->name;
    unsigned int menuEntriesIndex = 1;
    unsigned int paramCurrentValue = getParamValueFromBuffer(custTable, param);
    unsigned int startIndex = 0;
    bool canBeManualValue = validateValueByFixedLimits(fixedLimits, paramCurrentValue);
    if (fixedValues != NULL)
        for (unsigned int valueI = 0; valueI < fixedValues->valuesCount; ++valueI) {
            const Value *fixedValue = &fixedValues->values[valueI];
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