#ifndef SERVO_H
#define SERVO_H 

/* ========================================================================== */
/* function: servo_init( fpb, channel, angle); */
/* */
/* description: initialises a servo channel. */
/* */
/* pre: fpb - peripheral bus clock frequency in Hz */
/* channel - number of the servo channel to initialise */
/* (range 1...5) */
/* angle - servo opening angle in degrees (range -45...45) */
/* */
/* post: return value - 0 if initialisation failed, 1 if succeeded */
/* ========================================================================== */
unsigned char servo_init
(
unsigned int fpb,
unsigned char channel,
signed char angle
);
/* ========================================================================== */
/* function: servo_setpos( fpb, channel, angle); */
/* */
/* description: changes the opening angle for a servo channel. */
/* */
/* pre: channel - number of the servo channel to set the position for */
/* (range 1...5) */
/* angle - servo opening angle in degrees (range -45...45) */
/* */
/* post: none */
/* ========================================================================== */
void servo_setpos
(
unsigned char channel,
signed char angle
);

#endif/*SERVO.H*/
