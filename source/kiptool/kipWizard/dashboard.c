#include "dashboard.h"

#include <mem/heap.h>
#include <mem/sdram.h>
#include <soc/fuse.h>
#include <soc/t210.h>
#include <string.h>
#include <utils/util.h>

#include "../../4ekate/4ekate.h"
#include "../../gfx/gfx.h"
#include "../../gfx/gfxutils.h"
#include "../../hid/hid.h"
#include "../../tegraexplorer/tconf.h"
#include "../helpers/hw.h"
#include "../helpers/kiprw.h"
#include "../helpers/param.h"

typedef struct {
    int lastX;
    int lastY;
} ShowResult;

void printHWInfo() {
    // Decode fuses.
    char* sku;
    char dram_man[64];
    u8 dram_id = fuse_read_dramid(true);

    switch (fuse_read_hw_type()) {
        case FUSE_NX_HW_TYPE_ICOSA:
            sku = "Icosa (Erista)";
            break;
        case FUSE_NX_HW_TYPE_IOWA:
            sku = "Iowa (Mariko)";
            break;
        case FUSE_NX_HW_TYPE_HOAG:
            sku = "Hoag (Mariko)";
            break;
        case FUSE_NX_HW_TYPE_AULA:
            sku = "Aula (Mariko)";
            break;
        default:
            sku = "#FF8000 Unknown#";
            break;
    }

    // Prepare dram id info.
    if (!TConf.isMariko) {
        switch (dram_id) {
            // LPDDR4 3200Mbps.
            case LPDDR4_ICOSA_4GB_SAMSUNG_K4F6E304HB_MGCH:
                strcpy(dram_man, "Samsung K4F6E304HB-MGCH 4GB");
                break;
            case LPDDR4_ICOSA_4GB_HYNIX_H9HCNNNBPUMLHR_NLE:
                strcpy(dram_man, "Hynix H9HCNNNBPUMLHR-NLE 4GB");
                break;
            case LPDDR4_ICOSA_4GB_MICRON_MT53B512M32D2NP_062_WTC:
                strcpy(dram_man, "Micron MT53B512M32D2NP-062 WT:C");
                break;
            case LPDDR4_ICOSA_6GB_SAMSUNG_K4FHE3D4HM_MGCH:
                strcpy(dram_man, "Samsung K4FHE3D4HM-MGCH 6GB");
                break;
            case LPDDR4_ICOSA_8GB_SAMSUNG_K4FBE3D4HM_MGXX:
                strcpy(dram_man, "Samsung K4FBE3D4HM-MGXX 8GB");
                break;
            default:
                strcpy(dram_man, "#FF8000 Unknown#");
                break;
        }
    } else {
        switch (dram_id) {
            // LPDDR4X 3733Mbps.
            case LPDDR4X_IOWA_4GB_SAMSUNG_K4U6E3S4AM_MGCJ:
            case LPDDR4X_HOAG_4GB_SAMSUNG_K4U6E3S4AM_MGCJ:
                strcpy(dram_man, "Samsung K4U6E3S4AM-MGCJ 4GB");
                break;
            case LPDDR4X_IOWA_8GB_SAMSUNG_K4UBE3D4AM_MGCJ:
            case LPDDR4X_HOAG_8GB_SAMSUNG_K4UBE3D4AM_MGCJ:
                strcpy(dram_man, "Samsung K4UBE3D4AM-MGCJ 8GB");
                break;
            case LPDDR4X_IOWA_4GB_HYNIX_H9HCNNNBKMMLHR_NME:
            case LPDDR4X_HOAG_4GB_HYNIX_H9HCNNNBKMMLHR_NME:
                strcpy(dram_man, "Hynix H9HCNNNBKMMLHR-NME 4GB");
                break;
            case LPDDR4X_IOWA_4GB_MICRON_MT53E512M32D2NP_046_WTE:  // 4266Mbps.
            case LPDDR4X_HOAG_4GB_MICRON_MT53E512M32D2NP_046_WTE:  // 4266Mbps.
                strcpy(dram_man, "Micron MT53E512M32D2NP-046 WT:E");
                break;

            // LPDDR4X 4266Mbps
            case LPDDR4X_IOWA_4GB_SAMSUNG_K4U6E3S4AA_MGCL:
            case LPDDR4X_HOAG_4GB_SAMSUNG_K4U6E3S4AA_MGCL:
            case LPDDR4X_AULA_4GB_SAMSUNG_K4U6E3S4AA_MGCL:
                strcpy(dram_man, "Samsung K4U6E3S4AA-MGCL 4GB");
                break;
            case LPDDR4X_IOWA_8GB_SAMSUNG_K4UBE3D4AA_MGCL:
            case LPDDR4X_HOAG_8GB_SAMSUNG_K4UBE3D4AA_MGCL:
            case LPDDR4X_AULA_8GB_SAMSUNG_K4UBE3D4AA_MGCL:
                strcpy(dram_man, "Samsung K4UBE3D4AA-MGCL 8GB");
                break;
            case LPDDR4X_IOWA_4GB_SAMSUNG_K4U6E3S4AB_MGCL:
            case LPDDR4X_HOAG_4GB_SAMSUNG_K4U6E3S4AB_MGCL:
            case LPDDR4X_AULA_4GB_SAMSUNG_K4U6E3S4AB_MGCL:
                strcpy(dram_man, "Samsung K4U6E3S4AB-MGCL 4GB");
                break;
            case LPDDR4X_IOWA_4GB_MICRON_MT53E512M32D2NP_046_WTF:
            case LPDDR4X_HOAG_4GB_MICRON_MT53E512M32D2NP_046_WTF:
            case LPDDR4X_AULA_4GB_MICRON_MT53E512M32D2NP_046_WTF:
                strcpy(dram_man, "Micron MT53E512M32D2NP-046 WT:F");
                break;
            case LPDDR4X_HOAG_4GB_HYNIX_H9HCNNNBKMMLXR_NEE:  // Replaced from Copper.
            case LPDDR4X_AULA_4GB_HYNIX_H9HCNNNBKMMLXR_NEE:  // Replaced from Copper.
            case LPDDR4X_IOWA_4GB_HYNIX_H9HCNNNBKMMLXR_NEE:  // Replaced from Copper.
                strcpy(dram_man, "Hynix H9HCNNNBKMMLXR-NEE 4GB");
                break;
            case LPDDR4X_IOWA_4GB_HYNIX_H54G46CYRBX267:
            case LPDDR4X_HOAG_4GB_HYNIX_H54G46CYRBX267:
            case LPDDR4X_AULA_4GB_HYNIX_H54G46CYRBX267:
                strcpy(dram_man, "Hynix H54G46CYRBX267 4GB");
                break;
            case LPDDR4X_IOWA_4GB_MICRON_MT53E512M32D1NP_046_WTB:
            case LPDDR4X_HOAG_4GB_MICRON_MT53E512M32D1NP_046_WTB:
            case LPDDR4X_AULA_4GB_MICRON_MT53E512M32D1NP_046_WTB:
                strcpy(dram_man, "Micron MT53E512M32D1NP-046 WT:B");
                break;

            default:
                strcpy(dram_man, "#FF8000 Contact me!#");
                break;
        }
    }
    gfx_printf("%kSKU:%k %d - %s - %s %kDRAM:%k %s", COLORTORGB(COLOR_GREEN), COLORTORGB(COLOR_ORANGE), FUSE(FUSE_SKU_INFO), sku,
               fuse_read_hw_state() ? "Dev" : "Retail", COLORTORGB(COLOR_BLUE), COLORTORGB(COLOR_ORANGE), dram_man);
}

