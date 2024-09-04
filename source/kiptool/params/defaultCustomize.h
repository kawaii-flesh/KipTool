#pragma once

#include "customize.h"

#define getOffset(param) (int)((const void*)&param - (const void*)defaultCustTable.cust)
#define S_ST2 2665600

const CustomizeTable defaultCustTable =
    {
        .cust = CUST,
        .custRev = KT_CUST_VER,

        // eBAMATIC; LEGACY; DEBUG; ALTMODE
        .mtcConf = eBAMATIC,
        // eBAMATIC	MHz
        // MARIKO eBAL
        // ERISTA eBAL
        //  120 133 146 160 173 186 200 213 226 240 253 266 280 293 306 320 333 346 360 373
        //  1,	1, 	1,	1, 	1, 	2, 	2, 	2, 	3, 	3, 	4, 	5, 	5, 	5, 	5, 	5, 	5,  5,  5,  5
        //  1,	1, 	1,	1, 	2, 	3, 	4, 	5, 	5, 	5, 	5, 	5, 	5, 	5

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
        .marikoEmcMaxClock = S_ST2,  // MICRON E/H eBAL 4 < 3.8GHz  // SAMSUNG B eBAL 4 < 3.9GHz // HYNIX CJR/DJR eBAL 4 < 3.8GHz
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

        .marikoGpuVoltArray =
            {
                395,  // 307200   307
                420,  // 345600   345
                445,  // 384000   384
                470,  // 422400   422
                495,  // 460800   460
                520,  // 499200   499
                545,  // 537600   537
                570,  // 576000   576
                595,  // 614400   614
                620,  // 652800   652
                645,  // 691200   691
                670,  // 729600   729
                695,  // 768000   768
                720,  // 806400   806
                750,  // 844800   845
                780,  // 883200   883
                810,  // 921600   921
                840,  // 960000   960
                870,  // 998400   998
                900,  // 1036800  1036
                930,  // 1075200  1075
                960,  // 1113600  1113
                990,  // 1152000  1152
                1020  // 1190400  1190
            },

        .eristaCpuDvfsTable =
            {
                // freq       cvb_dfll_param	   cvb_pll_param
                // -----      ----------------------------------    	   ----------------------------------
                // u64	 s32     s32     s32     s32     s32     s32   	  	   s32      s32     s32     s32     s32     s32
                // freq       	  c0      c1      c2      c3      c4      c5    	  	c0       c1      c2      c3      c4      c5
                {408000, {786986, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}},
                {510000, {819932, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}},
                {612000, {852878, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}},
                {714000, {885824, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}},
                {816000, {918770, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}},
                {918000, {951716, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}},
                {1020000, {984662, 0, 0, 0, 0, 0}, {-2875621, 358099, -8585, 0, 0, 0}},
                {1122000, {1017608, 0, 0, 0, 0, 0}, {-52225, 104159, -2816, 0, 0, 0}},
                {1224000, {1050554, 0, 0, 0, 0, 0}, {1076868, 8356, -727, 0, 0, 0}},
                {1326000, {1083500, 0, 0, 0, 0, 0}, {2208191, -84659, 1240, 0, 0, 0}},
                {1428000, {1116446, 0, 0, 0, 0, 0}, {2519460, -105063, 1611, 0, 0, 0}},
                {1581000, {1130000, 0, 0, 0, 0, 0}, {2889664, -122173, 1834, 0, 0, 0}},
                {1683000, {1168000, 0, 0, 0, 0, 0}, {5100873, -279186, 4747, 0, 0, 0}},
                {1785000, {1227500, 0, 0, 0, 0, 0}, {5100873, -279186, 4747, 0, 0, 0}},
                {1887000, {1235000, 0, 0, 0, 0, 0}, {5100873, -279186, 4747, 0, 0, 0}},
                {1963500, {1235000, 0, 0, 0, 0, 0}, {5100873, -279186, 4747, 0, 0, 0}},
                {2091000, {1235000, 0, 0, 0, 0, 0}, {5100873, -279186, 4747, 0, 0, 0}},
                {2193000, {1235000, 0, 0, 0, 0, 0}, {5100873, -279186, 4747, 0, 0, 0}},
                {2295000, {1235000, 0, 0, 0, 0, 0}, {5100873, -279186, 4747, 0, 0, 0}},
                {2397000, {1235000, 0, 0, 0, 0, 0}, {5100873, -279186, 4747, 0, 0, 0}},
                {2499000, {1235000, 0, 0, 0, 0, 0}, {5100873, -279186, 4747, 0, 0, 0}},
                {2602000, {1235000, 0, 0, 0, 0, 0}, {5100873, -279186, 4747, 0, 0, 0}},
                //{ 2703000, { 1350000,      0,      0,      0,      0,      0 }, {  5100873, -279186,   4747,      0,      0,      0 } },
                //{ 2805000, { 1375000,      0,      0,      0,      0,      0 }, {  5100873, -279186,   4747,      0,      0,      0 } },
            },

        .marikoCpuDvfsTable =
            {
                // freq       cvb_dfll_param	   cvb_pll_param
                // -----      ----------------------------------    	   ----------------------------------
                // u64	 s32     s32     s32     s32     s32     s32   	  	   s32      s32     s32     s32     s32     s32
                // freq       	  c0      c1      c2      c3      c4      c5    	  	c0       c1      c2      c3      c4      c5
                {408000, {760024, -18195, 113, 0, 0, 0}, {0, 0, 0, 0, 0, 0}},         {510000, {789258, -19055, 113, 0, 0, 0}, {0, 0, 0, 0, 0, 0}},
                {612000, {853926, -20775, 113, 0, 0, 0}, {0, 0, 0, 0, 0, 0}},         {714000, {889361, -21625, 113, 0, 0, 0}, {0, 0, 0, 0, 0, 0}},
                {816000, {926862, -22485, 113, 0, 0, 0}, {0, 0, 0, 0, 0, 0}},         {918000, {966431, -23345, 113, 0, 0, 0}, {0, 0, 0, 0, 0, 0}},
                {1020000, {1008066, -24205, 113, 0, 0, 0}, {1120000, 0, 0, 0, 0, 0}}, {1122000, {1051768, -25065, 113, 0, 0, 0}, {1120000, 0, 0, 0, 0, 0}},
                {1224000, {1097537, -25925, 113, 0, 0, 0}, {1120000, 0, 0, 0, 0, 0}}, {1326000, {1145373, -26785, 113, 0, 0, 0}, {1120000, 0, 0, 0, 0, 0}},
                {1428000, {1195276, -27645, 113, 0, 0, 0}, {1120000, 0, 0, 0, 0, 0}}, {1581000, {1274006, -28935, 113, 0, 0, 0}, {1120000, 0, 0, 0, 0, 0}},
                {1683000, {1329076, -29795, 113, 0, 0, 0}, {1120000, 0, 0, 0, 0, 0}}, {1785000, {1386213, -30655, 113, 0, 0, 0}, {1120000, 0, 0, 0, 0, 0}},
                {1887000, {1445416, -31515, 113, 0, 0, 0}, {1120000, 0, 0, 0, 0, 0}}, {1963500, {1490873, -32155, 113, 0, 0, 0}, {1120000, 0, 0, 0, 0, 0}},
                {2091000, {1580725, -33235, 113, 0, 0, 0}, {1235000, 0, 0, 0, 0, 0}}, {2193000, {1580725, -33235, 113, 0, 0, 0}, {1235000, 0, 0, 0, 0, 0}},
                {2295000, {1635431, -34095, 113, 0, 0, 0}, {1235000, 0, 0, 0, 0, 0}}, {2397000, {1702903, -34955, 113, 0, 0, 0}, {1235000, 0, 0, 0, 0, 0}},
                {2499000, {1754400, -35643, 113, 0, 0, 0}, {1235000, 0, 0, 0, 0, 0}}, {2601000, {1805897, -36331, 113, 0, 0, 0}, {1235000, 0, 0, 0, 0, 0}},
                {2703000, {1857394, -37019, 113, 0, 0, 0}, {1235000, 0, 0, 0, 0, 0}}, {2805000, {1908891, -37707, 113, 0, 0, 0}, {1235000, 0, 0, 0, 0, 0}},
                {2907000, {1960388, -38395, 113, 0, 0, 0}, {1235000, 0, 0, 0, 0, 0}}, {3009000, {2011885, -39083, 113, 0, 0, 0}, {1235000, 0, 0, 0, 0, 0}},
                //{ 3111000, { 2063382, -39771,    113,      0,      0,      0 }, { 1235000,      0,      0,      0,      0,      0 } },
                //{ 3213000, { 2063382, -39771,    113,      0,      0,      0 }, { 1235000,      0,      0,      0,      0,      0 } },
            },

        .marikoCpuDvfsTableSLT =
            {
                // freq       cvb_dfll_param	   cvb_pll_param
                // -----      ----------------------------------    	   ----------------------------------
                // u64	 s32     s32     s32     s32     s32     s32   	  	   s32      s32     s32     s32     s32     s32
                // freq       	  c0      c1      c2      c3      c4      c5    	  	c0       c1      c2      c3      c4      c5
                //{  204000, {  732856, -17335,    113,      0,      0,      0 }, {0,       0,      0,      0,      0,      0 } },
                //{  306000, {  760024, -18195,    113,      0,      0,      0 }, {0,       0,      0,      0,      0,      0 } },
                {408000, {760024, -18195, 113, 0, 0, 0}, {0, 0, 0, 0, 0, 0}},         {510000, {789258, -19055, 113, 0, 0, 0}, {0, 0, 0, 0, 0, 0}},
                {612000, {853926, -20775, 113, 0, 0, 0}, {0, 0, 0, 0, 0, 0}},         {714000, {889361, -21625, 113, 0, 0, 0}, {0, 0, 0, 0, 0, 0}},
                {816000, {926862, -22485, 113, 0, 0, 0}, {0, 0, 0, 0, 0, 0}},         {918000, {966431, -23345, 113, 0, 0, 0}, {0, 0, 0, 0, 0, 0}},
                {1020000, {1008066, -24205, 113, 0, 0, 0}, {1120000, 0, 0, 0, 0, 0}}, {1122000, {1051768, -25065, 113, 0, 0, 0}, {1120000, 0, 0, 0, 0, 0}},
                {1224000, {1097537, -25925, 113, 0, 0, 0}, {1120000, 0, 0, 0, 0, 0}}, {1326000, {1145373, -26785, 113, 0, 0, 0}, {1120000, 0, 0, 0, 0, 0}},
                {1428000, {1195276, -27645, 113, 0, 0, 0}, {1120000, 0, 0, 0, 0, 0}}, {1581000, {1274006, -28935, 113, 0, 0, 0}, {1120000, 0, 0, 0, 0, 0}},
                {1683000, {1329076, -29795, 113, 0, 0, 0}, {1120000, 0, 0, 0, 0, 0}}, {1785000, {1386213, -30655, 113, 0, 0, 0}, {1120000, 0, 0, 0, 0, 0}},
                {1887000, {1445416, -31515, 113, 0, 0, 0}, {1120000, 0, 0, 0, 0, 0}}, {1963500, {1490873, -32155, 113, 0, 0, 0}, {1120000, 0, 0, 0, 0, 0}},
                {2091000, {1580725, -33235, 113, 0, 0, 0}, {1235000, 0, 0, 0, 0, 0}}, {2193000, {1580725, -33235, 113, 0, 0, 0}, {1235000, 0, 0, 0, 0, 0}},
                {2295000, {1635431, -34095, 113, 0, 0, 0}, {1235000, 0, 0, 0, 0, 0}}, {2397000, {1702903, -34955, 113, 0, 0, 0}, {1235000, 0, 0, 0, 0, 0}},
                {2499000, {1754400, -35643, 113, 0, 0, 0}, {1235000, 0, 0, 0, 0, 0}}, {2601000, {1805897, -36331, 113, 0, 0, 0}, {1235000, 0, 0, 0, 0, 0}},
                {2703000, {1857394, -37019, 113, 0, 0, 0}, {1235000, 0, 0, 0, 0, 0}}, {2805000, {1908891, -37707, 113, 0, 0, 0}, {1235000, 0, 0, 0, 0, 0}},
                {2907000, {1960388, -38395, 113, 0, 0, 0}, {1235000, 0, 0, 0, 0, 0}}, {3009000, {2011885, -39083, 113, 0, 0, 0}, {1235000, 0, 0, 0, 0, 0}},
                //{ 3111000, { 2063382, -39771,    113,      0,      0,      0 }, { 1235000,      0,      0,      0,      0,      0 } },
                //{ 3213000, { 2063382, -39771,    113,      0,      0,      0 }, { 1235000,      0,      0,      0,      0,      0 } },
            },

        // ERISTA GPU ECO LOGIC // ECO ST1 = -12500uV // ECO ST2 = -25000uV // ECO ST3 = -37500uV // MANUAL = -75000uV << Default >> +75000uV
        .eristaGpuDvfsTable =
            {
                // freq       cvb_dfll_paramcvb_pll_param
                // -----      ----------------------------------    ----------------------------------
                // u64s32     s32     s32     s32     s32     s32   s32     s32     s32     s32     s32     s32
                // freq       c0      c1      c2      c3      c4      c5    c0      c1      c2      c3      c4      c5
                {192000, {0, 0, 0, 0, 0, 0}, {675000, 0, 0, 0, 0, 0}},   {230400, {0, 0, 0, 0, 0, 0}, {687500, 0, 0, 0, 0, 0}},
                {268800, {0, 0, 0, 0, 0, 0}, {700000, 0, 0, 0, 0, 0}},   {307200, {0, 0, 0, 0, 0, 0}, {712500, 0, 0, 0, 0, 0}},
                {345600, {0, 0, 0, 0, 0, 0}, {725000, 0, 0, 0, 0, 0}},   {384000, {0, 0, 0, 0, 0, 0}, {737500, 0, 0, 0, 0, 0}},
                {422400, {0, 0, 0, 0, 0, 0}, {750000, 0, 0, 0, 0, 0}},   {460800, {0, 0, 0, 0, 0, 0}, {762500, 0, 0, 0, 0, 0}},
                {500000, {0, 0, 0, 0, 0, 0}, {775000, 0, 0, 0, 0, 0}},   {537600, {0, 0, 0, 0, 0, 0}, {787500, 0, 0, 0, 0, 0}},
                {576000, {0, 0, 0, 0, 0, 0}, {800000, 0, 0, 0, 0, 0}},   {613400, {0, 0, 0, 0, 0, 0}, {812500, 0, 0, 0, 0, 0}},
                {653000, {0, 0, 0, 0, 0, 0}, {825000, 0, 0, 0, 0, 0}},   {691200, {0, 0, 0, 0, 0, 0}, {837500, 0, 0, 0, 0, 0}},
                {729600, {0, 0, 0, 0, 0, 0}, {850000, 0, 0, 0, 0, 0}},   {768000, {0, 0, 0, 0, 0, 0}, {862500, 0, 0, 0, 0, 0}},
                {805400, {0, 0, 0, 0, 0, 0}, {875000, 0, 0, 0, 0, 0}},   {840800, {0, 0, 0, 0, 0, 0}, {887500, 0, 0, 0, 0, 0}},
                {883200, {0, 0, 0, 0, 0, 0}, {912500, 0, 0, 0, 0, 0}},   {921600, {0, 0, 0, 0, 0, 0}, {925000, 0, 0, 0, 0, 0}},
                {960000, {0, 0, 0, 0, 0, 0}, {950000, 0, 0, 0, 0, 0}},   {998400, {0, 0, 0, 0, 0, 0}, {962500, 0, 0, 0, 0, 0}},
                {1036800, {0, 0, 0, 0, 0, 0}, {975000, 0, 0, 0, 0, 0}},  {1074200, {0, 0, 0, 0, 0, 0}, {1000000, 0, 0, 0, 0, 0}},
                {1113600, {0, 0, 0, 0, 0, 0}, {1037500, 0, 0, 0, 0, 0}}, {1152000, {0, 0, 0, 0, 0, 0}, {1062500, 0, 0, 0, 0, 0}},
                {1190400, {0, 0, 0, 0, 0, 0}, {1100000, 0, 0, 0, 0, 0}}, {1228800, {0, 0, 0, 0, 0, 0}, {1125000, 0, 0, 0, 0, 0}},
                {1266200, {0, 0, 0, 0, 0, 0}, {1150000, 0, 0, 0, 0, 0}},
            },

        .marikoGpuDvfsTable =
            {
                // freq       cvb_dfll_paramcvb_pll_param
                // -----      ----------------------------------    ----------------------------------
                // u64s32     s32     s32     s32     s32     s32   s32     s32     s32     s32     s32     s32
                // freq       c0      c1      c2      c3      c4      c5    c0      c1      c2      c3      c4      c5
                {307200, {0, 0, 0, 0, 0, 0}, {485000, 0, 0, 0, 0, 0}},  {345600, {0, 0, 0, 0, 0, 0}, {490000, 0, 0, 0, 0, 0}},
                {384000, {0, 0, 0, 0, 0, 0}, {500000, 0, 0, 0, 0, 0}},  {422400, {0, 0, 0, 0, 0, 0}, {510000, 0, 0, 0, 0, 0}},
                {460800, {0, 0, 0, 0, 0, 0}, {520000, 0, 0, 0, 0, 0}},  {499200, {0, 0, 0, 0, 0, 0}, {530000, 0, 0, 0, 0, 0}},
                {537600, {0, 0, 0, 0, 0, 0}, {540000, 0, 0, 0, 0, 0}},  {576000, {0, 0, 0, 0, 0, 0}, {550000, 0, 0, 0, 0, 0}},
                {614400, {0, 0, 0, 0, 0, 0}, {560000, 0, 0, 0, 0, 0}},  {652800, {0, 0, 0, 0, 0, 0}, {570000, 0, 0, 0, 0, 0}},
                {691200, {0, 0, 0, 0, 0, 0}, {585000, 0, 0, 0, 0, 0}},  {729600, {0, 0, 0, 0, 0, 0}, {595000, 0, 0, 0, 0, 0}},
                {768000, {0, 0, 0, 0, 0, 0}, {610000, 0, 0, 0, 0, 0}},  {806400, {0, 0, 0, 0, 0, 0}, {620000, 0, 0, 0, 0, 0}},
                {844800, {0, 0, 0, 0, 0, 0}, {635000, 0, 0, 0, 0, 0}},  {883200, {0, 0, 0, 0, 0, 0}, {645000, 0, 0, 0, 0, 0}},
                {921600, {0, 0, 0, 0, 0, 0}, {660000, 0, 0, 0, 0, 0}},  {960000, {0, 0, 0, 0, 0, 0}, {670000, 0, 0, 0, 0, 0}},
                {998400, {0, 0, 0, 0, 0, 0}, {685000, 0, 0, 0, 0, 0}},  {1036800, {0, 0, 0, 0, 0, 0}, {700000, 0, 0, 0, 0, 0}},
                {1075200, {0, 0, 0, 0, 0, 0}, {715000, 0, 0, 0, 0, 0}}, {1113600, {0, 0, 0, 0, 0, 0}, {730000, 0, 0, 0, 0, 0}},
                {1152000, {0, 0, 0, 0, 0, 0}, {750000, 0, 0, 0, 0, 0}}, {1190400, {0, 0, 0, 0, 0, 0}, {765000, 0, 0, 0, 0, 0}},
                {1228800, {0, 0, 0, 0, 0, 0}, {785000, 0, 0, 0, 0, 0}}, {1267200, {0, 0, 0, 0, 0, 0}, {815000, 0, 0, 0, 0, 0}},
                {1305600, {0, 0, 0, 0, 0, 0}, {845000, 0, 0, 0, 0, 0}}, {1344000, {0, 0, 0, 0, 0, 0}, {875000, 0, 0, 0, 0, 0}},
                {1382400, {0, 0, 0, 0, 0, 0}, {905000, 0, 0, 0, 0, 0}}, {1420800, {0, 0, 0, 0, 0, 0}, {935000, 0, 0, 0, 0, 0}},
                {1459200, {0, 0, 0, 0, 0, 0}, {960000, 0, 0, 0, 0, 0}},
            },

        .marikoGpuDvfsTableSLT =
            {
                // freq       cvb_dfll_paramcvb_pll_param
                // -----      ----------------------------------    ----------------------------------
                // u64s32     s32     s32     s32     s32     s32   s32     s32     s32     s32     s32     s32
                // freq       c0      c1      c2      c3      c4      c5    c0      c1      c2      c3      c4      c5
                {307200, {0, 0, 0, 0, 0, 0}, {465000, 0, 0, 0, 0, 0}},
                {345600, {0, 0, 0, 0, 0, 0}, {470000, 0, 0, 0, 0, 0}},
                {384000, {0, 0, 0, 0, 0, 0}, {475000, 0, 0, 0, 0, 0}},
                {422400, {0, 0, 0, 0, 0, 0}, {480000, 0, 0, 0, 0, 0}},
                {460800, {0, 0, 0, 0, 0, 0}, {495000, 0, 0, 0, 0, 0}},
                {499200, {0, 0, 0, 0, 0, 0}, {505000, 0, 0, 0, 0, 0}},
                {537600, {0, 0, 0, 0, 0, 0}, {520000, 0, 0, 0, 0, 0}},
                {576000, {0, 0, 0, 0, 0, 0}, {530000, 0, 0, 0, 0, 0}},
                {614400, {0, 0, 0, 0, 0, 0}, {545000, 0, 0, 0, 0, 0}},
                {652800, {0, 0, 0, 0, 0, 0}, {555000, 0, 0, 0, 0, 0}},
                {691200, {0, 0, 0, 0, 0, 0}, {565000, 0, 0, 0, 0, 0}},
                {729600, {0, 0, 0, 0, 0, 0}, {575000, 0, 0, 0, 0, 0}},
                {768000, {0, 0, 0, 0, 0, 0}, {585000, 0, 0, 0, 0, 0}},
                {806400, {0, 0, 0, 0, 0, 0}, {595000, 0, 0, 0, 0, 0}},
                {844800, {0, 0, 0, 0, 0, 0}, {610000, 0, 0, 0, 0, 0}},
                {883200, {0, 0, 0, 0, 0, 0}, {625000, 0, 0, 0, 0, 0}},
                {921600, {0, 0, 0, 0, 0, 0}, {635000, 0, 0, 0, 0, 0}},
                {960000, {0, 0, 0, 0, 0, 0}, {650000, 0, 0, 0, 0, 0}},
                {998400, {0, 0, 0, 0, 0, 0}, {660000, 0, 0, 0, 0, 0}},
                {1036800, {0, 0, 0, 0, 0, 0}, {675000, 0, 0, 0, 0, 0}},
                {1075200, {0, 0, 0, 0, 0, 0}, {690000, 0, 0, 0, 0, 0}},
                {1113600, {0, 0, 0, 0, 0, 0}, {710000, 0, 0, 0, 0, 0}},
                {1152000, {0, 0, 0, 0, 0, 0}, {730000, 0, 0, 0, 0, 0}},
                {1190400, {0, 0, 0, 0, 0, 0}, {750000, 0, 0, 0, 0, 0}},
                {1228800, {0, 0, 0, 0, 0, 0}, {770000, 0, 0, 0, 0, 0}},
                {1267200, {0, 0, 0, 0, 0, 0}, {785000, 0, 0, 0, 0, 0}},
                {1305600, {0, 0, 0, 0, 0, 0}, {800000, 0, 0, 0, 0, 0}},
                {1344000, {0, 0, 0, 0, 0, 0}, {825000, 0, 0, 0, 0, 0}},
                {1382400, {0, 0, 0, 0, 0, 0}, {850000, 0, 0, 0, 0, 0}},
                {1420800, {0, 0, 0, 0, 0, 0}, {880000, 0, 0, 0, 0, 0}},
                //{ 1459200, {       0,      0,      0,      0,      0,      0 }, { 905000,      0,      0,      0,      0,      0 } },
                //{ 1497600, {       0,      0,      0,      0,      0,      0 }, { 935000,      0,      0,      0,      0,      0 } },
                {1536000, {0, 0, 0, 0, 0, 0}, {960000, 0, 0, 0, 0, 0}},
            },

        .marikoGpuDvfsTableHiOPT =
            {
                // freq       cvb_dfll_paramcvb_pll_param
                // -----      ----------------------------------    ----------------------------------
                // u64s32     s32     s32     s32     s32     s32   s32     s32     s32     s32     s32     s32
                // freq       c0      c1      c2      c3      c4      c5    c0      c1      c2      c3      c4      c5
                {307200, {0, 0, 0, 0, 0, 0}, {445000, 0, 0, 0, 0, 0}},
                {345600, {0, 0, 0, 0, 0, 0}, {450000, 0, 0, 0, 0, 0}},
                {384000, {0, 0, 0, 0, 0, 0}, {455000, 0, 0, 0, 0, 0}},
                {422400, {0, 0, 0, 0, 0, 0}, {460000, 0, 0, 0, 0, 0}},
                {460800, {0, 0, 0, 0, 0, 0}, {465000, 0, 0, 0, 0, 0}},
                {499200, {0, 0, 0, 0, 0, 0}, {475000, 0, 0, 0, 0, 0}},
                {537600, {0, 0, 0, 0, 0, 0}, {485000, 0, 0, 0, 0, 0}},
                {576000, {0, 0, 0, 0, 0, 0}, {495000, 0, 0, 0, 0, 0}},
                {614400, {0, 0, 0, 0, 0, 0}, {510000, 0, 0, 0, 0, 0}},
                {652800, {0, 0, 0, 0, 0, 0}, {525000, 0, 0, 0, 0, 0}},
                {691200, {0, 0, 0, 0, 0, 0}, {540000, 0, 0, 0, 0, 0}},
                {729600, {0, 0, 0, 0, 0, 0}, {555000, 0, 0, 0, 0, 0}},
                {768000, {0, 0, 0, 0, 0, 0}, {570000, 0, 0, 0, 0, 0}},
                {806400, {0, 0, 0, 0, 0, 0}, {585000, 0, 0, 0, 0, 0}},
                {844800, {0, 0, 0, 0, 0, 0}, {595000, 0, 0, 0, 0, 0}},
                {883200, {0, 0, 0, 0, 0, 0}, {605000, 0, 0, 0, 0, 0}},
                {921600, {0, 0, 0, 0, 0, 0}, {615000, 0, 0, 0, 0, 0}},
                {960000, {0, 0, 0, 0, 0, 0}, {630000, 0, 0, 0, 0, 0}},
                {998400, {0, 0, 0, 0, 0, 0}, {640000, 0, 0, 0, 0, 0}},
                {1036800, {0, 0, 0, 0, 0, 0}, {655000, 0, 0, 0, 0, 0}},
                {1075200, {0, 0, 0, 0, 0, 0}, {670000, 0, 0, 0, 0, 0}},
                {1113600, {0, 0, 0, 0, 0, 0}, {690000, 0, 0, 0, 0, 0}},
                {1152000, {0, 0, 0, 0, 0, 0}, {700000, 0, 0, 0, 0, 0}},
                {1190400, {0, 0, 0, 0, 0, 0}, {720000, 0, 0, 0, 0, 0}},
                {1228800, {0, 0, 0, 0, 0, 0}, {745000, 0, 0, 0, 0, 0}},
                {1267200, {0, 0, 0, 0, 0, 0}, {760000, 0, 0, 0, 0, 0}},
                {1305600, {0, 0, 0, 0, 0, 0}, {775000, 0, 0, 0, 0, 0}},
                {1344000, {0, 0, 0, 0, 0, 0}, {800000, 0, 0, 0, 0, 0}},
                {1382400, {0, 0, 0, 0, 0, 0}, {825000, 0, 0, 0, 0, 0}},
                {1420800, {0, 0, 0, 0, 0, 0}, {850000, 0, 0, 0, 0, 0}},
                //{ 1459200, {       0,      0,      0,      0,      0,      0 }, { 870000,      0,      0,      0,      0,      0 } },
                //{ 1497600, {       0,      0,      0,      0,      0,      0 }, { 890000,      0,      0,      0,      0,      0 } },
                //{ 1536000, {       0,      0,      0,      0,      0,      0 }, { 910000,      0,      0,      0,      0,      0 } },
                //{ 1574400, {       0,      0,      0,      0,      0,      0 }, { 935000,      0,      0,      0,      0,      0 } },
                {1612800, {0, 0, 0, 0, 0, 0}, {960000, 0, 0, 0, 0, 0}},
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
        .pMEH = {0, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 3, 2, 0, 0},
        // DEF =  0  2  0  2  2  0  0  0  0  0  0  0  1  0  0  0  0  0  0  1  3  2  >> RESERVED >>
        // NUM =  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23

        // SECONDARY MICRO-ENHANCE LOGIC (SAFE)	// 0 ARB-Boost 1-9		// 1 ARB-BCD 0-4	// 2 ARB-BRP 0-4	// 3 ARB-RTR 0-4
        // 4 ARB-RTW 0-4	// 5 ARB-WTR 0-4	// 6 eZQ Override 0-7	// 7 trDVFS 0-1		// 8 E-Boost 0-2	// 9 SSC Logic 0-1
        // 10 Latent 0-8  	// 11 REF-NEH 0-4	// 12 Clatok 0-1		// 13 CPriora 0-4	// 14 GetLow 0-3	// 15 GetHigh 0-3
        // 16 SYK-LOH 0-1
        .sMEH = {7, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        // DEF =  7  2  2  2  2  2  1  0  0  0  0  2  1  0  0  0  0 >> RESERVED >>
        // NUM =  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23

        // Secret Hardware Assisted Integration Tool 4 Advanced Necessities
        // SPELL = [S][   SLOT1   ][   SLOT2   ][   SLOT3   ][R]
        .SHAITAN = {0, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 0},  //! DANGER
                                                                            // NUM 	 =  0   1  2  3  4   5  6  7  8   9 10 11 12 13
                                                                            // Magic numbers - right combination adds feautures from the future

        // .eristaMtcTable = const_cast<EristaMtcTable *>(&EristaMtcTablePlaceholder),
        // .marikoMtcTable = const_cast<MarikoMtcTable *>(&MarikoMtcTablePlaceholder),
};
