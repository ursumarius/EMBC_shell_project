#include <p32xxxx.h>
#include "buttons.h"
#include "plib.h"
#define 	BTN1 ((PORTA >> 6) & 0x00001)
#define 	BTN2 ((PORTA >> 7) & 0x00001)

	unsigned int debouncetime;
	unsigned int t0;
	unsigned int t02;
	unsigned int Prev1, Prev2;


int ButtonsInit(void){
//Button variables
	
	debouncetime = 8000000; //( -- 32Mhz)
	t0 = 0;
	t02 = 0;
	TRISA = 0b11000000;
	Prev1=1;
	Prev2=1;
	return 1;
//Button variables


}



int ButtonPress1(void){
	

//***ButtonPress1
		if (BTN1 ) {
		
			if (Prev1){

			t0 = ReadCoreTimer(); 
			Prev1 = 0;
			return 1;
			}
			else if (ReadCoreTimer() - t0 > debouncetime)
				{	return 0;
				
				}
			
		}
	
		else {
				if (ReadCoreTimer() - t0 > debouncetime)	{

					Prev1 = 1;
				}
				return 0;
			}	
			
//***ButtonPress1

	
}

ButtonPress2()
{			
//***ButtonPress2
		if (BTN2) {
			if (Prev2){

			t02 = ReadCoreTimer(); 
			Prev2 = 0;
			return 1;
			}
			if (ReadCoreTimer() - t02 > debouncetime)
			{	
				return 0;
			}
			
		}
		else {
				if (ReadCoreTimer() - t02 > debouncetime)	{

					Prev2 = 1;
				}
				return 0;
			}	
			
//***ButtonPress2

}
