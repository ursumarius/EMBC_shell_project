/* ========================================================================== */
/* eeprom.h                                                                   */
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
/*                   library. More work needed.                               */
/* ========================================================================== */
 
#ifndef EEPROM_H
#define EEPROM_H

/* -------------------------------------------------------------------------- */
/* definitions.                                                               */
/* -------------------------------------------------------------------------- */
#define EEPROM_I2C_BUS      I2C2
#define EEPROM_I2C_ADDRESS  0x50

/* -------------------------------------------------------------------------- */
/* function prototypes.                                                       */
/* -------------------------------------------------------------------------- */

/* ========================================================================== */
/* function: eeprom_init( fpb );                                              */
/*                                                                            */
/* description: initialises the I2C bus for communicating with the EEPROM IC. */                                               
/*                                                                            */
/* pre:  fpb          - peripheral bus clock frequency in Hz                  */
/*                                                                            */
/* post: return value - 0 if initialisation failed, 1 if succeeded            */
/* ========================================================================== */
unsigned char eeprom_init(unsigned int fpb);

/* ========================================================================== */
/* function: eeprom_write( unsigned short int data );                         */
/*                                                                            */
/* description: writes an unsigned short int (16 bits) to the EEPROM.         */
/*                                                                            */
/* precondition: the eeprom module must have been initialised.                */
/*                                                                            */
/* pre:  data         - data byte to be written                               */
/*                                                                            */
/* post: return value - 0 if write failed, 1 if succeeded                     */
/* ========================================================================== */
unsigned char eeprom_write(unsigned short int address, unsigned short int data);

/* ========================================================================== */
/* function: eeprom_read( unsigned short int *data );                         */
/*                                                                            */
/* description: reads an unsigned short int (16 bits) from the EEPROM.        */
/*                                                                            */
/* precondition: the eeprom module must have been initialised.                */
/*                                                                            */
/* pre:  data         - pointer to an unsigned short int in which the read    */
/*                      data will be written                                  */
/*                                                                            */
/* post: return value - 0 if write failed, 1 if succeeded                     */
/* ========================================================================== */
unsigned char eeprom_read(unsigned short int address, unsigned short int *data);

#endif /* EEPROM_H */
