/* ========================================================================== */
/* pwm.c                                                                      */
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
/* changes:          
/* ========================================================================== */

#include <p32xxxx.h>
#include "pwm.h"
#include "timer.h"
#include "oc.h"

/* -------------------------------------------------------------------------- */
/* global variables.                                                          */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* local function prototypes.                                                 */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* functions.                                                                 */
/* -------------------------------------------------------------------------- */
unsigned char pwm_init(unsigned int fpb, unsigned char channel, unsigned int freq, unsigned int width_us)
{   
    unsigned char c1 = 0;
    
    if( timer_init( fpb, 2, 1e6/freq, 1, 7 ) == 0 )
    {
        return 0;
    }    

    if( oc_init( fpb, channel, 2, width_us, 3, 1, 6 ) == 0 )
    {
        return 0;
    }    
    
    return 1;
}    

void pwm_setwidth(unsigned char channel, unsigned int width_us)
{
    oc_set( channel, width_us );
}
