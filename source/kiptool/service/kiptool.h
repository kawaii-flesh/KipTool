#pragma once

#include <libs/fatfs/ff.h>
#include <stdbool.h>

#define KTDIR "sd:/.kt"

FRESULT createKTDirIfNotExist();
FRESULT overwriteCUST(FIL* kipFile, const unsigned int custOffset, const u8* custTable);
