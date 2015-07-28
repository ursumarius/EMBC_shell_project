/* ========================================================================== */
/* timer.h                                                                    */
/* ========================================================================== */
/* This module includes functions for setting up the timer units of the PIC32.*/
/* ========================================================================== */
/* Requires:         TIMER1,2,3,4 and/or 5                                    */
/* ========================================================================== */
/* author:           Ronnie Duisters                                          */
/* affiliation:      Fontys Hogescholen Engineering, Eindhoven                */
/* initial revision: 11-10-2011 (v1.0)                                        */
/* current version:  1.0                                                      */
/* changes:                                                                   */
/* ========================================================================== */

#ifndef TIMER_H
#define TIMER_H

/* -------------------------------------------------------------------------- */
/* definitions.                                                               */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* function prototypes.                                                       */
/* -------------------------------------------------------------------------- */

/* ========================================================================== */
/* function: timer_init( fpb, channel, time_us, int_onoff, int_priority );     */
/*                                                                            */
/* description: initialises and activates one of the 5 timers of the PIC32    */
/*              microprocessor.                                               */
/*                                                                            */
/* pre:  fpb          - peripheral bus clock frequency in Hz                  */
/*       channel       - channel of the timer to initialise (range 1...5)       */
/*       time_us      - repetition time of the timer in microseconds          */
/*       int_onoff    - interrupt on (1) or off (0)                           */
/*       int_priority - interrupt priority (range 0...7)                      */ 
/*                                                                            */
/* post: return value - 0 if initialisation failed, 1 if succeeded            */
/* ========================================================================== */
unsigned char timer_init
(
    unsigned int fpb,
    unsigned char channel,
    unsigned int time_us,
    unsigned char int_onoff,
    unsigned char int_priority
);
/*----------------------------------------------------------------------------*/
/*creation of callback function.
/*----------------------------------------------------------------------------*/
typedef void(*T2callback)(void);
void timer_register_T2callback(T2callback ptr_T2callback);
    
#endif /* TIMER_H */
