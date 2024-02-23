#pragma once

enum LimitsType {
    EFixedLimits,
    EFixedOneValue,
    EFixedValues,
    EMinByParam,
    EMaxByParam,
    EMinAndMaxByParam
};

typedef struct {
    const unsigned int value;
    const char *label;
} Value;

typedef struct {
    const char *name;
    const char *measure;
    const char *description;
    const unsigned int offset;
    const unsigned int length;
    const unsigned int defaultValue;
    const enum LimitsType limitsType;
    const void *limits;
} Param;

typedef struct {
    const unsigned int valuesCount;
    const Value values[];
} FixedValues;

typedef struct {
    const Value value;
} FixedOneValue;

typedef struct {
    const unsigned int min;
    const unsigned int max;
    const unsigned int stepSize;
} FixedLimits;

typedef struct {
    const Param *min;
    const unsigned int max;
    const unsigned int stepSize;
} MinByParam;

typedef struct {
    const unsigned int min;
    const Param *max;
    const unsigned int stepSize;
} MaxByParam;

typedef struct {
    const Param *min;
    const Param *max;
    const unsigned int stepSize;
} MinAndMaxByParam;