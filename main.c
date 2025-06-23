#include "keyboard_driver.h"

int main(void) 
{
    keyboardInit();
    keyboardRead();
    while(1);
}