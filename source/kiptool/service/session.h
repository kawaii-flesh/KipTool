#pragma once

#include "../params/customize.h"
#include "kiptool.h"

#define KT_SESSIONS_DIR "sd:/.kt/sessions"
#define KT_SESSIONS_IDSTORAGE "sd:/.kt/sessions/id_storage.bin"

bool loadSession(const KTSection* ktSection, CustomizeTable* customizeTable);
bool saveSession(const KTSection* ktSection, const CustomizeTable* customizeTable);
bool removeSession(const KTSection* ktSection);
const char* getSessionPath(const KTSection* ktSection);
bool isSessionsSupported();
void setSessionSupported(bool value);
bool sessionIsExist(const KTSection* ktSection);
