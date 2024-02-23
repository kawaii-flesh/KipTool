#pragma once
#include "../param.h"

const Param mdCPUv = {"dCPUv", "mV", NULL, 12348, 3, 0, EFixedLimits, {700, 890, 5}};

const Param mCPUMinimalVoltage = {"CPU Minimal Voltage",  "mV", NULL, 48, 3, 0, EMaxByParam,
                                  {250000, &mdCPUv, 5000}};

const Param mCPUMaximumVoltage = {"CPU Maximum Voltage", "mV", NULL, 28, 3, 0, EMinByParam,
                                  {&mdCPUv, 1270, 10}};

const Param mCPUBoostClock = {"CPU Boost Clock",       "MHz", NULL, 12, 3, 0, EFixedLimits,
                              {1785000, 3009000, 1000}};

const FixedValues mLowMHzUndervoltValues = {6,
                                            {{0, "Base undervolting"},
                                             {1, "Level 1"},
                                             {2, "Level 2"},
                                             {3, "Level 3"},
                                             {4, "Level 4"},
                                             {5, "Level 5"}}};
const Param mLowMHzUndervolt = {"Low MHz Undervolt",    NULL, NULL, 40, 1, 0, EFixedValues,
                                &mLowMHzUndervoltValues};

const FixedValues mHighMHzUndervoltValues = {8,
                                             {{0, "Base undervolting"},
                                              {1, "Level 1"},
                                              {2, "Level 2"},
                                              {3, "Level 3"},
                                              {4, "Level 4"},
                                              {5, "Level 5"},
                                              {6, "Level 6"},
                                              {7, "Level 7"}}};
const Param mHighMHzUndervolt = {"High MHz Undervolt",    NULL, NULL, 12340, 1, 0, EFixedValues,
                                 &mHighMHzUndervoltValues};

const FixedValues mSpeedShiftValues = {5,
                                       {{0, "Default"},
                                        {50, "Sport"},
                                        {100, "ECO Stage 1"},
                                        {125, "ECO Stage 2"},
                                        {150, "ECO Stage 3"}}};
const Param mSpeedShift = {"Speed Shift",     NULL, NULL, 12336, 1, 0, EFixedValues,
                           &mSpeedShiftValues};

const Param *mCPUParams[] = {
    &mCPUMinimalVoltage, &mdCPUv,         &mCPUMaximumVoltage, &mLowMHzUndervolt,
    &mHighMHzUndervolt,  &mCPUBoostClock, &mSpeedShift};
const unsigned int mCPUParamsCount = 7;