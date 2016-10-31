#include "motor.h"
#include "light.h"
#include "display.h"
#include "switch.h"


void Motor_Init() {
    	// Disable ADC (very important as ADC is on by default)
    	// After POR, ADPCFG=0 resulting in all ADC pins being analog input rather than digital I/O function.
    	// Hence in the source code (ADPCFG = 0xFFFF;) sets all port analog pins to digital I/O, as required for the robot.)
    	//ADPCFG = 0xFFFF;
    	// State of a modulo 4 conuter
    	//int count = 0;
    	// Bit pattern sent to the display module
    	//int pattern = CHAR_0;

    	TRISBbits.TRISB6 = 0;
    	PORTBbits.RB6 = 1;   // Sets Reset off for both motors to enable input (active low, 1 = reset off)

    	TRISBbits.TRISB5 = 0;
    	TRISBbits.TRISB4 = 0;
    	PORTBbits.RB5 = 1; // AI1_L
    	PORTBbits.RB4 = 1; // AI0_L


    	TRISBbits.TRISB3 = 0;
    	TRISBbits.TRISB2 = 0;
    	PORTBbits.RB3 = 1; // BI1_L
    	PORTBbits.RB2 = 1; // BI0_L

    	TRISDbits.TRISD8 = 0;
    	TRISDbits.TRISD9 = 0;
    	PORTDbits.RD8 = 1; // BI0_R
    	PORTDbits.RD9 = 1; // BI1_R


    	TRISDbits.TRISD10 = 0;
    	TRISDbits.TRISD11 = 0;
    	PORTDbits.RD10 = 1; // AI0_R
    	PORTDbits.RD11 = 1; // AI1_R

    	TRISBbits.TRISB7 = 0;

    	TRISAbits.TRISA14 = 0;
    	TRISAbits.TRISA15 = 0;

    	TRISEbits.TRISE8 = 0;
    	TRISEbits.TRISE9 = 0;

    	TRISDbits.TRISD0 = 0;
    	PORTDbits.RD0 = 1; // Activates status LEDs on robot
}

 void Motor_Off(){
   // Set all the Speed Variables to 0 to come to a stop
   PORTBbits.RB5 = 1; // AI1_L
   PORTBbits.RB4 = 1; // AI0_L

   PORTDbits.RD10 = 1; // AI0_R
   PORTDbits.RD11 = 1; // AI1_R

   PORTBbits.RB3 = 1; // BI1_L
   PORTBbits.RB2 = 1; // BI0_L

   PORTDbits.RD8 = 1; // BI0_R
   PORTDbits.RD9 = 1; // BI1_R
   PORTBbits.RB7 = 0; // Disables Drive
   Lights_Indicate_Right(0);
   Lights_Indicate_Left(0);
}

int Motor_Rotate(int Steps)
{
	if (Steps > 0)
    {
		return Motor_Right(Steps);
	}
	else if (Steps < 0)
    {
		return -Motor_Left(-Steps);
	}
    else
    {
        return 0;
    }
}

