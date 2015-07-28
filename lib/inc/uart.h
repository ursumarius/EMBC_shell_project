/* ========================================================================== */
/* uart.h                                                                     */
/* ========================================================================== */
/* This module includes functions for controlling the UART modules.           */
/* ========================================================================== */
/* Requires:         UART1 and/or UART2                                       */
/*                   UART1 RX interrupt now set at priority level 1           */
/*                   UART2 RX interrupt now set at priority level 2           */
/* ========================================================================== */
/* author:           Ronnie Duisters                                          */
/* affiliation:      Fontys Hogescholen Engineering, Eindhoven                */
/* initial revision: 13-12-2012 (v1.0)                                        */
/* current version:  1.1                                                      */
/* changes:                                                                   */
/* ========================================================================== */

/* -------------------------------------------------------------------------- */
/* definitions.                                                               */
/* -------------------------------------------------------------------------- */
#define UART_BUFFSIZE                (8)         //The software rx buffer size

/* -------------------------------------------------------------------------- */
/* function prototypes.                                                       */
/* -------------------------------------------------------------------------- */

/* ========================================================================== */
/* function: uart_init( fpb, channel, baudrate, Ndatabits, Nstopbits,         */
/*                      parity );                                             */
/*                                                                            */
/* description: initialises UART1 for communication with the PC.              */
/*                                                                            */
/* pre:  fpb       - peripheral bus clock frequency in Hz                     */
/*       channel   - UART channel which is used for transmission (1 or 2)     */
/*       baudrate  - desired baudrate                                         */
/*       Ndatabits - number of databits (range: 8 or 9)                       */
/*       Nstopbits - number of stopbits (range: 1 or 2)                       */
/*       parity    - 0: no parity                                             */
/*                   1: even parity (only for 8 databits)                     */
/*                   2: odd parity (only for 8 databits)                      */
/*       int_onoff    - interrupt on (1) or off (0)                           */
/*       int_priority - interrupt priority (range 0...7)                      */ 
/*                                                                            */
/* post: return value - 0 if initialisation failed, 1 if succeeded            */
/* ========================================================================== */
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
);

/* ========================================================================== */
/* function: uart_sendchar( channel, data );                                  */
/*                                                                            */
/* description: transmits a data byte via the UART.                           */
/*                                                                            */
/* pre:  channel - UART channel which is used for transmission (1 or 2)       */
/*       data    - a byte of data to be sent                                  */
/*                                                                            */
/* post: none                                                                 */
/* ========================================================================== */
void uart_sendchar
(
    unsigned char channel,
    unsigned char data
);

/* ========================================================================== */
/* function: uart_sendstring( channel, data );                                */
/*                                                                            */
/* description: transmits a data byte via the UART.                           */
/*                                                                            */
/* pre:  channel - UART channel which is used for transmission (1 or 2)       */
/*       data    - the string to be transmitted                               */
/*                                                                            */
/* post: none                                                                 */
/* ========================================================================== */
void uart_sendstring
(
    unsigned char channel,
    unsigned char data[]
);

/* ========================================================================== */
/* function: uart_read( *data );                                              */
/*                                                                            */
/* description: reads a data byte from the rx data buffer.                    */
/*                                                                            */
/* pre:  channel - UART channel which is used for transmission (1 or 2)       */
/*       data    - pointer for storing the data byte that is read.            */
/*                                                                            */
/* post: return value - 1 if data was read from the buffer                    */
/*                      0 if the buffer was empty                             */
/* ========================================================================== */
unsigned char uart_read
(
    unsigned char channel,
    unsigned char *data
);
