#pragma once

#include <utils/types.h>

#include "../../fs/fsutils.h"
#include "../helpers/rw.h"
#include "kiptool.h"

typedef struct {
    const char magic[8];
    u32 id;
} IDStorage;

FRESULT createIdStorage(const char idStoragePath[]) {
    const IDStorage idStorage = {.magic = KT_MAGIC, .id = 0};
    return writeData(idStoragePath, -1, &idStorage, sizeof(IDStorage), 0);
}

u32 getId(const char idStoragePath[]) {
    if (!FileExists(idStoragePath)) createIdStorage(idStoragePath);
    IDStorage* idStorage = malloc(sizeof(IDStorage));
    u32 idValue = 0;
    if (readData(idStoragePath, idStorage, sizeof(IDStorage)) != FR_OK)
        idValue = 0;
    else {
        idValue = ++idStorage->id;
        writeData(idStoragePath, -1, idStorage, sizeof(IDStorage), 0);
    }
    free(idStorage);
    return idValue;
}
