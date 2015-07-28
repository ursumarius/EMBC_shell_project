/* ========================================================================== */
/* uart.c                                                                     */
/* ========================================================================== */
/* This module includes functions for controlling the UART modules.           */
/* ========================================================================== */
/* Requires:         UART1 and/or UART2                                       */
/*                   UART1 RX interrupt at priority level 1                   */
/*                   UART2 RX interrupt at priority level 1                   */
/* ========================================================================== */
/* author:           Ronnie Duisters                                          */
/* affiliation:      Fontys Hogescholen Engineering, Eindhoven                */
/* initial revision: 13-12-2012 (v1.0)                                        */
/* current version:  1.1                                                      */
/* changes:                                                                   */
/* ========================================================================== */

#include <p32xxxx.h>
#include <plib.h>
#include <stdlib.h>
#include <string.h>
#include "uart.h"

/* -------------------------------------------------------------------------- */
/* global variables.                                                          */
/* -------------------------------------------------------------------------- */
unsigned char buffer[2][UART_BUFFSIZE];
unsigned char buffwrpos[2];
unsigned char buffrdpos[2];

/* -------------------------------------------------------------------------- */
/* interrupt service routines.                                                */
/* -------------------------------------------------------------------------- */

/* ========================================================================== */
/* Receive interrupt service routine                                          */
/* UART 1 interrupt handler is set at priority level 1                        */
/* ========================================================================== */
void __ISR(_UART1_VECTOR, ipl1) IntUart1Handler(void)
{	
	buffer[0][buffwrpos[0]++] = U1RXREG;  // Read value in buffer
	if( buffwrpos[0] == UART_BUFFSIZE )     // Update read buffer
	{
    	buffwrpos[0] = 0;
    }    	
	IFS0CLR = 0x8000000;           // Clear interrupt flag
}

/* ========================================================================== */
/* Receive interrupt service routine                                          */
/* UART 2 interrupt handler is set at priority level 2                        */
/* ========================================================================== */
void __ISR(_UART2_VECTOR, ipl2) IntUart2Handler(void)
{	
	buffer[1][buffwrpos[1]++] = U2RXREG;  // Read value in buffer
	if( buffwrpos[1] == UART_BUFFSIZE )     // Update read buffer
	{
    	buffwrpos[1] = 0;
    }    	
	IFS1CLR = 0x200;           // Clear interrupt flag
}

/* -------------------------------------------------------------------------- */
/* exported function implementations.                                         */
/* -------------------------------------------------------------------------- */
unsigned char uart_init
(
    unsigned int  fpb, 
    unsigned char channel,  
    unsigned int  baudrate,
    unsigned char Ndatabits,
    unsigned char Nstopbits,
    unsigned char parity,
    unsigned char int_onoff,
    unsigned char int_priority
)
{
    
    if( ( Ndatabits < 8 || Ndatabits > 9 ) ||
        ( Nstopbits > 2 || parity > 2 ) )
    {
        return 0;
    }    
    
    switch( channel )
    {
        case 1:
            buffwrpos[0] = 0;
            buffrdpos[0] = 0;
            U1BRG = (fpb / (16 * baudrate)) - 1; // Set Baud rate
            U1STA = 0;    
            
            U1MODE = 0;           
            if( Ndatabits == 8 )
            {
                if( parity == 1 )
                {
                    U1MODESET = 2;
                }
                else if( parity == 2 )
                {
                    U1MODESET = 4;
                }        
            }    
            else
            {
                U1MODESET = 6;
            }    
            
            if( Nstopbits == 2 )
            {
                U1MODESET = 1;         // 2 stop bits
            }    
            U1MODESET = 0x8000;        // Enable UART1
    
            if( int_onoff )
            {
                IFS0CLR = 0x8000000;           // Clear interrupt flag
                IEC0SET = 0x8000000;           // Enable receive interrupt
                IPC6SET = (int_priority << 2); // Set interrupt priority level
            }
            
            U1STASET = 0x1400;         // Enable Transmit and Receive
            break;
            
        case 2:
            buffwrpos[1] = 0;
            buffrdpos[1] = 0;
            U2BRG = (fpb / (16 * baudrate)) - 1; // Set Baud rate
            U2STA = 0;    
            
            U2MODE = 0;           
            if( Ndatabits == 8 )
            {
                if( parity == 1 )
                {
                    U2MODESET = 2;
                }
                else if( parity == 2 )
                {
                    U2MODESET = 4;
                }        
            }    
            else
            {
                U2MODESET = 6;
            }    
            
            if( Nstopbits == 2 )
            {
                U2MODESET = 1;         // 2 stop bits
            }    
            U2MODESET = 0x8000;        // Enable UART2
                
            if( int_onoff )
            {
                IFS1CLR = 0x200;               // Clear interrupt flag
                IEC1SET = 0x200;               // Enable receive interrupt
                IPC8SET = (int_priority << 2); // Set interrupt priority level
            }
            
            U2STASET = 0x1400;      // Enable Transmit and Receive
            break;
        
        default:
            return 0;            
    }
    
    return 1;        
}	


void uart_sendchar(unsigned char channel, unsigned char data)
{
    switch( channel )
    {
        case 1:        
            while( U1STA & 0x200 )  // wait if transmit buffer is full
            {
            }
            
            U1TXREG = data;         // put data in transmit register
            break;
           
        case 2:
            while( U2STA & 0x200 )  // wait if transmit buffer is full
            {
            }
            
            U2TXREG = data;         // put data in transmit register
            break;
        
        default: 
            break;            
    }        
}


void uart_sendstring(unsigned char channel, unsigned char data[])
{
    unsigned char c1 = 0;
    
    while( data[c1] != 0 )
    {
        uart_sendchar( channel, data[c1] );
        c1++;
    }
}


unsigned char uart_read(unsigned char channel, unsigned char *data)
{
	if( buffrdpos[channel-1] != buffwrpos[channel-1] )
	{
    	*data = buffer[channel-1][buffrdpos[channel-1]++];
    	if( buffrdpos[channel-1] == UART_BUFFSIZE )
    	{
        	buffrdpos[channel-1] = 0;
        }   	
		return 1;		
	}
	else 
	{
    	return 0;
    }   
}
