#pragma once

#include <utils/types.h>

typedef struct _inputs {
    union {
        struct {
            // Joy-Con (R).
            u32 y : 1;
            u32 x : 1;
            u32 b : 1;
            u32 a : 1;
            u32 sr_r : 1;
            u32 sl_r : 1;
            u32 r : 1;
            u32 zr : 1;

            // Shared
            u32 minus : 1;
            u32 plus : 1;
            u32 r3 : 1;
            u32 l3 : 1;
            u32 home : 1;
            u32 cap : 1;
            u32 pad : 1;
            u32 wired : 1;

            // Joy-Con (L).
            u32 down : 1;
            u32 up : 1;
            u32 right : 1;
            u32 left : 1;
            u32 sr_l : 1;
            u32 sl_l : 1;
            u32 l : 1;
            u32 zl : 1;

            u32 power : 1;
            u32 volp : 1;
            u32 volm : 1;

            u32 rDown : 1;
            u32 rUp : 1;
            u32 rRight : 1;
            u32 rLeft : 1;
        };
        u32 buttons;
    };
} Input_t;
