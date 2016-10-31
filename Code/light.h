#ifndef _light_H
#define	_light_H

#include <p30fxxxx.h>
#define FCY 12000000ULL
#include <libpic30.h>

//turns headlights on/off based on input
void Lights_Headlights(int state);

//turns brake lights on/off based on input
void Lights_Brakes(int state);

//turns reverse lights on/off based on input
void Lights_Reverse(int state);

//turns left indicator light on/off based on input
void Lights_Indicate_Left(int state);

//turns right indicator on/off based on input
void Lights_Indicate_Right(int state);

//turns heartbeat LED on/off based on input
void Lights_Heartbeat(int state);

#endif

