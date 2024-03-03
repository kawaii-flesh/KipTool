#pragma once

enum LimitsType { EFixedLimits, EFixedOneValue, EFixedValues, EMinByParam, EMaxByParam, EMinAndMaxByParam };
enum Category { GENERAL, CPU, GPU, RAM };
enum Platform { COMMON, MARIKO, ERISTA };

typedef struct {
    const unsigned int value;
    const char *label;
} Value;

typedef struct {
    const enum LimitsType type;
    const void *values;
} Limit;

typedef struct {
    const char *name;
    const enum Category category;
    const enum Platform platform;
    const char *measure;
    const char *description;
    const unsigned int offset;
    const unsigned int length;
    const unsigned int defaultValue;
    const unsigned int limitsCount;
    const Limit limits[];
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
    const char *measure;
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

typedef struct Params {
    unsigned int count;
    Param *params[];
} Params;