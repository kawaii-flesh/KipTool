#pragma once
#include <utils/types.h>

#define CURRENT_VERSION 19
#define CUST \
    { 'C', 'U', 'S', 'T' }

#define DvfsTableEntryCount 32
#define DvfsTableEntryLimit DvfsTableEntryCount - 1
#define getOffset(param) (int)((const void*)&param - (const void*)custTable.cust)

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

typedef struct {
    u8 cust[4];                                                // 0        CUST
    u32 custRev;                                               // 4        KIP version
    u32 mtcConf;                                               // 8        MTC_MAGIC
    u32 commonCpuBoostClock;                                   // 12       MARIKO - CPU
    u32 commonEmcMemVolt;                                      // 16       COMMON - RAM
    u32 eristaCpuMaxVolt;                                      // 20       ERISTA - CPU
    u32 eristaEmcMaxClock;                                     // 24       ERISTA - RAM
    u32 marikoCpuMaxVolt;                                      // 28       MARIKO - CPU
    u32 marikoEmcMaxClock;                                     // 32       MARIKO - RAM
    u32 marikoEmcVddqVolt;                                     // 36       ARIKO - RAM
    u32 marikoCpuUV;                                           // 40       MARIKO - CPU
    u32 marikoGpuUV;                                           // 44       MARIKO - GPU
    u32 CPUv;                                                  // 48       MARIKO - CPU
    u32 GPUv;                                                  // 52       COMMON - GPU
    u32 marikoEmcDvbShift;                                     // 56       MARIKO - RAM
    u32 ramTimingPresetOne;                                    // 60       COMMON - RAM
    u32 ramTimingPresetTwo;                                    // 64       COMMON - RAM
    u32 ramTimingPresetThree;                                  // 68       COMMON - RAM
    u32 ramTimingPresetFour;                                   // 72       COMMON - RAM
    u32 ramTimingPresetFive;                                   // 76       COMMON - RAM
    u32 ramTimingPresetSix;                                    // 80       COMMON - RAM
    u32 ramTimingPresetSeven;                                  // 84       COMMON - RAM
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
    u32 hGPUv;                                                 // 12344    MARIKO - GPU
    u32 dCPUv;                                                 // 12348    MARIKO - CPU
    u32 eBAL;                                                  // 12352    COMMON - RAM
    u32 ramTimingPresetEight;                                  // 12356    COMMON - RAM
    u32 eBAS;                                                  // 12360    COMMON - RAM
    u32 pMEH[24];                                              // 12364    COMMON - RAM
    u32 sMEH[24];                                              // 12460    COMMON - RAM
    u32 SHAITAN[14];                                           // 12556    SOON
} CustomizeTable;

