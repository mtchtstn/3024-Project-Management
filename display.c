#include "display.h"
#include "coords.h"
#include <string.h>

static int __display_on[7];
static int __display_values_current[7];
static int __display_moving_place;

void Display_Current_Character(int display);

// Initialise display variables
void Display_Init()
{
    int i;
    for (i = 0; i < 7; i++)
    {
        __display_on[i] = 0;
        __display_values_current[i] = 0;
    }
    __display_moving_place = 0;
}

// Scroll through displays and if they are on display their respective character for 100us
void Display_Keep_Alive()
{
    int i;
    for (i = 0; i < 7; i++)
    {
        if (__display_on[i])
        {
            Display_Current_Character(i);
            __delay_us(100);
        }
    }
}

// Scroll a moving | along the display for when motor is running
void Display_Moving()
{
    Display_Update_Character(__display_moving_place, 'I');
    Display_Current_Character(__display_moving_place);
    __display_moving_place--;
    if (__display_moving_place < 0)
    {
        __display_moving_place = 6;
    }
}

// Separate string into characters for each display
void Display_String(char* string)
{
    int length = strlen(string);
    int i;
    for (i = length; i >= 0; i--)
    {
        Display_Update_Character(i, string[length - (i + 1)]);
    }
    for (i = 6; i >= length; i--)
    {
        Display_Update_Character(i, ' ');        
    }
}

// Save passed character for passed display to display later
void Display_Update_Character(int display, char character)
{
    int characterCode;
    
    // Numerals
    if (character == '0')
    {
        characterCode = CHAR_0;
    }
    else if (character == '1')
    {
        characterCode = CHAR_1;
    }
    else if (character == '2')
    {
        characterCode = CHAR_2;
    }
    else if (character == '3')
    {
        characterCode = CHAR_3;        
    }
    else if (character == '4')
    {
        characterCode = CHAR_4;        
    }
    else if (character == '5')
    {
        characterCode = CHAR_5;        
    }
    else if (character == '6')
    {
        characterCode = CHAR_6;        
    }
    else if (character == '7')
    {
        characterCode = CHAR_7;        
    }
    else if (character == '8')
    {
        characterCode = CHAR_8;        
    }
    else if (character == '9')
    {
        characterCode = CHAR_9;        
    }
    // Alpha    
    else if (character == 'A' || character == 'a')
    {
        characterCode = CHAR_A;        
    }
    else if (character == 'B' || character == 'b')
    {
        characterCode = CHAR_B;        
    }
    else if (character == 'C' || character == 'c')
    {
        characterCode = CHAR_C;        
    }
    else if (character == 'D' || character == 'd')
    {
        characterCode = CHAR_D;        
    }
    else if (character == 'E' || character == 'e')
    {
        characterCode = CHAR_E;        
    }
    else if (character == 'F' || character == 'f')
    {
        characterCode = CHAR_F;        
    }
    else if (character == 'G' || character == 'g')
    {
        characterCode = CHAR_G;        
    }
    else if (character == 'H' || character == 'h')
    {
        characterCode = CHAR_H;        
    }
    else if (character == 'I' || character == 'i')
    {
        characterCode = CHAR_I;        
    }
    else if (character == 'J' || character == 'j')
    {
        characterCode = CHAR_J;        
    }
    else if (character == 'K' || character == 'k')
    {
        characterCode = CHAR_K;        
    }
    else if (character == 'L' || character == 'l')
    {
        characterCode = CHAR_L;        
    }
    else if (character == 'M' || character == 'm')
    {
        characterCode = CHAR_M;        
    }
    else if (character == 'N' || character == 'n')
    {
        characterCode = CHAR_N;        
    }
    else if (character == 'O' || character == 'o')
    {
        characterCode = CHAR_O;        
    }
    else if (character == 'P' || character == 'p')
    {
        characterCode = CHAR_P;        
    }
    else if (character == 'Q' || character == 'q')
    {
        characterCode = CHAR_Q;        
    }
    else if (character == 'R' || character == 'r')
    {
        characterCode = CHAR_R;        
    }
    else if (character == 'S' || character == 's')
    {
        characterCode = CHAR_S;        
    }
    else if (character == 'T' || character == 't')
    {
        characterCode = CHAR_T;        
    }
    else if (character == 'U' || character == 'u')
    {
        characterCode = CHAR_U;        
    }
    else if (character == 'V' || character == 'v')
    {
        characterCode = CHAR_V;        
    }
    else if (character == 'W' || character == 'w')
    {
        characterCode = CHAR_W;        
    }
    else if (character == 'X' || character == 'x')
    {
        characterCode = CHAR_X;        
    }
    else if (character == 'Y' || character == 'y')
    {
        characterCode = CHAR_Y;        
    }
    else if (character == 'Z' || character == 'z')
    {
        characterCode = CHAR_Z;        
    }
    // Symbols
    else if (character == '-')
    {
        characterCode = CHAR_MINUS;
    }
    
    // Else Error
    else
    {
        characterCode = CHAR_ERR;        
    }
    int data_b = (characterCode<<8);
    
    __display_values_current[display] = data_b;
    __display_on[display] = 1;
    
    // Special case for space, turn off display
    if (character == ' ')
    {
        __display_on[display] = 0;
    }
}

