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
0 , 100 ,
21 , 92 ,
40 , 70 ,
52 , 38 ,
56 , 0 ,
52 , -38 ,
40 , -70 ,
};

const signed char seg1[] = {
6,
92 , 25 ,
70 , 46 ,
38 , 60 ,
0 , 65 ,
-38 , 60 ,
-70 , 46 ,
-92 , 25 ,
};
const signed char seg2[] = {
6,
92 , 16 ,
70 , 30 ,
38 , 40 ,
0 , 43 ,
-38 , 40 ,
-70 , 30 ,
-92 , 16 ,
};
const signed char seg3[] = {
6,
92 , 5 ,
70 , 10 ,
38 , 13 ,
0 , 14 ,
-38 , 13 ,
-70 , 10 ,
-92 , 5 ,
};
const signed char seg4[] = {
6,
92 , -6 ,
70 , -11 ,
38 , -15 ,
0 , -16 ,
-38 , -15 ,
-70 , -11 ,
-92 , -6 ,
};
const signed char seg5[] = {
6,
92 , -17 ,
70 , -32 ,
38 , -41 ,
0 , -45 ,
-38 , -41 ,
-70 , -32 ,
-92 , -17 ,
};
const signed char seg6[] = {
6,
92 , -25 ,
70 , -47 ,
38 , -61 ,
0 , -67 ,
-38 , -61 ,
-70 , -47 ,
-92 , -25 ,
};
const signed char seg7[] = {
6,
92 , -30 ,
70 , -55 ,
38 , -72 ,
0 , -78 ,
-38 , -72 ,
-70 , -55 ,
-92 , -30 ,
};

const signed char *ball[MAX_ANIM] = {
                                 ball0,
                               };

#endif