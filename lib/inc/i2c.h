/* ========================================================================== */
/* i2c.h                                                                      */
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

#ifndef I2C_H
#define I2C_H

/* -------------------------------------------------------------------------- */
/* definitions.                                                               */
/* -------------------------------------------------------------------------- */
#define I2C_CLOCK_FREQ 5e3

/* -------------------------------------------------------------------------- */
/* function prototypes.                                                       */
/* -------------------------------------------------------------------------- */

/* ------------------------------------------------------------ 
**	Function:
**		unsigned char I2Cinit( I2C_MODULE I2C_BUS )
**
**  Summary:
** 		Configures the given I2C bus.
**
** 	Description:
** 		This routine initializes the I2C bus for making it posible to connect with an other
**		peripherals.
**
**	Precondition:
**		none.
**
**	Parameters:
**		I2C_BUS - This must be a I2C_MODULE corect I2C bus (I2C1, I2C2, etc.)
**
**	Returns:
**		TRUE    - If successful
**		FALSE   - If the I2C did not initialize.
**
**	Example:
**		<code>
**		I2Cinit(I2C1);
**		</code>
**
**	Remarks:
**		none.
*/
unsigned char i2c_init(unsigned int fpb, I2C_MODULE I2C_BUS);

/* ------------------------------------------------------------ 
**	Function:
**		unsigned char i2c_starttransfer( unsigned char restart )
**
**  Summary:
**    Starts (or restarts) a transfer to/from the EEPROM.
**
** 	Description:
** 		This routine starts (or restarts) a transfer to/from the SRF08 waiting (in
**		a blocking loop) until the start (or re-start) condition has completed.
**
**	Precondition:
**		The I2C module must have been initialized.
**
**	Parameters:
**		restart - If FALSE, send a "Start" condition
**				- If TRUE, send a "Restart" condition
**
**	Returns:
**		TRUE    - If successful
**		FALSE   - If a collision occured during Start signaling
**
**	Example:
**		<code>
**		i2c_starttransfer(FALSE);
**		</code>
**
**	Remarks:
**		This is a blocking routine that waits for the bus to be idle and the Start
**		(or Restart) signal to complete.
*/
unsigned char i2c_starttransfer(unsigned char restart, I2C_MODULE I2C_BUS);

/* ------------------------------------------------------------ 
**  Function:
**  	unsigned char i2c_transmitonebyte( unsigned char data )
**
**	Summary:
**    	This transmits one byte to the EEPROM.
**
** 	Description:
**    	This transmits one byte to the EEPROM, and reports errors for any bus
**    	collisions.
**
**  Precondition:
**    	The transfer must have been previously started.
**
**	Parameters:
**	  	data    - Data byte to transmit
**	
**	Returns:
**		TRUE    - Data was sent successfully
**		FALSE   - A bus collision occured
**	
**	Example:
**		<code>
**		i2c_transmitonebyte(0xAA);
**		</code>
**	
**	Remarks:
**	  	This is a blocking routine that waits for the transmission to complete.
*/
unsigned char i2c_transmitonebyte(unsigned char data, I2C_MODULE I2C_BUS);

/* ------------------------------------------------------------ 
**	Function:
**		Bool i2c_receiveonebyte( unsigned char address, unsigned char *data, unsigned char AckNack )
**
**  Summary:
*/
unsigned char i2c_receiveonebyte(unsigned char *data, I2C_MODULE I2C_BUS, unsigned char AckNack);

/* ------------------------------------------------------------ 
**	Function:
**		void i2c_stoptransfer( void )
**
**	Summary:
**		Stops a transfer to/from the EEPROM.
**
**	Description:
**		This routine Stops a transfer to/from the EEPROM, waiting (in a 
**		blocking loop) until the Stop condition has completed.
**
**	Precondition:
**		The I2C module must have been initialized & a transfer started.
**
**	Parameters:
**		None.
**
**	Returns:
**		None.
**
**	Example:
**		<code>
**		i2c_stoptransfer();
**		</code>
**
**	Remarks:
**		This is a blocking routine that waits for the Stop signal to complete.
*/
void i2c_stoptransfer(I2C_MODULE I2C_BUS);

#endif /* I2C_H */
