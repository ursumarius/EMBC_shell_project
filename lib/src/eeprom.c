/* ========================================================================== */
/* eeprom.c                                                                   */
/* ========================================================================== */
/* This module includes functions for setting up and controlling the EEPROM   */
/* IC (24LC256) on the Cerebot board , which is connected to the I2C2 bus.    */
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
/*                   library. More work needed to remove all I2C plib-related */
/*                   I2C commands.                                            */
/* ========================================================================== */

#include <plib.h>
#include "eeprom.h"
#include "i2c.h"

unsigned char eeprom_init(unsigned int fpb)
{
    i2c_init( fpb, EEPROM_I2C_BUS );
}

unsigned char eeprom_write(unsigned short int address, unsigned short int data)
{
    unsigned char     i2cData[5];
    I2C_7_BIT_ADDRESS SlaveAddress;
    int               Index;
    int               DataSz;
    unsigned char     Acknowledged;
    unsigned char     Success = 1;
    unsigned char     i2cbyte;	
	unsigned char 	  DataB[sizeof(unsigned short int)];
	
	if( address > 32e3 )
	{
    	return 0;
    }   
	
	memcpy( DataB, &data, sizeof(unsigned short int) );

    //
    // Send the data to EEPROM to program one location
    //

    // Initialize the data buffer
    I2C_FORMAT_7_BIT_ADDRESS(SlaveAddress, EEPROM_I2C_ADDRESS, I2C_WRITE);
    i2cData[0] = SlaveAddress.byte;
    i2cData[1] = (address >> 8);       // EEPROM location to program (high address byte)
    i2cData[2] = (address & 0xFF);     // EEPROM location to program (low address byte)
    i2cData[3] = DataB[1];             // Data to write MSB
    i2cData[4] = DataB[0];             // Data to write LSB
    DataSz = 5;

    // Start the transfer to write data to the EEPROM
    if( !i2c_starttransfer(0, EEPROM_I2C_BUS) )
    {
        return 0;
    }

    // Transmit all data
    Index = 0;
    while( Success && (Index < DataSz) )
    {
        // Transmit a byte
        if (i2c_transmitonebyte(i2cData[Index], EEPROM_I2C_BUS))
        {
            // Advance to the next byte
            Index++;

            // Verify that the byte was acknowledged
            if( !I2CByteWasAcknowledged( EEPROM_I2C_BUS ) )
            {
                  Success = 0;
            }
        }
        else
        {
            Success = 0;
        }
    }

    // End the transfer (hang here if an error occured)
    i2c_stoptransfer( EEPROM_I2C_BUS );
    if( !Success )
    {
        return 0;
    }


    // Wait for EEPROM to complete write process, by polling the ack status.
    Acknowledged = 0;
    do
    {
        // Start the transfer to address the EEPROM
        if( !i2c_starttransfer( 0, EEPROM_I2C_BUS ) )
        {
        	return 0;
        }
        
        // Transmit just the EEPROM's address
        if (i2c_transmitonebyte(SlaveAddress.byte, EEPROM_I2C_BUS))
        {
            // Check to see if the byte was acknowledged
            Acknowledged = I2CByteWasAcknowledged(EEPROM_I2C_BUS);
        }
        else
        {
            Success = 0;
        }

        // End the transfer (stop here if an error occured)
        i2c_stoptransfer(EEPROM_I2C_BUS);
        if(!Success)
        {
        	return 0;
        }

    } while (Acknowledged != 1);
	
	return 1;
}

unsigned char eeprom_read(unsigned short int address, unsigned short int *data)
{
    unsigned char      i2cData[3];
    I2C_7_BIT_ADDRESS  SlaveAddress;
    int                Index;
    int                DataSz;
    unsigned char      Acknowledged;
    unsigned char      Success = 1;
    unsigned char      HighB,LowB;

	if( address > 32e3 )
	{
    	return 0;
    }   

    //
    // Read the data back from the EEPROM.
    //

    // Initialize the data buffer
    I2C_FORMAT_7_BIT_ADDRESS(SlaveAddress, EEPROM_I2C_ADDRESS, I2C_WRITE);
    i2cData[0] = SlaveAddress.byte;
    i2cData[1] = (address >> 8);       // EEPROM location to program (high address byte)
    i2cData[2] = (address & 0xFF);     // EEPROM location to program (low address byte)
    DataSz = 3;
    
    // Start the transfer to read the EEPROM.
    if( !i2c_starttransfer(0, EEPROM_I2C_BUS) )
    {
        return 0;
    }
    
    // Address the EEPROM.
    Index = 0;
    while( Success & (Index < DataSz) )
    {
        // Transmit a byte
        if (i2c_transmitonebyte(i2cData[Index], EEPROM_I2C_BUS))
        {
            // Advance to the next byte
            Index++;
        }
        else
        {
            Success = 0;
        }

        // Verify that the byte was acknowledged
        if(!I2CByteWasAcknowledged(EEPROM_I2C_BUS))
        {
            Success = 0;
        }
    }

    // Restart and send the EEPROM's internal address to switch to a read transfer
    if(Success)
    {
        // Send a Repeated Started condition
        if( !i2c_starttransfer(1, EEPROM_I2C_BUS) )
        {
        	return 0;
        }

        // Transmit the address with the READ bit set
        I2C_FORMAT_7_BIT_ADDRESS(SlaveAddress, EEPROM_I2C_ADDRESS, I2C_READ);
        if (i2c_transmitonebyte(SlaveAddress.byte, EEPROM_I2C_BUS))
        {
            // Verify that the byte was acknowledged
            if(!I2CByteWasAcknowledged(EEPROM_I2C_BUS))
            {
                Success = 0;
            }
        }
        else
        {
            Success = 0;
        }
    }

    // Read the data from the desired address
    if( Success )
    {
        if( i2c_receiveonebyte( &HighB, EEPROM_I2C_BUS, 1 ) )
        {
		    if( i2c_receiveonebyte( &LowB, EEPROM_I2C_BUS, 0 ) )
		    {
			    *data = (HighB << 8) | LowB;
		    }
		}
    }

    // End the transfer (stop here if an error occured)
    i2c_stoptransfer( EEPROM_I2C_BUS );
    if( !Success )
    {
        return 0;
    }

    // Read complete
	return 1;
}
