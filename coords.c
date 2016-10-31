#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "coords.h"

//variables for storing the 16 coordinates and angle
double yCoord[16];
double xCoord[16];
double currentAng;


//sets default values for coordinates
void coord_Init()
{
	currentAng = 0;
	int i;
	for(i = 0; i < 16; i++ )
	{
        yCoord[i] = 51;
        xCoord[i] = 51;
	}
	yCoord[0] = 0;
	xCoord[0] = 0;
    
}

//takes in a coordinate index and decrements the y coordinate by the program unit. (1 or 10 in SFD)
void yCoordDec(double programUnit, int coordIndex)
{
	//if coordinate is outside bound, resets the coordinate to 0 and returns
   	if(yCoord[coordIndex] > 50 || yCoord[coordIndex] < -50)
	{

		xCoord[coordIndex]=0;
		yCoord[coordIndex]=0;
        return;
	}
	yCoord[coordIndex]=yCoord[coordIndex]-programUnit;
	//if yCoord exceeds range limit, it will be set to 51, the 'null' coordinate
	if(yCoord[coordIndex] > 50 || yCoord[coordIndex] < -50)
	{
		xCoord[coordIndex]=51;
		yCoord[coordIndex]=51;
	}
}
//takes in a coordinate index and increments the y coordinate by the program unit. (1 or 10 in SFD)
void yCoordInc(double programUnit, int coordIndex)
{
	//if coordinate is outside bound, resets the coordinate to 0 and returns
    	if(yCoord[coordIndex] > 50 || yCoord[coordIndex] < -50)
	{
		xCoord[coordIndex]=0;
		yCoord[coordIndex]=0;
        return;
	}
	yCoord[coordIndex]=yCoord[coordIndex]+programUnit;
	//if yCoord exceeds range limit, it will be set to 51, the 'null' coordinate
	if(yCoord[coordIndex] > 50 || yCoord[coordIndex] < -50)
	{
		xCoord[coordIndex]=51;
		yCoord[coordIndex]=51;
	}
}

//takes in a coordinate index and decrements the x coordinate by the program unit. (1 or 10 in SFD)
void xCoordDec(double programUnit, int coordIndex)
{
	//if coordinate is outside bound, resets the coordinate to 0 and returns
    	if(xCoord[coordIndex] > 50 || xCoord[coordIndex] < -50)
	{
		xCoord[coordIndex]=0;
		yCoord[coordIndex]=0;
        return;
	}
	xCoord[coordIndex]=xCoord[coordIndex]-programUnit;
	//if xCoord exceeds range limit, it will be set to 51, the 'null' coordinate
	if(xCoord[coordIndex] > 50 || xCoord[coordIndex] < -50)
	{
		xCoord[coordIndex]=51;
		yCoord[coordIndex]=51;
	}
}

//takes in a coordinate index and increments the x coordinate by the program unit. (1 or 10 in SFD)
void xCoordInc(double programUnit, int coordIndex)
{
	//if coordinate is outside bound, resets the coordinate to 0 and returns
    	if(xCoord[coordIndex] > 50 || xCoord[coordIndex] < -50)
	{
		xCoord[coordIndex]=0;
		yCoord[coordIndex]=0;
        return;
	}
	xCoord[coordIndex]=xCoord[coordIndex]+programUnit;
	//if xCoord exceeds range limit, it will be set to 51, the 'null' coordinate
	if(xCoord[coordIndex] > 50 || xCoord[coordIndex] < -50)
	{
		xCoord[coordIndex]=51;
		yCoord[coordIndex]=51;
	}
}



