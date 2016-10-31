#include "light.h"



void Lights_Headlights(int state)
{
    //sets pin to output and turns light on/off depending on input
    TRISEbits.TRISE2 = 0;
    PORTEbits.RE2 = state;
}

void Lights_Brakes(int state)
{
    //sets pin to output and turns light on/off depending on input
    TRISEbits.TRISE7 = 0;
    PORTEbits.RE7 = state;
}

void Lights_Reverse(int state)
{
    //sets pin to output and turns light on/off depending on input
    TRISEbits.TRISE6 = 0;
    PORTEbits.RE6 = state;
}

void Lights_Indicate_Left(int state)
{
    //sets pin to output and turns light on/off depending on input
    TRISEbits.TRISE3 = 0;
    PORTEbits.RE3 = state;
}

void Lights_Indicate_Right(int state)
{
    //sets pin to output and turns light on/off depending on input
    TRISEbits.TRISE5 = 0;
    PORTEbits.RE5 = state;
}

void Lights_Heartbeat(int state) 
{
    //sets pin to output and turns light on/off depending on input
    TRISEbits.TRISE4 = 0;
    PORTEbits.RE4 = state;
}
