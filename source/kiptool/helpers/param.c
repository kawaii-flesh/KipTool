#include "param.h"

#include <stdlib.h>
#include <string.h>
#include <utils/sprintf.h>

#include "../../hid/hid.h"
#include "../params/param.h"
#include "kiprw.h"

void addPostfix(const Param* param, char* displayBuff, unsigned int value, int isParam, int addToDefault) {
    if (param->defaultValue == value && addToDefault)
        strcpy(displayBuff + strlen(displayBuff), " - Default");
    else if (isParam)
        strcpy(displayBuff + strlen(displayBuff), " - Changed");
}

void addLabel(const Value* value, char* displayBuff) {
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

void getDisplayValue(const Param* param, char* displayBuff, unsigned int value) {
    formatValue(displayBuff, value);
    const Value* foundedValue = NULL;
    const char* measure = param->measure;
    bool founded = false;
    for (unsigned int limitIndex = 0; limitIndex < param->limitsCount; ++limitIndex) {
        const Limit limit = param->limits[limitIndex];
        if (limit.type == EFixedOneValue) {
            const FixedOneValue* fixedOneValue = (const FixedOneValue*)limit.values;
            if (fixedOneValue->value.value == value) {
                foundedValue = &fixedOneValue->value;
                founded = true;
                break;
            }
        } else if (limit.type == EFixedValues) {
            const FixedValues* fixedValues = (const FixedValues*)limit.values;
            for (unsigned int i = 0; i < fixedValues->valuesCount; ++i) {
                if (fixedValues->values[i].value == value) {
                    foundedValue = &fixedValues->values[i];
                    founded = true;
                    break;
                }
            }
            if (founded) break;
        } else if (limit.type == EFixedLimits) {
            const FixedLimits* fixedLimits = (const FixedLimits*)limit.values;
            if ((fixedLimits->min <= value && value <= fixedLimits->max) && (value % fixedLimits->stepSize == 0)) {
                if (fixedLimits->measure != NULL) measure = fixedLimits->measure;
                founded = true;
                break;
            }
        } else if (limit.type == EFixedRange) {
            const FixedRange* fixedRange = (const FixedRange*)limit.values;
            if (fixedRange->start <= value && value <= fixedRange->end) {
                founded = true;
                break;
            }
        }
    }
    if (!founded) {
        strcpy(displayBuff + strlen(displayBuff), " - Unknown value");
        return;
    }
    if (foundedValue != NULL) {
        if (foundedValue->measure != NULL) measure = foundedValue->measure;
    }
    if (measure != NULL) strcpy(displayBuff + strlen(displayBuff), measure);
    if (foundedValue != NULL) addLabel(foundedValue, displayBuff);
    return;
}

void getFormatingData(FormatingData* formatingData, const u8* custTable, const unsigned int paramsCount, const Param* params[]) {
    char* displayBuff = calloc(1024, 1);
    char* start = displayBuff;
    unsigned int nameLen = 0;
    unsigned int valueLen = 0;
    unsigned int labelLen = 0;
    for (unsigned int i = 0; i < paramsCount; ++i) {
        unsigned partsCount = 0;
        s_printf(displayBuff, "%s - ", params[i]->name);
        u32 value = getParamValueFromBuffer(custTable, params[i]);
        getDisplayValue(params[i], displayBuff + strlen(displayBuff), value);
        addPostfix(params[i], displayBuff, value, 1, 1);
        bool space = false;
        for (unsigned int c = 0; c < strlen(displayBuff); ++c) {
            if (displayBuff[c] == '-' && space) ++partsCount;
            space = displayBuff[c] == ' ';
        }
        space = false;
        unsigned int tmp = 0;
        while (*displayBuff != '-' || !space) {
            space = *displayBuff == ' ';
            ++displayBuff;
            ++tmp;
        }
        space = false;
        if (tmp > nameLen) nameLen = tmp;
        tmp = 0;
        while (*displayBuff != '-' || !space) {
            space = *displayBuff == ' ';
            ++displayBuff;
            ++tmp;
        }
        space = false;
        if (tmp > valueLen) valueLen = tmp;
        if (partsCount == 3) {
            tmp = 0;
            while (*displayBuff != '-' || !space) {
                space = *displayBuff == ' ';
                ++displayBuff;
                ++tmp;
            }
            if (tmp > labelLen) labelLen = tmp;
        }
    }
    formatingData->nameLen = nameLen;
    formatingData->valueLen = valueLen;
    formatingData->labelLen = labelLen;
    free(start);
}

char* getFormattedBuff(FormatingData* formatingData, char* buff) {
    char* newBuff = calloc(1024, 1);
    char* start = newBuff;
    char* oldBuff = buff;
    unsigned int tmp = 0;
    bool space = false;
    unsigned int partsCount = 0;
    for (unsigned int c = 0; c < strlen(oldBuff); ++c) {
        if (oldBuff[c] == '-' && space) ++partsCount;
        space = oldBuff[c] == ' ';
    }
    space = false;
    while (*oldBuff != '-' || !space) {
        space = *oldBuff == ' ';
        *newBuff = *oldBuff;
        ++tmp;
        ++oldBuff;
        ++newBuff;
    }
    for (unsigned int i = 0; i < formatingData->nameLen - tmp; ++i) {
        *newBuff = ' ';
        ++newBuff;
    }
    space = false;
    tmp = 0;
    while (*oldBuff != '-' || !space) {
        space = *oldBuff == ' ';
        *newBuff = *oldBuff;
        ++tmp;
        ++oldBuff;
        ++newBuff;
    }
    space = false;
    for (unsigned int i = 0; i < formatingData->valueLen - tmp; ++i) {
        *newBuff = ' ';
        ++newBuff;
    }
    space = false;
    tmp = 0;
    if (partsCount == 3) {
        while (*oldBuff != '-' || !space) {
            space = *oldBuff == ' ';
            *newBuff = *oldBuff;
            ++tmp;
            ++oldBuff;
            ++newBuff;
        }
        space = false;
    } else {
        if (formatingData->labelLen > 0) {
            *newBuff = '-';
            ++newBuff;
            tmp = 1;
        }
    }
    for (unsigned int i = 0; i < formatingData->labelLen - tmp; ++i) {
        *newBuff = ' ';
        ++newBuff;
    }
    while (*oldBuff != '\0') {
        *newBuff = *oldBuff;
        ++oldBuff;
        ++newBuff;
    }
    return start;
}
