#include "kiprw.h"

#include <mem/heap.h>
#include <utils/sprintf.h>

#include "../../helpers/mem.h"
#include "../gfx/gfx.h"
#include "../params/param.h"

unsigned int getParamValueFromBuffer(const u8* buffer, const Param* param) { return *(unsigned int*)(buffer + param->offset); }

unsigned int getParamValueFromFile(FIL* file, const unsigned int baseOffset, const Param* param) {
    u32 value;
    unsigned int bytesReaded = 0;
    f_lseek(file, baseOffset + param->offset);
    f_read(file, &value, 4, &bytesReaded);
    return value;
}

int checkVersionAndMagicFromBuffer(const CustomizeTable* customizeTable) {
    return customizeTable->custRev == KT_CUST_VER && compareU8Arrays((const u8*)customizeTable->cust, (const u8*)"CUST", 4);
}

void setParamValue(const u8* buffer, const Param* param, unsigned int value) {
    *(unsigned int*)(buffer + param->offset) = value;
    char* message = calloc(256, 1);
    s_printf(message, "[Session] Param: %s has been changed", param->name);
    gfx_printBottomInfoKT(message);
    free(message);
}

void setParamValueWithoutSaveSession(const u8* buffer, const Param* param, unsigned int value) { *(unsigned int*)(buffer + param->offset) = value; }
