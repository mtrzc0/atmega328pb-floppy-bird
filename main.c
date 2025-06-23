#include <avr/io.h>

#include "keyboard_driver.h"

int main(void) 
{
    keyboardRead();
    while(1){}
}