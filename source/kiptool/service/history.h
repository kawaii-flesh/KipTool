// #pragma once

// #include <utils/types.h>
// #include "kiptool.h"

// #define KT_IDSTORAGE "sd:/.kt/id_storage.bin"

// typedef struct {
//     const char magic[8];
//     u32 id;
//     u32 custRev;
// } HistoryHeader;

// typedef struct {
//     u32 order;
//     u32 from;
//     u32 to;
//     u32 offset;
//     const char* target;
// } HistoryEntry;

// typedef struct {
//     HistoryHeader header;
//     HistoryEntry entries[];
// } History;

// u32 createHistory(const char* kipFilePath);
// int addHistoryEntry(u32 historyId, u32 from, u32 to, u32 offset, const char* target);
