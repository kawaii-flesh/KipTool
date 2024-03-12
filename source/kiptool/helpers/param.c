#include "param.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../params/param.h"

void addDefaultPostfix(const Param* param, char* displayBuff, unsigned int value, int isParam) {
    if (param->defaultValue == value)
        strcpy(displayBuff + strlen(displayBuff), " - Default");
    else if (isParam)
        strcpy(displayBuff + strlen(displayBuff), " - Changed");
}

void addLabel(const Param* param, const Value* value, char* displayBuff) {
    if (value->label == NULL) return;
    s_printf(displayBuff + strlen(displayBuff), " - %s", value->label);
}

bool addLabelToFixedValue(const Param* param, char* displayBuff, unsigned int value) {
    const FixedValues* limits = (FixedValues*)(param->limits);
    for (unsigned int i = 0; i < limits->valuesCount; ++i) {
        if (limits->values[i].value == value) {
            if (limits->values[i].label == NULL) return true;
            s_printf(displayBuff + strlen(displayBuff), " - %s", limits->values[i].label);
            return true;
        }
    }
    return false;
}

void doubleToStr(char* buffer, double value) {
    unsigned int wholePart = (unsigned int)value;
    double fractionPart = value - wholePart;

    utoa(wholePart, buffer, 10);

    int len = strlen(buffer);
    buffer[len] = '.';
    len++;
    fractionPart *= 10;
    buffer[len] = (char)((int)(fractionPart + 0.1) + '0');
    buffer[len + 1] = '\0';
}

void formatValue(char* displayBuff, const unsigned int value) {
    if (value > 1500) {
        double dValue = value;
        dValue /= 1000.0;
        doubleToStr(displayBuff, dValue);
    } else
        utoa(value, displayBuff, 10);
    return;
}

void formatValueDiv(char* displayBuff, const unsigned int value, bool div) {
    if (div) {
        double dValue = value;
        dValue /= 1000.0;
        doubleToStr(displayBuff, dValue);
    } else
        utoa(value, displayBuff, 10);
    return;
}

void getDisplayValue(const Param* param, char* displayBuff, unsigned int value, int isParam) {
    formatValue(displayBuff, value);
    if (param->measure != NULL) strcpy(displayBuff + strlen(displayBuff), param->measure);
    bool founded = false;
    for (unsigned limitIndex = 0; limitIndex < param->limitsCount; ++limitIndex) {
        const Limit limit = param->limits[limitIndex];
        if (limit.type == EFixedOneValue) {
            const FixedOneValue* fixedOneValue = (const FixedOneValue*)limit.values;
            if (fixedOneValue->value.value == value) {
                addLabel(param, &fixedOneValue->value, displayBuff);
                founded = true;
                break;
            }
        } else if (limit.type == EFixedValues) {
            const FixedValues* fixedValues = (const FixedValues*)limit.values;
            for (unsigned int i = 0; i < fixedValues->valuesCount; ++i)
                if (fixedValues->values[i].value == value) {
                    addLabel(param, &fixedValues->values[i], displayBuff);
                    founded = true;
                    break;
                }
        } else if (limit.type == EFixedLimits) {
            const FixedLimits* fixedLimits = (const FixedLimits*)limit.values;
            if ((fixedLimits->min <= value && value <= fixedLimits->max) && (value % fixedLimits->stepSize == 0)) {
                if (fixedLimits->measure != NULL) strcpy(displayBuff + strlen(displayBuff), fixedLimits->measure);
                founded = true;
                break;
            }
        }
    }
    if (!founded) {
        strcpy(displayBuff + strlen(displayBuff), " - Unknown value");
        return;
    }
    addDefaultPostfix(param, displayBuff, value, isParam);
    return;
}