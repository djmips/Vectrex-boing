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

// const signed char ball0[] = {
//                             15,
//                             -2 * SPRITE_SIZE,  0 * SPRITE_SIZE,
//                             -2 * SPRITE_SIZE,  1 * SPRITE_SIZE,
//                             -1 * SPRITE_SIZE,  1 * SPRITE_SIZE,
//                             -1 * SPRITE_SIZE,  2 * SPRITE_SIZE,
//                              0 * SPRITE_SIZE,  2 * SPRITE_SIZE,

//                              1 * SPRITE_SIZE,  2 * SPRITE_SIZE,
//                              1 * SPRITE_SIZE,  1 * SPRITE_SIZE,
//                              2 * SPRITE_SIZE,  1 * SPRITE_SIZE,

//                              2 * SPRITE_SIZE,  0 * SPRITE_SIZE,
//                              2 * SPRITE_SIZE, -1 * SPRITE_SIZE,
//                              1 * SPRITE_SIZE, -1 * SPRITE_SIZE,
//                              1 * SPRITE_SIZE, -2 * SPRITE_SIZE,

//                              0 * SPRITE_SIZE, -2 * SPRITE_SIZE,
//                             -1 * SPRITE_SIZE, -2 * SPRITE_SIZE,
//                             -1 * SPRITE_SIZE, -1 * SPRITE_SIZE,
//                             -2 * SPRITE_SIZE, -1 * SPRITE_SIZE,
//                            };

const signed char ball0[] = {
                            15,
30 , 92 ,
56 , 70 ,
73 , 38 ,
80 , 0 ,
73 , -38 ,
56 , -70 ,
30 , -92 ,
0 , -100 ,
-30 , -92 ,
-56 , -70 ,
-73 , -38 ,
-80 , 0 ,
-73 , 38 ,
-56 , 70 ,
-30 , 92 ,
0 , 100 ,
                           };

const signed char seg0[] = {
5,
55 , 70 ,
72 , 38 ,
78 , 0 ,
72 , -38 ,
55 , -70 ,
29 , -92 ,
};
const signed char seg1[] = {
5,
46 , 70 ,
60 , 38 ,
65 , 0 ,
60 , -38 ,
46 , -70 ,
25 , -92 ,
};
const signed char seg2[] = {
5,
30 , 70 ,
40 , 38 ,
43 , 0 ,
40 , -38 ,
30 , -70 ,
16 , -92 ,
};
const signed char seg3[] = {
5,
10 , 70 ,
13 , 38 ,
14 , 0 ,
13 , -38 ,
10 , -70 ,
5 , -92 ,
};
const signed char seg4[] = {
5,
-11 , 70 ,
-15 , 38 ,
-16 , 0 ,
-15 , -38 ,
-11 , -70 ,
-6 , -92 ,
};
const signed char seg5[] = {
5,
-32 , 70 ,
-41 , 38 ,
-45 , 0 ,
-41 , -38 ,
-32 , -70 ,
-17 , -92 ,
};
const signed char seg6[] = {
5,
-47 , 70 ,
-61 , 38 ,
-67 , 0 ,
-61 , -38 ,
-47 , -70 ,
-25 , -92 ,
};
const signed char seg7[] = {
5,
-55 , 70 ,
-72 , 38 ,
-78 , 0 ,
-72 , -38 ,
-55 , -70 ,
-30 , -92 ,
};

const signed char *ball[MAX_ANIM] = {
                                 ball0,
                               };

#endif