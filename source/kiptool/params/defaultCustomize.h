#pragma once

#include "customize.h"

#define getOffset(param) (int)((const void *)&param - (const void *)defaultCustTable.cust)
#define D_ST3 2400000

const CustomizeTable defaultCustTable = {
    .cust = CUST,
    .custRev = KT_CUST_VER,

    // eBAMATIC; LEGACY; DEBUG; ALTMODE
    .mtcConf = eBAMATIC,
    // eBAMATIC	MHz
    // MARIKO eBAL
    // ERISTA eBAL
    //  120 133 146 160 173 186 200 213 226 240 253 266 280 293 306 320 333 346 360 373
    //  1,	1, 	1,	1, 	2, 	2, 	2, 	2, 	3, 	3, 	3, 	4, 	4, 	5, 	5, 	5, 	5, 	5,  5,  5
    //  1,	1, 	1,	1, 	1, 	2, 	3, 	4, 	5, 	5, 	5, 	5, 	5, 	5

    // CPU LAUNCH CONTROL TARGET
    // 1428000 CPU-HI uV DEBUG
    // 1785000 CPU-LOW uV DEBUG
    // 2000000 E
    // 2500000 D
    // 3000000 S
    // 1400000-3000000 MANUAL 100000 STEP
    // eBAMATIC
    .commonCpuBoostClock = eBAMATIC,

    // RAM VDD MODE
    // 1175'000 ECO
    // 1275'000 DEFAULT
    // 1375'000 SRT
    // 950'000-1400'000 MANUAL 12'500uV STEP
    .commonEmcMemVolt = 1350000,

    // ERISTA CPU VMAX MODE
    // 1200 ECO
    // 1250-1350 STAGE 1-3
    // 1180-1375 MANUAL 5mV STEP
    .eristaCpuMaxVolt = 1235,

    // 4IFIR MODE ON ERISTA
    // S-LOH 1600 / 1600000
    // E ST2 1733 / 1734400
    // E ST1 1866 / 1868800
    // D ST1 2000 / 1996800
    // D ST2 2133 / 2131200
    // S ST1 2266 / 2265600
    // L-C4C 2366 / 2361600
    .eristaEmcMaxClock = 2124800,  // 2278400 2240000 2201600 2163200 2124800
    // 1600000-2366000 MANUAL 38.4MHz STEP

    // MARIKO CPU VMAX MODE
    // 1150 ECO
    // 1180-1250 STAGE 1-3
    // 1130-1375 MANUAL 5mV STEP
    .marikoCpuMaxVolt = eBAMATIC,

    // 4IFIR MODE ON MARIKO / VDQ / eBL1 / eBL2 / eBL3 / eBL4 / eBL5 /
    // S_LOH 1600 / 1600000 / 500 / 1350 / 1200 / 1050	  900		 /
    // E_ST3 1733 / 1734400 / 525 / 1400 / 1250 / 1100	  950	     /
    // E_ST2 1866 / 1868800 / 550 / 	 / 1300 / 1150	 1000	     /
    // E_ST1 2000 / 1996800 / 575 / 	 / 1350 / 1200	 1050	 900 /
    // D_ST1 2133 / 2131200 / 600 / 	 / 1400 / 1250 / 1100    950 /
    // D_ST2 2266 / 2265600 / 625 / 	   	    / 1300 / 1150   1000 /
    // D_ST3 2400 / 2400000 / 650 / 	   		/ 1350 / 1200 / 1050 /
    // S_ST1 2533 / 2534400 / 675 / 	  		/ 1400 / 1250 / 1100 /
    // S_ST2 2666 / 2665600 / 700 / 	  			   / 1300 / 1150 /
    // S_ST3 2800 / 2800000 / 725 / 	   	  		   / 1350 / 1200 /
    // L_C4C 2933 / 2934400 / 750 / 	   	  		   / 1400 / 1250 /
    .marikoEmcMaxClock = D_ST3,
    // MICRON E/H eBAL 4 < 3.8GHz
    // SAMSUNG B eBAL 4 < 3.9GHz
    // HYNIX CJR/DJR eBAL 4 < 3.8GHz
    // 1333000-2733000 MANUAL 38.4MHz STEP

    // RAM VDDQ MODE
    // 500'000 ECO
    // 650'000 DEFAULT
    // 700'000 SRT
    // 300'000-800'000 MANUAL
    .marikoEmcVddqVolt = 650000,

    // CPU-LOW ECO LOGIC
    // 0 ECO ALT-MODE
    // 1 AUTO ECO ST1
    // 3 AUTO ECO ST2
    // 5 AUTO ECO ST3
    // 1-6 MANUAL
    .marikoCpuUV = 0,

    // GPU ECO LOGIC
    // 0 AUTO ECO ST1
    // 1 AUTO ECO ST2
    // 2 AUTO ECO ST3
    .marikoGpuUV = 0,
    // 3 MANUAL ( -75mV << marikoGpuVoltArray ECO ST2 >> +75mV ) 5mV STEP
    // ERISTA = eristaGpuDvfsTable uV - (12500 uV * marikoGpuUV)

    // CPU UNDER LOGIC
    // 3 AUTO ECO ST1
    // 2 AUTO ECO ST2
    // 1 AUTO ECO ST3
    // 430-670 MANUAL 5-10mV STEP
    .CPUv = 3,
    // 620mV DEFAULT
    // MARIKO CPU VOLT MIN = CPUv
    // ERISTA CPU VOLT MIN = CPUv + 205mV

    // GPU UNDER LOGIC
    // 3 AUTO ECO ST1
    // 2 AUTO ECO ST2
    // 1 AUTO ECO ST3
    // 430-970 MANUAL mV 5-10mV STEP
    .GPUv = 3,
    // 610mV DEFAULT
    // MARIKO GPU VOLT MIN = CPUv
    // ERISTA GPU VOLT MIN = CPUv + 100mV

    // EMB ECO LOGIC
    // eBAMATIC
    // 1 AUTO ECO ST3
    // 2 AUTO ECO ST2
    // 3 AUTO ECO ST1
    // 600-1150 MANUAL mV
    .marikoEmcDvbShift = eBAMATIC,

    // DERIVATIVE TIMINGS ORCHESTRATORs // SAMSUNG D/E 2666 eBAL 2 RCD 12
    .drochr01 = 1,         // 0 DEBUG // 1 AUTO SAFE // 2-9 AUTO STAGE
    .drochr02 = 1,         // 0 DEBUG // 1 AUTO SAFE // 2-8 AUTO STAGE // 9 ALT LOGIC
    .drochr03 = eBAMATIC,  // 1 AUTO SAFE // 2-9 AUTO STAGE // 10 ALT LOGIC
    .drochr04 = 1,         // 0 DEBUG // 1 AUTO SAFE // 2-9 AUTO STAGE
    .drochr05 = 1,         // 0 DEBUG // 1 AUTO SAFE // 2-9 AUTO STAGE // ! drochr05 = drochr01 + drochr05
    .drochr06 = 1,         // 0 DEBUG // 1 AUTO SAFE // 2-14 AUTO STAGE
    .drochr07 = 1,         // 0 DEBUG // 1 AUTO SAFE // 2-10 AUTO STAGE

    .marikoGpuVoltArray = {395, 420, 445, 470, 495, 520, 545, 570, 595, 620, 645, 670, 695, 720, 750, 780, 810, 840, 870, 900, 930, 960, 990, 1020},

    .eristaCpuDvfsTable =
        {
            {408000, {786986}, {}},
            {510000, {819932}, {}},
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
            {2295000, {1235000}, {5100873, -279186, 4747}},
            {2397000, {1235000}, {5100873, -279186, 4747}},
            {2499000, {1235000}, {5100873, -279186, 4747}},
            {2602000, {1235000}, {5100873, -279186, 4747}},
            //{ 2703000, { 1350000 }, {  5100873, -279186,  4747 } },
            //{ 2805000, { 1375000 }, {  5100873, -279186,  4747 } },
        },

    .marikoCpuDvfsTable =
        {
            //{  204000, {  732856, -17335, 113 }, {} },
            //{  306000, {  760024, -18195, 113 }, {} },
            {408000, {760024, -18195, 113}, {}},          {510000, {789258, -19055, 113}, {}},          {612000, {853926, -20775, 113}, {}},
            {714000, {889361, -21625, 113}, {}},          {816000, {926862, -22485, 113}, {}},          {918000, {966431, -23345, 113}, {}},
            {1020000, {1008066, -24205, 113}, {1120000}}, {1122000, {1051768, -25065, 113}, {1120000}}, {1224000, {1097537, -25925, 113}, {1120000}},
            {1326000, {1145373, -26785, 113}, {1120000}}, {1428000, {1195276, -27645, 113}, {1120000}}, {1581000, {1274006, -28935, 113}, {1120000}},
            {1683000, {1329076, -29795, 113}, {1120000}}, {1785000, {1386213, -30655, 113}, {1120000}}, {1887000, {1445416, -31515, 113}, {1120000}},
            {1963500, {1490873, -32155, 113}, {1120000}}, {2091000, {1580725, -33235, 113}, {1235000}}, {2193000, {1580725, -33235, 113}, {1235000}},
            {2295000, {1635431, -34095, 113}, {1235000}}, {2397000, {1702903, -34955, 113}, {1235000}}, {2499000, {1754400, -35643, 113}, {1235000}},
            {2601000, {1805897, -36331, 113}, {1235000}}, {2703000, {1857394, -37019, 113}, {1235000}}, {2805000, {1908891, -37707, 113}, {1235000}},
            {2907000, {1960388, -38395, 113}, {1235000}}, {3009000, {2011885, -39083, 113}, {1235000}},
            //{ 3111000, { 2063382, -39771, 113 }, { 1235000 } },
            //{ 3213000, { 2063382, -39771, 113 }, { 1235000 } },
        },

    .marikoCpuDvfsTableSLT =
        {
            //{  204000, {  732856, -17335, 113 }, {} },
            //{  306000, {  760024, -18195, 113 }, {} },
            {408000, {760024, -18195, 113}, {}},          {510000, {789258, -19055, 113}, {}},          {612000, {853926, -20775, 113}, {}},
            {714000, {889361, -21625, 113}, {}},          {816000, {926862, -22485, 113}, {}},          {918000, {966431, -23345, 113}, {}},
            {1020000, {1008066, -24205, 113}, {1120000}}, {1122000, {1051768, -25065, 113}, {1120000}}, {1224000, {1097537, -25925, 113}, {1120000}},
            {1326000, {1145373, -26785, 113}, {1120000}}, {1428000, {1195276, -27645, 113}, {1120000}}, {1581000, {1274006, -28935, 113}, {1120000}},
            {1683000, {1329076, -29795, 113}, {1120000}}, {1785000, {1386213, -30655, 113}, {1120000}}, {1887000, {1445416, -31515, 113}, {1120000}},
            {1963500, {1490873, -32155, 113}, {1120000}}, {2091000, {1580725, -33235, 113}, {1120000}}, {2193000, {1580725, -33235, 113}, {1235000}},
            {2295000, {1635431, -34095, 113}, {1235000}}, {2397000, {1702903, -34955, 113}, {1235000}}, {2499000, {1754400, -35643, 113}, {1235000}},
            {2601000, {1805897, -36331, 113}, {1235000}}, {2703000, {1857394, -37019, 113}, {1235000}}, {2805000, {1908891, -37707, 113}, {1235000}},
            {2907000, {1960388, -38395, 113}, {1235000}}, {3009000, {2011885, -39083, 113}, {1235000}},
            //{ 3111000, { 2063382, -39771, 113 }, { 1235000 } },
            //{ 3213000, { 2063382, -39771, 113 }, { 1235000 } },
        },

    // ERISTA GPU ECO LOGIC
    // ECO ST1 = -12500uV
    // ECO ST2 = -25000uV
    // ECO ST3 = -37500uV
    // MANUAL = -75000uV << Default >> +75000uV
    .eristaGpuDvfsTable =
        {
            // Freq KHz  	// Volt uV
            {192000,
             {},
             {
                 675000,
             }},
            {230400,
             {},
             {
                 687500,
             }},
            {268800,
             {},
             {
                 700000,
             }},
            {307200,
             {},
             {
                 712500,
             }},
            {345600,
             {},
             {
                 725000,
             }},
            {384000,
             {},
             {
                 737500,
             }},
            {422400,
             {},
             {
                 750000,
             }},
            {460800,
             {},
             {
                 762500,
             }},
            {500000,
             {},
             {
                 775000,
             }},
            {537600,
             {},
             {
                 787500,
             }},
            {576000,
             {},
             {
                 800000,
             }},
            {613400,
             {},
             {
                 812500,
             }},
            {653000,
             {},
             {
                 825000,
             }},
            {691200,
             {},
             {
                 837500,
             }},
            {729600,
             {},
             {
                 850000,
             }},
            {768000,
             {},
             {
                 862500,
             }},
            {805400,
             {},
             {
                 875000,
             }},
            {840800,
             {},
             {
                 887500,
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
                 950000,
             }},
            {998400,
             {},
             {
                 962500,
             }},
            {1036800,
             {},
             {
                 975000,
             }},
            {1074200,
             {},
             {
                 1000000,
             }},
            {1113600,
             {},
             {
                 1037500,
             }},
            {1152000,
             {},
             {
                 1062500,
             }},
            {1190400,
             {},
             {
                 1100000,
             }},
            {1228800,
             {},
             {
                 1125000,
             }},
            {1266200,
             {},
             {
                 1150000,
             }},
        },

    // Freq KHz // Volt uV
    .marikoGpuDvfsTable =
        {
            // Freq KHz  	// Volt uV
            {307200,
             {},
             {
                 485000,
             }},
            {345600,
             {},
             {
                 490000,
             }},
            {384000,
             {},
             {
                 500000,
             }},
            {422400,
             {},
             {
                 510000,
             }},
            {460800,
             {},
             {
                 520000,
             }},
            {499200,
             {},
             {
                 530000,
             }},
            {537600,
             {},
             {
                 540000,
             }},
            {576000,
             {},
             {
                 550000,
             }},
            {614400,
             {},
             {
                 560000,
             }},
            {652800,
             {},
             {
                 570000,
             }},
            {691200,
             {},
             {
                 585000,
             }},
            {729600,
             {},
             {
                 595000,
             }},
            {768000,
             {},
             {
                 610000,
             }},
            {806400,
             {},
             {
                 620000,
             }},
            {844800,
             {},
             {
                 635000,
             }},
            {883200,
             {},
             {
                 645000,
             }},
            {921600,
             {},
             {
                 660000,
             }},
            {960000,
             {},
             {
                 670000,
             }},
            {998400,
             {},
             {
                 685000,
             }},
            {1036800,
             {},
             {
                 700000,
             }},
            {1075200,
             {},
             {
                 715000,
             }},
            {1113600,
             {},
             {
                 730000,
             }},
            {1152000,
             {},
             {
                 750000,
             }},
            {1190400,
             {},
             {
                 765000,
             }},
            {1228800,
             {},
             {
                 785000,
             }},
            {1267200,
             {},
             {
                 815000,
             }},
            {1305600,
             {},
             {
                 845000,
             }},
            {1344000,
             {},
             {
                 875000,
             }},
            {1382400,
             {},
             {
                 905000,
             }},
            {1420800,
             {},
             {
                 935000,
             }},
            {1459200,
             {},
             {
                 960000,
             }},
        },

    .marikoGpuDvfsTableSLT =
        {
            // Freq KHz  	// Volt uV
            {307200,
             {},
             {
                 465000,
             }},
            {345600,
             {},
             {
                 470000,
             }},
            {384000,
             {},
             {
                 475000,
             }},
            {422400,
             {},
             {
                 480000,
             }},
            {460800,
             {},
             {
                 495000,
             }},
            {499200,
             {},
             {
                 505000,
             }},
            {537600,
             {},
             {
                 520000,
             }},
            {576000,
             {},
             {
                 530000,
             }},
            {614400,
             {},
             {
                 545000,
             }},
            {652800,
             {},
             {
                 555000,
             }},
            {691200,
             {},
             {
                 565000,
             }},
            {729600,
             {},
             {
                 575000,
             }},
            {768000,
             {},
             {
                 585000,
             }},
            {806400,
             {},
             {
                 595000,
             }},
            {844800,
             {},
             {
                 610000,
             }},
            {883200,
             {},
             {
                 625000,
             }},
            {921600,
             {},
             {
                 635000,
             }},
            {960000,
             {},
             {
                 650000,
             }},
            {998400,
             {},
             {
                 660000,
             }},
            {1036800,
             {},
             {
                 675000,
             }},
            {1075200,
             {},
             {
                 690000,
             }},
            {1113600,
             {},
             {
                 710000,
             }},
            {1152000,
             {},
             {
                 730000,
             }},
            {1190400,
             {},
             {
                 750000,
             }},
            {1228800,
             {},
             {
                 770000,
             }},
            {1267200,
             {},
             {
                 785000,
             }},
            {1305600,
             {},
             {
                 800000,
             }},
            {1344000,
             {},
             {
                 825000,
             }},
            {1382400,
             {},
             {
                 850000,
             }},
            {1420800,
             {},
             {
                 880000,
             }},
            //{ 1459200, {}, { 905000, } },
            //{ 1497600, {}, { 935000, } },
            {1536000,
             {},
             {
                 960000,
             }},
        },

    .marikoGpuDvfsTableHiOPT =
        {
            // Freq KHz  	// Volt uV
            {307200,
             {},
             {
                 445000,
             }},
            {345600,
             {},
             {
                 450000,
             }},
            {384000,
             {},
             {
                 455000,
             }},
            {422400,
             {},
             {
                 460000,
             }},
            {460800,
             {},
             {
                 465000,
             }},
            {499200,
             {},
             {
                 475000,
             }},
            {537600,
             {},
             {
                 485000,
             }},
            {576000,
             {},
             {
                 495000,
             }},
            {614400,
             {},
             {
                 510000,
             }},
            {652800,
             {},
             {
                 525000,
             }},
            {691200,
             {},
             {
                 540000,
             }},
            {729600,
             {},
             {
                 555000,
             }},
            {768000,
             {},
             {
                 570000,
             }},
            {806400,
             {},
             {
                 585000,
             }},
            {844800,
             {},
             {
                 595000,
             }},
            {883200,
             {},
             {
                 605000,
             }},
            {921600,
             {},
             {
                 615000,
             }},
            {960000,
             {},
             {
                 630000,
             }},
            {998400,
             {},
             {
                 640000,
             }},
            {1036800,
             {},
             {
                 655000,
             }},
            {1075200,
             {},
             {
                 670000,
             }},
            {1113600,
             {},
             {
                 690000,
             }},
            {1152000,
             {},
             {
                 700000,
             }},
            {1190400,
             {},
             {
                 720000,
             }},
            {1228800,
             {},
             {
                 745000,
             }},
            {1267200,
             {},
             {
                 760000,
             }},
            {1305600,
             {},
             {
                 775000,
             }},
            {1344000,
             {},
             {
                 800000,
             }},
            {1382400,
             {},
             {
                 825000,
             }},
            {1420800,
             {},
             {
                 850000,
             }},
            //{ 1459200, {}, { 870000, } },
            //{ 1497600, {}, { 890000, } },
            //{ 1536000, {}, { 910000, } },
            //{ 1574400, {}, { 935000, } },
            {1612800,
             {},
             {
                 960000,
             }},
        },

    // SPEEDSHIFT ECO LOGIC
    // eBAMATIC
    // 1 DEFAULT
    // 50 SRT ST1
    // 100 ECO ST1
    // 125 ECO ST2
    // 150 ECO ST3
    // 25-175 MANUAL
    .SpeedShift = eBAMATIC,
    // Ov << 100 >> uV

    // MARIKO CPU-HI ECO LOGIC
    // eBAMATIC
    // 1 AUTO ECO ST1
    // 3 AUTO ECO ST2
    // 5 AUTO ECO ST3
    // 1-8 MANUAL
    .marikoCpuHUV = eBAMATIC,

    // GPU OVER LOGIC
    // eBAMATIC
    // MARIKO: 750-1200 MANUAL
    // ERISTA: 850-1300 MANUAL
    .hGPUv = eBAMATIC,

    // MARIKO CPU MIN-HIGH LOGIC
    // eBAMATIC
    // 1 AUTO ECO ST1
    // 2 AUTO ECO ST2
    // 3 AUTO ECO ST3
    // 750-850 MANUAL
    .dCPUv = eBAMATIC,

    // EMC BALLANCE ADVANCED LOGIC
    // eBAMATIC
    // 1 SYK-LOH
    // 2 ECO ST1
    // 3 DEFAULT
    // 4 SRT ST1
    // 5 SRT ST2
    .eBAL = eBAMATIC,
    // TRADE MAX FREQ FOR EFFICIENCY
    // EFFICIENCY << PRIORITY >> FREQUENCY

    // 0 DEBUG
    // 1 AUTO SAFE
    // 2-12 AUTO STAGE
    .drochr08 = 1,

    // EBA-SHIFT
    // 0 DEFAULT
    // 1 AUTO ST1
    // 2 SYK-LOH
    // 3 AUTO ST3
    // 4 AUTO ST4
    // 5 LOH-C4C
    .eBAS = 1,
    // TRADE MAX FREQ FOR EFFICIENCY
    // FREQUENCY << PRIORITY >> EFFICIENCY

    // PRIMARY MICRO-ENHANCE LOGIC			 		// 0 eBAS Sub-Zero 0-1   // 1 divMB Supressor 0-4  // 2 1333>1065>800 0-3
    // 3 eBAW Shift 0-4		// 4 eBAR Shift 0-4     // 5 eBAW Crement 0-4	 // 6 eBAR Crement 0-4 	   // 7 eBAS Crement 0-4
    // 8 RCD Decret 0-4 	// 9 RP Decret 0-4      // 10 RAS Decret 0-8	 // 11 SRPD 0-15 		   // 12 E-Enhance P 0-1
    // 13 DR Debug 0-8		// 14 GameChanger 0-24	// 15 eFOS MK 0-1		 // 16 lovec 0-1		   // 17 DBI 0-3
    // 18 eBAMATIC ST 0-3	// 19 vMINetune 0-9		// 20 rVDDick 0-6		 // 21 gVMINDick 0-9
    .pMEH = {0, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 4, 2, 0, 0},
    // DEF =  0  2  0  2  2  0  0  0  0  0  0  0  1  0  0  0  0  0  0  1  4  2  >> RESERVED >>
    // NUM =  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23

    // SECONDARY MICRO-ENHANCE LOGIC (SAFE)	// 0 ARB-Boost 1-9		// 1 ARB-BCD 0-4	// 2 ARB-BRP 0-4	// 3 ARB-RTR 0-4
    // 4 ARB-RTW 0-4	// 5 ARB-WTR 0-4	// 6 eZQ Override 0-7	// 7 trDVFS 0-1		// 8 E-Boost 0-2	// 9 SSC Logic 0-1
    // 10 Latent 0-8  	// 11 REF-NEH 0-4	// 12 Clatok 0-1		// 13 CPriora 0-4	// 14 GetLow 0-3	// 15 GetHigh 0-3
    // 16 SYK-LOH 0-1
    .sMEH = {7, 2, 2, 2, 2, 1, 1, 0, 0, 1, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // DEF =  7  2  2  2  2  1  1  0  0  1  0  2  1  0  0  0  0 >> RESERVED >>
    // NUM =  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23

    // Secret Hardware Assisted Integration Tool 4 Advanced Necessities
    // SPELL = [S][   SLOT1   ][   SLOT2   ][   SLOT3   ][R]
    .SHAITAN = {0, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 0},  //! DANGER
    // NUM 	 =  0   1  2  3  4   5  6  7  8   9 10 11 12 13
    // Magic numbers - right combination adds feautures from the future

    // .eristaMtcTable = const_cast<EristaMtcTable *>(&EristaMtcTablePlaceholder),
    // .marikoMtcTable = const_cast<MarikoMtcTable *>(&MarikoMtcTablePlaceholder),
};
