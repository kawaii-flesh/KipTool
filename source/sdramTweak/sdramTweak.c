#include "sdramTweak.h"

#include <libs/fatfs/ff.h>
#include <mem/heap.h>
#include <mem/sdram_param_t210b01.h>
#include <string.h>

#include "../helpers/mem.h"
#include "../kiptool/helpers/rw.h"
#include "sdramTweak.h"
#include <utils/list.h>
#include <utils/util.h>
#include <utils/ini.h>

char *_keys = NULL;
ValueOffset *_newValues = NULL;
void initSDRAMTweak() {
    if (_keys == NULL) {
        _keys = malloc(SDRAM_TWEAK_KEYS_FILE_SIZE);
        readData(SDRAM_TWEAK_KEYS_FILE_PATH, _keys, SDRAM_TWEAK_KEYS_FILE_SIZE, 0);
    }
    if (_newValues == NULL) {
        _newValues = malloc(sizeof(ValueOffset)*sizeof(sdram_params_t210b01_t)/sizeof(u32));
    }
}

int getKeyOffset(const char *keyName) {
    u32 count = 0;
    u32 currentKeysOffset = 0;
    u32 keyNameLen = strlen(keyName);
    while ((keyNameLen + currentKeysOffset) < SDRAM_TWEAK_KEYS_FILE_SIZE) {
        if (compareU8Arrays(SDRAM_TWEAK_KEYS_FILE_END, keyName, 4))
            return -1;
        else if (compareU8Arrays(currentKeysOffset + _keys, keyName, keyNameLen))
            return count;
        while (_keys[currentKeysOffset] != 0 && currentKeysOffset < SDRAM_TWEAK_KEYS_FILE_SIZE) ++currentKeysOffset;
        ++currentKeysOffset;
        ++count;
    }
    return -1;
}

u32 parseValues() {
    u32 count = 0;
    LIST_INIT(ini_sections);
    if (ini_parse(&ini_sections, SDRAM_TWEAK_KV_FILE_PATH, false)) {
        LIST_FOREACH_ENTRY(ini_sec_t, ini_sec, &ini_sections, link) {
            if (strcmp(ini_sec->name, "sdram")) continue;

            LIST_FOREACH_ENTRY(ini_kv_t, kv, &ini_sec->kvs, link) {
                int offset = getKeyOffset(kv->key);
                if(offset != -1) {
                    ValueOffset newValue;
                    newValue.value = strtol(kv->val, NULL, 16);
                    newValue.offset = offset;
                    _newValues[count] = newValue;
                    ++count;
                }
            }
        }
    }
    return count;
}

void applyNewChanges() {
    initSDRAMTweak();
    u32 count = parseValues();
    for(int i = 0; i < count; ++i) {
        writeData("sd:/payload.bin", SDRAM_TWEAK_PAYLOAD_OFFSET + sizeof(u32) * _newValues[i].offset, &_newValues[i].value, sizeof(u32), 0);
    }
}