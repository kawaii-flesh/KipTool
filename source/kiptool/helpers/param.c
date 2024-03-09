#include "param.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../params/param.h"

extern const Param gKipVersion;
void addDefaultPostfix(const Param* param, char* displayBuff, unsigned int value) {
    if (param != &gKipVersion && param->defaultValue == value) strcpy(displayBuff + strlen(displayBuff), " - Default");
}

void addLabel(const Param* param, const Value* value, char* displayBuff) {
    if (value->label == NULL) return;
    strcpy(displayBuff + strlen(displayBuff), " - ");
    strcpy(displayBuff + strlen(displayBuff), value->label);
}

bool addLabelToFixedValue(const Param* param, char* displayBuff, unsigned int value) {
    const FixedValues* limits = (FixedValues*)(param->limits);
    for (unsigned int i = 0; i < limits->valuesCount; ++i) {
        if (limits->values[i].value == value) {
            if (limits->values[i].label == NULL) return true;
            strcpy(displayBuff + strlen(displayBuff), " - ");
            strcpy(displayBuff + strlen(displayBuff), limits->values[i].label);
            return true;
        }
    }
    return false;
}

void getDisplayValue(const Param* param, char* displayBuff, unsigned int value) {
    utoa(value > 1500 ? value / 1000 : value, displayBuff, 10);
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
    addDefaultPostfix(param, displayBuff, value);
    return;
}