#include "tools.h"

#include <display/di.h>
#include <libs/fatfs/ff.h>
#include <mem/heap.h>
#include <storage/nx_sd.h>
#include <string.h>
#include <utils/sprintf.h>
#include <utils/util.h>

#include "../err.h"
#include "../fs/fscopy.h"
#include "../fs/fsutils.h"
#include "../fs/readers/folderReader.h"
#include "../gfx/gfx.h"
#include "../gfx/gfxutils.h"
#include "../gfx/menu.h"
#include "../hid/hid.h"
#include "../tegraexplorer/tconf.h"
#include "../utils/utils.h"

extern bool sd_mounted;

void TakeScreenshot() {
    static u32 timer = 0;

    if (!TConf.minervaEnabled || !sd_mounted) return;

    if (timer + 3 < get_tmr_s())
        timer = get_tmr_s();
    else
        return;

    char *name, *path;
    const char basepath[] = "sd:/tegraexplorer/screenshots";
    name = malloc(40);
    s_printf(name, "Screenshot_%08X.bmp", get_tmr_us());

    f_mkdir("sd:/tegraexplorer");
    f_mkdir(basepath);
    path = CombinePaths(basepath, name);
    free(name);

    const u32 file_size = 0x384000 + 0x36;
    u8* bitmap = malloc(file_size);
    u32* fb = malloc(0x384000);
    u32* fb_ptr = gfx_ctxt.fb;

    for (int x = 1279; x >= 0; x--) {
        for (int y = 719; y >= 0; y--) fb[y * 1280 + x] = *fb_ptr++;
    }

    memcpy(bitmap + 0x36, fb, 0x384000);
    bmp_t* bmp = (bmp_t*)bitmap;

    bmp->magic = 0x4D42;
    bmp->size = file_size;
    bmp->rsvd = 0;
    bmp->data_off = 0x36;
    bmp->hdr_size = 40;
    bmp->width = 1280;
    bmp->height = 720;
    bmp->planes = 1;
    bmp->pxl_bits = 32;
    bmp->comp = 0;
    bmp->img_size = 0x384000;
    bmp->res_h = 2834;
    bmp->res_v = 2834;
    bmp->rsvd2 = 0;

    sd_save_to_file(bitmap, file_size, path);
    free(bitmap);
    free(fb);
    free(path);

    display_backlight_brightness(255, 1000);
    msleep(100);
    display_backlight_brightness(100, 1000);
}