int Motor_Left(int Steps_L)
{
	PORTBbits.RB7 = 1;  //  Enables Drive

    //Setting default Phases
	int PhaseA_L = 1;
	int PhaseB_L = 1;
	int PhaseA_R = 1;
	int PhaseB_R = 1;

	//Setting default Currents
	int AI0_L = 1;
	int AI1_L = 1;
	int BI0_L = 1;
	int BI1_L = 1;

	int AI0_R = 1;
	int AI1_R = 1;
	int BI0_R = 1;
	int BI1_R = 1;

	int steps = Steps_L;
  int ind_flag = 0;

	int i;
	for(i = 0;  i < steps; i++)
	{
		switch (i % 12)
	    	{
	        	case 0:
                    // Phase +-
                    PhaseA_L = 1;   // Sets the Phase of the Left Motor
                    PhaseB_L = 0;	// ^
                    PhaseA_R = 1;   // Sets the Phase of the Right Motor
                    PhaseB_R = 0;	// ^

                    // Current A = 71%
                    // Current B = -38%
                    AI0_L = 0;	//Sets current of Phase A for Left Motor
                    AI1_L = 1;	// ^
                    BI0_L = 1;	//Sets current of Phase B for Left Motor
                    BI1_L = 0;	// ^

                    // Current A = 71%
                    // Current B = -38%
                    AI0_R = 0;	//Sets current of Phase A for Right Motor
                    AI1_R = 1;	// ^
                    BI0_R = 1;	//Sets current of Phase B for Right Motor
                    BI1_R = 0;	// ^

                    break;

		        case 1:
                    // Phase +-
                    PhaseA_L = 1;   // Sets the Phase of the Left Motor
                    PhaseB_L = 0;	// ^
                    PhaseA_R = 1;   // Sets the Phase of the Right Motor
                    PhaseB_R = 0;	// ^

                    // Current A = 38%
                    // Current B = -71%
                    AI0_L = 1;	//Sets current of Phase A for Left Motor
                    AI1_L = 0;	// ^
                    BI0_L = 0;	//Sets current of Phase B for Left Motor
                    BI1_L = 1;	// ^

                    // Current A = 38%
                    // Current B = -71%
                    AI0_R = 1;	//Sets current of Phase A for Right Motor
                    AI1_R = 0;	// ^
                    BI0_R = 0;	//Sets current of Phase B for Right Motor
                    BI1_R = 1;	// ^

		        	break;

	        	case 2:
		            	// Phase +-
		            	PhaseA_L = 1;   // Sets the Phase of the Left Motor
		            	PhaseB_L = 0;	// ^
		            	PhaseA_R = 1;   // Sets the Phase of the Right Motor
		            	PhaseB_R = 0;	// ^

          				// Current A = 0%
          				// Current B = -100%
          				AI0_L = 1;	//Sets current of Phase A for Left Motor
          				AI1_L = 1;	// ^
          				BI0_L = 0;	//Sets current of Phase B for Left Motor
          				BI1_L = 0;	// ^

          				// Current A = 0%
          				// Current B = -100%
          				AI0_R = 1;	//Sets current of Phase A for Right Motor
          				AI1_R = 1;	// ^
          				BI0_R = 0;	//Sets current of Phase B for Right Motor
          				BI1_R = 0;	// ^

		            	break;

	        	case 3:
		            	// Phase --
		            	PhaseA_L = 0;   // Sets the Phase of the Left Motor
		            	PhaseB_L = 0;	// ^
		            	PhaseA_R = 0;   // Sets the Phase of the Right Motor
		            	PhaseB_R = 0;	// ^

          				// Current A = -38%
          				// Current B = -71%
          				AI0_L = 1;	//Sets current of Phase A for Left Motor
          				AI1_L = 0;	// ^
          				BI0_L = 0;	//Sets current of Phase B for Left Motor
          				BI1_L = 1;	// ^

          				// Current A = -38%
          				// Current B = -71%
          				AI0_R = 1;	//Sets current of Phase A for Right Motor
          				AI1_R = 0;	// ^
          				BI0_R = 0;	//Sets current of Phase B for Right Motor
          				BI1_R = 1;	// ^

		            	break;

	        	case 4:
		            	// Phase --
		            	PhaseA_L = 0;   // Sets the Phase of the Left Motor
		            	PhaseB_L = 0;	// ^
		            	PhaseA_R = 0;   // Sets the Phase of the Right Motor
		            	PhaseB_R = 0;	// ^

          				// Current A = -71%
          				// Current B = -38%
          				AI0_L = 0;	//Sets current of Phase A for Left Motor
          				AI1_L = 1;	// ^
          				BI0_L = 1;	//Sets current of Phase B for Left Motor
          				BI1_L = 0;	// ^

          				// Current A = -71%
          				// Current B = -38%
          				AI0_R = 0;	//Sets current of Phase A for Right Motor
          				AI1_R = 1;	// ^
          				BI0_R = 1;	//Sets current of Phase B for Right Motor
          				BI1_R = 0;	// ^

		            	break;

			case 5:
		            	// Phase --
		            	PhaseA_L = 0;   // Sets the Phase of the Left Motor
		            	PhaseB_L = 0;	// ^
		            	PhaseA_R = 0;   // Sets the Phase of the Right Motor
		            	PhaseB_R = 0;	// ^

          				// Current A = -100%
          				// Current B = 0%
          				AI0_L = 0;	//Sets current of Phase A for Left Motor
          				AI1_L = 0;	// ^
          				BI0_L = 1;	//Sets current of Phase B for Left Motor
          				BI1_L = 1;	// ^

          				// Current A = -100%
          				// Current B = 0%
          				AI0_R = 0;	//Sets current of Phase A for Right Motor
          				AI1_R = 0;	// ^
          				BI0_R = 1;	//Sets current of Phase B for Right Motor
          				BI1_R = 1;	// ^

		            	break;

	        	case 6:
		            	// Phase -+
		            	PhaseA_L = 0;   // Sets the Phase of the Left Motor
		            	PhaseB_L = 1;	// ^
		            	PhaseA_R = 0;   // Sets the Phase of the Right Motor
		            	PhaseB_R = 1;	// ^

          				// Current A = -71%
          				// Current B = 38%
          				AI0_L = 0;	//Sets current of Phase A for Left Motor
          				AI1_L = 1;	// ^
          				BI0_L = 1;	//Sets current of Phase B for Left Motor
          				BI1_L = 0;	// ^

          				// Current A = -71%
          				// Current B = 38%
          				AI0_R = 0;	//Sets current of Phase A for Right Motor
          				AI1_R = 1;	// ^
          				BI0_R = 1;	//Sets current of Phase B for Right Motor
          				BI1_R = 0;	// ^

		            	break;

	        	case 7:
		            	// Phase -+
		            	PhaseA_L = 0;   // Sets the Phase of the Left Motor
		            	PhaseB_L = 1;	// ^
		            	PhaseA_R = 0;   // Sets the Phase of the Right Motor
		            	PhaseB_R = 1;	// ^

          				// Current A = -38%
          				// Current B = 71%
          				AI0_L = 1;	//Sets current of Phase A for Left Motor
          				AI1_L = 0;	// ^
          				BI0_L = 0;	//Sets current of Phase B for Left Motor
          				BI1_L = 1;	// ^

          				// Current A = -38%
          				// Current B = 71%
          				AI0_R = 1;	//Sets current of Phase A for Right Motor
          				AI1_R = 0;	// ^
          				BI0_R = 0;	//Sets current of Phase B for Right Motor
          				BI1_R = 1;	// ^

		            	break;

	        	case 8:
		            	// Phase -+
		            	PhaseA_L = 0;   // Sets the Phase of the Left Motor
		            	PhaseB_L = 1;	// ^
		            	PhaseA_R = 0;   // Sets the Phase of the Right Motor
		            	PhaseB_R = 1;	// ^

          				// Current A = 0%
          				// Current B = 100%
          				AI0_L = 1;	//Sets current of Phase A for Left Motor
          				AI1_L = 1;	// ^
          				BI0_L = 0;	//Sets current of Phase B for Left Motor
          				BI1_L = 0;	// ^

          				// Current A = 0%
          				// Current B = 100%
          				AI0_R = 1;	//Sets current of Phase A for Right Motor
          				AI1_R = 1;	// ^
          				BI0_R = 0;	//Sets current of Phase B for Right Motor
          				BI1_R = 0;	// ^

		            	break;

	        	case 9:
		            	// Phase ++
		            	PhaseA_L = 1;   // Sets the Phase of the Left Motor
		        	PhaseB_L = 1;	// ^
			        PhaseA_R = 1;   // Sets the Phase of the Right Motor
		        	PhaseB_R = 1;	// ^

      				// Current A = 38%
      				// Current B = 71%
      				AI0_L = 1;	//Sets current of Phase A for Left Motor
      				AI1_L = 0;	// ^
      				BI0_L = 0;	//Sets current of Phase B for Left Motor
      				BI1_L = 1;	// ^

      				// Current A = 38%
      				// Current B = 71%
      				AI0_R = 1;	//Sets current of Phase A for Right Motor
      				AI1_R = 0;	// ^
      				BI0_R = 0;	//Sets current of Phase B for Right Motor
      				BI1_R = 1;	// ^

		            	break;

	        	case 10:
				// Phase ++
			        PhaseA_L = 1;   // Sets the Phase of the Left Motor
			        PhaseB_L = 1;	// ^
			        PhaseA_R = 1;   // Sets the Phase of the Right Motor
			        PhaseB_R = 1;	// ^

      				// Current A = 71%
      				// Current B = 38%
      				AI0_L = 0;	//Sets current of Phase A for Left Motor
      				AI1_L = 1;	// ^
      				BI0_L = 1;	//Sets current of Phase B for Left Motor
      				BI1_L = 0;	// ^

      				// Current A = 71%
      				// Current B = 38%
      				AI0_R = 0;	//Sets current of Phase A for Right Motor
      				AI1_R = 1;	// ^
      				BI0_R = 1;	//Sets current of Phase B for Right Motor
      				BI1_R = 0;	// ^

		            	break;

		        case 11:
		        	// Phase ++
		            	PhaseA_L = 1;   // Sets the Phase of the Left Motor
		            	PhaseB_L = 1;	// ^
		            	PhaseA_R = 1;   // Sets the Phase of the Right Motor
		            	PhaseB_R = 1;	// ^

          				// Current A = 100%
          				// Current B = 0%
          				AI0_L = 0;	//Sets current of Phase A for Left Motor
          				AI1_L = 0;	// ^
          				BI0_L = 1;	//Sets current of Phase B for Left Motor
          				BI1_L = 1;	// ^

          				// Current A = 100%
          				// Current B = 0%
          				AI0_R = 0;	//Sets current of Phase A for Right Motor
          				AI1_R = 0;	// ^
          				BI0_R = 1;	//Sets current of Phase B for Right Motor
          				BI1_R = 1;	// ^

		            	break;

	    	}

	    	//Setting Currents to Correct Values
    		PORTBbits.RB4 = AI0_L;
    		PORTBbits.RB5 = AI1_L;
    		PORTBbits.RB2 = BI0_L;
    		PORTBbits.RB3 = BI1_L;

    		PORTDbits.RD10 = AI0_R;
    		PORTDbits.RD11 = AI1_R;
    		PORTDbits.RD8 = BI0_R;
    		PORTDbits.RD9 = BI1_R;

	    	//Setting Phases to Correct Values
	    	PORTEbits.RE8 = PhaseB_L;
	    	PORTEbits.RE9 = PhaseA_L;

	    	PORTAbits.RA14 = PhaseB_R;
	    	PORTAbits.RA15 = PhaseA_R;
  	if (i % 30 == 0){		// Updates the display each step
  		    Display_Moving();
		}
		if (i % 300 == 0) // Toggles the indicators every 300 motor steps, using ind_flag as a switch between states
        		{
        		 if (ind_flag == 0){
				            Lights_Indicate_Right(1);
                 		ind_flag = 1;
           		 	}
            	else if( ind_flag ==  1){
                		Lights_Indicate_Right(0);
                		ind_flag = 0;
            			}
        		}

		 if (Switch_Event() == 1){	    // End case is the event button is pressed during execution,
			     Lights_Indicate_Right(0);   //ensures all LEDS are turned off when break occurs and
            		return i+1;		    //returns how many steps have occured at time of break
             		}

	  __delay_us(1483);
	}
  Motor_Off();
  return steps;
}

