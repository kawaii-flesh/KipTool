#include "ktMenu.h"

#include "../../../gfx/gfxutils.h"
#include "../../../hid/hid.h"

int newMenuKT(MenuEntry entries[], const unsigned int entriesCount, unsigned int startIndex, const void* additionalData,
              void (*printMenuEntryFunc)(MenuEntry* entry, u32 maxLen, u8 highlighted, u32 bg, void* additionalData)) {
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
    Input_t* input = hidRead();

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

void printEntry(MenuEntry* entry, u32 maxLen, u8 highlighted, u32 bg, void* additionalData) {
    if (entry->hide) return;

    (highlighted) ? SETCOLOR(bg, RGBUnionToU32(entry->optionUnion)) : SETCOLOR(RGBUnionToU32(entry->optionUnion), bg);

    if (entry->icon) {
        gfx_putc(entry->icon);
        gfx_putc(' ');
        maxLen -= 2;
    }

    u32 curX = 0, curY = 0;
    gfx_con_getpos(&curX, &curY);
    if (entry->type == ELabel) gfx_puts_limit((const char*)entry->entry, maxLen);

    gfx_putc('\n');
}