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
-15, 93,
-43, 79,
-64, 53,
-76, 18,
-76, -18,
-64, -53,
-43, -79,
-15, -93,
};
const signed char seg1[] = {
6,
-15, 78,
-43, 66,
-64, 44,
-76, 15,
-76, -15,
-64, -44,
-43, -66,
-15, -78,
};
const signed char seg2[] = {
6,
-15, 52,
-43, 44,
-64, 29,
-76, 10,
-76, -10,
-64, -29,
-43, -44,
-15, -52,
};
const signed char seg3[] = {
6,
-15, 17,
-43, 14,
-64, 9,
-76, 3,
-76, -3,
-64, -9,
-43, -14,
-15, -17,
};
const signed char seg4[] = {
6,
-15, -19,
-43, -16,
-64, -11,
-76, -3,
-76, 3,
-64, 11,
-43, 16,
-15, 19,
};
const signed char seg5[] = {
6,
-15, -54,
-43, -45,
-64, -30,
-76, -10,
-76, 10,
-64, 30,
-43, 45,
-15, 54,
};
const signed char seg6[] = {
6,
-15, -80,
-43, -68,
-64, -45,
-76, -15,
-76, 15,
-64, 45,
-43, 68,
-15, 80,
};
const signed char seg7[] = {
6,
-15, -94,
-43, -79,
-64, -53,
-76, -18,
-76, 18,
-64, 53,
-43, 79,
-15, 94,
};

const signed char *ball[MAX_ANIM] = {
                                 ball0,
                               };

#endif