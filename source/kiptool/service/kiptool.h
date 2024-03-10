#pragma once

#include <libs/fatfs/ff.h>
#include <stdbool.h>

#define KTDIR "sd:/.kt"
#define KTMAGIC \
    { 'K', 'I', 'P', 'T', 'O', 'O', 'L', 0 }

bool isDirExist(const char* path);
void createKTDirIfNotExist();