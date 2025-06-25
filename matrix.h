
#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h> // zaprawa
#include <avr/interrupt.h> // przerwania

// fajne globalki
#define F_CPU 16000000UL
#define COLS 8
#define ROWS 8

// Bufor stanu matrycy: każdy bajt to jedna kolumna, bity to wiersze (1 = LED zapalona)
extern volatile uint8_t matrix[COLS];
extern volatile uint8_t current_col;

// Inicjalizacja portów i timera do sterownika
void matrix_init(void);
// Ustawienie pojedynczego piksela (col, row, on(1)/off(0))
void matrix_set(uint8_t col, uint8_t row, uint8_t on);
// Wyczyszczenie całego bufora - get zeroed B)
void matrix_clear(void);

#endif 