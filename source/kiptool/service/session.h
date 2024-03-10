#pragma once

#include "../params/customize.h"
#include "kiptool.h"

#define KTSESSION "sd:/.kt/session.bin"

typedef struct Session {
    const char magic[8];
    const unsigned int kipVersion;
    const CustomizeTable customizeTable;
} Session;

bool loadSession(Session* session);
bool saveSession(const u8* customizeTable);
bool isSessionExist();