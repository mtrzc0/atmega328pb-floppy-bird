#include "matrix.h" 


/*
Tutaj pinout jeba**** leda 8x8
Col - kolumny - sterowane z PORTB (1-6) i PORTC (7-8)
Row - sterowane z port D

Schemat, żeby świeciło - row zwieramy do masy, col wystawiamy wysokie 


                 PD3 row 4  ________________________ col 1 -----[R]----- PB0
                 PD1 row 2  ___| 1              |___ col 2 -----[R]----- PB1
   PC0 -----[R]----- col 7  ___| 0              |___ row 7 PD6
   PB5 -----[R]----- col 6  ___| 8              |___ col 8 -----[R]----- PC1
                 PD0 row 1  ___| 8              |___ row 5 PD4
   PB3 -----[R]----- col 4  ___| A              |___ col 3 -----[R]----- PB2
                 PD2 row 3  ___| B              |___ col 5 -----[R]----- PB4
                 PD5 row 6  ___|________________|___ row 8 PD7
    





*/

// Maski bitów kolumn na portb, one wyglądają tak: _BV(PB1) =  0b00000010, 6 i 7 są na portc 
static const uint8_t col_mask[COLS] = {
    _BV(PB0), _BV(PB1), _BV(PB2),
    _BV(PB3), _BV(PB4), _BV(PB5), _BV(PC0), _BV(PC1)
};
// Maski bitów wierszy PORTD, tak samo działają 
static const uint8_t row_mask[ROWS] = {
    _BV(PD0), _BV(PD1), _BV(PD2), _BV(PD3),
    _BV(PD4), _BV(PD5), _BV(PD6), _BV(PD7)
};

volatile uint8_t matrix[COLS]; //święta matryca
volatile uint8_t current_col = 0; // pomocnicze

void matrix_init(void) {
    // Konfiguracja portów jako wyjścia
    DDRB = 0b00111111;
    DDRD = 0xFF;
    DDRC = 0b00000011;
    // Wyłącz wszystkie kolumny i ustaw wszystkie wiersze na high (420 69)
    PORTB = 0x00;
    PORTD |= 0xFF;
    PORTC |= 0b00000011;

    // Timer1 CTC: nie bardzo wiem jak to działa, ale tak jest w bibliotece xdd
    TCCR1B = _BV(WGM12) | _BV(CS11) | _BV(CS10); // ustawia porównywanie do OCR1A i dzieli zegar 16MHz/64
    OCR1A  = 400; // no tutaj własnie to porównynwanie 
    TIMSK1 = _BV(OCIE1A); //to w jakiś sposób zezwala żeby wszystko się działo (pomocy xddd)
    sei();
}

// użyteczna wywołanie
void matrix_set(uint8_t col, uint8_t row, uint8_t on) {
    if (col < COLS && row < ROWS) {
        if (on) matrix[col] |=  row_mask[row];
        else    matrix[col] &= ~row_mask[row];
    }
}
// get  zeroed  B)
void matrix_clear(void) {
    for (uint8_t i = 0; i < COLS; i++) matrix[i] = 0;
}

// ISR - stary, działał tylko na PB+PD
/*
ISR(TIMER1_COMPA_vect) {
    PORTB &= ~col_mask[current_col];
    PORTD |=  0xFF;
    current_col = (current_col + 1) % COLS;
    PORTB |=  col_mask[current_col];
    PORTD &= ~matrix[current_col];
}
*/

//nowy, działa na portb + portc + portd
ISR(TIMER1_COMPA_vect) {
    // wyłączanie poprzeniej kolumny, pierwsze 6 portb, reszta portc 
    if (current_col < 6) {
        PORTB &= ~col_mask[current_col];
    } else {
        PORTC &= ~col_mask[current_col]; // col_mask[6]=_BV(PC0), col_mask[7]=_BV(PC1)
    }
    // Zresetuj wiersze (zaporowo wszystkie diody)
    PORTD |= 0xFF;

    // Przejdź do następnej kolumny
    current_col = (current_col + 1) % COLS;

    // Włącz nową kolumnę na odpowiednim porcie
    if (current_col < 6) {
        PORTB |= col_mask[current_col];
    } else {
        PORTC |= col_mask[current_col];
    }
    // Wszystkie diody do masy => przewodzą (i nawet świecą)
    PORTD &= ~matrix[current_col];
}
