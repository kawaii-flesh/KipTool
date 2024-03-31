#pragma once

#include "../params/customize.h"
#include "kiptool.h"

#define KTSESSION "sd:/.kt/session.bin"

bool loadSession(CustomizeTable* customizeTable);
bool saveSession(const CustomizeTable* customizeTable);
bool removeSession();
