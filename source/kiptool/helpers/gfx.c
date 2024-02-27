#include "gfx.h"
#include "hw.h"

void gfx_printTopInfoKT() {
    SETCOLOR(COLOR_DEFAULT, COLOR_WHITE);
    gfx_con_setpos(0, 0);
    gfx_printf("Kip Tool %d.%d.%d | SoC: %s | Battery: %d%% %c\n", KT_VER_MJ, KT_VER_MN, KT_VER_BF,
               isMarikoHWType() ? "Mariko" : "Erista", getBatteryValue(),
               (getCurrentChargeState() ? 129 : 32));
    RESETCOLOR;
}

void gfx_clearscreenKT() {
    gfx_boxGrey(0, 16, 1279, 703, 0x1b);

    gfx_boxGrey(0, 703, 1279, 719, 0xFF);
    gfx_boxGrey(0, 0, 1279, 15, 0xFF);

    gfx_printTopInfoKT();
}