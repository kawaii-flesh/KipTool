#pragma once

#define SDRAM_TWEAK_KEYS_COUNT 526
#define SDRAM_TWEAK_KEYS_FILE_SIZE 12243
#define SDRAM_TWEAK_KEYS_FILE_PATH "sd:/sdram_keys.bin"
#define SDRAM_TWEAK_KEYS_FILE_END "end."
#define SDRAM_TWEAK_KV_FILE_PATH "sd:/config/4IFIR/sdram.ini"
#define SDRAM_TWEAK_PAYLOAD_OFFSET 0x0001804d

#include <utils/types.h>

typedef struct ValueOffset {
    u32 value;
    u32 offset;
} ValueOffset;

void initSDRAMTweak();
int getKeyOffset(const char *keyName);
u32 parseValues();
void applyNewChanges();
extern ValueOffset *_newValues;
