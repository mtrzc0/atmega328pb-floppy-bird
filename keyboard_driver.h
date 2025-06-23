#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t keyboardRead(void);
void keyboardInit(void);

#endif