// Actually display a display's saved character
void Display_Current_Character(int display)
{
    int data_b = __display_values_current[display];
    // Set output lines in preparation for latching data
    TRISB &= 0X00FF;
    PORTB = (PORTB&0x00FF)|data_b;

    // Transition the latches clock high
    PORTBbits.RB11 = 1;
    PORTBbits.RB11 = 0;
    
    int displayCode;
    switch (display)
    {
        case 0:
            displayCode = DISP_0;
            break;
        case 1:
            displayCode = DISP_1;
            break;
        case 2:
            displayCode = DISP_2;
            break;
        case 3:
            displayCode = DISP_3;
            break;
        case 4:
            displayCode = DISP_4;
            break;
        case 5:
            displayCode = DISP_5;
            break;
        case 6:
            displayCode = DISP_6;
            break;
        default:
            displayCode = DISP_0;
            break;
    }
    
    PORTB = (PORTB&0x00FF)|(displayCode<<8);
}

// Helper function to generate and display string based on coordinate index
void Display_Coordinate(int coordIndex)
{
    char coordIndexXY[7];
    if( coordIndex == 0)
    {
        strcpy(coordIndexXY, (char*)"0");
    }
    else if( coordIndex == 1)
    {
        strcpy(coordIndexXY, "1");
    }
    else if( coordIndex == 2)
    {
        strcpy(coordIndexXY, "2");
    }
    else if( coordIndex == 3)
    {
        strcpy(coordIndexXY, "3");
    }
    else if( coordIndex == 4)
    {
        strcpy(coordIndexXY, "4");
    }
    else if( coordIndex == 5)
    {
        strcpy(coordIndexXY, "5");
    }
    else if( coordIndex == 6)
    {
        strcpy(coordIndexXY, "6");
    }
    else if( coordIndex == 7)
    {
        strcpy(coordIndexXY, "7");
    }
    else if( coordIndex == 8)
    {
        strcpy(coordIndexXY, "8");
    }
    else if( coordIndex == 9)
    {
        strcpy(coordIndexXY, "9");
    }
    else if( coordIndex == 10)
    {
        strcpy(coordIndexXY, "A");
    }
    else if( coordIndex == 11)
    {
        strcpy(coordIndexXY, "B");
    }
    else if( coordIndex == 12)
    {
        strcpy(coordIndexXY, "C");
    }
    else if( coordIndex == 13)
    {
        strcpy(coordIndexXY, "D");
    }
    else if( coordIndex == 14)
    {
        strcpy(coordIndexXY, "E");
    }
    else if( coordIndex == 15)
    {
        strcpy(coordIndexXY, "F");
    }
    strcat(coordIndexXY, getXCoord(coordIndex));
    strcat(coordIndexXY, getYCoord(coordIndex));
    Display_String(coordIndexXY);
}