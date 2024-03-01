#include "hw.h"

#include <power/bq24193.h>
#include <power/max17050.h>
#include <soc/hw_init.h>
#include <soc/t210.h>

bool isMarikoHWType() {
    static int isMariko = -1;
    if (isMariko == -1) isMariko = hw_get_chip_id() == GP_HIDREV_MAJOR_T210B01;
    return isMariko;
}

unsigned int getBatteryValue() {
    int battery = 0;
    max17050_get_property(MAX17050_RepSOC, &battery);
    return battery >> 8;
}

int getCurrentChargeState() {
    int currentChargeStatus = 0;
    bq24193_get_property(BQ24193_ChargeStatus, &currentChargeStatus);
    return currentChargeStatus;
}