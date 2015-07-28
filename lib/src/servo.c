#include"servo.h"
#include"pwm.h"
#include<p32xxxx.h>//Against the architecture
#include<plib.h>
#include"timer.h"
#include"oc.h"
void servo_T2callback()
{
	PORTG = 0x1000;
}
void servo_OC1callback()
{
	PORTG = 0x0;
}
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
unsigned char servo_init(unsigned int fpb, unsigned char channel, signed char angle)
{	
	int pulse = 20;//pulse cycle in ms
	int freq = 1000/pulse;//pwm frequency
	int width_us = 1500 + (40/3) * angle;//Converting angle to pulse width
	TRISG = 0;
	timer_register_T2callback(servo_T2callback);
	timer_register_OC1callback(servo_OC1callback);
	if(pwm_init(fpb, channel, freq, width_us))
		return 1;
	else
		return 0;
}

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
void servo_setpos(unsigned char channel, signed char angle)
{
	int width_us = 1500 + (40/3) * angle;//Converting angle to pulse width
	pwm_setwidth(channel, width_us);
	timer_register_T2callback(servo_T2callback);
	timer_register_OC1callback(servo_OC1callback);
}

