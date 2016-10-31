#ifndef _motor_H
#define	_motor_H

#include <p30fxxxx.h>
#define FCY     12000000ULL
#include <libpic30.h>


void Motor_Init();
void Motor_Off();
int Motor_Forward(int Steps);
int Motor_Right(int Steps_R);
int Motor_Left(int Steps_L);
int Motor_Rotate(int Steps);


#endif	/* XC_HEADER_TEMPLATE_H */

