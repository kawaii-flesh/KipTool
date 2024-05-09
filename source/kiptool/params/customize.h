#pragma once
#include <utils/types.h>

#define CUST \
    { 'C', 'U', 'S', 'T' }

#define DvfsTableEntryCount 32
#define DvfsTableEntryLimit DvfsTableEntryCount - 1

typedef struct cvb_coefficients {
    s32 c0;
    s32 c1;
    s32 c2;
    s32 c3;
    s32 c4;
    s32 c5;
} cvb_coefficients;  // 24

typedef struct cvb_entry_t {
    u64 freq;                         // 8
    cvb_coefficients cvb_dfll_param;  // 24
    cvb_coefficients cvb_pll_param;   // 24
} cvb_entry_t;                        // 56

enum MtcConfig : u32 {
    eBAMATIC = 0,
    CUSTOM_ADJ_ALL = 1,
    NO_ADJ_ALL = 2,
    CUSTOMIZED_ALL = 4,
};

typedef struct {
    u8 cust[4];                                                // 0        CUST
    u32 custRev;                                               // 4        KIP version
    u32 mtcConf;                                               // 8        MtcConfig
    u32 commonCpuBoostClock;                                   // 12       MARIKO - CPU
    u32 commonEmcMemVolt;                                      // 16       COMMON - RAM
    u32 eristaCpuMaxVolt;                                      // 20       ERISTA - CPU
    u32 eristaEmcMaxClock;                                     // 24       ERISTA - RAM
    u32 marikoCpuMaxVolt;                                      // 28       MARIKO - CPU
    u32 marikoEmcMaxClock;                                     // 32       MARIKO - RAM
    u32 marikoEmcVddqVolt;                                     // 36       MARIKO - RAM
    u32 marikoCpuUV;                                           // 40       MARIKO - CPU
    u32 marikoGpuUV;                                           // 44       COMMON - GPU
    u32 CPUv;                                                  // 48       COMMON - CPU
    u32 GPUv;                                                  // 52       COMMON - GPU
    u32 marikoEmcDvbShift;                                     // 56       MARIKO - RAM
    u32 drochr01;                                              // 60       COMMON - RAM
    u32 drochr02;                                              // 64       COMMON - RAM
    u32 drochr03;                                              // 68       COMMON - RAM
    u32 drochr04;                                              // 72       COMMON - RAM
    u32 drochr05;                                              // 76       COMMON - RAM
    u32 drochr06;                                              // 80       COMMON - RAM
    u32 drochr07;                                              // 84       COMMON - RAM
    u32 marikoGpuVoltArray[24];                                // 88       MARIKO - GPU
    cvb_entry_t eristaCpuDvfsTable[DvfsTableEntryLimit];       // 184      ERISTA - CPU
    cvb_entry_t marikoCpuDvfsTable[DvfsTableEntryLimit];       // 1920     MARIKO - CPU
    cvb_entry_t marikoCpuDvfsTableSLT[DvfsTableEntryLimit];    // 3656     MARIKO - CPU
    cvb_entry_t eristaGpuDvfsTable[DvfsTableEntryLimit];       // 5392     ERISTA - GPU
    cvb_entry_t marikoGpuDvfsTable[DvfsTableEntryLimit];       // 7128     MARIKO - GPU
    cvb_entry_t marikoGpuDvfsTableSLT[DvfsTableEntryLimit];    // 8864     MARIKO - GPU
    cvb_entry_t marikoGpuDvfsTableHiOPT[DvfsTableEntryLimit];  // 10600    MARIKO - GPU
    u32 SpeedShift;                                            // 12336    MARIKO - CPU
    u32 marikoCpuHUV;                                          // 12340    MARIKO - CPU
    u32 hGPUv;                                                 // 12344    COMMON - GPU
    u32 dCPUv;                                                 // 12348    MARIKO - CPU
    u32 eBAL;                                                  // 12352    COMMON - RAM
    u32 drochr08;                                              // 12356    COMMON - RAM
    u32 eBAS;                                                  // 12360    COMMON - RAM
    u32 pMEH[24];                                              // 12364    COMMON - RAM
    u32 sMEH[24];                                              // 12460    COMMON - RAM
    u32 SHAITAN[14];                                           // 12556    SOON
    // EristaMtcTable* eristaMtcTable;
    // MarikoMtcTable* marikoMtcTable;
} CustomizeTable;
