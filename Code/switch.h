#ifndef _switch_H
#define	_switch_H

#include <p30fxxxx.h>
#define FCY     12000000ULL
#include <libpic30.h>

//1 us delay for switches 1-7
//returns 1 if switch_X has been pressed, 0 otherwise.
int Switch_1();
int Switch_2();
int Switch_3();
int Switch_4();
int Switch_5();
int Switch_6();
int Switch_7();
//returns 1 if event switch is held down.
int Switch_Eventself();

//5 us delay
//returns 1 if event switch has been held down for 5us, 0 others
int Switch_Event();



#endif