int Motor_Right(int steps_R)
{
  PORTBbits.RB7 = 1;  //  Enables Drive

  //Setting default Phases
	int PhaseA_L = 1;
	int PhaseB_L = 1;
	int PhaseA_R = 1;
	int PhaseB_R = 1;

	//Setting default Currents
	int AI0_L = 1;
	int AI1_L = 1;
	int BI0_L = 1;
	int BI1_L = 1;

	int AI0_R = 1;
	int AI1_R = 1;
	int BI0_R = 1;
	int BI1_R = 1;

  int ind_flag = 0;

	int i;
	int steps = steps_R;

	for(i = 0;  i < steps; i++)
	{
		switch (i % 12)
	    	{
	        	case 0:
		        	// Phase ++
		            	PhaseA_L = 1;   // Sets the Phase of the Left Motor
		            	PhaseB_L = 1;	// ^
		            	PhaseA_R = 1;   // Sets the Phase of the Right Motor
		            	PhaseB_R = 1;	// ^

          				// Current A = 100%
          				// Current B = 0%
          				AI0_L = 0;	//Sets current of Phase A for Left Motor
          				AI1_L = 0;	// ^
          				BI0_L = 1;	//Sets current of Phase B for Left Motor
          				BI1_L = 1;	// ^

          				// Current A = 100%
          				// Current B = 0%
          				AI0_R = 0;	//Sets current of Phase A for Right Motor
          				AI1_R = 0;	// ^
          				BI0_R = 1;	//Sets current of Phase B for Right Motor
          				BI1_R = 1;	// ^

		            	break;

	        	case 1:
				// Phase ++
			        PhaseA_L = 1;   // Sets the Phase of the Left Motor
			        PhaseB_L = 1;	// ^
			        PhaseA_R = 1;   // Sets the Phase of the Right Motor
			        PhaseB_R = 1;	// ^

      				// Current A = 71%
      				// Current B = 38%
      				AI0_L = 0;	//Sets current of Phase A for Left Motor
      				AI1_L = 1;	// ^
      				BI0_L = 1;	//Sets current of Phase B for Left Motor
      				BI1_L = 0;	// ^

      				// Current A = 71%
      				// Current B = 38%
      				AI0_R = 0;	//Sets current of Phase A for Right Motor
      				AI1_R = 1;	// ^
      				BI0_R = 1;	//Sets current of Phase B for Right Motor
      				BI1_R = 0;	// ^

		            	break;

	        	case 2:
		            	// Phase ++
		            	PhaseA_L = 1;   // Sets the Phase of the Left Motor
		        	PhaseB_L = 1;	// ^
			        PhaseA_R = 1;   // Sets the Phase of the Right Motor
		        	PhaseB_R = 1;	// ^

      				// Current A = 38%
      				// Current B = 71%
      				AI0_L = 1;	//Sets current of Phase A for Left Motor
      				AI1_L = 0;	// ^
      				BI0_L = 0;	//Sets current of Phase B for Left Motor
      				BI1_L = 1;	// ^

      				// Current A = 38%
      				// Current B = 71%
      				AI0_R = 1;	//Sets current of Phase A for Right Motor
      				AI1_R = 0;	// ^
      				BI0_R = 0;	//Sets current of Phase B for Right Motor
      				BI1_R = 1;	// ^

		            	break;

	        	case 3:
		            	// Phase -+
		            	PhaseA_L = 0;   // Sets the Phase of the Left Motor
		            	PhaseB_L = 1;	// ^
		            	PhaseA_R = 0;   // Sets the Phase of the Right Motor
		            	PhaseB_R = 1;	// ^

          				// Current A = 0%
          				// Current B = 100%
          				AI0_L = 1;	//Sets current of Phase A for Left Motor
          				AI1_L = 1;	// ^
          				BI0_L = 0;	//Sets current of Phase B for Left Motor
          				BI1_L = 0;	// ^

          				// Current A = 0%
          				// Current B = 100%
          				AI0_R = 1;	//Sets current of Phase A for Right Motor
          				AI1_R = 1;	// ^
          				BI0_R = 0;	//Sets current of Phase B for Right Motor
          				BI1_R = 0;	// ^

		            	break;

	        	case 4:
		            	// Phase -+
		            	PhaseA_L = 0;   // Sets the Phase of the Left Motor
		            	PhaseB_L = 1;	// ^
		            	PhaseA_R = 0;   // Sets the Phase of the Right Motor
		            	PhaseB_R = 1;	// ^

          				// Current A = -38%
          				// Current B = 71%
          				AI0_L = 1;	//Sets current of Phase A for Left Motor
          				AI1_L = 0;	// ^
          				BI0_L = 0;	//Sets current of Phase B for Left Motor
          				BI1_L = 1;	// ^

          				// Current A = -38%
          				// Current B = 71%
          				AI0_R = 1;	//Sets current of Phase A for Right Motor
          				AI1_R = 0;	// ^
          				BI0_R = 0;	//Sets current of Phase B for Right Motor
          				BI1_R = 1;	// ^

		            	break;

	        	case 5:
		            	// Phase -+
		            	PhaseA_L = 0;   // Sets the Phase of the Left Motor
		            	PhaseB_L = 1;	// ^
		            	PhaseA_R = 0;   // Sets the Phase of the Right Motor
		            	PhaseB_R = 1;	// ^

          				// Current A = -71%
          				// Current B = 38%
          				AI0_L = 0;	//Sets current of Phase A for Left Motor
          				AI1_L = 1;	// ^
          				BI0_L = 1;	//Sets current of Phase B for Left Motor
          				BI1_L = 0;	// ^

          				// Current A = -71%
          				// Current B = 38%
          				AI0_R = 0;	//Sets current of Phase A for Right Motor
          				AI1_R = 1;	// ^
          				BI0_R = 1;	//Sets current of Phase B for Right Motor
          				BI1_R = 0;	// ^

		            	break;

			case 6:
		            	// Phase --
		            	PhaseA_L = 0;   // Sets the Phase of the Left Motor
		            	PhaseB_L = 0;	// ^
		            	PhaseA_R = 0;   // Sets the Phase of the Right Motor
		            	PhaseB_R = 0;	// ^

          				// Current A = -100%
          				// Current B = 0%
          				AI0_L = 0;	//Sets current of Phase A for Left Motor
          				AI1_L = 0;	// ^
          				BI0_L = 1;	//Sets current of Phase B for Left Motor
          				BI1_L = 1;	// ^

          				// Current A = -100%
          				// Current B = 0%
          				AI0_R = 0;	//Sets current of Phase A for Right Motor
          				AI1_R = 0;	// ^
          				BI0_R = 1;	//Sets current of Phase B for Right Motor
          				BI1_R = 1;	// ^

		            	break;

	        	case 7:
		            	// Phase --
		            	PhaseA_L = 0;   // Sets the Phase of the Left Motor
		            	PhaseB_L = 0;	// ^
		            	PhaseA_R = 0;   // Sets the Phase of the Right Motor
		            	PhaseB_R = 0;	// ^

          				// Current A = -71%
          				// Current B = -38%
          				AI0_L = 0;	//Sets current of Phase A for Left Motor
          				AI1_L = 1;	// ^
          				BI0_L = 1;	//Sets current of Phase B for Left Motor
          				BI1_L = 0;	// ^

          				// Current A = -71%
          				// Current B = -38%
          				AI0_R = 0;	//Sets current of Phase A for Right Motor
          				AI1_R = 1;	// ^
          				BI0_R = 1;	//Sets current of Phase B for Right Motor
          				BI1_R = 0;	// ^

		            	break;

	        	case 8:
		            	// Phase --
		            	PhaseA_L = 0;   // Sets the Phase of the Left Motor
		            	PhaseB_L = 0;	// ^
		            	PhaseA_R = 0;   // Sets the Phase of the Right Motor
		            	PhaseB_R = 0;	// ^

          				// Current A = -38%
          				// Current B = -71%
          				AI0_L = 1;	//Sets current of Phase A for Left Motor
          				AI1_L = 0;	// ^
          				BI0_L = 0;	//Sets current of Phase B for Left Motor
          				BI1_L = 1;	// ^

          				// Current A = -38%
          				// Current B = -71%
          				AI0_R = 1;	//Sets current of Phase A for Right Motor
          				AI1_R = 0;	// ^
          				BI0_R = 0;	//Sets current of Phase B for Right Motor
          				BI1_R = 1;	// ^

		            	break;

	        	case 9:
		            	// Phase +-
		            	PhaseA_L = 1;   // Sets the Phase of the Left Motor
		            	PhaseB_L = 0;	// ^
		            	PhaseA_R = 1;   // Sets the Phase of the Right Motor
		            	PhaseB_R = 0;	// ^

          				// Current A = 0%
          				// Current B = -100%
          				AI0_L = 1;	//Sets current of Phase A for Left Motor
          				AI1_L = 1;	// ^
          				BI0_L = 0;	//Sets current of Phase B for Left Motor
          				BI1_L = 0;	// ^

          				// Current A = 0%
          				// Current B = -100%
          				AI0_R = 1;	//Sets current of Phase A for Right Motor
          				AI1_R = 1;	// ^
          				BI0_R = 0;	//Sets current of Phase B for Right Motor
          				BI1_R = 0;	// ^

		            	break;

		        case 10:
		            	// Phase +-
		            	PhaseA_L = 1;   // Sets the Phase of the Left Motor
		            	PhaseB_L = 0;	// ^
		            	PhaseA_R = 1;   // Sets the Phase of the Right Motor
		            	PhaseB_R = 0;	// ^

          				// Current A = 38%
          				// Current B = -71%
          				AI0_L = 1;	//Sets current of Phase A for Left Motor
          				AI1_L = 0;	// ^
          				BI0_L = 0;	//Sets current of Phase B for Left Motor
          				BI1_L = 1;	// ^

          				// Current A = 38%
          				// Current B = -71%
          				AI0_R = 1;	//Sets current of Phase A for Right Motor
          				AI1_R = 0;	// ^
          				BI0_R = 0;	//Sets current of Phase B for Right Motor
          				BI1_R = 1;	// ^

		        	break;

	        	case 11:
		            	// Phase +-
		            	PhaseA_L = 1;   // Sets the Phase of the Left Motor
		            	PhaseB_L = 0;	// ^
		            	PhaseA_R = 1;   // Sets the Phase of the Right Motor
		            	PhaseB_R = 0;	// ^

          				// Current A = 71%
          				// Current B = -38%
          				AI0_L = 0;	//Sets current of Phase A for Left Motor
          				AI1_L = 1;	// ^
          				BI0_L = 1;	//Sets current of Phase B for Left Motor
          				BI1_L = 0;	// ^

          				// Current A = 71%
          				// Current B = -38%
          				AI0_R = 0;	//Sets current of Phase A for Right Motor
          				AI1_R = 1;	// ^
          				BI0_R = 1;	//Sets current of Phase B for Right Motor
          				BI1_R = 0;	// ^

		            	break;
	    	}
	    	//Setting Phases to Correct Values
	    	PORTEbits.RE8 = PhaseB_L;
	    	PORTEbits.RE9 = PhaseA_L;

	    	PORTAbits.RA14 = PhaseB_R;
	    	PORTAbits.RA15 = PhaseA_R;

    		//Setting Currents to Correct Values
    		PORTBbits.RB4 = AI0_L;
    		PORTBbits.RB5 = AI1_L;
    		PORTBbits.RB2 = BI0_L;
    		PORTBbits.RB3 = BI1_L;

    		PORTDbits.RD10 = AI0_R;
    		PORTDbits.RD11 = AI1_R;
    		PORTDbits.RD8 = BI0_R;
    		PORTDbits.RD9 = BI1_R;

		if (i % 300 == 0)// Toggles the indicators every 300 motor steps, using ind_flag as a switch between states
        		{
			    if (ind_flag == 0){
				        Lights_Indicate_Left(1);
				            ind_flag = 1;
			    }
			    else if( ind_flag ==  1){
				        Lights_Indicate_Left(0);
				            ind_flag = 0;
			    }
        }

		if (Switch_Event() == 1){		//End case is the event button is pressed during execution,
			Lights_Indicate_Left(0);	//ensures all LEDS are turned off when break occurs and
      Motor_Off();
			return i+1;			//returns how many steps have occured at time of break
			}
  	if (i % 30 == 0){		// Updates the display each step
  		    Display_Moving();
		}
	    	__delay_us(1483);
	}
        Motor_Off();
        return steps;
}