ShowResult showParams(const CustomizeTable* cust, int paramsCount, const Param* params[], int maxLengthInit, int x, int y) {
    int tmpY = y;
    int maxLength = maxLengthInit;
    int fontSize = gfx_con.fntsz;
    char* displayBuff = malloc(1024);
    for (int j = 0; j < paramsCount; ++j) {
        const Param* param = params[j];
        const u32 value = getParamValueFromBuffer((const u8*)cust, param);
        int color = value == param->defaultValue ? COLORTORGB(COLOR_DEFAULT_PARAM) : COLORTORGB(COLOR_CHANGED_PARAM);
        getDisplayValue(param, displayBuff, value);
        addPostfix(param, displayBuff, value, 0, 0);
        gfx_con_setpos(x, tmpY);
        gfx_printf("%k%s ", color, param->name);
        gfx_con_setpos(x + fontSize * (maxLength + 1), tmpY);
        gfx_printf("%s", displayBuff);
        tmpY += fontSize;
    }
    free(displayBuff);
    ShowResult result;
    gfx_con_getpos(&result.lastX, &result.lastY);
    result.lastY += fontSize;
    return result;
}

ShowResult showTables(const CustomizeTable* cust, const Tables* tables[], int color, int count, int maxLengthInit, int x, int y) {
    ShowResult result = {0, 0};
    int tmpX = x;
    int tmpY = y;
    int lineLength = 20;
    int fontSize = gfx_con.fntsz;
    gfx_con_setpos(tmpX, tmpY);
    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < tables[i]->count; ++j) {
            const Table* table = tables[i]->tables[j];
            gfx_printf("%k%s", color, table->name);
            tmpY += fontSize;
            gfx_con_setpos(tmpX, tmpY);
            for (int k = 0; k < lineLength; ++k) gfx_printf("=");
            tmpY += fontSize;
            gfx_con_setpos(tmpX, tmpY);
            ShowResult newResult = showParams(cust, table->paramsCount, table->params, maxLengthInit, tmpX, tmpY);
            tmpX = x;
            tmpY = newResult.lastY;
            gfx_con_setpos(tmpX, tmpY);
            gfx_printf("%k", color);
            for (int i = 0; i < lineLength; ++i) gfx_printf("=");
        }
    }
    gfx_con_getpos(&result.lastX, &result.lastY);
    return result;
}

