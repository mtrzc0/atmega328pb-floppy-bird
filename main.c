#include "keyboard_driver.h"

int main(void) 
{
    keyboardInit();
    uint8_t clickedBtn=0;
    keyboardRead(&clickedBtn);
}