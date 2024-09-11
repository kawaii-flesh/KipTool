#pragma once

#define SDRAM_CONFIG_KEYS_COUNT 526
#define SDRAM_CONFIG_KEYS_FILE_SIZE 12243
#define SDRAM_CONFIG_KEYS_FILE_PATH "sd:/sdram_keys.bin"
#define SDRAM_CONFIG_KEYS_FILE_END "end."
#define SDRAM_CONFIG_KV_FILE_PATH "sd:/config/4IFIR/sdram.ini"

#include <utils/types.h>

typedef struct ValueOffset {
    u32 value;
    u32 offset;
} ValueOffset;

void initSDRAMConfig();
int getKeyOffset(const char *keyName);
u32 parseValues(char *section);
void sdramConfig();
extern ValueOffset *_newValues;
