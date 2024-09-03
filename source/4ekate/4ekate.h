#pragma once
#include <libs/fatfs/ff.h>

#include "../kiptool/service/kiptool.h"

#define CHEKATE_UNKNOWN_STAGE "4EKATE - UNKNOWN Stage"
#define CHEKATE_STAGES_COUNT 3
#define CHIFIX_DETECT_OFFSET 0x90
#define CHEKATE_FILES_COUNT 4

typedef struct {
    unsigned int mc_emem_adr_cfg_channel_mask;
    unsigned int mc_emem_adr_cfg_bank_mask0;
    unsigned int mc_emem_adr_cfg_bank_mask1;
    unsigned int mc_emem_adr_cfg_bank_mask2;
} CHEKATEParams;

void set4ekateStagesOffsets();
int getCurrentStageId();
const char* getCurrentStageTitle();
extern const char* stagesTitles[CHEKATE_STAGES_COUNT];
extern const char* chekateFilesPaths[CHEKATE_FILES_COUNT];
extern bool chekateStageWasChanged;
bool chekateFilesExists();

void chekate();
