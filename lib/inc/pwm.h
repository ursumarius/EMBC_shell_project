/* ========================================================================== */
/* pwm.h                                                                      */
/* ========================================================================== */
/* This module includes functions setting up pwm signals.                     */
/* ========================================================================== */
/* Requires:         TIMER2 and OC1,2,3,4 and/or 5                            */
/* ========================================================================== */
/* author:           Ronnie Duisters                                          */
/* affiliation:      Fontys Hogescholen Engineering, Eindhoven                */
/* library:          embc (Embedded Connectivity)                             */
/* initial revision: 24-01-2013 (v1.0)                                        */
/* current version:  1.0                                                      */
/* changes:                                                                   */
/* ========================================================================== */

#ifndef PWM_H
#define PWM_H

/* -------------------------------------------------------------------------- */
/* definitions.                                                               */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* function prototypes.                                                       */
/* -------------------------------------------------------------------------- */

/* ========================================================================== */
/* function: pwm_init( fpb, channel, freq, width_us );                        */
/*                                                                            */
/* description: initialises a PWM channel.                                    */
/*                                                                            */
/* pre:  fpb           - peripheral bus clock frequency in Hz                 */
/*       channel       - number of the pwm channel to initialise (range 1...5)*/
/*       freq          - repetition frequency of the pulse in Hz              */
/*       width_us      - pulse width in microseconds                          */
/*                                                                            */
/* post: return value  - 0 if initialisation failed, 1 if succeeded           */
/* ========================================================================== */
unsigned char pwm_init
(
    unsigned int fpb,
    unsigned char channel,
    unsigned int freq,
    unsigned int width_us
);
    
/* ========================================================================== */
/* function: pwm_setwidth( channel, width_us );                               */
/*                                                                            */
/* description: initialises a PWM channel.                                    */
/*                                                                            */
/* pre:  channel       - number of the pwm channel to adjust (range 1...5)    */
/*       width_us      - pulse width in microseconds                          */
/*                                                                            */
/* post: none                                                                 */
/* ========================================================================== */
void pwm_setwidth
(
    unsigned char channel,
    unsigned int width_us
);
    
#endif /* PWM_H */
