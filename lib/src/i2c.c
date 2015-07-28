/* ========================================================================== */
/* i2c.c                                                                      */
/* ========================================================================== */
/* This module includes functions for setting up and controlling the I2C      */
/* channels of the PIC32 microcontroller.                                     */
/* ========================================================================== */
/* Requires:         I2C1 and/or I2C2                                         */
/* ========================================================================== */
/* author:           Rob van Eldijk                                           */
/* affiliation:      Fontys Hogescholen Engineering, Eindhoven                */
/* library:          embc (Embedded Connectivity)                             */
/* initial revision: 2-3-2012 (v1.0)                                          */
/* current version:  1.1                                                      */
/* changes:          24-01-2013 (v1.1) Ronnie Duisters                        */
/*                   Changed the code and layout to match the new embc        */
/*                   library. More work needed.                               */
/* ========================================================================== */

#include <plib.h>
#include "i2c.h"

unsigned char i2c_init(unsigned int fpb, I2C_MODULE I2C_BUS)
{
	unsigned int actualClock;

    // Set the I2C baudrate
    actualClock = I2CSetFrequency( I2C_BUS, fpb, I2C_CLOCK_FREQ );
    
    if ( abs(actualClock-I2C_CLOCK_FREQ) > I2C_CLOCK_FREQ/10 )
    {
        return 0;
    }

    // Enable the I2C bus
    I2CEnable( I2C_BUS, 1 );

	return 1;
}

unsigned char i2c_starttransfer(unsigned char restart, I2C_MODULE I2C_BUS)
{
	I2C_STATUS status;

 	// Send the Start (or Restart) signal
    if( restart )
    {
        I2CRepeatStart( I2C_BUS );
    }
    else
    {
        // Wait for the bus to be idle, then start the transfer
        while( !I2CBusIsIdle( I2C_BUS ) );
		
        if( I2CStart( I2C_BUS ) != I2C_SUCCESS )
        {
            #ifdef PIC32_STARTER_KIT
				DBPRINTF("Error: Bus collision during transfer Start\n");
			#endif
        }
    }

    // Wait for the signal to complete
    do
    {
        status = I2CGetStatus(I2C_BUS);

    } while ( !(status & I2C_START) );

}

unsigned char i2c_transmitonebyte(unsigned char data,I2C_MODULE I2C_BUS)
{
    // Wait for the transmitter to be ready
    while( !I2CTransmitterIsReady( I2C_BUS ) );

    // Transmit the byte
    if( I2CSendByte( I2C_BUS, data ) == I2C_MASTER_BUS_COLLISION )
    {
        #ifdef PIC32_STARTER_KIT
			DBPRINTF("Error: I2C Master Bus Collision\n");
		#endif

        return 0;
    }

    // Wait for the transmission to finish
	while( !I2CTransmissionHasCompleted(I2C_BUS) );

    return 1;
}

unsigned char i2c_receiveonebyte(unsigned char *data, I2C_MODULE I2C_BUS, unsigned char AckNack)
{
	if(I2CReceiverEnable(I2C_BUS, 1) == I2C_RECEIVE_OVERFLOW)
	{
	  	#ifdef PIC32_STARTER_KIT  
			DBPRINTF("Error: I2C Receive Overflow\n");
		#endif
	
	    return 0;
	}
	else
	{
		while( !I2CReceivedDataIsAvailable( I2C_BUS ) );
		
		// With this line, and without last line, it doesn't work 
	    I2CAcknowledgeByte( I2C_BUS, AckNack );       // ACK or NAK

		*data = I2CGetByte(I2C_BUS);

		if( I2C_BUS == I2C1 ) 
		{
    		IdleI2C1();
        }  		
		else 
		{
    		IdleI2C2();
        }  				
	
		return 1; 		 	
	}
}	

void i2c_stoptransfer(I2C_MODULE I2C_BUS)
{
    I2C_STATUS status;

    // Send the Stop signal
    I2CStop( I2C_BUS );

    // Wait for the signal to complete
    do
    {
        status = I2CGetStatus( I2C_BUS );

    } while ( !(status & I2C_STOP) );
}
