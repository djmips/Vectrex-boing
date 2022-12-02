#ifndef BALL_H
#define BALL_H

/*
 * A ball Sprite is defined here.
 */

#define _SCALE 30
#define SPRITE_SIZE 25
#define MAX_ANIM 11

const signed char ball[] = {
                            15,
-15, 91,
-43, 77,
-64, 52,
-76, 18,
-76, -18,
-64, -52,
-43, -77,
-15, -91,
15, -91,
43, -77,
64, -52,
76, -18,
76, 18,
64, 52,
43, 77,
15, 91
};

const signed char latSeg0[] = {
0,
0, -92,
};

// const signed char latSeg1[] = {
// -58, 169,
// 0, 339,
// };
// const signed char latSeg2[] = {
// -123, 221,
// 0, 443,
// };
const signed char latSeg3[] = {
// -200, 240,
 0,
 0, 127,
 0, 120,
 };
// const signed char latSeg4[] = {
// -276, 221,
// 0, 443,
// };
// const signed char latSeg5[] = {
// -341, 169,
// 0, 339,
// };
// const signed char latSeg6[] = {
// -384, 91,
// 0, 183,
// };

#include "long.h"

const signed char *anim[MAX_ANIM] = {
                                 long0,
                                 long1,
                                 long2,
                                 long3,
                                 long4,
                                 long5,
                                 long6,
                                 long7,
                                 long8,
                                 long9,
                                 long10
                               };


#endif