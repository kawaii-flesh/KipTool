#include "gfx.h"

#include <stdlib.h>
#include <string.h>

#include "../../gfx/gfx.h"
#include "../../gfx/gfxutils.h"
#include "../../hid/hid.h"
#include "../helpers/hw.h"
#include "../helpers/kiprw.h"
#include "../params/param.h"
#include "../params/table.h"

void gfx_printTopInfoKT() {
    SETCOLOR(COLOR_DEFAULT, COLOR_WHITE);
    gfx_con_setpos(0, 0);
    gfx_printf("Kip Tool %d.%d.%d-%d | SoC: %s | Battery: %d%% %c\n", KT_VER_MJ, KT_VER_MN, KT_VER_BF, KT_CUST_VER,
               getHWType() == COMMON   ? "Common"
               : getHWType() == MARIKO ? "Mariko"
                                       : "Erista",
               getBatteryValue(), (getCurrentChargeState() ? 129 : 32));
    RESETCOLOR;
}

void gfx_printBottomInfoKT(const char* message) {
    gfx_boxGrey(0, 703, 1279, 719, 0xFF);
    gfx_con_setpos(0, 704);
    SETCOLOR(COLOR_DEFAULT, COLOR_WHITE);
    gfx_puts_limit(message, (1280 / gfx_con.fntsz) - 8);
}

void gfx_clearscreenKT() {
    gfx_boxGrey(0, 16, 1279, 703, 0x1b);

    gfx_boxGrey(0, 0, 1279, 15, 0xFF);

    gfx_printTopInfoKT();
}