#include "keyboard_driver.h"

/*
    KEYBORAD MATRIX LAYOUT
    +---+---+---+---+
    | 1 | 2 | 3 | 4 |
    +---+---+---+---+
    | 5 | 6 | 7 | 8 |
    +---+---+---+---+
    | 9 | 10| 11| 12|
    +---+---+---+---+
    | 13| 14| 15| 16|
    +---+---+---+---+

    FUNCTIONS
    keyboardRead() -> The number of clicked button
 */

uint8_t keyboardRead(void)
{
    //turn on some LEDs on external module
    //aka Hello World
    DDRB=0xFF;
    PORTB=0b00001110;
    return 1;
}