#pragma once
#include "../kiptool/service/kiptool.h"

#define CHEKATE_PARAMS_ABSOLUTE_OFFSET 0x00019f78
#define CHEKATE_UNKNOWN_STAGE "4EKATE - UNKNOWN Stage"
#define CHEKATE_PAYLOAD_PATH "sd:/payload.bin"
#define CHEKATE_PAYLOAD_BACKUP_PATH (KTDIR "/backup_payload.bin")

typedef struct {
    unsigned int p0;
    unsigned int p1;
    unsigned int p2;
    unsigned int p3;
} CHEKATEParams;

const char* getCurrentStageTitle();

void chekate();