//Function that will take in two coordinates and calculate the required number of steps for rotation
int angCalc(int firstCoord, int secondCoord)
{
	//sets two coordinates based on the given indexes
	int oldY = yCoord[firstCoord];
	int newY = yCoord[secondCoord];
	int oldX = xCoord[firstCoord];
	int newX = xCoord[secondCoord];

	//calculates the difference between x coords and y coords
	double a = newY - oldY;
	double b = newX - oldX;

	// Assigned the Angle Calc to improve readability
	//Converting Angle to degrees as all code from this point onwards assumes that every angle is in degrees
	double angle = (atan2(a, b) * (180.0 / M_PI)) - 90;

	//calculates the angle required to turn and ensures its from -180 degrees to 180 degrees
    	double requiredAngle = angle - currentAng;
    	while (requiredAngle > 180)
    	{
    		requiredAngle = requiredAngle - 360;
    	}
    	while (requiredAngle <= -180)
    	{
		requiredAngle = requiredAngle + 360;
    	}
    
	//Determine correct number of steps for rotation andadds 0.5 for rounding when converted to an int
	double tempAng2 = (requiredAngle * __angCoef) + 0.5F;
	//converts tempang2 to an interger
	int angSteps = tempAng2;
	
	//returns how many steps are required to rotate
	return angSteps;
}

//Function that will take in two coordinates and calculate the required number of steps for movement
int distCalc(int firstCoord, int secondCoord)
{
	//sets two coordinates based on the given indexes
	int y1coord = yCoord[firstCoord];
	int y2coord = yCoord[secondCoord];
	int x1coord = xCoord[firstCoord];
	int x2coord = xCoord[secondCoord];

	//calculates the difference between x coords and y coords
	double a = y2coord - y1coord;
	double b = x2coord - x1coord;

	//calculates the total distance required a^2+b^2=c^2
	double reqDist = sqrt(pow(a,2) + pow(b,2));
	
	//Determine correct number of steps for movement
	double tempDist = reqDist * __distCoef;
	
	//adds 0.5 for rounding when converted to an int
	tempDist = tempDist + 0.5;
	
	//converts tempDist to an interger
	int distSteps = tempDist;

	//returns steps needed to move a certain distance
	return distSteps;
}

//takes in the amount of steps taken and what coordinate is being used, returns the number of steps inputted
int StepsTakenForward(int steps, int index)
{
    //calculates the distance traveled based on the number of steps taken
    double distance = steps / __distCoef;
   
    //calculates the distance traveled in the x direction and stores it in the same index
    double xCoordChange = distance * asin(currentAng);
    xCoord[index] = xCoord[index] + xCoordChange;
    
    //calculates the distance traveled in the y direction and stores it in the same index
    double yCoordChange = distance * acos(currentAng);
    yCoord[index] = yCoord[index] + yCoordChange;
            
    return steps;
}

//takes in the amount of steps taken and what coordinate is being used, returns the number of steps inputted
int StepsTakenRotate(int steps)
{
	//calculates the rotation based on the number of steps taken
    double angle = steps / __angCoef;
	
	//updates the global angle based on rotation
    currentAng = currentAng + angle;
	//ensures rotation is between -180 and 180 degrees
    while (currentAng > 180)
    {
        currentAng = currentAng - 360;
    }
    while (currentAng <= -180)
    {
        currentAng = currentAng + 360;
    }
	//returns initial steps input
    return steps;
}


