#ifndef SHELL_H
#define SHELL_H 

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
unsigned char shell_init(unsigned int fpb);
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
unsigned char shell_getcommand(unsigned char *command);
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
void shell_sendmessage(unsigned char *message);
#endif/*SHELL.H*/