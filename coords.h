#ifndef _coords_H
#define	_coords_H

#include <p30fxxxx.h>
#define FCY     12000000ULL
#include <libpic30.h>

//distance coefficient used for calibrating
#define __distCoef 34.0
//angle coefficient used for calibrating
#define __angCoef  4.00
//PI
#define M_PI 3.14159

//Variables used for storing coordinates and current angle
extern double yCoord[16];
extern double xCoord[16];
extern double currentAng;

//initialises origin to (0,0) & all other coords to (nn,nn)
void coord_Init();

//returns the value of the coordinate as a char array, or " nn" if outside valid coordinates
const char* getYCoord(int coordIndex);
const char* getXCoord(int coordIndex);

//decrements the x/y coordinate at the index by program unit
void xCoordDec(double programUnit, int coordIndex);
void yCoordDec(double programUnit, int coordIndex);

//increments the x/y coordinate at the index by program unit
void yCoordInc(double programUnit, int coordIndex);
void xCoordInc(double programUnit, int coordIndex);

//calculates the the required angle and returns how many steps are needed to rotate that angle
int angCalc(int firstCoord, int secondCoord);

//calculates the the required distance turns how many steps are needed to move that far
int distCalc(int firstCoord, int secondCoord);

//takes in steps rotated and updates currentAng
int StepsTakenRotate(int steps);

//takes in steps and updates current coordinates
int StepsTakenForward(int steps, int index);

#endif