//Returns char array of the Y coordinate at the index
const char* getYCoord(int coordIndex)
{
	if(yCoord[coordIndex] == -50)
		return "-50";
	else if(yCoord[coordIndex] == -49)
		return "-49";
	else if(yCoord[coordIndex] == -48)
		return "-48";
	else if(yCoord[coordIndex] == -47)
		return "-47";
	else if(yCoord[coordIndex] == -46)
		return "-46";
	else if(yCoord[coordIndex] == -45)
		return "-45";
	else if(yCoord[coordIndex] == -44)
		return "-44";
	else if(yCoord[coordIndex] == -43)
		return "-43";
	else if(yCoord[coordIndex] == -42)
		return "-42";
	else if(yCoord[coordIndex] == -41)
		return "-41";
	else if(yCoord[coordIndex] == -40)
		return "-40";
	else if(yCoord[coordIndex] == -39)
		return "-39";
	else if(yCoord[coordIndex] == -38)
		return "-38";
	else if(yCoord[coordIndex] == -37)
		return "-37";
	else if(yCoord[coordIndex] == -36)
		return "-36";
	else if(yCoord[coordIndex] == -35)
		return "-35";
	else if(yCoord[coordIndex] == -34)
		return "-34";
	else if(yCoord[coordIndex] == -33)
		return "-33";
	else if(yCoord[coordIndex] == -32)
		return "-32";
	else if(yCoord[coordIndex] == -31)
		return "-31";
	else if(yCoord[coordIndex] == -30)
		return "-30";
	else if(yCoord[coordIndex] == -29)
		return "-29";
	else if(yCoord[coordIndex] == -28)
		return "-28";
	else if(yCoord[coordIndex] == -27)
		return "-27";
	else if(yCoord[coordIndex] == -26)
		return "-26";
	else if(yCoord[coordIndex] == -25)
		return "-25";
	else if(yCoord[coordIndex] == -24)
		return "-24";
	else if(yCoord[coordIndex] == -23)
		return "-23";
	else if(yCoord[coordIndex] == -22)
		return "-22";
	else if(yCoord[coordIndex] == -21)
		return "-21";
	else if(yCoord[coordIndex] == -20)
		return "-20";
	else if(yCoord[coordIndex] == -19)
		return "-19";
	else if(yCoord[coordIndex] == -18)
		return "-18";
	else if(yCoord[coordIndex] == -17)
		return "-17";
	else if(yCoord[coordIndex] == -16)
		return "-16";
	else if(yCoord[coordIndex] == -15)
		return "-15";
	else if(yCoord[coordIndex] == -14)
		return "-14";
	else if(yCoord[coordIndex] == -13)
		return "-13";
	else if(yCoord[coordIndex] == -12)
		return "-12";
	else if(yCoord[coordIndex] == -11)
		return "-11";
	else if(yCoord[coordIndex] == -10)
		return "-10";
	else if(yCoord[coordIndex] == -9)
		return "-09";
	else if(yCoord[coordIndex] == -8)
		return "-08";
	else if(yCoord[coordIndex] == -7)
		return "-07";
	else if(yCoord[coordIndex] == -6)
		return "-06";
	else if(yCoord[coordIndex] == -5)
		return "-05";
	else if(yCoord[coordIndex] == -4)
		return "-04";
	else if(yCoord[coordIndex] == -3)
		return "-03";
	else if(yCoord[coordIndex] == -2)
		return "-02";
	else if(yCoord[coordIndex] == -1)
		return "-01";
	else if(yCoord[coordIndex] == 0)
		return " 00";
    else if(yCoord[coordIndex] == 50)
		return " 50";
	else if(yCoord[coordIndex] == 49)
		return " 49";
	else if(yCoord[coordIndex] == 48)
		return " 48";
	else if(yCoord[coordIndex] == 47)
		return " 47";
	else if(yCoord[coordIndex] == 46)
		return " 46";
	else if(yCoord[coordIndex] == 45)
		return " 45";
	else if(yCoord[coordIndex] == 44)
		return " 44";
	else if(yCoord[coordIndex] == 43)
		return " 43";
	else if(yCoord[coordIndex] == 42)
		return " 42";
	else if(yCoord[coordIndex] == 41)
		return " 41";
	else if(yCoord[coordIndex] == 40)
		return " 40";
	else if(yCoord[coordIndex] == 39)
		return " 39";
	else if(yCoord[coordIndex] == 38)
		return " 38";
	else if(yCoord[coordIndex] == 37)
		return " 37";
	else if(yCoord[coordIndex] == 36)
		return " 36";
	else if(yCoord[coordIndex] == 35)
		return " 35";
	else if(yCoord[coordIndex] == 34)
		return " 34";
	else if(yCoord[coordIndex] == 33)
		return " 33";
	else if(yCoord[coordIndex] == 32)
		return " 32";
	else if(yCoord[coordIndex] == 31)
		return " 31";
	else if(yCoord[coordIndex] == 30)
		return " 30";
	else if(yCoord[coordIndex] == 29)
		return " 29";
	else if(yCoord[coordIndex] == 28)
		return " 28";
	else if(yCoord[coordIndex] == 27)
		return " 27";
	else if(yCoord[coordIndex] == 26)
		return " 26";
	else if(yCoord[coordIndex] == 25)
		return " 25";
	else if(yCoord[coordIndex] == 24)
		return " 24";
	else if(yCoord[coordIndex] == 23)
		return " 23";
	else if(yCoord[coordIndex] == 22)
		return " 22";
	else if(yCoord[coordIndex] == 21)
		return " 21";
	else if(yCoord[coordIndex] == 20)
		return " 20";
	else if(yCoord[coordIndex] == 19)
		return " 19";
	else if(yCoord[coordIndex] == 18)
		return " 18";
	else if(yCoord[coordIndex] == 17)
		return " 17";
	else if(yCoord[coordIndex] == 16)
		return " 16";
	else if(yCoord[coordIndex] == 15)
		return " 15";
	else if(yCoord[coordIndex] == 14)
		return " 14";
	else if(yCoord[coordIndex] == 13)
		return " 13";
	else if(yCoord[coordIndex] == 12)
		return " 12";
	else if(yCoord[coordIndex] == 11)
		return " 11";
	else if(yCoord[coordIndex] == 10)
		return " 10";
	else if(yCoord[coordIndex] == 9)
		return " 09";
	else if(yCoord[coordIndex] == 8)
		return " 08";
	else if(yCoord[coordIndex] == 7)
		return " 07";
	else if(yCoord[coordIndex] == 6)
		return " 06";
	else if(yCoord[coordIndex] == 5)
		return " 05";
	else if(yCoord[coordIndex] == 4)
		return " 04";
	else if(yCoord[coordIndex] == 3)
		return " 03";
	else if(yCoord[coordIndex] == 2)
		return " 02";
	else if(yCoord[coordIndex] == 1)
		return " 01";
    //if not a valid coordinate, returns " nn"
    return " nn";
}


