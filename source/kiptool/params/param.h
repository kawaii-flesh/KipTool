#pragma once

enum LimitsType { EFixedLimits, EFixedRange, EFixedOneValue, EFixedValues, EMinByParam, EMaxByParam, EMinAndMaxByParam };

typedef struct {
    const unsigned int value;
    const char* label;
} Value;

typedef struct {
    const enum LimitsType type;
    const void* values;
} Limit;

typedef struct {
    const char* name;
    const char* measure;
    const char* description;
    const unsigned int offset;
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
    const char* measure;
} FixedLimits;

typedef struct {
    const unsigned int start;
    const unsigned int end;
} FixedRange;

typedef struct {
    const Param* min;
    const unsigned int max;
    const unsigned int stepSize;
} MinByParam;

typedef struct {
    const unsigned int min;
    const Param* max;
    const unsigned int stepSize;
} MaxByParam;

typedef struct {
    const Param* min;
    const Param* max;
    const unsigned int stepSize;
} MinAndMaxByParam;

typedef struct Params {
    const unsigned int count;
    const Param* params[];
} Params;