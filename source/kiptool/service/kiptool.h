#pragma once

#include <libs/fatfs/ff.h>
#include <stdbool.h>

#define KT_DIR "sd:/.kt"
#define KT_MAGIC \
    { '.', 'K', 'I', 'P', 'T', 'O', 'O', 'L' }

typedef struct {
    const char magic[8];
    u32 idSession;
    u32 idHistory;
} KTSection;

FRESULT addKTSection(const char kipFilePath[], KTSection* buffer);
