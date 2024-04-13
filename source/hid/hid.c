#include "hid.h"

#include <display/di.h>
#include <input/joycon.h>
#include <input/touch.h>
#include <soc/timer.h>
#include <utils/btn.h>
#include <utils/types.h>
#include <utils/util.h>

#include "../gfx/gfx.h"
#include "../tegraexplorer/tconf.h"
#include "../tegraexplorer/tools.h"
#include "../utils/utils.h"
#include "inputType.h"
#include "touchutils.h"

static Input_t inputs = {0};
u16 LbaseX = 0, LbaseY = 0, RbaseX = 0, RbaseY = 0;

#define SLEEP_TIME_MS 16

bool canUpdate() {
    static u32 lastUpdateRequest = 0;
    if (get_tmr_ms() - lastUpdateRequest < SLEEP_TIME_MS) return 0;
    lastUpdateRequest = get_tmr_ms();
    return 1;
}

Input_t* hidRead() {
    if (*isTouchEnabled()) {
        Input_t tmp = {0};
        touch_event tevent;
        touch_poll(&tevent);
        if (tevent.fingers == 3)
            TakeScreenshot();
        else
            updateInput(&tmp, &tevent);
        if (tmp.buttons != 0) {
            inputs.buttons = tmp.buttons;
            return &inputs;
        }
    }
    if (!canUpdate()) return &inputs;

    jc_gamepad_rpt_t* controller = joycon_poll();
    inputs.buttons = 0;
    u8 left_connected = 0;
    u8 right_connected = 0;
    if (controller != NULL) {
        if (controller->home && !TConf.isMariko) RebootToPayloadOrRcm();

        if (controller->cap) TakeScreenshot();

        inputs.buttons = controller->buttons;

        left_connected = controller->conn_l;
        right_connected = controller->conn_r;
    }

    u8 btn = btn_read();
    inputs.volp = (btn & BTN_VOL_UP) ? 1 : 0;
    inputs.volm = (btn & BTN_VOL_DOWN) ? 1 : 0;
    inputs.power = (btn & BTN_POWER) ? 1 : 0;

    if (left_connected) {
        // Hoag has inverted Y axis (only the left stick O_o)
        if (controller->sio_mode) controller->lstick_y *= -1;
        if ((LbaseX == 0 || LbaseY == 0) || controller->l3) {
            LbaseX = controller->lstick_x;
            LbaseY = controller->lstick_y;
        }
        inputs.up = (controller->up || inputs.volp || (controller->lstick_y > LbaseY + 500)) ? 1 : 0;
        inputs.down = (controller->down || inputs.volm || (controller->lstick_y < LbaseY - 500)) ? 1 : 0;
        inputs.left = (controller->left || (controller->lstick_x < LbaseX - 500)) ? 1 : 0;
        inputs.right = (controller->right || (controller->lstick_x > LbaseX + 500)) ? 1 : 0;
    } else {
        inputs.up = inputs.volp;
        inputs.down = inputs.volm;
    }

    if (right_connected) {
        if ((RbaseX == 0 || RbaseY == 0) || controller->r3) {
            RbaseX = controller->rstick_x;
            RbaseY = controller->rstick_y;
        }

        inputs.rUp = (controller->rstick_y > RbaseY + 500) ? 1 : 0;
        inputs.rDown = (controller->rstick_y < RbaseY - 500) ? 1 : 0;
        inputs.rLeft = (controller->rstick_x < RbaseX - 500) ? 1 : 0;
        inputs.rRight = (controller->rstick_x > RbaseX + 500) ? 1 : 0;
    }
    inputs.a = inputs.a || inputs.power;
    inputs.b = inputs.b || (inputs.volp && inputs.volm);

    return &inputs;
}

Input_t* hidWaitMask(u32 mask) {
    Input_t* in = hidRead();

    while (in->buttons & mask) hidRead();

    while (!(in->buttons & mask)) {
        hidRead();
    }

    return in;
}

Input_t* hidWait() {
    Input_t* in = hidRead();

    while (in->buttons) hidRead();

    while (!(in->buttons)) hidRead();
    return in;
}

bool hidConnected() {
    msleep(SLEEP_TIME_MS);
    jc_gamepad_rpt_t* controller = joycon_poll();
    return (controller->conn_l && controller->conn_r) ? 1 : 0;
}
