/* ========================================================================== */
/* timer.c                                                                    */
/* ========================================================================== */
/* This module includes functions for setting up the timer units of the PIC32.*/
/* ========================================================================== */
/* Requires:         TIMER1,2,3,4 and/or 5                                    */
/* ========================================================================== */
/* author:           Ronnie Duisters                                          */
/* affiliation:      Fontys Hogescholen Engineering, Eindhoven                */
/* library:          embc (Embedded Connectivity)                             */
/* initial revision: 02-01-2013 (v1.0)                                        */
/* current version:  1.0                                                      */
/* changes:          
/* ========================================================================== */

#include <p32xxxx.h>
#include <plib.h>
#include "timer.h"

/* -------------------------------------------------------------------------- */
/* global variables.                                                          */
/* -------------------------------------------------------------------------- */
unsigned int prescaler1[] = {1, 8, 64, 256};
unsigned int ps1length = 4;
unsigned int prescalerx[] = {1, 2, 4, 8, 16, 32, 64, 256};
unsigned int psxlength = 8;

T2callback T2callbackfp;
unsigned char T2callbackflag = 0;

/* -------------------------------------------------------------------------- */
/* local function prototypes.                                                 */
/* -------------------------------------------------------------------------- */
unsigned char getprescalerx
(
   unsigned int fpb,
   unsigned int time_us,
   unsigned char *ps
);


/* -------------------------------------------------------------------------- */
/* exported functions.                                                        */
/* -------------------------------------------------------------------------- */
unsigned char timer_init(unsigned int fpb, unsigned char channel,unsigned int time_us, unsigned char int_onoff, unsigned char int_priority)
{   
    unsigned char c1 = 0;
    
    /* ********************************************************************** */
    /* return a 0 for erroneous parameter values.                             */
    /* ********************************************************************** */
    if( ( channel < 1 || channel > 5 ) ||
        ( int_onoff > 1 ) ||
        ( int_priority > 7 ) )
    {
        return 0;
    }        

    switch( channel )
    {
        case 1:
            T1CON = 0;
            TMR1 = 0;
            while( (((fpb / 1e6) / prescaler1[c1]) * time_us - 1) > 65535 )
            {
                c1++;
                if( c1 > ps1length )
                {
                    return 0;
                }
            }
            T1CONSET = ( c1 << 4 );                         /* set prescaler */
            PR1 = ((fpb / 1e6) / prescaler1[c1]) * time_us - 1; /* set value */
            
            if( int_onoff )
            {
                IFS0CLR = 0x10;
                IPC1SET = (int_priority << 2);
                IEC0SET = 0x10;
            }    

            T1CONSET = 0x8000;                              /* switch timer on */
            break;
            
        case 2:
            T2CON = 0;
            TMR2 = 0;
            if( !(getprescalerx( fpb, time_us, &c1 )) )
            {
                return 0;
            }
            T2CONSET = ( c1 << 4 );                         /* set prescaler */
            PR2 = ((fpb / 1e6) / prescalerx[c1]) * time_us - 1; /* set value */
            
            if( int_onoff )
            {
                IFS0CLR = 0x100;
                IPC2SET = (int_priority << 2);
                IEC0SET = 0x100;
            }    

            T2CONSET = 0x8000;                              /* switch timer on */
            break;

        case 3:
            T3CON = 0;
            TMR3 = 0;
            if( !(getprescalerx( fpb, time_us, &c1 )) )
            {
                return 0;
            }
            T3CONSET = ( c1 << 4 );                         /* set prescaler */
            PR3 = ((fpb / 1e6) / prescalerx[c1]) * time_us - 1; /* set value */
            
            if( int_onoff )
            {
                IFS0CLR = 0x1000;
                IPC3SET = (int_priority << 2);
                IEC0SET = 0x1000;
            }    
            
            T3CONSET = 0x8000;                              /* switch timer on */
            break;

        case 4:
            T4CON = 0;
            TMR4 = 0;
            if( !(getprescalerx( fpb, time_us, &c1 )) )
            {
                return 0;
            }
            T4CONSET = ( c1 << 4 );                         /* set prescaler */
            PR4 = ((fpb / 1e6) / prescalerx[c1]) * time_us - 1; /* set value */
           
            if( int_onoff )
            {
                IFS0CLR = 0x10000;
                IPC4SET = (int_priority << 2);
                IEC0SET = 0x10000;
            }    
            
            T4CONSET = 0x8000;                              /* switch timer on */
            break;

        case 5:
            T5CON = 0;
            TMR5 = 0;
            if( !(getprescalerx( fpb, time_us, &c1 )) )
            {
                return 0;
            }
            T5CONSET = ( c1 << 4 );                         /* set prescaler */
            PR5 = ((fpb / 1e6) / prescalerx[c1]) * time_us - 1; /* set value */
            
            if( int_onoff )
            {
                IFS0CLR = 0x100000;
                IPC5SET = (int_priority << 2);
                IEC0SET = 0x100000;
            }    
            
            T5CONSET = 0x8000;                              /* switch timer on */
            break;

        default:
            return 0;
            break;
    }   
    
    return 1;
}    

/* -------------------------------------------------------------------------- */
/* local functions.                                                           */
/* -------------------------------------------------------------------------- */
unsigned char getprescalerx(unsigned int fpb, unsigned int time_us, unsigned char *ps)
{
    *ps = 0;
    
    while( (((fpb / 1e6) / prescalerx[(*ps)]) * time_us - 1) > 65535 )
    {
        (*ps)++;
        if( (*ps) > psxlength )
        {
            return 0;
        }
    }
    return 1;
}



/* -------------------------------------------------------------------------- */
/* interrupt service routines.                                                */
/* -------------------------------------------------------------------------- */
/* example interrupt service routine */
void __ISR( _TIMER_2_VECTOR, ipl7 ) T2InterruptHandler( void )
{	
	if(T2callbackflag == 1)
	{
		T2callbackfp();
	}
    IFS0CLR = 0x100;
}

void timer_register_T2callback(T2callback ptr_T2callback)
{
	T2callbackfp = ptr_T2callback;
	T2callbackflag = 1;
}    
