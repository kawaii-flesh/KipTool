#include "utils.h"

#include <mem/heap.h>
#include <soc/timer.h>
#include <string.h>
#include <utils/types.h>
#include <utils/util.h>

#include "../fs/fsutils.h"
#include "../gfx/gfx.h"
#include "../gfx/gfxutils.h"
#include "../gfx/menu.h"
#include "../hid/hid.h"
#include "../tegraexplorer/tconf.h"
#include "vector.h"

extern int launch_payload(char* path);

#define ALWAYS_INLINE inline __attribute__((always_inline))

void ALWAYS_INLINE power_off() { power_set_state(POWER_OFF_RESET); }

void ALWAYS_INLINE reboot_rcm() { power_set_state(REBOOT_RCM); }

void ALWAYS_INLINE reboot_normal() { power_set_state((TConf.isMariko) ? REBOOT_BYPASS_FUSES : POWER_OFF_REBOOT); }

void RebootToPayloadOrRcm() {
    if (FileExists("sd:/atmosphere/reboot_payload.bin")) launch_payload("sd:/atmosphere/reboot_payload.bin");
    reboot_rcm();
}

char* CpyStr(const char* in) {
    int len = strlen(in);
    char* out = malloc(len + 1);
    out[len] = 0;
    memcpy(out, in, len);
    return out;
}

void MaskIn(char* mod, u32 bitstream, char mask) {
    u32 len = strlen(mod);
    for (int i = 0; i < len; i++) {
        if (!(bitstream & 1)) *mod = mask;

        bitstream >>= 1;
        mod++;
    }
}

// non-zero is yes, zero is no
bool StrEndsWith(char* begin, char* end) {
    begin = strrchr(begin, *end);
    if (begin != NULL) return !strcmp(begin, end);

    return 0;
}

void WaitFor(u32 ms) {
    u32 a = get_tmr_ms();
    while (a + ms > get_tmr_ms());
}

char* lines[] = {
    "1234567890*",  // 0 - 10
    "qwertyuiop~",  // 11 - 21
    "asdfghjkl.+",  // 22 - 32
    "^zxcvbnm_<>"   // 33 - 43
};

char* ShowKeyboard(const char* toEdit, u8 alwaysRet) {
    char* ret = CpyStr(toEdit);
    int pos = 0;
    int posOnWord = 0;
    bool shift = 0;

    gfx_printf("*/(B) = exit | ~/(X) = backspace | ^(left) = shift | +/(Y) = add char\n\n");

    u32 x, y;
    gfx_con_getpos(&x, &y);

    while (1) {
        gfx_con_setpos(x, y);

        for (int i = 0; i < strlen(ret); i++) {
            (i == posOnWord) ? SETCOLOR(COLOR_WHITE, COLOR_VIOLET) : SETCOLOR(COLOR_WHITE, COLOR_DEFAULT);
            gfx_putc(ret[i]);
        }

        RESETCOLOR;
        gfx_putc(' ');

        for (int a = 0; a < 4; a++) {
            for (int b = 0; b < 11; b++) {
                (pos == ((b % 11) + (a * 11))) ? SETCOLOR(COLOR_DEFAULT, COLOR_WHITE) : SETCOLOR(COLOR_WHITE, COLOR_DEFAULT);
                gfx_con_setpos(x + 16 + (b * 2 * 16), y + a * 16 * 2 + 32);
                if (shift && lines[a][b] >= 'a' && lines[a][b] <= 'z')
                    gfx_putc(lines[a][b] & ~BIT(5));
                else
                    gfx_putc(lines[a][b]);
            }
        }

        Input_t* input = hidWait();
        if (input->buttons) {
            int isAPressed = input->a;
            if ((pos == 42 && isAPressed) || input->l) {
                if (posOnWord > 0) posOnWord--;
            } else if ((pos == 43 && isAPressed) || input->r) {
                if (strlen(ret) - 1 > posOnWord) posOnWord++;
            } else if (pos == 10 && isAPressed) {  // *
                break;
            } else if ((pos == 21 && isAPressed) || input->x) {  // ~
                u32 wordLen = strlen(ret);
                if (!wordLen) continue;

                for (int i = posOnWord; i < wordLen - 1; i++) {
                    ret[i] = ret[i + 1];
                }
                ret[wordLen - 1] = 0;
                if (posOnWord > wordLen - 2) posOnWord--;
            } else if ((pos == 32 && isAPressed) || input->plus || input->y) {  // +
                u32 wordLen = strlen(ret);
                if (wordLen >= 79) continue;

                char* copy = calloc(wordLen + 2, 1);
                memcpy(copy, ret, wordLen);
                copy[wordLen] = 'a';
                posOnWord = wordLen;
                free(ret);
                ret = copy;
            } else if (pos == 33 && isAPressed) {
                shift = !shift;
            } else if (isAPressed) {
                char toPut = lines[pos / 11][pos % 11];
                if (shift) toPut &= ~BIT(5);
                ret[posOnWord] = toPut;

                if (strlen(ret) - 1 > posOnWord) posOnWord++;
            }
        }
        int val = (input->up || input->down) ? 11 : 1;

        if (input->volm) {
            if (pos > 0) pos -= 1;
        } else if (input->volp) {
            if (pos < 43) pos += 1;
        } else if (input->buttons & (JoyLLeft | JoyLUp)) {
            if (pos > -1 + val) pos -= val;
        } else if (input->buttons & (JoyLRight | JoyLDown)) {
            if (pos < 44 - val) pos += val;
        }

        if (input->b) {
            break;
        }
    }

    if (!strcmp(ret, toEdit) && !alwaysRet) {
        free(ret);
        return NULL;
    }

    return ret;
}