ShowResult showTablesH(const CustomizeTable* cust, const Tables* tables[], int count, int x, int y, int maxLength) {
    ShowResult result = {0, 0};
    int tmpX = x;
    int tmpY = y;
    int fontSize = gfx_con.fntsz;
    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < tables[i]->count; ++j) {
            const Table* table = tables[i]->tables[j];
            gfx_con_setpos(tmpX, tmpY);

            int isRamTimings = !strcmp(table->name, RAM_TIMINGS_TABLE_NAME);
            gfx_printf("%k%s", COLORTORGB(COLOR_YELLOW), table->name);
            if (isRamTimings) {
                const char* stageTitle = getCurrentStageTitle();
                int color = COLORTORGB(COLOR_ORANGE);
                if (stageTitle == stagesTitles[0])
                    color = COLORTORGB(COLOR_VIOLET);
                else if (!strcmp(stageTitle, CHEKATE_UNKNOWN_STAGE))
                    color = COLORTORGB(COLOR_GREY);
                gfx_con_setpos(tmpX + fontSize * (maxLength + 1), tmpY);
                gfx_printf("%k%s", color, stageTitle);
            }
            tmpY += fontSize;
            gfx_con_setpos(tmpX, tmpY);
            gfx_printf("%k", COLORTORGB(COLOR_BLUE));
            for (int p = 0; p < table->paramsCount; ++p) {
                const Param* param = table->params[p];
                const u32 value = getParamValueFromBuffer((const u8*)cust, param);
                const int startIndex = p + (isRamTimings ? 1 : 0);
                gfx_printf("%d", startIndex);
                if (startIndex > 9)
                    tmpX += fontSize * 3;
                else if (value > 9)
                    tmpX += fontSize * 3;
                else
                    tmpX += fontSize * 2;
                gfx_con_setpos(tmpX, tmpY);
            }
            tmpY += fontSize;
            tmpX = x;
            gfx_con_setpos(tmpX, tmpY);
            for (int p = 0; p < table->paramsCount; ++p) {
                const Param* param = table->params[p];
                const u32 value = getParamValueFromBuffer((const u8*)cust, param);
                int color = value == param->defaultValue ? COLORTORGB(COLOR_DEFAULT_PARAM) : COLORTORGB(COLOR_CHANGED_PARAM);
                gfx_printf("%k%d", color, value);
                const int startIndex = p + (isRamTimings ? 1 : 0);
                if (startIndex > 9)
                    tmpX += fontSize * 3;
                else if (value > 9)
                    tmpX += fontSize * 3;
                else
                    tmpX += fontSize * 2;
                gfx_con_setpos(tmpX, tmpY);
            }
            tmpX = x;
            tmpY += fontSize * 2;
        }
    }
    gfx_con_getpos(&result.lastX, &result.lastY);
    return result;
}

