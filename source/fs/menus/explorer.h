#pragma once
#include "../../gfx/menu.h"
#include "../../utils/vector.h"
#include "../fstypes.h"

void FileExplorer(const char* path);
MenuEntry_t MakeMenuOutFSEntry(FSEntry_t entry);
