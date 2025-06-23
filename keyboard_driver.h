#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#include <avr/io.h>
#include <avr/interrupt.h>

void keyboardInit(void);
void keyboardRead(uint8_t *var);

#endif