int Motor_Forward(int Steps)
{
    PORTBbits.RB7 = 1;  //  Enables Drive

    	//Setting default Phases
	int PhaseA_L = 1;
	int PhaseB_L = 1;
	int PhaseA_R = 1;
	int PhaseB_R = 1;

	//Setting default Currents
	int AI0_L = 1;
	int AI1_L = 1;
	int BI0_L = 1;
	int BI1_L = 1;

	int AI0_R = 1;
	int AI1_R = 1;
	int BI0_R = 1;
	int BI1_R = 1;


	int i;
  int steps = Steps;
  int decel;
  int accel;

  if (steps < 300){		// Special case if the distance to be moved is less than the predefined acceleration-
        accel = steps / 2;	// decelration period (400 each for a total period of 800 steps,
        decel = steps - accel;	//the robot does not reach maximum speed during this case
   	 }
  else{
        decel = steps - 150;
        accel = 150;
   }

	int delay = 6000;		//Acceleration/Deceleration is achieved by manipulating the delay in the motor step
	for(i = 0;  i < steps; i++){  	// our inital delay is set 6000 us and decreases to achieve an ideal speed at 1500 us
		switch (i % 12)
	    	{
	        	case 0:
                        // Phase +-/++
		            	PhaseA_L = 1;   // Sets the Phase of the Left Motor
		            	PhaseB_L = 0;	// ^
		            	PhaseA_R = 1;   // Sets the Phase of the Right Motor
		            	PhaseB_R = 1;	// ^

                        // Current A = 78%
                        // Current B = -38%
                        AI0_L = 0;	//Sets current of Phase A for Left Motor
                        AI1_L = 1;	// ^
                        BI0_L = 1;	//Sets current of Phase B for Left Motor
                        BI1_L = 0;	// ^

                        // Current A = 100%
                        // Current B = 0%
                        AI0_R = 0;	//Sets current of Phase A for Right Motor
                        AI1_R = 0;	// ^
                        BI0_R = 1;	//Sets current of Phase B for Right Motor
                        BI1_R = 1;	// ^

		            break;

	        	case 1:
                        // Phase +-/++
                        PhaseA_L = 1;   // Sets the Phase of the Left Motor
                        PhaseB_L = 0;	// ^
                        PhaseA_R = 1;   // Sets the Phase of the Right Motor
                        PhaseB_R = 1;	// ^

                        // Current A = 38%
                        // Current B = -71%
                        AI0_L = 1;	//Sets current of Phase A for Left Motor
                        AI1_L = 0;	// ^
                        BI0_L = 0;	//Sets current of Phase B for Left Motor
                        BI1_L = 1;	// ^

                        // Current A = 71%
                        // Current B = 38%
                        AI0_R = 0;	//Sets current of Phase A for Right Motor
                        AI1_R = 1;	// ^
                        BI0_R = 1;	//Sets current of Phase B for Right Motor
                        BI1_R = 0;	// ^

		            break;

	        	case 2:
		            	// Phase +-/++
		            	PhaseA_L = 1;   // Sets the Phase of the Left Motor
                        PhaseB_L = 0;	// ^
                        PhaseA_R = 1;   // Sets the Phase of the Right Motor
                        PhaseB_R = 1;	// ^

                        // Current A = 0%
                        // Current B = -100%
                        AI0_L = 1;	//Sets current of Phase A for Left Motor
                        AI1_L = 1;	// ^
                        BI0_L = 0;	//Sets current of Phase B for Left Motor
                        BI1_L = 0;	// ^

                        // Current A = 38%
                        // Current B = 71%
                        AI0_R = 1;	//Sets current of Phase A for Right Motor
                        AI1_R = 0;	// ^
                        BI0_R = 0;	//Sets current of Phase B for Right Motor
                        BI1_R = 1;	// ^

		            break;

	        	case 3:
		            	// Phase --/-+
		            	PhaseA_L = 0;   // Sets the Phase of the Left Motor
		            	PhaseB_L = 0;	// ^
		            	PhaseA_R = 0;   // Sets the Phase of the Right Motor
		            	PhaseB_R = 1;	// ^

                        // Current A = -38%
                        // Current B = -71%
                        AI0_L = 1;	//Sets current of Phase A for Left Motor
                        AI1_L = 0;	// ^
                        BI0_L = 0;	//Sets current of Phase B for Left Motor
                        BI1_L = 1;	// ^

                        // Current A = 0%
                        // Current B = 100%
                        AI0_R = 1;	//Sets current of Phase A for Right Motor
                        AI1_R = 1;	// ^
                        BI0_R = 0;	//Sets current of Phase B for Right Motor
                        BI1_R = 0;	// ^

		            break;

	        	case 4:
		            	// Phase --/-+
		            	PhaseA_L = 0;   // Sets the Phase of the Left Motor
		            	PhaseB_L = 0;	// ^
		            	PhaseA_R = 0;   // Sets the Phase of the Right Motor
		            	PhaseB_R = 1;	// ^

                        // Current A = -71%
                        // Current B = -38%
                        AI0_L = 0;	//Sets current of Phase A for Left Motor
                        AI1_L = 1;	// ^
                        BI0_L = 1;	//Sets current of Phase B for Left Motor
                        BI1_L = 0;	// ^

                        // Current A = -38%
                        // Current B = 71%
                        AI0_R = 1;	//Sets current of Phase A for Right Motor
                        AI1_R = 0;	// ^
                        BI0_R = 0;	//Sets current of Phase B for Right Motor
                        BI1_R = 1;	// ^

		            break;

	        	case 5:
		            	// Phase --/-+
		            	PhaseA_L = 0;   // Sets the Phase of the Left Motor
		            	PhaseB_L = 0;	// ^
		            	PhaseA_R = 0;   // Sets the Phase of the Right Motor
		            	PhaseB_R = 1;	// ^

                        // Current A = -100%
                        // Current B = 0%
                        AI0_L = 0;	//Sets current of Phase A for Left Motor
                        AI1_L = 0;	// ^
                        BI0_L = 1;	//Sets current of Phase B for Left Motor
                        BI1_L = 1;	// ^

                        // Current A = -71%
                        // Current B = 38%
                        AI0_R = 0;	//Sets current of Phase A for Right Motor
                        AI1_R = 1;	// ^
                        BI0_R = 1;	//Sets current of Phase B for Right Motor
                        BI1_R = 0;	// ^

		            break;

			case 6:
		            	// Phase -+/--
		            	PhaseA_L = 0;   // Sets the Phase of the Left Motor
		            	PhaseB_L = 1;	// ^
		            	PhaseA_R = 0;   // Sets the Phase of the Right Motor
		            	PhaseB_R = 0;	// ^

                        // Current A = -71%
                        // Current B = 38%
                        AI0_L = 0;	//Sets current of Phase A for Left Motor
                        AI1_L = 1;	// ^
                        BI0_L = 1;	//Sets current of Phase B for Left Motor
                        BI1_L = 0;	// ^

                        // Current A = -100%
                        // Current B = 0%
                        AI0_R = 0;	//Sets current of Phase A for Right Motor
                        AI1_R = 0;	// ^
                        BI0_R = 1;	//Sets current of Phase B for Right Motor
                        BI1_R = 1;	// ^

		            break;

	        	case 7:
		            	// Phase -+/--
		            	PhaseA_L = 0;   // Sets the Phase of the Left Motor
		            	PhaseB_L = 1;	// ^
		            	PhaseA_R = 0;   // Sets the Phase of the Right Motor
		            	PhaseB_R = 0;	// ^

                        // Current A = -38%
                        // Current B = 71%
                        AI0_L = 1;	//Sets current of Phase A for Left Motor
                        AI1_L = 0;	// ^
                        BI0_L = 0;	//Sets current of Phase B for Left Motor
                        BI1_L = 1;	// ^

                        // Current A = -71%
                        // Current B = -38%
                        AI0_R = 0;	//Sets current of Phase A for Right Motor
                        AI1_R = 1;	// ^
                        BI0_R = 1;	//Sets current of Phase B for Right Motor
                        BI1_R = 0;	// ^

		            break;

	        	case 8:
		            	// Phase -+/--
		            	PhaseA_L = 0;   // Sets the Phase of the Left Motor
		            	PhaseB_L = 1;	// ^
		            	PhaseA_R = 0;   // Sets the Phase of the Right Motor
		            	PhaseB_R = 0;	// ^

                        // Current A = 0%
                        // Current B = 100%
                        AI0_L = 1;	//Sets current of Phase A for Left Motor
                        AI1_L = 1;	// ^
                        BI0_L = 0;	//Sets current of Phase B for Left Motor
                        BI1_L = 0;	// ^

                        // Current A = -38%
                        // Current B = -71%
                        AI0_R = 1;	//Sets current of Phase A for Right Motor
                        AI1_R = 0;	// ^
                        BI0_R = 0;	//Sets current of Phase B for Right Motor
                        BI1_R = 1;	// ^

		            break;

	        	case 9:
		            	// Phase ++/+-
		            	PhaseA_L = 1;   // Sets the Phase of the Left Motor
		            	PhaseB_L = 1;	// ^
		            	PhaseA_R = 1;   // Sets the Phase of the Right Motor
		            	PhaseB_R = 0;	// ^

                        // Current A = 38%
                        // Current B = 71%
                        AI0_L = 1;	//Sets current of Phase A for Left Motor
                        AI1_L = 0;	// ^
                        BI0_L = 0;	//Sets current of Phase B for Left Motor
                        BI1_L = 1;	// ^

                        // Current A = 0%
                        // Current B = -100%
                        AI0_R = 1;	//Sets current of Phase A for Right Motor
                        AI1_R = 1;	// ^
                        BI0_R = 0;	//Sets current of Phase B for Right Motor
                        BI1_R = 0;	// ^

		            break;

		        case 10:
		            	// Phase ++/+-
		            	PhaseA_L = 1;   // Sets the Phase of the Left Motor
		            	PhaseB_L = 1;	// ^
		            	PhaseA_R = 1;   // Sets the Phase of the Right Motor
		            	PhaseB_R = 0;	// ^

                        // Current A = 71%
                        // Current B = 38%
                        AI0_L = 0;	//Sets current of Phase A for Left Motor
                        AI1_L = 1;	// ^
                        BI0_L = 1;	//Sets current of Phase B for Left Motor
                        BI1_L = 0;	// ^

                        // Current A = 38%
                        // Current B = -71%
                        AI0_R = 1;	//Sets current of Phase A for Right Motor
                        AI1_R = 0;	// ^
                        BI0_R = 0;	//Sets current of Phase B for Right Motor
                        BI1_R = 1;	// ^

		        	break;

	        	case 11:
                    // Phase ++/+-
                    PhaseA_L = 1;   // Sets the Phase of the Left Motor
                    PhaseB_L = 1;	// ^
                    PhaseA_R = 1;   // Sets the Phase of the Right Motor
                    PhaseB_R = 0;	// ^

                    // Current A = 100%
                    // Current B = 0%
                    AI0_L = 0;	//Sets current of Phase A for Left Motor
                    AI1_L = 0;	// ^
                    BI0_L = 1;	//Sets current of Phase B for Left Motor
                    BI1_L = 1;	// ^

                    // Current A = 71%
                    // Current B = -38%
                    AI0_R = 0;	//Sets current of Phase A for Right Motor
                    AI1_R = 1;	// ^
                    BI0_R = 1;	//Sets current of Phase B for Right Motor
                    BI1_R = 0;	// ^

                    break;
	    	}
        //Setting Phases to Correct Values
        PORTEbits.RE8 = PhaseB_L;
        PORTEbits.RE9 = PhaseA_L;

        PORTAbits.RA14 = PhaseB_R;
        PORTAbits.RA15 = PhaseA_R;

  		//Setting Currents to Correct Values
  		PORTBbits.RB4 = AI0_L;
  		PORTBbits.RB5 = AI1_L;
  		PORTBbits.RB2 = BI0_L;
  		PORTBbits.RB3 = BI1_L;

  		PORTDbits.RD10 = AI0_R;
  		PORTDbits.RD11 = AI1_R;
  		PORTDbits.RD8 = BI0_R;
  		PORTDbits.RD9 = BI1_R;

      if (Switch_Event() == 1){	// Break case for if the event button is pressed, turns off LEDS and returns
  		    Lights_Brakes(0);	// the amount of steps taken so far
          Motor_Off();
  		      return i+1;
          }

      if( i <= accel ){		// Reduces the delay by 30 us for each step taking during the acceleration
              __delay_us(delay);
              delay = delay - 30;
          }
      else if(i == decel){		// Turns on the Break lights for decelerations
  		    Lights_Brakes(1);
          	}
      else if( i > decel ){		// Increases the delay by 30 us for each step taking during the deceleration
  		    __delay_us(delay);
  		      delay = delay + 30;
          }
      else{
  	    	__delay_us(1483);
          	}

  	if (i % 30 == 0){		// Updates the display each step
  		    Display_Moving();
		}
	}
  Lights_Brakes(0);		// Turns off brake lights to make sure no LEDs stay on after movement
  Motor_Off();
  return steps;
}