const CustomizeTable custTable = {
    .cust = CUST,
    .custRev = CURRENT_VERSION,

    .mtcConf = 0,  // eBAMATIC; CUSTOM_ADJ_ALL; NO_ADJ_ALL; CUSTOMIZED_ALL

    // CPU LAUNCH CONTROL TARGET // 1428000 CPU-HI uV DEBUG // 1785000 CPU-LOW uV DEBUG // 2000000 E // 2500000 D // 3000000 S
    // // 1400000-3000000 MANUAL 100000 STEP
    .commonCpuBoostClock = 3000000,

    // RAM VDD MODE // 1175'000 ECO // 1275'000 DEFAULT // 1375'000 SRT // 950'000-1400'000 MANUAL 12'500uV STEP
    .commonEmcMemVolt = 1350000,

    // ERISTA CPU VMAX MODE // 1200 ECO // 1250-1350 STAGE 1-3 // 1180-1350 MANUAL 5mV STEP
    .eristaCpuMaxVolt = 1235,

    // 4IFIR MODE / RAM VDD MODE
    // E 1866 1868800 / 1150'000
    // D 2000 1996800 / 1250'000
    // S 2133 2131200 / 1350'000
    // S 2266 2265600 / 1350'000
    .eristaEmcMaxClock = 2265600,
    // 1600000-2366000 MANUAL 38400 KHz STEP

    // MARIKO CPU VMAX MODE // 1150 ECO // 1180-1250 STAGE 1-3 // 1130-1280 MANUAL 5mV STEP
    .marikoCpuMaxVolt = 1150,

    // 4IFIR MODE / eBAMATIC STAGE: 1-2-3
    // S-LOH 1600 / 1600000 / eBAL: 1 1 2
    // E ST3 1733 / 1734400 / eBAL: 1 2 2
    // E ST2 1866 / 1862400 / eBAL: 2 2 2
    // E ST1 2000 / 1996800 / eBAL: 2 2 3
    // D ST1 2133 / 2131200 / eBAL: 2 3 3
    // D ST2 2266 / 2265600 / eBAL: 3 3 3
    // D ST3 2400 / 2400000 / eBAL: 3 3 4
    // S ST1 2533 / 2534400 / eBAL: 3 4 4
    // S ST2 2666 / 2665600 / eBAL: 4 4 4
    // S ST3 2800 / 2800000 / eBAL: 4 4 5
    // L-C4C 2933 / 2934400 / eBAL: 4 5 5
    .marikoEmcMaxClock = 2265600,
    // 1333000-2733000 MANUAL 38400 KHz STEP

    // RAM VDDQ MODE // 550'000 ECO // 650'000 DEFAULT // 750'000 SRT // 300'000-800'000 MANUAL
    .marikoEmcVddqVolt = 650000,

    // CPU-LOW ECO LOGIC // 0 DEFAULT // 1 ECO ST1 // 3 ECO ST2 // 5 ECO ST3 // 1-6 MANUAL
    .marikoCpuUV = 0,

    // GPU ECO LOGIC // 0 ECO ST1 // 1 ECO ST2 // 2 ECO ST3 // 3 MANUAL ( -75mV << marikoGpuVoltArray ECO ST2 >> +75mV ) 5mV
    // STEP
    .marikoGpuUV = 0,

    // CPU UNDER MODE // 620 DEFAULT // 590 ECO ST1 // 560 ECO ST2 (4IFIR E or D only) // 530 ECO ST3 (4IFIR E only) // 430-670
    // MANUAL 5-10mV STEP
    .CPUv = 620,

    // GPU UNDER LOGIC // 3 AUTO ECO ST1 // 2 AUTO ECO ST2 // 1 AUTO ECO ST3 // 430-770 MANUAL mV 5-10mV STEP
    .GPUv = 3,

    // EMB ECO LOGIC // 3 AUTO // 2 AUTO ECO ST1 // 1 AUTO ECO ST2 // 0 AUTO ECO ST3 // 300-1150 MANUAL mV
    .marikoEmcDvbShift = 3,

    .ramTimingPresetOne = 1,

    .ramTimingPresetTwo = 1,

    .ramTimingPresetThree = 1,

    .ramTimingPresetFour = 1,

    .ramTimingPresetFive = 1,

    .ramTimingPresetSix = 1,

    .ramTimingPresetSeven = 1,

    .marikoGpuVoltArray = {395, 420, 445, 470, 495, 520, 545, 570, 595, 620, 645, 670,
                           695, 720, 750, 780, 810, 840, 870, 900, 930, 960, 990, 1020},

    .eristaCpuDvfsTable =
        {
            {612000, {852878}, {}},
            {714000, {885824}, {}},
            {816000, {918770}, {}},
            {918000, {951716}, {}},
            {1020000, {984662}, {-2875621, 358099, -8585}},
            {1122000, {1017608}, {-52225, 104159, -2816}},
            {1224000, {1050554}, {1076868, 8356, -727}},
            {1326000, {1083500}, {2208191, -84659, 1240}},
            {1428000, {1116446}, {2519460, -105063, 1611}},
            {1581000, {1130000}, {2889664, -122173, 1834}},
            {1683000, {1168000}, {5100873, -279186, 4747}},
            {1785000, {1227500}, {5100873, -279186, 4747}},
            {1887000, {1235000}, {5100873, -279186, 4747}},
            {1963500, {1235000}, {5100873, -279186, 4747}},
            {2091000, {1235000}, {5100873, -279186, 4747}},
            {2193000, {1235000}, {5100873, -279186, 4747}},
            {2296000, {1240000}, {5100873, -279186, 4747}},
            {2397000, {1262000}, {5100873, -279186, 4747}},
            {2499000, {1298000}, {5100873, -279186, 4747}},
            {2602000, {1358000}, {5100873, -279186, 4747}},
            //{ 2703000, { 1358000 }, {  5100873, -279186,  4747 } },
        },

    .marikoCpuDvfsTable =
        {
            //{  204000, {  732856,   -17335,      113 }, {} },
            //{  306000, {  760024,   -18195,      113 }, {} },
            //{  408000, {  760024,   -18195,      113 }, {} },
            //{  510000, {  789258,   -19055,      113 }, {} },
            {612000, {853926, -20775, 113}, {}},          {714000, {889361, -21625, 113}, {}},
            {816000, {926862, -22485, 113}, {}},          {918000, {966431, -23345, 113}, {}},
            {1020000, {1008066, -24205, 113}, {1120000}}, {1122000, {1051768, -25065, 113}, {1120000}},
            {1224000, {1097537, -25925, 113}, {1120000}}, {1326000, {1145373, -26785, 113}, {1120000}},
            {1428000, {1195276, -27645, 113}, {1120000}}, {1581000, {1274006, -28935, 113}, {1120000}},
            {1683000, {1329076, -29795, 113}, {1120000}}, {1785000, {1386213, -30655, 113}, {1120000}},
            {1887000, {1445416, -31515, 113}, {1120000}}, {1963500, {1490873, -32155, 113}, {1120000}},
            {2091000, {1580725, -33235, 113}, {1120000}}, {2193000, {1580725, -33235, 113}, {1235000}},
            {2295000, {1635431, -34095, 113}, {1235000}}, {2397000, {1702903, -34955, 113}, {1235000}},
            {2499000, {1754400, -35643, 113}, {1235000}}, {2602000, {1805897, -36331, 113}, {1235000}},
            //{ 2703000, { 1857394,   -37019,      113 }, { 1235000 } },
            //{ 2805000, { 1908891,   -37707,      113 }, { 1235000 } },
            //{ 2907000, { 1960388,   -38395,      113 }, { 1235000 } },
            //{ 3009000, { 2011885,   -39083,      113 }, { 1235000 } },
        },

    .marikoCpuDvfsTableSLT =
        {
            //{  204000, {  732856,   -17335,      113 }, {} },
            //{  306000, {  760024,   -18195,      113 }, {} },
            //{  408000, {  760024,   -18195,      113 }, {} },
            //{  510000, {  789258,   -19055,      113 }, {} },
            {612000, {853926, -20775, 113}, {}},          {714000, {889361, -21625, 113}, {}},
            {816000, {926862, -22485, 113}, {}},          {918000, {966431, -23345, 113}, {}},
            {1020000, {1008066, -24205, 113}, {1120000}}, {1122000, {1051768, -25065, 113}, {1120000}},
            {1224000, {1097537, -25925, 113}, {1120000}}, {1326000, {1145373, -26785, 113}, {1120000}},
            {1428000, {1195276, -27645, 113}, {1120000}}, {1581000, {1274006, -28935, 113}, {1120000}},
            {1683000, {1329076, -29795, 113}, {1120000}}, {1785000, {1386213, -30655, 113}, {1120000}},
            {1887000, {1445416, -31515, 113}, {1120000}}, {1963500, {1490873, -32155, 113}, {1120000}},
            {2091000, {1580725, -33235, 113}, {1120000}}, {2193000, {1580725, -33235, 113}, {1235000}},
            {2295000, {1635431, -34095, 113}, {1235000}}, {2397000, {1702903, -34955, 113}, {1235000}},
            {2499000, {1754400, -35643, 113}, {1235000}}, {2601000, {1805897, -36331, 113}, {1235000}},
            {2703000, {1857394, -37019, 113}, {1235000}}, {2805000, {1908891, -37707, 113}, {1235000}},
            {2907000, {1960388, -38395, 113}, {1235000}}, {3009000, {2011885, -39083, 113}, {1235000}},
            //{ 3111000, { 2063382,   -39771,      113 }, { 1235000 } },
        },

    // ERISTA GPU ECO LOGIC // ECO ST1 = -12500uV // ECO ST2 = -25000uV // ECO ST3 = -37500uV // MANUAL = -75000uV << Default >>
    // +75000uV
    .eristaGpuDvfsTable =
        {
            // Freq KHz  	// Volt uV
            {192000,
             {},
             {
                 687500,
             }},
            {230400,
             {},
             {
                 700000,
             }},
            {268800,
             {},
             {
                 712500,
             }},
            {307200,
             {},
             {
                 725000,
             }},
            {345600,
             {},
             {
                 737500,
             }},
            {384000,
             {},
             {
                 750000,
             }},
            {422400,
             {},
             {
                 762500,
             }},
            {460800,
             {},
             {
                 775000,
             }},
            {499200,
             {},
             {
                 787500,
             }},
            {537600,
             {},
             {
                 800000,
             }},
            {576000,
             {},
             {
                 812500,
             }},
            {614400,
             {},
             {
                 825000,
             }},
            {652800,
             {},
             {
                 837500,
             }},
            {691200,
             {},
             {
                 850000,
             }},
            {729600,
             {},
             {
                 862500,
             }},
            {768000,
             {},
             {
                 875000,
             }},
            {806400,
             {},
             {
                 887500,
             }},
            {844800,
             {},
             {
                 900000,
             }},
            {883200,
             {},
             {
                 912500,
             }},
            {921600,
             {},
             {
                 925000,
             }},
            {960000,
             {},
             {
                 937500,
             }},
            {998400,
             {},
             {
                 950000,
             }},
            {1036800,
             {},
             {
                 975000,
             }},
            {1075200,
             {},
             {
                 1012500,
             }},
            {1113600,
             {},
             {
                 1050000,
             }},
            {1152000,
             {},
             {
                 1100000,
             }},
            {1190400,
             {},
             {
                 1150000,
             }},
            {1228800,
             {},
             {
                 1175000,
             }},
        },

    .marikoGpuDvfsTable =
        {
            {192000,
             {},
             {
                 415000,
             }},
            {230400,
             {},
             {
                 430000,
             }},
            {307200,
             {},
             {
                 455000,
             }},
            {384000,
             {},
             {
                 480000,
             }},
            {460800,
             {},
             {
                 505000,
             }},
            {537600,
             {},
             {
                 530000,
             }},
            {614400,
             {},
             {
                 555000,
             }},
            {691200,
             {},
             {
                 580000,
             }},
            {768000,
             {},
             {
                 605000,
             }},
            {844800,
             {},
             {
                 630000,
             }},
            {921600,
             {},
             {
                 655000,
             }},
            {998400,
             {},
             {
                 680000,
             }},
            {1075200,
             {},
             {
                 710000,
             }},
            {1152000,
             {},
             {
                 745000,
             }},
            {1228800,
             {},
             {
                 780000,
             }},
            {1305600,
             {},
             {
                 840000,
             }},
            {1344000,
             {},
             {
                 870000,
             }},
            {1382400,
             {},
             {
                 900000,
             }},
            {1420800,
             {},
             {
                 930000,
             }},
            {1459200,
             {},
             {
                 960000,
             }},
            //{ 1497600, {}, { 1000000, } },
            //{ 1536000, {}, { 1050000, } },
            //{ 1574400, {}, { 1100000, } },
            //{ 1612800, {}, { 1150000, } },
        },

    .marikoGpuDvfsTableSLT =
        {
            {192000,
             {},
             {
                 395000,
             }},
            {230400,
             {},
             {
                 420000,
             }},
            {307200,
             {},
             {
                 435000,
             }},
            {384000,
             {},
             {
                 460000,
             }},
            {460800,
             {},
             {
                 485000,
             }},
            {537600,
             {},
             {
                 515000,
             }},
            {614400,
             {},
             {
                 540000,
             }},
            {691200,
             {},
             {
                 560000,
             }},
            {768000,
             {},
             {
                 585000,
             }},
            {844800,
             {},
             {
                 610000,
             }},
            {921600,
             {},
             {
                 635000,
             }},
            {998400,
             {},
             {
                 660000,
             }},
            {1075200,
             {},
             {
                 690000,
             }},
            {1152000,
             {},
             {
                 730000,
             }},
            {1228800,
             {},
             {
                 770000,
             }},
            {1305600,
             {},
             {
                 800000,
             }},
            {1344000,
             {},
             {
                 835000,
             }},
            {1382400,
             {},
             {
                 860000,
             }},
            {1420800,
             {},
             {
                 885000,
             }},
            {1458200,
             {},
             {
                 910000,
             }},
            {1497600,
             {},
             {
                 935000,
             }},
            {1536000,
             {},
             {
                 960000,
             }},
            //{ 1574400, {}, {  985000, } },
            //{ 1612800, {}, { 1020000, } },
        },

    .marikoGpuDvfsTableHiOPT =
        {
            {192000,
             {},
             {
                 380000,
             }},
            {230400,
             {},
             {
                 415000,
             }},
            {307200,
             {},
             {
                 430000,
             }},
            {384000,
             {},
             {
                 455000,
             }},
            {460800,
             {},
             {
                 475000,
             }},
            {537600,
             {},
             {
                 500000,
             }},
            {614400,
             {},
             {
                 525000,
             }},
            {691200,
             {},
             {
                 545000,
             }},
            {768000,
             {},
             {
                 570000,
             }},
            {844800,
             {},
             {
                 595000,
             }},
            {921600,
             {},
             {
                 620000,
             }},
            {998400,
             {},
             {
                 645000,
             }},
            {1075200,
             {},
             {
                 670000,
             }},
            {1152000,
             {},
             {
                 695000,
             }},
            {1228800,
             {},
             {
                 720000,
             }},
            {1305600,
             {},
             {
                 755000,
             }},
            {1344000,
             {},
             {
                 780000,
             }},
            {1382400,
             {},
             {
                 805000,
             }},
            {1420800,
             {},
             {
                 830000,
             }},
            {1458200,
             {},
             {
                 855000,
             }},
            {1497600,
             {},
             {
                 880000,
             }},
            {1534000,
             {},
             {
                 905000,
             }},
            {1574400,
             {},
             {
                 930000,
             }},
            {1612800,
             {},
             {
                 960000,
             }},
        },

    // SPEEDSHIFT ECO LOGIC // 0 DEFAULT // 50 AUTO SRT // 100 AUTO ECO ST1 // 125 AUTO ECO ST2 // 150 AUTO ECO ST3 // 1-200
    // MANUAL
    .SpeedShift = 0,

    // MARIKO CPU-HI ECO LOGIC // 0 DEFAULT // 1 AUTO ECO ST1 // 3 AUTO ECO ST2 // 5 AUTO ECO ST3 // 1-7 MANUAL
    .marikoCpuHUV = 0,

    // MARIKO GPU OVER MODE // 1000 4IFIR ECO // 1050 DEFAULT // 1100 4IFIR SRT // 750-1200 MANUAL
    .hGPUv = 1050,

    // MARIKO CPU MIN-HIGH LOGIC // 0 DEFAULT // 1 AUTO ECO ST1 // 2 AUTO ECO ST2 // 3 AUTO ECO ST3 // 750-850 MANUAL
    .dCPUv = 0,

    // EMC BALLANCE ADVANCED LOGIC // 0 RESERVED // 1 SYK-LOH // 2 ECO ST1 // 3 DEFAULT // 4 SRT ST1 // 5 SRT ST2
    .eBAL = 3,  // TRADE MAX FREQ FOR EFFICIENCY // EFFICIENCY << PRIORITY >> FREQUENCY

    .ramTimingPresetEight = 1,  // ХХ MGCJ 2400 >< 2 EBAL // 5 MGCJ 2400 >< 2 EBAL // 15

    // EBA-SHIFT // 0 DEFAULT // 1 ECO ST1 // 2 SYK-LOH // 3 RESERVED // 4 RESERVED // 5 LOH-C4C
    .eBAS = 0,  // TRADE MAX FREQ FOR EFFICIENCY // FREQUENCY << PRIORITY >> EFFICIENCY

    // PRIMARY MICRO-ENHANCE LOGIC			 	         // 0 eBAS Sub-Zero 0-1   // 1 divMB Supressor 0-4  // 2
    // 1333>1065>800
    // 0-2
    // 3 eBAW Shift 0-4		    // 4 eBAR Shift 0-4      // 5 RTW Shift 0-8	      // 6 WTR Shift 0-8 	    // 7 WTP
    // Shift
    // 0-8
    // 8 RCD Reduct 0-4 	    // 9 RP Reduct 0-4       // 10 RAS Shift 0-16	  // 11 SRPD 0-3
    // // 12 E-Enhance P
    // 0-1
    // 13 DR Debug 0-4		    // 14 GameChanger 0-24	 // 15 Eri-Bump 0-1
    .pMEH = {0, 2, 0, 2, 2, 4, 4, 4, 0, 0, 8, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    // DEF = 0  2  0  2  2  4  4  4  0  0  8  0  0  0  0  1 >> RESERVED >>
    // NUM = 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23

    // SECONDARY MICRO-ENHANCE LOGIC (SAFE) 		 // 0 ARB-Boost 1-9  // 1 ARB-BCD 0-4   // 2 ARB-BRP 0-4   // 3 ARB-RTR
    // 0-4  // 4
    // ARB-RTW 0-4
    // 5 ARB-WTR 0-4  		  // 5 ARB-WTR 0-4   // 7 trDVFS 0-1     // 8 E-Boost 0-1   // 9 SSC Logic 0-1 // 10 Latent 0-8
    // //
    // 11 CP-THM 0-4
    .sMEH = {4, 2, 2, 2, 2, 2, 0, 1, 1, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // DEF = 4  2  2  2  2  2  0  1  1  1  0  2 >> RESERVED >>
    // NUM = 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23

    // Secret Hardware Assisted Integration Tool for Advanced Necessities (UNSAFE)
    // SPELL = [ SLOT1 ][ SLOT2 ][ SLOT3 ][ SLOT4 ][S][RP]
    .SHAITAN = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13}
    // Magic numbers, the right combination adds functionality from the future

};