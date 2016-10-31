#include "switch.h"
static int down_E;

void Switch_Clear();

int Switch_1() 
{
    Switch_Clear();
  static int state_last = 0, state_curr = 0; // Variables for storing switch state
  int result; // Variable for storing whether or not a switch was pressed

  // Precharge bit-line
  TRISBbits.TRISB15 = 0;
  PORTBbits.RB15 = 1;
  TRISBbits.TRISB15 = 1;
  __delay_us(1);

  // Read in switch state
  state_curr = PORTBbits.RB15;

  // Record a button-press if the switch state has transitioned from un-pressed to pressed
  result = state_last & ~state_curr;
  // Set state_last in preparation for next call to get_switch()
  state_last = state_curr;

  return result;
}

int Switch_2() 
{
    Switch_Clear();

  static int state_last = 0, state_curr = 0; // Variables for storing switch state
  int result; // Variable for storing whether or not a switch was pressed

  // Precharge bit-line
  TRISBbits.TRISB14 = 0;
  PORTBbits.RB14 = 1;
  TRISBbits.TRISB14 = 1;
  __delay_us(1);

  // Read in switch state
  state_curr = PORTBbits.RB14;

  // Record a button-press if the switch state has transitioned from un-pressed to pressed
  result = state_last & ~state_curr;
  // Set state_last in preparation for next call to get_switch()
  state_last = state_curr;

  return result;
}

int Switch_3() 
{
    Switch_Clear();

  static int state_last = 0, state_curr = 0; // Variables for storing switch state
  int result; // Variable for storing whether or not a switch was pressed

  // Precharge bit-line
  TRISBbits.TRISB13 = 0;
  PORTBbits.RB13 = 1;
  TRISBbits.TRISB13 = 1;
  __delay_us(1);

  // Read in switch state
  state_curr = PORTBbits.RB13;

  // Record a button-press if the switch state has transitioned from un-pressed to pressed
  result = state_last & ~state_curr;
  // Set state_last in preparation for next call to get_switch()
  state_last = state_curr;

  return result;
}

int Switch_4() 
{
    Switch_Clear();

  static int state_last = 0, state_curr = 0; // Variables for storing switch state
  int result; // Variable for storing whether or not a switch was pressed

  // Precharge bit-line
  TRISBbits.TRISB12 = 0;
  PORTBbits.RB12 = 1;
  TRISBbits.TRISB12 = 1;
  __delay_us(1);

  // Read in switch state
  state_curr = PORTBbits.RB12;

  // Record a button-press if the switch state has transitioned from un-pressed to pressed
  result = state_last & ~state_curr;
  // Set state_last in preparation for next call to get_switch()
  state_last = state_curr;

  return result;
}

int Switch_5() 
{
    Switch_Clear();

  static int state_last = 0, state_curr = 0; // Variables for storing switch state
  int result; // Variable for storing whether or not a switch was pressed

  
  // Precharge bit-line
  TRISBbits.TRISB8 = 0;
  PORTBbits.RB8 = 1;
  TRISBbits.TRISB8 = 1;
  __delay_us(1);

  // Read in switch state
  state_curr = PORTBbits.RB8;

  // Record a button-press if the switch state has transitioned from un-pressed to pressed
  result = state_last & ~state_curr;
  // Set state_last in preparation for next call to get_switch()
  state_last = state_curr;

  return result;
}

int Switch_6() 
{
    Switch_Clear();

  static int state_last = 0, state_curr = 0; // Variables for storing switch state
  int result; // Variable for storing whether or not a switch was pressed

  // Precharge bit-line
  TRISBbits.TRISB9 = 0;
  PORTBbits.RB9 = 1;
  TRISBbits.TRISB9 = 1;
  __delay_us(1);

  // Read in switch state
  state_curr = PORTBbits.RB9;

  // Record a button-press if the switch state has transitioned from un-pressed to pressed
  result = state_last & ~state_curr;
  // Set state_last in preparation for next call to get_switch()
  state_last = state_curr;

  return result;
}

int Switch_7() 
{
    Switch_Clear();
  static int state_last = 0, state_curr = 0; // Variables for storing switch state
  int result; // Variable for storing whether or not a switch was pressed

  // Precharge bit-line
  TRISBbits.TRISB10 = 0;
  PORTBbits.RB10 = 1;
  TRISBbits.TRISB10 = 1;
  __delay_us(1);

  // Read in switch state
  state_curr = PORTBbits.RB10;

  // Record a button-press if the switch state has transitioned from un-pressed to pressed
  result = state_last & ~state_curr;
  // Set state_last in preparation for next call to get_switch()
  state_last = state_curr;

  return result;
}



//prevents buttons turning on display
void Switch_Clear()
{
   int data_b = (0<<8);   

   TRISB &= 0X00FF;
   PORTB = (PORTB&0x00FF)|data_b;

   PORTBbits.RB11 = 1;
   PORTBbits.RB11 = 0;

   PORTB = (PORTB&0x00FF)|(0x77<<8);
}

int Switch_Event() 
{    
    // Precharge bit-line
    TRISDbits.TRISD13 = 0;
    PORTDbits.RD13 = 1;
    TRISDbits.TRISD13 = 1; 
    
    __delay_us(1);
    
    // Read in event state
    down_E = PORTDbits.RD13;
  
    //if event switch is held of 5us will trigger event on, due to flickerings of event switch.
    //function maintains constant delay
    if (down_E)
    {
        if(Switch_Eventself() == 1)
        {
            if(Switch_Eventself() == 1)
            {
                if(Switch_Eventself() == 1)
                {
                    if(Switch_Eventself() == 1)
                    {
                        if(Switch_Eventself() == 1)
                        {
                            if(Switch_Eventself() == 1)
                            {
                                if(Switch_Eventself() == 1)
                                {
                                    if(Switch_Eventself() == 1)
                                    {
                                        return 1;
                                    }
                                }
                                else
                                {
                                    __delay_us(2);
                                }
                            }
                            else
                            {
                                __delay_us(4);
                            }
                        }
                        else
                        {
                            __delay_us(6);
                        }
                    }
                    else
                    {
                        __delay_us(8);
                    }
                }
                else
                {
                    __delay_us(10);
                }
            }
            else
            {
                __delay_us(12);
            }
        }
        else
        {
            __delay_us(14);
        }
                    
    }
    return 0;
}

int Switch_Eventself(void)
{
    //precharge bit line
    TRISDbits.TRISD13 = 0;
    PORTDbits.RD13 = 1;
    TRISDbits.TRISD13 = 1; 
    
    __delay_us(2);

    //returns event state
    int down_E = PORTDbits.RD13;
    return down_E;
}
