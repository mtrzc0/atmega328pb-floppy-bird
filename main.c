#include <avr/io.h>

int main(void) 
{
    DDRB=0xFF;
    PORTB=0b00001010;
}