// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _display_H
#define	_display_H

#include <p30fxxxx.h>
#define FCY     12000000ULL
#include <libpic30.h>

// Define mappings from character segment to hex digit
#define SEG_A 0x80
#define SEG_B 0x40  //    a
#define SEG_C 0x20  //  f   b
#define SEG_D 0x10  //    g
#define SEG_E 0x01  //  e   c
#define SEG_F 0x02  //    d
#define SEG_G 0x04

// Define mappings from characters to character segments
#define CHAR_ERR SEG_A +                 SEG_D +                 SEG_G // Triple equals for ERROR (so it doesnt look like anything)

#define CHAR_0   SEG_A + SEG_B + SEG_C + SEG_D + SEG_E + SEG_F
#define CHAR_1           SEG_B + SEG_C
#define CHAR_2   SEG_A + SEG_B +         SEG_D + SEG_E +         SEG_G
#define CHAR_3   SEG_A + SEG_B + SEG_C + SEG_D +                 SEG_G
#define CHAR_4           SEG_B + SEG_C +                 SEG_F + SEG_G
#define CHAR_5   SEG_A +         SEG_C + SEG_D +         SEG_F + SEG_G
#define CHAR_6   SEG_A +         SEG_C + SEG_D + SEG_E + SEG_F + SEG_G
#define CHAR_7   SEG_A + SEG_B + SEG_C
#define CHAR_8   SEG_A + SEG_B + SEG_C + SEG_D + SEG_E + SEG_F + SEG_G
#define CHAR_9   SEG_A + SEG_B + SEG_C + SEG_D +         SEG_F + SEG_G

#define CHAR_A   SEG_A + SEG_B + SEG_C +         SEG_E + SEG_F + SEG_G
#define CHAR_B                   SEG_C + SEG_D + SEG_E + SEG_F + SEG_G    
#define CHAR_C   SEG_A +                 SEG_D + SEG_E + SEG_F    
#define CHAR_D           SEG_B + SEG_C + SEG_D + SEG_E +         SEG_G    
#define CHAR_E   SEG_A +                 SEG_D + SEG_E + SEG_F + SEG_G
#define CHAR_F   SEG_A +                         SEG_E + SEG_F + SEG_G
#define CHAR_G   CHAR_9
#define CHAR_H           SEG_B + SEG_C +         SEG_E + SEG_F + SEG_G
#define CHAR_I                                   SEG_E + SEG_F
#define CHAR_J           SEG_B + SEG_C + SEG_D
#define CHAR_K                           SEG_D + SEG_E + SEG_F + SEG_G    
#define CHAR_L                           SEG_D + SEG_E + SEG_F
#define CHAR_M   SEG_A + SEG_B + SEG_C +         SEG_E + SEG_F
#define CHAR_N                   SEG_C +         SEG_E +         SEG_G
#define CHAR_O   CHAR_0
#define CHAR_P   SEG_A + SEG_B +                 SEG_E + SEG_F + SEG_G
#define CHAR_Q   CHAR_O
#define CHAR_R                                   SEG_E +       + SEG_G
#define CHAR_S   CHAR_5
#define CHAR_T                                   SEG_E + SEG_F + SEG_G
#define CHAR_U           SEG_B + SEG_C + SEG_D + SEG_E + SEG_F
#define CHAR_V   CHAR_U
#define CHAR_W   CHAR_U
#define CHAR_X   CHAR_ERR // X cant be realised
#define CHAR_Y           SEG_B + SEG_C + SEG_D +         SEG_F + SEG_G
#define CHAR_Z   CHAR_2
#define CHAR_MINUS                                               SEG_G

#define DISP_0   0x77
#define DISP_1   0xB7
#define DISP_2   0xD7
#define DISP_3   0xE7
#define DISP_4   0xF6
#define DISP_5   0xF5
#define DISP_6   0xF3

void Display_Init();
void Display_Keep_Alive();
void Display_Update_Character(int display, char character);
void Display_String(char* string);
void Display_Moving();
void Display_Coordinate(int coordIndex);

#endif	/* XC_HEADER_TEMPLATE_H */

