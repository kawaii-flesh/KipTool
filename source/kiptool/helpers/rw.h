#pragma once
#include <libs/fatfs/ff.h>

FRESULT writeData(const char *path, const int offset, const void *data, u32 dataSize, BYTE flags);
FRESULT readData(const char *path, void *buffer, u32 bufferSize);
FRESULT createDirIfNotExist(const char path[]);
