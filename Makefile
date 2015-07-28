# MPLAB IDE generated this makefile for use with GNU make.
# Project: Assignment1.1.mcp
# Date: Sat Mar 08 13:56:17 2014

AS = pic32-as.exe
CC = pic32-gcc.exe
LD = pic32-ld.exe
AR = pic32-ar.exe
HX = pic32-bin2hex.exe
RM = rm

Assignment1.1.hex : Assignment1.1.elf
	$(HX) "Assignment1.1.elf"

Assignment1.1.elf : obj/oc.o obj/pwm.o obj/servo.o obj/timer.o obj/testservo.o obj/button.o obj/eeprom.o obj/i2c.o obj/shell.o obj/uart.o
	$(CC) -mdebugger -mprocessor=32MX460F512L "obj\oc.o" "obj\pwm.o" "obj\servo.o" "obj\timer.o" "obj\testservo.o" "obj\button.o" "obj\eeprom.o" "obj\i2c.o" "obj\shell.o" "obj\uart.o" -o"Assignment1.1.elf" -Wl,-L"Q:\00003221.UK1\MPLAB C32 Suite\lib",-L"Q:\00003221.UK1\MPLAB C32 Suite\pic32mx\lib",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=__ICD2RAM=1,-Map="Assignment1.1.map"

obj/oc.o : lib/src/oc.c lib/inc/oc.h
	$(CC) -mprocessor=32MX460F512L -x c -c "lib\src\oc.c" -o"./obj\oc.o" -MMD -MF"./obj\oc.d" -I"./inc" -I"./lib/inc" -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -g

obj/pwm.o : lib/src/pwm.c lib/inc/pwm.h lib/inc/timer.h lib/inc/oc.h
	$(CC) -mprocessor=32MX460F512L -x c -c "lib\src\pwm.c" -o"./obj\pwm.o" -MMD -MF"./obj\pwm.d" -I"./inc" -I"./lib/inc" -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -g

obj/servo.o : lib/src/servo.c lib/inc/servo.h lib/inc/pwm.h lib/inc/timer.h lib/inc/oc.h
	$(CC) -mprocessor=32MX460F512L -x c -c "lib\src\servo.c" -o"./obj\servo.o" -MMD -MF"./obj\servo.d" -I"./inc" -I"./lib/inc" -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -g

obj/timer.o : lib/src/timer.c lib/inc/timer.h
	$(CC) -mprocessor=32MX460F512L -x c -c "lib\src\timer.c" -o"./obj\timer.o" -MMD -MF"./obj\timer.d" -I"./inc" -I"./lib/inc" -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -g

obj/testservo.o : src/testservo.c lib/inc/servo.h inc/testservo.h lib/inc/button.h lib/inc/eeprom.h lib/inc/shell.h
	$(CC) -mprocessor=32MX460F512L -x c -c "src\testservo.c" -o"./obj\testservo.o" -MMD -MF"./obj\testservo.d" -I"./inc" -I"./lib/inc" -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -g

obj/button.o : lib/src/button.c lib/inc/button.h
	$(CC) -mprocessor=32MX460F512L -x c -c "lib\src\button.c" -o"./obj\button.o" -MMD -MF"./obj\button.d" -I"./inc" -I"./lib/inc" -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -g

obj/eeprom.o : lib/src/eeprom.c lib/inc/eeprom.h lib/inc/i2c.h
	$(CC) -mprocessor=32MX460F512L -x c -c "lib\src\eeprom.c" -o"./obj\eeprom.o" -MMD -MF"./obj\eeprom.d" -I"./inc" -I"./lib/inc" -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -g

obj/i2c.o : lib/src/i2c.c lib/inc/i2c.h
	$(CC) -mprocessor=32MX460F512L -x c -c "lib\src\i2c.c" -o"./obj\i2c.o" -MMD -MF"./obj\i2c.d" -I"./inc" -I"./lib/inc" -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -g

obj/shell.o : lib/src/shell.c lib/inc/shell.h lib/inc/uart.h
	$(CC) -mprocessor=32MX460F512L -x c -c "lib\src\shell.c" -o"./obj\shell.o" -MMD -MF"./obj\shell.d" -I"./inc" -I"./lib/inc" -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -g

obj/uart.o : lib/src/uart.c lib/inc/uart.h
	$(CC) -mprocessor=32MX460F512L -x c -c "lib\src\uart.c" -o"./obj\uart.o" -MMD -MF"./obj\uart.d" -I"./inc" -I"./lib/inc" -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -g

clean : 
	$(RM) "obj\oc.o" "obj\pwm.o" "obj\servo.o" "obj\timer.o" "obj\testservo.o" "obj\button.o" "obj\eeprom.o" "obj\i2c.o" "obj\shell.o" "obj\uart.o" "Assignment1.1.elf" "Assignment1.1.hex"

