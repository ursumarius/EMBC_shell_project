/* ========================================================================== */
/* oc.c                                                                       */
/* ========================================================================== */
/* This module includes functions for setting up and adjusting the output     */
/* compare units.                                                             */
/* ========================================================================== */
/* Requires:         OC1,2,3,4 and/or 5                                       */
/* ========================================================================== */
/* author:           Ronnie Duisters                                          */
/* affiliation:      Fontys Hogescholen Engineering, Eindhoven                */
/* library:          embc (Embedded Connectivity)                             */
/* initial revision: 24-01-2013 (v1.0)                                        */
/* current version:  1.0                                                      */
/* changes:                                                                   */
/* ========================================================================== */

#include <p32xxxx.h>
#include <plib.h>
#include "oc.h"

/* -------------------------------------------------------------------------- */
/* global variables.                                                          */
/* -------------------------------------------------------------------------- */
unsigned int factor; /* !! this is going to cause problems as we are using */
                     /* multiple oc's with either counter 2 or 3           */
                     /* -> fix with struct.                                */
OC1callback OC1callbackfp;
unsigned char OC1callbackflag = 0;

/* -------------------------------------------------------------------------- */
/* local function prototypes.                                                 */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* functions.                                                                 */
/* -------------------------------------------------------------------------- */
unsigned char oc_init(
    unsigned int fpb,
    unsigned char number,
    unsigned char coupled_timer,
    unsigned int time_us,
    unsigned char mode,
    unsigned char int_onoff,
    unsigned char int_priority)
{   
    unsigned int prescalerx[] = {1, 2, 4, 8, 16, 32, 64, 256};
    unsigned char psvalue = 0;
    
    /* ********************************************************************** */
    /* return a 0 for erroneous parameter values.                             */
    /* ********************************************************************** */
    if( ( number < 1 || number > 5 ) ||
        ( coupled_timer < 2 || coupled_timer > 3 ) ||
        ( int_onoff > 1 ) || ( int_priority > 7 ) )
    {
        return 0;
    }        

    switch( number )
    {
        case 1:        
            OC1CON = 0;          /* turn module off */
            OC1CONSET = mode;    /* set mode */
            if( coupled_timer == 3 )
            {
                OC1CONSET = 0x8; /* set timer 3 as timer source */
                psvalue = ((T3CON & 0x70) >> 4);
            }
            else
            {
                psvalue = ((T2CON & 0x70) >> 4);
            }    

            if( int_onoff )
            {
                IFS0CLR = 0x40;
                IPC1SET = ( int_priority << 18 );
                IEC0SET = 0x40;
            }    
                      
            factor = ((fpb / 1e6) / prescalerx[psvalue]);
            OC1R = factor * time_us;          
            OC1CONSET = 0x8000; /* turn module on */            
            break;
            
        case 2:
            OC2CON = 0;          /* turn module off */
            OC2CONSET = mode;    /* set mode */
            if( coupled_timer == 3 )
            {
                OC2CONSET = 0x8; /* set timer 3 as timer source */
                psvalue = ((T3CON & 0x70) >> 4);
            }
            else
            {
                psvalue = ((T2CON & 0x70) >> 4);
            }    

            if( int_onoff )
            {
                IFS0CLR = 0x400;
                IPC2SET = ( int_priority << 18 );
                IEC0SET = 0x400;
            }    
                      
            factor = ((fpb / 1e6) / prescalerx[psvalue]);
            OC2R = factor * time_us;          
            OC2CONSET = 0x8000; /* turn module on */            
            break;

        case 3:
            OC3CON = 0;          /* turn module off */
            OC3CONSET = mode;    /* set mode */
            if( coupled_timer == 3 )
            {
                OC3CONSET = 0x8; /* set timer 3 as timer source */
                psvalue = ((T3CON & 0x70) >> 4);
            }
            else
            {
                psvalue = ((T2CON & 0x70) >> 4);
            }    

            if( int_onoff )
            {
                IFS0CLR = 0x4000;
                IPC3SET = ( int_priority << 18 );
                IEC0SET = 0x4000;
            }    
                      
            factor = ((fpb / 1e6) / prescalerx[psvalue]);
            OC3R = factor * time_us;          
            OC3CONSET = 0x8000; /* turn module on */            
            break;

        case 4:
            OC4CON = 0;          /* turn module off */
            OC4CONSET = mode;    /* set mode */
            if( coupled_timer == 3 )
            {
                OC4CONSET = 0x8; /* set timer 3 as timer source */
                psvalue = ((T3CON & 0x70) >> 4);
            }
            else
            {
                psvalue = ((T2CON & 0x70) >> 4);
            }    

            if( int_onoff )
            {
                IFS0CLR = 0x40000;
                IPC4SET = ( int_priority << 18 );
                IEC0SET = 0x40000;
            }    
                      
            factor = ((fpb / 1e6) / prescalerx[psvalue]);
            OC4R = factor * time_us;          
            OC4CONSET = 0x8000; /* turn module on */            
            break;

        case 5:
            OC5CON = 0;          /* turn module off */
            OC5CONSET = mode;    /* set mode */
            if( coupled_timer == 3 )
            {
                OC5CONSET = 0x8; /* set timer 3 as timer source */
                psvalue = ((T3CON & 0x70) >> 4);
            }
            else
            {
                psvalue = ((T2CON & 0x70) >> 4);
            }    

            if( int_onoff )
            {
                IFS0CLR = 0x400000;
                IPC5SET = ( int_priority << 18 );
                IEC0SET = 0x400000;
            }    
                      
            factor = ((fpb / 1e6) / prescalerx[psvalue]);
            OC5R = factor * time_us;          
            OC5CONSET = 0x8000; /* turn module on */            
            break;

        default:
            return 0;
            break;
    }   
    
    return 1;
}    

void oc_set(unsigned char number, unsigned int time_us)
{
    switch( number )
    {
        case 1:
            OC1R = factor * time_us;          
            break;
            
        case 2:
            OC2R = factor * time_us;          
            break;

        case 3:
            OC3R = factor * time_us;          
            break;

        case 4:
            OC4R = factor * time_us;          
            break;

        case 5:
            OC5R = factor * time_us;          
            break;

        default:
            break;
    }    
}


/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* interrupt service routines.                                                */
/* -------------------------------------------------------------------------- */
/* example interrupt service routine */
void __ISR( _OUTPUT_COMPARE_1_VECTOR, ipl6 ) OC1InterruptHandler( void )
{
	if(OC1callbackflag == 1)
	{
		OC1callbackfp();
	}
 	IFS0CLR = 0x40;
} 
/* -------------------------------------------------------------------------- */

void timer_register_OC1callback(OC1callback ptr_OC1callback)
{
	OC1callbackfp = ptr_OC1callback;
	OC1callbackflag = 1;
}  

