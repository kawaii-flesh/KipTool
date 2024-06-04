#include "profile.h"

#include <mem/heap.h>
#include <string.h>

#include "../../fs/fscopy.h"
#include "../../fs/fsutils.h"
#include "../../fs/readers/folderReader.h"
#include "../../utils/utils.h"
#include "../../utils/vector.h"
#include "../gfx/dialogs/confirmationDialog.h"
#include "../gfx/gfx.h"
#include "../gfx/menus/ktMenu.h"
#include "../helpers/rw.h"

int addFileToProfiles(char* path, FSEntry_t entry) {
    gfx_clearscreenKT();
    char* buff = malloc(256);
    char* currentProfile = getCurrentProfileName();
    strcpy(buff, !strcmp(currentProfile, KT_PROFILES_NOT_SELECTED) ? entry.name : currentProfile);
    char* value = ShowKeyboard(buff, false);
    if (value == NULL) value = entry.name;
    strcpy(buff, KT_PROFILES_DIR);
    strcat(buff, "/");
    strcat(buff, value);
    const char* message[] = {"Do you want to add a profile?", NULL};
    if (confirmationDialog(message, ENO) == EYES) {
        char* inPath = malloc(256);
        strcpy(inPath, path);
        strcat(inPath, "/");
        strcat(inPath, entry.name);
        gfx_clearscreenKT();
        if (FileExists(buff)) {
            const char* fileMessage[] = {"The profile with that name already exists.", "Do you want to overwrite it?", NULL};
            if (confirmationDialog(fileMessage, ENO) == EYES) {
                gfx_clearscreenKT();
                FileCopy(inPath, buff, COPY_MODE_PRINT);
            }
        } else
            FileCopy(inPath, buff, COPY_MODE_PRINT);
        free(inPath);
    }
    free(buff);
    free(value);
    return 0;
}

void setCurrentProfile(const char profileName[]) {
    const char* fileMessage[] = {"This action will replace the loader.kip file.",
                                 "Save it before changing your profile",
                                 "if you don't want to lose the changes you've made",
                                 "Do you want to set profile?",
                                 profileName,
                                 NULL};
    if (confirmationDialog(fileMessage, ENO) != EYES) return;

    const char* currentProfile = getCurrentProfileName();

    char* newProfilePath = malloc(256);
    strcpy(newProfilePath, KT_PROFILES_DIR);
    strcat(newProfilePath, "/");
    strcat(newProfilePath, profileName);

    f_unlink(KT_PROFILES_CURRENT_FILE_PATH);
    writeData(KT_PROFILES_CURRENT_FILE_PATH, -1, profileName, strlen(profileName) + 1, 0);
    gfx_clearscreenKT();
    FileCopy(newProfilePath, KT_LOADER_KIP_PATH, COPY_MODE_PRINT);
    free(newProfilePath);
}

void deleteProfile(const char profileName[]) {
    const char* currentProfile = getCurrentProfileName();

    if (!strcmp(currentProfile, profileName)) f_unlink(KT_PROFILES_CURRENT_FILE_PATH);

    char* profilePath = malloc(256);
    strcpy(profilePath, KT_PROFILES_DIR);
    strcat(profilePath, "/");
    strcat(profilePath, profileName);

    f_unlink(profilePath);
    free(profilePath);
}

char* _currentProfileName = NULL;
char* getCurrentProfileName() {
    if (_currentProfileName == NULL) _currentProfileName = malloc(256);
    createDirIfNotExist(KT_PROFILES_DIR);
    if (!FileExists(KT_PROFILES_CURRENT_FILE_PATH))
        strcpy(_currentProfileName, KT_PROFILES_NOT_SELECTED);
    else {
        if (readAllFile(KT_PROFILES_CURRENT_FILE_PATH, _currentProfileName, 256) != FR_OK) strcpy(_currentProfileName, "READ ERROR!");
    }

    return _currentProfileName;
}

int getProfilesCount() {
    int res;
    Vector_t files = ReadFolder(KT_PROFILES_DIR, &res);
    int counter = 0;
    vecDefArray(FSEntry_t*, fsEntries, files);
    for (int i = 0; i < files.count; ++i)
        if (strcmp(KT_PROFILES_CURRENT_FILE, fsEntries[i].name)) ++counter;
    clearFileVector(&files);
    return counter;
}

void profiles() {
    if (!DirExists(KT_PROFILES_DIR)) return;
    int startIndex = 0;
    int resE;
    Vector_t files = ReadFolder(KT_PROFILES_DIR, &resE);
    MenuEntry* entries = malloc(sizeof(MenuEntry) * (files.count + 1));
    vecDefArray(FSEntry_t*, fsEntries, files);
    entries[0].optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT;
    entries[0].type = ETLabel;
    entries[0].entry = "Profiles: (A) - select | (X) - delete";
    while (true) {
        if (getProfilesCount() == 0) {
            clearFileVector(&files);
            free(entries);
            break;
        }
        int entriesCount = files.count + 1;
        for (int i = 0, j = 1; i < files.count; ++i) {
            if (!strcmp(KT_PROFILES_CURRENT_FILE, fsEntries[i].name)) {
                --entriesCount;
                continue;
            }
            entries[j].entry = fsEntries[i].name;
            entries[j].type = ETLabel;
            if (!strcmp(getCurrentProfileName(), fsEntries[i].name)) {
                entries[j].optionUnion = COLORTORGB(COLOR_BLUE);
                startIndex = j;
            } else
                entries[j].optionUnion = COLORTORGB(COLOR_ORANGE);
            ++j;
        }
        gfx_clearscreenKT();
        MenuResult menuResult = newMenuKT(entries, entriesCount, startIndex, JoyA | JoyX, NULL, printEntry);
        if (menuResult.buttons & JoyB) {
            clearFileVector(&files);
            free(entries);
            break;
        }
        startIndex = menuResult.index;
        if (menuResult.buttons & JoyA) {
            gfx_clearscreenKT();
            setCurrentProfile(entries[menuResult.index].entry);
        } else if (menuResult.buttons & JoyX) {
            gfx_clearscreenKT();
            const char* fileMessage[] = {"Do you want to delete the profile?", entries[menuResult.index].entry, NULL};
            if (confirmationDialog(fileMessage, ENO) != EYES) continue;
            deleteProfile(entries[menuResult.index].entry);
            startIndex = 0;
        }
        clearFileVector(&files);
        files = ReadFolder(KT_PROFILES_DIR, &resE);
    }
}
