#ifndef BALL_H
#define BALL_H

/*
 * A ball Sprite is defined here.
 *
 * It was drawn using the 'veccy' tool!
 */

#define _SCALE 30
#define SPRITE_SIZE 25
#define MAX_ANIM 1

const signed char ball0[] = {
                            15,
-15, 95,
-43, 81,
-64, 54,
-76, 19,
-76, -19,
-64, -54,
-43, -81,
-15, -95,
15, -95,
43, -81,
64, -54,
76, -19,
76, 19,
64, 54,
43, 81,
15, 95,
};

const signed char seg0[] = {
6,
-15, 84,
-43, 71,
-64, 48,
-76, 16,
-76, -16,
-64, -48,
-43, -71,
-15, -84,
};
const signed char seg1[] = {
6,
-15, 64,
-43, 55,
-64, 36,
-76, 12,
-76, -12,
-64, -36,
-43, -55,
-15, -64,
};
const signed char seg2[] = {
6,
-15, 35,
-43, 29,
-64, 19,
-76, 6,
-76, -6,
-64, -19,
-43, -29,
-15, -35,
};
const signed char seg3[] = {
6,
-15, 0,
-43, 0,
-64, 0,
-76, 0,
-76, 0,
-64, 0,
-43, 0,
-15, 0,
};
const signed char seg4[] = {
6,
-15, -35,
-43, -29,
-64, -19,
-76, -6,
-76, 6,
-64, 19,
-43, 29,
-15, 35,
};
const signed char seg5[] = {
6,
-15, -64,
-43, -55,
-64, -36,
-76, -12,
-76, 12,
-64, 36,
-43, 55,
-15, 64,
};
const signed char seg6[] = {
6,
-15, -84,
-43, -71,
-64, -48,
-76, -16,
-76, 16,
-64, 48,
-43, 71,
-15, 84,
};


const signed char *ball[MAX_ANIM] = {
                                 ball0,
                               };

#endif