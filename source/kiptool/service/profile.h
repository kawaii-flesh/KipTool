#pragma once

#include "../../fs/fstypes.h"
#include "../gfx/menus/ktMenu.h"

#define KT_PROFILES_DIR "sd:/.kt/profiles"
#define KT_PROFILES_CURRENT_FILE_PATH "sd:/.kt/profiles/current.bin"
#define KT_PROFILES_CURRENT_FILE "current.bin"
#define KT_PROFILES_EMPTY_MSG "no profiles"
#define KT_PROFILES_NOT_SELECTED "not selected"
#define KT_LOADER_KIP_PATH "sd:/atmosphere/kips/loader.kip"

int addFileToProfiles(char* path, FSEntry_t entry);
void setCurrentProfile(const char profileName[]);
void deleteProfile(const char profileName[]);
char* getCurrentProfileName();
int getProfilesCount();
void profiles();
