#include <p30fxxxx.h>
#define FCY     12000000ULL
#include <libpic30.h>

#define FALSE 0
#define TRUE !FALSE

#include "light.h"
#include "motor.h"
#include "display.h"
#include "switch.h"
#include "coords.h"



int main() 
{
    // Disable ADC (very important as ADC is on by default)
    // After POR, ADPCFG=0 resulting in all ADC pins being analog input rather than digital I/O function.
    // Hence in the source code (ADPCFG = 0xFFFF;) sets all port analog pins to digital I/O, as required for the robot.)
    ADPCFG = 0xFFFF;
	//initilises display and coordinate system
	Display_Init();
    coord_Init();

	//variable for keeping track of current mode
	// Welcome: 0, Select:1, Program: 2, Execute:3
	int mode = 0;
    
	// Chooses which id to display
	int idCounter = 0;
    
	//program mode trackers
	//how much to change coordinate by (1 or 10)
	int programUnit = 1;
	//coordinate index being changed
	int coordIndex = 0;
    
    // Execute trackers
	//the coordinate the robot is currently up to
    int currentCoord = 0;
	//how many steps needed to move to the next coordinate
	int stepsNeeded = 0;
	//how many steps were taken
    int stepsTaken = 0;
    
    
    __delay_ms(100);
	while(TRUE)
	{
		//Welcome mode
		if (mode == 0)
		{
			if(idCounter == 1)
			{
				//sets string to display
				Display_String("A1666545");
			}
			else if(idCounter == 2)
			{
				Display_String("A1637629");
			}
			else if(idCounter == 3)
			{
				Display_String("A1669059");
			}
			else if(idCounter == 4)
			{
				Display_String("A1668807");
			}
			else if(idCounter == 5)
			{
				Display_String("A1668040");
			}
			else
			{
				idCounter = 0;
				Display_String("GROUP 9");
			}
            int i;
			//uses Switch_Event() delay to delay id changes
            for(i = 0; i < 2000; i++)
            {
				//if Switch_Event() is pressed, changes to select mode 
                if (Switch_Event() == 1)
                {
                    mode = 1;
                    break;
                }
				//called to keep display active
                Display_Keep_Alive();
            }
            idCounter++;
		}

		//Select Mode
		else if (mode == 1)
		{
			Display_String("Select");
			//chooses which mode to enter
			if(Switch_7() == 1)
			{
				//Program Mode
				mode = 2;
			}
			else if(Switch_1() == 1)
			{
				//Execute Mode
				mode = 3;
			}
            Display_Keep_Alive();
		}
		
		else if(mode == 2)
		{
			//decrements yCoord if switch 1 is pressed
            if(Switch_1() == 1)
			{
				yCoordDec(programUnit, coordIndex);
			}
			//increments yCoord if switch 2 is pressed
			else if(Switch_2() == 1)
			{
				yCoordInc(programUnit, coordIndex);
			}
			//changes program unit between 1 & 10 if switch 3 is pressed
			else if(Switch_3() == 1)
			{
				if(programUnit == 1)
				{
					programUnit = 10;
				}
				else if(programUnit == 10)
				{
					programUnit = 1;
				}
			}
			//decrements xCoord if switch 4 is pressed
			else if(Switch_4() == 1)
			{
				xCoordDec(programUnit, coordIndex);
			}
			//decrements yCoord if switch 5 is pressed
			else if(Switch_5() == 1)
			{
				xCoordInc(programUnit, coordIndex);
			}
			//changes coordinate index if switch 6 is pressed
			else if (Switch_6() == 1)
			{
				coordIndex++;
				//origin + 15 coords
                if (coordIndex > 15)
                {
                    coordIndex = (coordIndex % 16) + currentCoord;                    
                }
			}
			//swaps to select mode if switch 7 is pressed.
			else if(Switch_7() == 1)
			{
				mode = 1;
			}
           
			//displays the coordinates in the form '[index][xcoord][ycoord]'
			Display_Coordinate(coordIndex);
            Display_Keep_Alive();            
		}

        //execute mode
		else if(mode == 3)
		{
            Display_String("START");
			//Sets robot to start moving if event switch is pressed
            while(Switch_Event() == 0)
            {
                Display_Keep_Alive();
            }
			//initilises motor and turns on head lights
            Motor_Init();
            Lights_Headlights(1);
            
			//sets delay at to show coords inbetween moving
            int delay;
            Display_Coordinate(currentCoord);
            for(delay = 2000; delay > 0; delay--)
            {
                Display_Keep_Alive();
            }
            
			//if next coord is valid, begin moving to it
            while(currentCoord < 15 && xCoord[currentCoord + 1] <= 50 && xCoord[currentCoord + 1] >= -50)
            {
				//calculates the required steps to rotate to face the next angle
                stepsNeeded = angCalc(currentCoord, currentCoord+1);
				//rotates that angle and returns how many steps were taken, updates currentAng based on how many steps were taken
                stepsTaken = StepsTakenRotate( Motor_Rotate( stepsNeeded ));
				//if steps are not the same, the process has been interupted and exits to select mode
                if(stepsTaken != stepsNeeded)
                {
                    mode = 1;
                    Lights_Headlights(0);
                    __delay_ms(250);
                    break;
                }
                else
                {
					//calculates required steps to move forward
                    stepsNeeded = distCalc(currentCoord, currentCoord+1);
					//moves forward that many steps and returns how many steps were taken, updates x,y coordinates based on steps taken
                    stepsTaken = StepsTakenForward(Motor_Forward(stepsNeeded), currentCoord);
					//if steps not the same, the robot has been interupted and enters select mode
                    if(stepsTaken < stepsNeeded)
                    {
                        mode = 1;
                        __delay_ms(250);
                        Lights_Headlights(0);
                        break;
                    }
                }
				//has successfully travelled to the next coordinate, increments counter
                currentCoord++;
                
				//displays coordinate reached
                int delay;
                Display_Coordinate(currentCoord);
                for(delay = 2000; delay > 0; delay--)
                {
                    Display_Keep_Alive();
                }                
            }
			//turns headlights off
            Lights_Headlights(0);
            
            if(stepsTaken == stepsNeeded)
            {
                Display_String("END");
                while(Switch_Event() == 0)
                {
                    Display_Keep_Alive();
                }

                mode = 1;
                __delay_ms(250);
            }
		}
	}  
}
