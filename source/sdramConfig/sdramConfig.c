#include "sdramConfig.h"

#include <libs/fatfs/ff.h>
#include <mem/heap.h>
#include <mem/sdram_param_t210b01.h>
#include <string.h>
#include <utils/ini.h>
#include <utils/list.h>
#include <utils/util.h>

#include "../helpers/mem.h"
#include "../hid/hid.h"
#include "../kiptool/gfx/dialogs/confirmationDialog.h"
#include "../kiptool/gfx/gfx.h"
#include "../kiptool/gfx/menus/ktMenu.h"
#include "../kiptool/helpers/rw.h"
#include "../sharedValues/sharedValues.h"

char *_keys = NULL;
ValueOffset *_newValues = NULL;

// "sd:/payload.bin"
// "sd:/bootloader/payloads/fusee.bin"
// "sd:/atmosphere/reboot_payload.bin"
// "sd:/bootloader/update.bin"
int sdramTableOffsets[PATCH_FILES_COUNT] = {0x0001804d, 0x00019dc0, 0x0001804d, 0x0001804d};

void initSDRAMConfig() {
    if (_keys == NULL) {
        _keys = malloc(SDRAM_CONFIG_KEYS_FILE_SIZE);
        readData(SDRAM_CONFIG_KEYS_FILE_PATH, _keys, SDRAM_CONFIG_KEYS_FILE_SIZE, 0);
    }
    if (_newValues == NULL) {
        _newValues = malloc(sizeof(ValueOffset) * (sizeof(sdram_params_t210b01_t) / sizeof(u32) + 1));
    }
}

int getKeyOffset(const char *keyName) {
    u32 count = 0;
    u32 currentKeysOffset = 0;
    u32 keyNameLen = strlen(keyName);
    while ((keyNameLen + currentKeysOffset) < SDRAM_CONFIG_KEYS_FILE_SIZE) {
        if (compareU8Arrays(SDRAM_CONFIG_KEYS_FILE_END, keyName, 4))
            return -1;
        else if (compareU8Arrays(currentKeysOffset + _keys, keyName, keyNameLen))
            return count;
        while (_keys[currentKeysOffset] != 0 && currentKeysOffset < SDRAM_CONFIG_KEYS_FILE_SIZE) ++currentKeysOffset;
        ++currentKeysOffset;
        ++count;
    }
    return -1;
}

u32 parseValues(char *section) {
    u32 count = 0;
    LIST_INIT(ini_sections);
    if (ini_parse(&ini_sections, SDRAM_CONFIG_KV_FILE_PATH, false)) {
        LIST_FOREACH_ENTRY(ini_sec_t, ini_sec, &ini_sections, link) {
            if (strcmp(ini_sec->name, section) || ini_sec->type != INI_CHOICE) continue;

            LIST_FOREACH_ENTRY(ini_kv_t, kv, &ini_sec->kvs, link) {
                int offset = getKeyOffset(kv->key);
                if (offset != -1) {
                    ValueOffset newValue;
                    newValue.value = strtol(kv->val, NULL, 16);
                    newValue.offset = offset;
                    _newValues[count] = newValue;
                    ++count;
                    if (count == SDRAM_CONFIG_KEYS_COUNT) break;
                }
            }

            break;
        }
    }
    ini_free(&ini_sections);
    return count;
}

typedef struct _SDRAMSection {
    struct _SDRAMSection *next;
    char *name;
} SDRAMSection;

typedef struct SDRAMSectionAndCount {
    SDRAMSection *section;
    u32 count;
} SDRAMSectionAndCount;

void freeSDRAMSection(SDRAMSection *section) {
    SDRAMSection *current = section;
    SDRAMSection *next;

    while (current != NULL) {
        next = current->next;
        if (current->name) {
            free(current->name);
        }
        free(current);
        current = next;
    }
}

SDRAMSectionAndCount getIniSections() {
    SDRAMSectionAndCount result;
    u32 count = 0;
    SDRAMSection *section = NULL;
    LIST_INIT(ini_sections);
    if (ini_parse(&ini_sections, SDRAM_CONFIG_KV_FILE_PATH, false)) {
        LIST_FOREACH_ENTRY(ini_sec_t, ini_sec, &ini_sections, link) {
            if (ini_sec->type != INI_CHOICE) continue;
            SDRAMSection *currentSection;
            if (section == NULL) {
                section = malloc(sizeof(SDRAMSection));
                currentSection = section;
            } else {
                currentSection->next = malloc(sizeof(SDRAMSection));
                currentSection = currentSection->next;
            }
            currentSection->next = NULL;
            currentSection->name = malloc(sizeof(strlen(ini_sec->name) + 1));
            strcpy(currentSection->name, ini_sec->name);
            ++count;
        }
    }

    result.count = count;
    result.section = section;
    ini_free(&ini_sections);
    return result;
}

extern bool chekateStageWasChanged;
void applyNewValues(char *section) {
    const char *applyMessage[] = {"Do you want to apply the configuration?", NULL};
    if (confirmationDialog(applyMessage, ENO) != EYES) return;
    u32 count = parseValues(section);
    gfx_clearscreenKT();
    for (int fileIndex = 0; fileIndex < PATCH_FILES_COUNT; ++fileIndex) {
        gfx_printf("Patching...: %s\n", patchFilesPaths[fileIndex]);
        for (int i = 0; i < count; ++i) {
            writeData(patchFilesPaths[fileIndex], sdramTableOffsets[fileIndex] + sizeof(u32) * _newValues[i].offset, &_newValues[i].value, sizeof(u32), 0);
        }
    }
    chekateStageWasChanged = true;
}
void sdramConfig() {
    initSDRAMConfig();
    SDRAMSectionAndCount sectionAndCount = getIniSections();
    if (sectionAndCount.count == 0) return;
    MenuEntry *menuEntries = calloc(1 + sectionAndCount.count, sizeof(MenuEntry));
    int startIndex = 1;
    menuEntries[0].optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT;
    menuEntries[0].type = ETLabel;
    menuEntries[0].entry = "SDRAM Configs";

    while (1) {
        gfx_clearscreenKT();
        for (int i = 1; i != sectionAndCount.count + 1; ++i) {
            menuEntries[i].type = ETLabel;
            SDRAMSection *currentSection;
            for (int j = 0; j != i; ++j) {
                if (j == 0)
                    currentSection = (SDRAMSection *)sectionAndCount.section;
                else
                    currentSection = (SDRAMSection *)currentSection->next;
            }
            menuEntries[i].entry = currentSection->name;
            menuEntries[i].optionUnion = COLORTORGB(COLOR_ORANGE);
        }
        MenuResult menuResult = newMenuKT(menuEntries, sectionAndCount.count + 1, startIndex, JoyA, NULL, printEntry);
        if (menuResult.buttons & JoyA) {
            startIndex = menuResult.index;
            applyNewValues(menuEntries[menuResult.index].entry);
        }
        if (menuResult.buttons & JoyB) {
            free(menuEntries);
            freeSDRAMSection(sectionAndCount.section);
            break;
        }
    }
}
