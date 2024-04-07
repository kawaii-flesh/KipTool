#pragma once
#include <utils/types.h>

#include "inputType.h"

// #define BIT(n) (1U << n)

#define JoyY BIT(0)
#define JoyX BIT(1)
#define JoyB BIT(2)
#define JoyA BIT(3)
#define JoyRB BIT(6)
#define JoyLMinus BIT(8)
#define JoyRPlus BIT(9)
#define JoyMenu BIT(12)
#define JoyLDown BIT(16)
#define JoyLUp BIT(17)
#define JoyLRight BIT(18)
#define JoyLLeft BIT(19)
#define JoyLB BIT(22)
#define BtnPow BIT(24)
#define BtnVolP BIT(25)
#define BtnVolM BIT(26)
#define JoyRDown BIT(27)
#define JoyRUp BIT(28)
#define JoyRRight BIT(29)
#define JoyRLeft BIT(30)

#define WAITBUTTONS (JoyY | JoyX | JoyB | JoyA | JoyLDown | JoyLUp | JoyLRight | JoyLLeft)

Input_t* hidRead();
Input_t* hidWait();
Input_t* hidWaitMask(u32 mask);
bool hidConnected();
