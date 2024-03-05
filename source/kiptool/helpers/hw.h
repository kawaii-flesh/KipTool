#pragma once
#include <power/max17050.h>

#include "../params/param.h"

enum Platform getHWType();
void setHWType(enum Platform platform);
unsigned int getBatteryValue();
int getCurrentChargeState();