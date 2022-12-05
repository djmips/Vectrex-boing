#ifndef BALL_H
#define BALL_H

/*
 * A ball Sprite is defined here.
 */

#define _SCALE 30
#define SPRITE_SIZE 25
#define MAX_ANIM 11

#include "circ.h"
#include "lat.h"
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