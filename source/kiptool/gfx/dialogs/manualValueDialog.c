#include "manualValueDialog.h"

#include <mem/heap.h>
#include <soc/timer.h>
#include <string.h>
#include <utils/sprintf.h>
#include <utils/util.h>

#include "../../../gfx/gfxutils.h"
#include "../../../hid/hid.h"
#include "../../helpers/param.h"
#include "../../params/param.h"
#include "../gfx.h"
#include "confirmationDialog.h"

unsigned int numPlaces(unsigned int n) {
    unsigned int r = 1;
    while (n > 9) {
        n /= 10;
        r++;
    }
    return r;
}

bool validateValue(unsigned int min, unsigned int max, unsigned int stepSize, const unsigned int value) {
    return min <= value && value <= max && value % stepSize == 0;
}

ManualValueResult manualValueDialog(const Param* param, int defaultValue) {
    const FixedLimits* fixedLimits = NULL;
    for (unsigned int i = 0; i < param->limitsCount; ++i)
        if (param->limits[i].type == EFixedLimits) fixedLimits = param->limits[i].values;
    if (fixedLimits == NULL) {
        const ManualValueResult notFixedLimits = {.status = EMVS_ITS_NOT_FIXEDLIMITS};
        return notFixedLimits;
    }

    int min = fixedLimits->min;
    int max = fixedLimits->max;
    int stepSize = fixedLimits->stepSize;
    int currentValue = defaultValue;
    if (currentValue == -1) {
        currentValue = min + (max - min) / 2;
        if (currentValue % stepSize != 0) currentValue += currentValue % stepSize;
    }
    unsigned int holdTimer = 200;
    const unsigned int linesCount = 5;
    const char help[] = "dec(<)/(down) inc(>)/(up) apply(A) back(B)";
    const char* measure = param->measure != NULL ? param->measure : fixedLimits->measure != NULL ? fixedLimits->measure : "";
    const unsigned int minMaxDif = numPlaces(max) - numPlaces(min);
    unsigned int maxStringLen = 16 + numPlaces(min > 1500 ? min / 1000 : min) + numPlaces(max > 1500 ? max / 1000 : max) * 2 +
                                numPlaces(stepSize > 1500 ? stepSize / 1000 : stepSize) + (measure != NULL ? strlen(measure) : 0) + minMaxDif + 6;
    if (strlen(help) + 2 > maxStringLen) maxStringLen = strlen(help) + 2;
    unsigned int fontSize = gfx_con.fntsz;
    unsigned int boxWidth = (maxStringLen * fontSize) + fontSize * 2;
    unsigned int boxHeight = (linesCount * fontSize) + fontSize * 2;
    unsigned int boxX0Position = 1280 / 2 - boxWidth / 2;
    unsigned int boxX1Position = 1280 / 2 + boxWidth / 2;
    unsigned int boxY0Position = 720 / 2 - boxHeight / 2;
    unsigned int boxY1Position = 720 / 2 + boxHeight / 2;
    unsigned int boxXMid = boxX0Position + boxWidth / 2;
    unsigned int paramNameXPosition = boxXMid - (strlen(param->name) / 2) * fontSize;
    unsigned int helpXPosition = boxXMid - 21 * fontSize;

    unsigned int paramNameYPosition = boxY0Position + 1 * fontSize;
    unsigned int helpYPosition = boxY0Position + 3 * fontSize;
    unsigned int selectorY0Position = boxY0Position + 5 * fontSize;

    unsigned int lastPress = 1000 + get_tmr_ms();
    unsigned int lastResult = currentValue;
    int mult = (max - min) / (stepSize * 10);
    if (mult < 2) mult = 2;
    bool redraw = true;
    bool fullRedraw = true;
    Input_t* input = hidRead();
    Input_t oldButtons = *input;
    bool isFromConfirmDialog = false;
    bool div = min > 1500 || currentValue > 1500 || max > 1500 || stepSize > 1500;
    char* minStr = malloc(8);
    formatValueDiv(minStr, min, div);
    char* currentStr = malloc(8);
    char* maxStr = malloc(8);
    formatValueDiv(maxStr, max, div);
    char* stepStr = malloc(8);
    formatValueDiv(stepStr, stepSize, div);
    char* buff = malloc(256);
    while (1) {
        if (redraw || fullRedraw) {
            gfx_printTopInfoKT();
            SETCOLOR(COLOR_WHITE, COLOR_GREY);
            if (fullRedraw) {
                minerva_periodic_training();
                gfx_box(boxX0Position, boxY0Position, boxX1Position, boxY1Position, COLOR_GREY);
                gfx_con_setpos(paramNameXPosition, paramNameYPosition);
                gfx_puts(param->name);
                gfx_con_setpos(helpXPosition, helpYPosition);
                gfx_puts(help);
                fullRedraw = false;
            }
            div = div || currentValue > 1500;
            formatValueDiv(currentStr, currentValue, div);
            s_printf(buff, "min=%s %s %s=max step=%s%s", minStr, currentStr, maxStr, stepStr, measure);
            maxStringLen = strlen(buff);
            unsigned int selectorX0Position = boxXMid - (maxStringLen / 2) * fontSize;
            if (redraw) {
                gfx_box(selectorX0Position - 2 * fontSize, selectorY0Position, selectorX0Position, selectorY0Position + fontSize, COLOR_GREY);
                gfx_box(selectorX0Position + maxStringLen * fontSize, selectorY0Position, boxX1Position, selectorY0Position + fontSize, COLOR_GREY);
                redraw = false;
            }
            gfx_con_setpos(selectorX0Position, selectorY0Position);
            gfx_printf("min=%s %k%s%k %s=max step=%s%s", minStr, COLOR_ORANGE, currentStr, COLOR_WHITE, maxStr, stepStr, measure);
        }
        if (isFromConfirmDialog) {
            const unsigned holdTimer = 500;
            unsigned int lastTmrCheck = get_tmr_ms();
            while (get_tmr_ms() < holdTimer + lastTmrCheck && hidRead()->buttons) {
            };
            isFromConfirmDialog = false;
            oldButtons = *input;
        }
        while (!hidRead()->buttons || oldButtons.buttons & input->buttons) {
            if (oldButtons.buttons != input->buttons) oldButtons = *input;
            if ((lastPress + holdTimer) < get_tmr_ms() && (oldButtons.buttons & input->buttons)) break;
        }
        if (input->buttons) oldButtons = *input;
        if (oldButtons.a) {
            if (validateValue(min, max, stepSize, currentValue)) {
                const ManualValueResult good = {.value = currentValue, .status = EMVS_GOOD};
                const char* message[] = {"Do you want to set new value?", NULL};
                if (confirmationDialog(message, EYES) == EYES) {
                    free(minStr);
                    free(currentStr);
                    free(maxStr);
                    free(stepStr);
                    free(buff);
                    return good;
                } else {
                    fullRedraw = true;
                    isFromConfirmDialog = true;
                    oldButtons = *input;
                    continue;
                }
            } else {
                const char* message[] = {"Oops... The selected value cannot be used O_o", "Do you want to continue editing?", NULL};
                if (confirmationDialog(message, ENO) != EYES) {
                    const ManualValueResult invalidValue = {.status = EMVS_INVALID_VALUE};
                    {
                        free(minStr);
                        free(currentStr);
                        free(maxStr);
                        free(stepStr);
                        free(buff);
                        return invalidValue;
                    }
                }
                continue;
            }
        } else if (oldButtons.b) {
            const ManualValueResult exit = {.status = EMVS_EXIT};
            const char* message[] = {"Do you want to close editor?", NULL};
            if (confirmationDialog(message, EYES) == EYES) {
                free(minStr);
                free(currentStr);
                free(maxStr);
                free(stepStr);
                free(buff);
                return exit;
            } else {
                fullRedraw = true;
                isFromConfirmDialog = true;
                oldButtons = *input;
                continue;
            }
            {
                free(minStr);
                free(currentStr);
                free(maxStr);
                free(stepStr);
                free(buff);
                return exit;
            }
        } else if (oldButtons.right || oldButtons.volp) {
            if (currentValue + stepSize < max)
                currentValue += stepSize;
            else
                currentValue = max;
        } else if (oldButtons.left || oldButtons.volm) {
            if (min < currentValue - stepSize)
                currentValue -= stepSize;
            else
                currentValue = min;
        } else if (oldButtons.up && !oldButtons.volp) {
            if (currentValue + stepSize * mult < max)
                currentValue += stepSize * mult;
            else
                currentValue = max;
        } else if (oldButtons.down && !oldButtons.volm) {
            if (min < currentValue - stepSize * mult)
                currentValue -= stepSize * mult;
            else
                currentValue = min;
        }
        if (currentValue != lastResult) {
            if (currentValue % stepSize != 0) currentValue += currentValue % stepSize;
            if (currentValue > max)
                currentValue = max;
            else if (currentValue < min)
                currentValue = min;
            lastResult = currentValue;
            redraw = true;
        }
        lastPress = get_tmr_ms();
    }
}
