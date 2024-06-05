#pragma once
#include "../kiptool/service/kiptool.h"

#define CHEKATE_UNKNOWN_STAGE "4EKATE - UNKNOWN Stage"
#define CHEKATE_PAYLOAD_PATH "sd:/payload.bin"
#define CHEKATE_FUSEE_PATH "sd:/bootloader/payloads/fusee.bin"
#define CHEKATE_PAYLOAD_BACKUP_PATH (KT_DIR "/backup_payload.bin")
#define CHEKATE_FUSEE_BACKUP_PATH (KT_DIR "/backup_fusee.bin")
#define CHEKATE_STAGES_COUNT 3

typedef struct {
    unsigned int mc_emem_adr_cfg_channel_mask;
    unsigned int mc_emem_adr_cfg_bank_mask0;
    unsigned int mc_emem_adr_cfg_bank_mask1;
    unsigned int mc_emem_adr_cfg_bank_mask2;
} CHEKATEParams;

const char* getCurrentStageTitle();
extern const char* stagesTitles[CHEKATE_STAGES_COUNT];

void chekate();
