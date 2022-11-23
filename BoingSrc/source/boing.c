/*
 * Include some standard vectrex functions first!
 */
#include <vectrex.h>
#include "controller.h"

#include "ball.h"

/*
 * Some defines, Maximal brightness is $7f, highest not set!
 * Max Scale would be $ff, well here we take only $f0!
 */
#define MAX_BRIGHTNESS (0x7f)
#define MAX_SCALE (0xf0)
#define MOVE_SCALE 0x90

#define EDGE 45
#define BOT 100

/*
 * For variable variables ALLWAYS leave them uninitialized, this way
 * the compiler puts them into the BSS ram section in vectrex ram
 * area from c880 onwards.
 *
 * All non BSS memory should be declared constant!
 * (This is still leaves the option of auto variables in a
 * functiion, which will takes it needed men from the stack)
 *
 */
unsigned char *current_song;

/*
 * If you declare a function 'static inline' it is pretty much sure that
 * the compiler will inline it completely, the function will not
 * appear in any way in the module.
 *
 * If you leave out the static, the compiler assumes it might be used
 * globally, and thus leaves the function in the code, even if
 * it is inlined everywhere!
 */
/*
 * This Funktion handles all startup code, needed for vectrex to work
 * correctly, recallibrating the beam and making sure that some sound
 * is played (if wanted).
 */
static inline void start_one_vectrex_round(void)
{
  DP_to_C8();                        /* vectrex internal... dp must point */
  Init_Music_chk(current_song);    /* to c800, could make a function which */
  Wait_Recal();                       /* sets this up allright... */
  Do_Sound();
}

/*
 * This function sets up a piece of music to be played from the start
 * of the next round on onward...
 */
static inline void play_song(void* song)
{
  Vec_Music_Flag = 1;       /* A makro to write to a specific memory */
  current_song = song;                /* address */
}

/*
 * A simple setup routine, enables/disables the joystick, and makes sure
 * that the button state is read correctly...
 */
void setup(void)
{
  enable_controller_1_x();
  enable_controller_1_y();
  disable_controller_2_x();
  disable_controller_2_y();
  Joy_Digital();
  check_buttons();                       /* last pressed button */
  Wait_Recal();                       /* sets this up allright... */
}

/*
 * Our main function we start of here...
 * we should make sure that we never return from here, or vectrex will
 * be surely bothered!
 */
int main(void)
{
  unsigned char anim_state;           /* our animation state counter */
  signed char whole;
  const signed char frac = 10;
  signed char ball_x;               /* where is the ball? */
  signed char ball_y;
  signed char n;  
  signed char xs;

  whole = 127;
  ball_x = 0;
  ball_y = 50;
  n = -2;
  xs = -1;
  anim_state = 0;
  setup();                            /* setup our program */

  while (1)                        /* never to return... */
  {
    start_one_vectrex_round();        /* start 'de round */
    Intensity_a(MAX_BRIGHTNESS);          /* set some brightness */
    //VIA_t1_cnt_lo = MAX_SCALE;               /* set scale factor */
    //Print_Str_d(100,-128, "JOYSTICK 1 TO MOVE BALL!\x80"); /* a message! */

    Reset0Ref();
    VIA_t1_cnt_lo = _SCALE;      /* set scale factor for the sprite */
    Moveto_d((ball_y + 50), ball_x);      /* position ball */
    VIA_t1_cnt_lo = _SCALE;      /* set scale factor for the sprite */
    //Draw_VLc((void*)(ball[anim_state])); /* draw the current ball */
    Draw_VLc((void*)ball0);
    //Reset0Ref();
    //Moveto_d(0, 0);
    //Draw_VLc((void*)seg0);
    Reset0Ref();
    //VIA_t1_cnt_lo = _SCALE;      /* set scale factor for the sprite */
    Moveto_d((ball_y + 50), ball_x);      /* position ball */
    //VIA_t1_cnt_lo = _SCALE;      /* set scale factor for the sprite */
    Draw_VLc((void*)seg0);

    Reset0Ref();
    Moveto_d((ball_y + 50), ball_x);      /* position ball */
    Draw_VLc((void*)seg1);
    Reset0Ref();
    Moveto_d((ball_y + 50), ball_x);      /* position ball */
    Draw_VLc((void*)seg2);
    Reset0Ref();
    Moveto_d((ball_y + 50), ball_x);      /* position ball */
    Draw_VLc((void*)seg3);
    Reset0Ref();
    Moveto_d((ball_y + 50), ball_x);      /* position ball */
    Draw_VLc((void*)seg4);
    Reset0Ref();
    Moveto_d((ball_y + 50), ball_x);      /* position ball */
    Draw_VLc((void*)seg5);
    Reset0Ref();
    Moveto_d((ball_y + 50), ball_x);      /* position ball */
    Draw_VLc((void*)seg6);
    Reset0Ref();
    Moveto_d((ball_y + 50), ball_x);      /* position ball */
    Draw_VLc((void*)seg7);

    anim_state++;                     /* next time the next animation */
    if (anim_state == MAX_ANIM)       /* could do a % MAXANIM, but this is */
       anim_state = 0;                /* more optimized */
    if (!Vec_Music_Flag)    /* music finished? */
       play_song((void*)&Vec_Music_4);     /* if so ... restart */
    if (joystick_1_x()>0)                /* check the joystick and */
    {                                 /* update position */
      ball_x++;
    }
    else if (joystick_1_x()<0)
    {
      ball_x--;
    }
    if (joystick_1_y()>0)
    {
      ball_y++;
    }
    else if (joystick_1_y()<0)
    {
      ball_y--;
    }

    ball_x = ball_x + xs;
    ball_y = ball_y + n;


    if (ball_x>=EDGE)
    { 
      ball_x = ball_x - xs;
      xs = -xs;
    }

    if (ball_x<=-EDGE) 
    {
      ball_x = ball_x - xs;
      xs = -xs;
    } 


    if (ball_y>=BOT) ball_y = BOT;

    if (ball_y<=-BOT) 
    {
      ball_y = -BOT;
      whole = 127;
      n = 4;
    }

    whole = whole - frac;
    if ( whole < 0 )
    {
        whole = whole + 127;
        n = n - 1;
    }

    Joy_Digital();                        /* call once per round, to insure */
  } /* while (1) */                    /* joystick information is up to date */
}

/* END OF FILE */
