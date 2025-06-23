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

    CONNECTIONS
    COL1...4 -> PORTB.0...PORTB.3
    ROW1 -> PORTD.0

    FUNCTIONS
    keyboardInit() -> Set ISR
    keyboardRead() -> The number of clicked button
 */

 static uint8_t keyboardBtnId = 0;

ISR(PCINT1_vect)
{
    register uint8_t cols=0;
    register uint8_t rows=0;

    //disable pcint interraupts on portc
    PCMSK1=0xff;
    //set rows as outputs and cols as input
    DDRC=0xf0;
    //set cols to high (pullup) and rows to low
    PORTC=0xCf;
    //read portc cols in low nibble
    cols=PINC&(0x0f);
    
    //set rows as inputs and cols as outputs
    DDRC=0x0f;
    //set rows to high (pullup) and cols to low
    PORTC=0x30;
    //read portc rows in high nibble
    rows=PINC&(0xf0);
    
    //store button position
    keyboardBtnId=rows|cols;
    PORTB=keyboardBtnId;

    //restore rows pcint as interrupt triggers
    PCMSK1=(1<<4)|(1<<5);
}

void keyboardInit(void)
{
    //set up leds
    DDRB=0xff;
    //set up rows as inputs and columns as outputs
    DDRC=0x0f;
    //set up rows to high (pull ups) and columns to low
    PORTC=0x30;
    //select rows as interrupt triggers
    PCMSK1=(1<<4)|(1<<5);
    //enable pcint1
    PCICR=(1<<1);
    sei();
}

uint8_t keyboardRead(void)
{
    return keyboardBtnId;
}