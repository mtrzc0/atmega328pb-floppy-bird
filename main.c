#include <avr/io.h>

int main(void) 
{
    DDRB=0xFF;
    for (uint8_t i=0;i<10;i++)
        PORTB|=(1<<i);
    PORTB^=PORTB;
}