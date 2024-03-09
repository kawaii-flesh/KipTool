#include "confirmationDialog.h"

#include <mem/minerva.h>
#include <utils/util.h>

#include "../../../gfx/gfxutils.h"
#include "../../../hid/hid.h"
#include "../gfx.h"

enum ConfirmationDialogResult confirmationDialog(const char* message, const enum ConfirmationDialogResult defaultValue) {
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
    Input_t* input = hidRead();
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