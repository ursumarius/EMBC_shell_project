/* ========================================================================== */
/* oc.h                                                                       */
/* ========================================================================== */
/* This module includes functions for setting up and adjusting the output     */
/* compare units.                                                             */
/* ========================================================================== */
/* Requires:         OC1,2,3,4 and/or 5                                       */
/* ========================================================================== */
/* author:           Ronnie Duisters                                          */
/* affiliation:      Fontys Hogescholen Engineering, Eindhoven                */
/* initial revision: 11-10-2011 (v1.0)                                        */
/* current version:  1.0                                                      */
/* changes:                                                                   */
/* ========================================================================== */

#ifndef OC_H
#define OC_H

/* -------------------------------------------------------------------------- */
/* definitions.                                                               */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* function prototypes.                                                       */
/* -------------------------------------------------------------------------- */

/* ========================================================================== */
/* function: oc_init( fpb, number, coupled_timer, time_us, mode, int_onoff,   */ 
/*                    int_priority );                                         */
/*                                                                            */
/* description: initialises one of the 5 output compare units of the PIC32    */
/*              microcontroller.                                              */
/*                                                                            */
/* pre:  fpb           - peripheral bus clock frequency in Hz                 */
/*       number        - number of the output compare unit to initialise      */
/*                       (range 1...5)                                        */
/*       coupled_timer - timer coupled to the output compare unit (2 or 3)    */
/*       time_us       - time value in microseconds to which the output       */ 
/*                       compare unit will compare the connected timer        */
/*       mode          - operation mode of the output compare unit            */ 
/*                       (range 0 to 7)                                       */
/*       int_onoff     - interrupt on (1) or off (0)                          */
/*       int_priority  - interrupt priority (range 0...7)                     */ 
/*                                                                            */
/* post: return value  - 0 if initialisation failed, 1 if succeeded           */
/* ========================================================================== */
unsigned char oc_init
(
    unsigned int fpb,
    unsigned char number,
    unsigned char coupled_timer,
    unsigned int time_us,
    unsigned char mode,
    unsigned char int_onoff,
    unsigned char int_priority
);

/* ========================================================================== */
/* function: oc_set( number, time_us );                                       */
/*                                                                            */
/* description: changes the compare time value for a specific output compare  */
/*              unit.                                                         */
/*                                                                            */
/* pre:  number        - number of the output compare unit to set             */
/*                       (range 1...5)                                        */
/*       time_us       - time value in microseconds to which the output       */ 
/*                       compare unit will compare the connected timer        */
/*                                                                            */
/* post: none                                                                 */
/* ========================================================================== */
void oc_set
(
    unsigned char number,
    unsigned int time_us
);

/*----------------------------------------------------------------------------*/
/*creation of callback function.
/*----------------------------------------------------------------------------*/
typedef void(*OC1callback)(void);
void timer_register_OC1callback(OC1callback ptr_OC1callback);
    
#endif /* OC_H */
