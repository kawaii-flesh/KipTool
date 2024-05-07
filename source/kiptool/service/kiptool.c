#include "kiptool.h"

#include <libs/fatfs/ff.h>
#include <stdbool.h>
#include <string.h>

#include "../../fs/fsutils.h"
#include "../helpers/rw.h"
#include "../params/customize.h"
#include "session.h"

const KTSection emptyKTSection = {.magic = KT_MAGIC, .idSession = 0, .idHistory = 0};
FRESULT addKTSection(const char kipFilePath[], KTSection* buffer) {
    memcpy(buffer, &emptyKTSection, sizeof(KTSection));
    buffer->idSession = getSessionId();
    buffer->idHistory = 0;
    FRESULT result = writeData(kipFilePath, -1, buffer, sizeof(KTSection), FA_OPEN_APPEND);
    return result;
}
