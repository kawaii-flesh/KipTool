#include "touchutils.h"

#include <input/touch.h>

int* isTouchEnabled() {
    static int touch_enabled = 0;
    return &touch_enabled;
}

#define TOUCH_SIZEW 240
#define TOUCH_SIZEH 240
int isTouchDown(touch_event* tevent) { return (tevent->x <= 1279) && (tevent->x >= 1279 - TOUCH_SIZEW) && (tevent->y >= 0) && (tevent->y < TOUCH_SIZEH); }

int isTouchRight(touch_event* tevent) {
    return (tevent->x <= 1279) && (tevent->x >= 1279 - TOUCH_SIZEW) && (tevent->y > 359 - TOUCH_SIZEH / 2) && (tevent->y <= 359 + TOUCH_SIZEH / 2);
}

int isTouchA(touch_event* tevent) { return (tevent->x <= 1279) && (tevent->x >= 1279 - TOUCH_SIZEW) && (tevent->y < 720) && (tevent->y >= 720 - TOUCH_SIZEH); }

int isTouchUp(touch_event* tevent) { return (tevent->x < TOUCH_SIZEW) && (tevent->x > 0) && (tevent->y >= 0) && (tevent->y < TOUCH_SIZEH); }

int isTouchLeft(touch_event* tevent) {
    return (tevent->x < TOUCH_SIZEW) && (tevent->x > 0) && (tevent->y > 359 - TOUCH_SIZEH / 2) && (tevent->y <= 359 + TOUCH_SIZEH / 2);
}

int isTouchB(touch_event* tevent) { return (tevent->x < TOUCH_SIZEW) && (tevent->x > 0) && (tevent->y < 720) && (tevent->y >= 720 - TOUCH_SIZEH); }

#define TOUCH_HOLD 300
void updateInput(Input_t* inputs, touch_event* tevent) {
    if (tevent->type == STMFTS_EV_MULTI_TOUCH_ENTER) {
        if (isTouchUp(tevent))
            inputs->up = 1;
        else if (isTouchDown(tevent))
            inputs->down = 1;
        else if (isTouchRight(tevent))
            inputs->right = 1;
        else if (isTouchLeft(tevent))
            inputs->left = 1;
        else if (isTouchA(tevent))
            inputs->a = 1;
        else if (isTouchB(tevent))
            inputs->b = 1;
    }
}
