#include <p32xxxx.h>
#include <string.h>
#include "servo.h"
#include "testservo.h"

#include "button.h"
#include "eeprom.h"
#include "shell.h"

int angle = 0;char *angleptr = &angle;
int a = 0, b = 0;
char *intro = "embc shell\r\n====================";
char *prompt = "\r\nembc>";
char cmd[20];
char *setangle = "setangle";
char *getangle = "getangle";
char *setmsg1 = "\nservo set to "; 
char *setmsg0 = " degrees";
char *getmsg0 = "\n\rcurrent angle: ";
char *errmsg = "\n\rerror: syntax error";
char *errangle = "\r\nerror: wrong angle\n\r->specify angle between -45 and +45";
char tempmsg[30];
char setmsg[25];
char getmsg[15];	
int main()
{
	servo_init(8e6, 1, angle);
/*	if(eeprom_init(8e6))
	{h
		eeprom_read(unsigned short int address, unsigned short int data);
	}*/
	shell_init(8e6);
    INTEnableSystemMultiVectoredInt();
    shell_sendmessage(intro);
    shell_sendmessage(prompt);
	TRISB = 0;
	PORTB = 0;
	while(1)
	{
		if(shell_getcommand(cmd))
		{
			
			if(cmd[0]==13)
				shell_sendmessage(prompt);
			else if(strncmp(cmd, setangle, 8) == 0)
			{
				memset(cmd, 32, 8);
				angle = atoi(cmd);
				if(angle < -45 || angle > 45)
				{
					shell_sendmessage(errangle);
					shell_sendmessage(prompt);
					continue;
				}
			
				servo_setpos(1, angle);
				strcpy(tempmsg, setmsg1);
				strcat(tempmsg, angleptr);
				strcat(tempmsg, setmsg0);
				
				shell_sendmessage(tempmsg);
				sprintf(setmsg, "\r\nservo set to %d degrees", angle);
				shell_sendmessage(setmsg);
				 
			//	strcat(text,temp);
			//	shell_sendmessage(setmsg);
				shell_sendmessage(prompt);
			}
			
			else if(!strncmp(cmd, getangle, 8))
			{
				sprintf(getmsg, "\r\ncurrent angle: %d degrees", angle);
				shell_sendmessage(getmsg);
				shell_sendmessage(prompt);
			}
			
			else
			{
				shell_sendmessage(errmsg);
				shell_sendmessage(prompt);
			}
				
		}
			
	}
return 0;
}