void showDashboard(const CustomizeTable* cust, int count, const Params* cpuParams[], const Tables* cpuTables[], const Params* gpuParams[],
                   const Tables* gpuTables[], const Params* ramParams[], const Tables* ramTables[]) {
    if (getHWType() == COMMON) return;
    const int maxLengthInit = 27;
    int fontSize = gfx_con.fntsz;
    const int initY = 24;
    const int initX = 16;
    int y = initY;
    int x = initX;
    const int lineLenth = 51;
    ShowResult result;
    gfx_con_setpos(x, y);
    gfx_printf("%kCPU", COLORTORGB(COLOR_GREEN));
    y += fontSize;
    gfx_con_setpos(x, y);
    for (int i = 0; i < lineLenth; ++i) gfx_printf("=");
    y += fontSize;
    gfx_con_setpos(x, y);
    for (int i = 0; i < count; ++i) {
        result = showParams(cust, cpuParams[i]->count, cpuParams[i]->params, maxLengthInit, x, y);
        y = result.lastY;
    }
    gfx_con_setpos(x, y);
    gfx_printf("%k", COLORTORGB(COLOR_GREEN));
    for (int i = 0; i < lineLenth; ++i) gfx_printf("=");
    y += fontSize * 2;
    gfx_con_setpos(x, y);
    gfx_printf("%kGPU", COLORTORGB(COLOR_ORANGE));
    y += fontSize;
    gfx_con_setpos(x, y);
    for (int i = 0; i < lineLenth; ++i) gfx_printf("=");
    y += fontSize;
    gfx_con_setpos(x, y);
    for (int i = 0; i < count; ++i) {
        result = showParams(cust, gpuParams[i]->count, gpuParams[i]->params, maxLengthInit, x, y);
        y = result.lastY;
    }
    gfx_con_setpos(x, y);
    gfx_printf("%k", COLORTORGB(COLOR_ORANGE));
    for (int i = 0; i < lineLenth; ++i) gfx_printf("=");
    y += fontSize * 2;
    gfx_con_setpos(x, y);
    gfx_printf("%kRAM", COLORTORGB(COLOR_BLUE));
    y += fontSize;
    gfx_con_setpos(x, y);
    for (int i = 0; i < lineLenth; ++i) gfx_printf("=");
    y += fontSize;
    gfx_con_setpos(x, y);
    for (int i = 0; i < count; ++i) {
        result = showParams(cust, ramParams[i]->count, ramParams[i]->params, maxLengthInit, x, y);
        y = result.lastY;
    }
    gfx_con_setpos(x, y);
    gfx_printf("%k", COLORTORGB(COLOR_BLUE));
    for (int i = 0; i < lineLenth; ++i) gfx_printf("=");
    gfx_con_getpos(&result.lastX, &result.lastY);

    y = initY;
    x = (maxLengthInit + 26 + (getHWType() == ERISTA ? 6 : 0)) * fontSize;
    showTables(cust, gpuTables, COLORTORGB(COLOR_ORANGE), count, 10, x, y);

    showTablesH(cust, ramTables, count, initX, result.lastY + 2 * fontSize, maxLengthInit);
    gfx_con_getpos(&result.lastX, &result.lastY);

    x = initX;
    y = result.lastY + fontSize * 2;
    gfx_con_setpos(x, y);
    printHWInfo();
    while (!hidRead()->b);
}
