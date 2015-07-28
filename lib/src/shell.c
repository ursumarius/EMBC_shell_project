#include <p32xxxx.h>
#include <plib.h>
#include "shell.h"
#include "uart.h"
#include <string.h>

unsigned char text[20];   // here we will store text until enter is pressed
char temp[1];// we will store char read from UART



/* ========================================================================== */
/* function: shell_init( fpb );     */
/* */
/* description: initialises the shell module.      */
/* */
/* pre: fpb  - peripheral bus clock frequency in Hz */
/* */
/* post: return value - 0 if initialisation failed */
/* 1 if initialisation succeeded    */
/* ========================================================================== */
unsigned char shell_init(unsigned int fpb)
{
	if(uart_init(fpb, 1, 9600, 8, 2, 1, 1, 1))//8 databits with 2 stop bit and 1 even parity//ipl 5
		return 1;
	return 0;
}
/* ========================================================================== */
/* function: shell_getcommand( command );      */
/* */
/* description: checks whether the terminal has received a command. If a */
/* command is received, it will return a 1, and the command will */
/* be placed in the command string. */
/* */
/* pre: command  - pointer to the first element of the string where the */ 
/* command needs to be placed in.   */
/* */
/* post: return value - 0 if no command is available    */
/* 1 if a command was received, the command will be */
/* placed in the command string */ 
/* command  - will hold the command string if the return value is 1 */
/* ========================================================================== */
unsigned char shell_getcommand(unsigned char *command)
{
	
	if (uart_read(1, temp))					// do we read something? yes - proceed
	{
												// it's not enter so keep making text
		//if (*temp >= 32)		// filter out enter specific keys (without if woy will have some weird simbols in your text			
		if(temp[0] > 30)
		{
			strcat(text,temp);				// add char we read from UART to end of text
		}
		//char *strcat(char *dest, const char *src)
		
		//if (*temp == "\r")	// is it enter? yes - proceed
		if(temp[0] == 13 && text[0] == NULL)
		{
			strcpy(command, "\r");
			return 1;
		}
		if(temp[0] == 13)
		{
			strcpy(command, text);				// it's enter so copy text we have to command
			memset(text, NULL ,sizeof(text));	// now we can clear text for next commands
			return 1;							// text is ready for comparing
		}
		return 0;
								// text is not ready
	}
	return 0;
}
/* ========================================================================== */
/* function: shell_sendmessage( message );      */
/* */
/* description: transmits a message, stored as a string in the message */
/* variable, to the terminal. The message will be terminated */
/* with a newline: "\n\r". */
/* */
/* pre: message  - pointer to the first element of the string to be   */
/*  transmitted to the terminal      */
/* */
/* post: return value - 0 if transmission failed */
/* 1 if transmission was successful  */
/* ========================================================================== */
void shell_sendmessage(unsigned char *message)
{
	uart_sendstring(1, message);
}