#include <p32xxxx.h>
#include <plib.h>
#include "button.h"
#define BUTTON1 (PORTA & 0x40)
#define BUTTON2 (PORTA & 0x80)
#define DEBOUNCE_TIME 100

unsigned int PREV_BUTTON1= 0, PREV_BUTTON2 = 0;
void button_timer_init1()
{
	TMR3 = 0;
	PR3 = 10000;
	T3CON = 0x8000;
}
void button_timer_init2()
{
	TMR4 = 0;
	PR4 = 10000;
	T4CON = 0x8000;
}

int debouncebutton1()
{
	button_timer_init1();
	
	if((BUTTON1) && (TMR3 >= DEBOUNCE_TIME) && (PREV_BUTTON1!= 1))
	{
		PREV_BUTTON1= 1;
		return 1;
	}
	else if(!BUTTON1)
	{
		PREV_BUTTON1= 0;
		TMR3 = 0;
			
	}
return 0;
	
}


int debouncebutton2()
{
	button_timer_init2();
	
	if((BUTTON2) && (TMR4 >= DEBOUNCE_TIME) && (PREV_BUTTON2!= 1))
	{
		PREV_BUTTON2= 1;
		return 1;
	}
	else if(!BUTTON2)
	{
		PREV_BUTTON2= 0;
		TMR4 = 0;
		
	}
	return 0;

	
}


