#pragma once

#include <input/touch.h>

#include "inputType.h"

int* isTouchEnabled();
void updateInput(Input_t* inputs, touch_event* tevent);