//Returns char array of the X coordinate at the index
const char* getXCoord(int coordIndex)
{
	if(xCoord[coordIndex] == -50)
		return "-50";
	else if(xCoord[coordIndex] == -49)
		return "-49";
	else if(xCoord[coordIndex] == -48)
		return "-48";
	else if(xCoord[coordIndex] == -47)
		return "-47";
	else if(xCoord[coordIndex] == -46)
		return "-46";
	else if(xCoord[coordIndex] == -45)
		return "-45";
	else if(xCoord[coordIndex] == -44)
		return "-44";
	else if(xCoord[coordIndex] == -43)
		return "-43";
	else if(xCoord[coordIndex] == -42)
		return "-42";
	else if(xCoord[coordIndex] == -41)
		return "-41";
	else if(xCoord[coordIndex] == -40)
		return "-40";
	else if(xCoord[coordIndex] == -39)
		return "-39";
	else if(xCoord[coordIndex] == -38)
		return "-38";
	else if(xCoord[coordIndex] == -37)
		return "-37";
	else if(xCoord[coordIndex] == -36)
		return "-36";
	else if(xCoord[coordIndex] == -35)
		return "-35";
	else if(xCoord[coordIndex] == -34)
		return "-34";
	else if(xCoord[coordIndex] == -33)
		return "-33";
	else if(xCoord[coordIndex] == -32)
		return "-32";
	else if(xCoord[coordIndex] == -31)
		return "-31";
	else if(xCoord[coordIndex] == -30)
		return "-30";
	else if(xCoord[coordIndex] == -29)
		return "-29";
	else if(xCoord[coordIndex] == -28)
		return "-28";
	else if(xCoord[coordIndex] == -27)
		return "-27";
	else if(xCoord[coordIndex] == -26)
		return "-26";
	else if(xCoord[coordIndex] == -25)
		return "-25";
	else if(xCoord[coordIndex] == -24)
		return "-24";
	else if(xCoord[coordIndex] == -23)
		return "-23";
	else if(xCoord[coordIndex] == -22)
		return "-22";
	else if(xCoord[coordIndex] == -21)
		return "-21";
	else if(xCoord[coordIndex] == -20)
		return "-20";
	else if(xCoord[coordIndex] == -19)
		return "-19";
	else if(xCoord[coordIndex] == -18)
		return "-18";
	else if(xCoord[coordIndex] == -17)
		return "-17";
	else if(xCoord[coordIndex] == -16)
		return "-16";
	else if(xCoord[coordIndex] == -15)
		return "-15";
	else if(xCoord[coordIndex] == -14)
		return "-14";
	else if(xCoord[coordIndex] == -13)
		return "-13";
	else if(xCoord[coordIndex] == -12)
		return "-12";
	else if(xCoord[coordIndex] == -11)
		return "-11";
	else if(xCoord[coordIndex] == -10)
		return "-10";
	else if(xCoord[coordIndex] == -9)
		return "-09";
	else if(xCoord[coordIndex] == -8)
		return "-08";
	else if(xCoord[coordIndex] == -7)
		return "-07";
	else if(xCoord[coordIndex] == -6)
		return "-06";
	else if(xCoord[coordIndex] == -5)
		return "-05";
	else if(xCoord[coordIndex] == -4)
		return "-04";
	else if(xCoord[coordIndex] == -3)
		return "-03";
	else if(xCoord[coordIndex] == -2)
		return "-02";
	else if(xCoord[coordIndex] == -1)
		return "-01";
	else if(xCoord[coordIndex] == 0)
		return " 00";
	else if(xCoord[coordIndex] == 50)
		return " 50";
	else if(xCoord[coordIndex] == 49)
		return " 49";
	else if(xCoord[coordIndex] == 48)
		return " 48";
	else if(xCoord[coordIndex] == 47)
		return " 47";
	else if(xCoord[coordIndex] == 46)
		return " 46";
	else if(xCoord[coordIndex] == 45)
		return " 45";
	else if(xCoord[coordIndex] == 44)
		return " 44";
	else if(xCoord[coordIndex] == 43)
		return " 43";
	else if(xCoord[coordIndex] == 42)
		return " 42";
	else if(xCoord[coordIndex] == 41)
		return " 41";
	else if(xCoord[coordIndex] == 40)
		return " 40";
	else if(xCoord[coordIndex] == 39)
		return " 39";
	else if(xCoord[coordIndex] == 38)
		return " 38";
	else if(xCoord[coordIndex] == 37)
		return " 37";
	else if(xCoord[coordIndex] == 36)
		return " 36";
	else if(xCoord[coordIndex] == 35)
		return " 35";
	else if(xCoord[coordIndex] == 34)
		return " 34";
	else if(xCoord[coordIndex] == 33)
		return " 33";
	else if(xCoord[coordIndex] == 32)
		return " 32";
	else if(xCoord[coordIndex] == 31)
		return " 31";
	else if(xCoord[coordIndex] == 30)
		return " 30";
	else if(xCoord[coordIndex] == 29)
		return " 29";
	else if(xCoord[coordIndex] == 28)
		return " 28";
	else if(xCoord[coordIndex] == 27)
		return " 27";
	else if(xCoord[coordIndex] == 26)
		return " 26";
	else if(xCoord[coordIndex] == 25)
		return " 25";
	else if(xCoord[coordIndex] == 24)
		return " 24";
	else if(xCoord[coordIndex] == 23)
		return " 23";
	else if(xCoord[coordIndex] == 22)
		return " 22";
	else if(xCoord[coordIndex] == 21)
		return " 21";
	else if(xCoord[coordIndex] == 20)
		return " 20";
	else if(xCoord[coordIndex] == 19)
		return " 19";
	else if(xCoord[coordIndex] == 18)
		return " 18";
	else if(xCoord[coordIndex] == 17)
		return " 17";
	else if(xCoord[coordIndex] == 16)
		return " 16";
	else if(xCoord[coordIndex] == 15)
		return " 15";
	else if(xCoord[coordIndex] == 14)
		return " 14";
	else if(xCoord[coordIndex] == 13)
		return " 13";
	else if(xCoord[coordIndex] == 12)
		return " 12";
	else if(xCoord[coordIndex] == 11)
		return " 11";
	else if(xCoord[coordIndex] == 10)
		return " 10";
	else if(xCoord[coordIndex] == 9)
		return " 09";
	else if(xCoord[coordIndex] == 8)
		return " 08";
	else if(xCoord[coordIndex] == 7)
		return " 07";
	else if(xCoord[coordIndex] == 6)
		return " 06";
	else if(xCoord[coordIndex] == 5)
		return " 05";
	else if(xCoord[coordIndex] == 4)
		return " 04";
	else if(xCoord[coordIndex] == 3)
		return " 03";
	else if(xCoord[coordIndex] == 2)
		return " 02";
	else if(xCoord[coordIndex] == 1)
		return " 01";
    //if not a valid coordinate, returns " nn"
    return " nn";
}
