#include <mem/heap.h>
#include <mem/minerva.h>
#include <string.h>
#include <utils/util.h>

#include "../../../gfx/gfxutils.h"
#include "../../../hid/hid.h"
#include "../gfx.h"
#include "confirmationDialog.h"

void informationDialog(const char** messages[]) {
    unsigned int holdTimer = 300;
    unsigned int maxLinesCount = 0;
    unsigned int maxStringLen = 17;  // "Press A/B to exit"
    unsigned int pagesCount = 0;
    unsigned int currentPage = 0;
    unsigned int lastPage = 0;

    for (unsigned int i = 0; messages[i] != NULL; ++i, ++pagesCount) {
        unsigned int linesCount = 0;
        for (unsigned int j = 0; messages[i][j] != NULL; ++j) {
            ++linesCount;
            const unsigned int strLen = strlen(messages[i][j]);
            if (strLen > maxStringLen) maxStringLen = strLen;
        }
        if (linesCount > maxLinesCount) maxLinesCount = linesCount;
    }

    unsigned int fontSize = gfx_con.fntsz;
    unsigned int boxWidth = (maxStringLen * fontSize) + fontSize * 6;
    unsigned int boxHeight = (maxLinesCount * fontSize) + fontSize * 6;
    unsigned int boxX0Position = 1280 / 2 - boxWidth / 2;
    unsigned int boxX1Position = 1280 / 2 + boxWidth / 2;
    unsigned int boxY0Position = 720 / 2 - boxHeight / 2;
    unsigned int boxY1Position = 720 / 2 + boxHeight / 2;
    unsigned int toExitX0 = boxX0Position + (boxWidth / 2 - (17 / 2 + (maxStringLen % 2 ? 0 : 1)) * fontSize);
    unsigned int toExitY0 = boxY1Position - 2 * fontSize;
    unsigned int arrowsY0 = boxY1Position - boxHeight / 2;
    unsigned int arrow1X = boxX0Position + fontSize;
    unsigned int arrow2X = boxX1Position - fontSize * 2;

    unsigned int lastPress = 1000 + get_tmr_ms();
    bool redraw = true;
    Input_t* input = hidRead();
    Input_t oldButtons = *input;
    while (1) {
        if (redraw) {
            minerva_periodic_training();
            redraw = false;
            gfx_box(boxX0Position, boxY0Position, boxX1Position, boxY1Position, COLOR_CONFIRM);
            char* pageNumberBuff = malloc(256);
            s_printf(pageNumberBuff, "Page %d/%d", currentPage + 1, pagesCount);
            unsigned int pageCountX0 = boxX0Position + (boxWidth / 2 - (strlen(pageNumberBuff) / 2 + (maxStringLen % 2 ? 0 : 1)) * fontSize);
            unsigned int pageCountY0 = boxY0Position + fontSize;
            gfx_con_setpos(pageCountX0, pageCountY0);
            SETCOLOR(RGBUnionToU32(COLOR_CONFIRM), COLOR_WHITE);
            gfx_puts(pageNumberBuff);
            free(pageNumberBuff);
            gfx_con_setpos(arrow2X, arrowsY0);
            gfx_puts(">");
            gfx_con_setpos(arrow1X, arrowsY0);
            gfx_puts("<");
            unsigned int messageY = boxY0Position + fontSize * 3;
            unsigned int messageX = boxX0Position + fontSize * 3;
            SETCOLOR(RGBUnionToU32(COLOR_WHITE), COLOR_CONFIRM);
            for (unsigned int i = 0; messages[currentPage][i] != NULL; ++i) {
                gfx_con_setpos(messageX, messageY);
                gfx_puts(messages[currentPage][i]);
                messageY += fontSize;
            }
            gfx_con_setpos(toExitX0, toExitY0);
            SETCOLOR(RGBUnionToU32(COLOR_CONFIRM), COLOR_WHITE);
            gfx_puts("Press A/B to exit");
        }

        while (!hidRead()->buttons || oldButtons.buttons & input->buttons) {
            if (oldButtons.buttons != input->buttons) oldButtons = *input;
            if ((lastPress + holdTimer) < get_tmr_ms() && (oldButtons.buttons & input->buttons)) break;
        }
        if (oldButtons.buttons != input->buttons) oldButtons = *input;
        if (oldButtons.a || oldButtons.b)
            return;
        else if (oldButtons.right || oldButtons.volp) {
            if (currentPage + 1 == pagesCount)
                currentPage = 0;
            else
                ++currentPage;
        } else if (oldButtons.left || oldButtons.volm) {
            if (currentPage == 0)
                currentPage = pagesCount - 1;
            else
                --currentPage;
        }
        if (currentPage != lastPage) {
            lastPage = currentPage;
            redraw = true;
        }
        lastPress = get_tmr_ms();
    }
}
