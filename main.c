#include <stdint.h>
#include "matrix.h"
#include <util/delay.h>

int main(void) {
    matrix_init();
    matrix_clear();

    /*
    // swastyka - tak każe obyczaj
   for(uint8_t j = 0; j < COLS; j++){
             for (uint8_t i = 0; i < ROWS; i++) {
             matrix_set(j, i, 1);
            }
        }
    matrix_set(2,0,0);
    matrix_set(2,1,0);
    matrix_set(2,2,0);

    matrix_set(5,5,0);
    matrix_set(5,6,0);
    matrix_set(5,7,0);

    matrix_set(5,2,0);
    matrix_set(6,2,0);
    matrix_set(7,2,0);

    matrix_set(0,5,0);
    matrix_set(1,5,0);
    matrix_set(2,5,0);
    */
    while (1) {
        
         
        //łądnie latające sprawdzanie ledów
        for(uint8_t j = 0; j < COLS; j++){

             for (uint8_t i = 0; i < ROWS; i++) {
             matrix_set(j, i, 1);
             _delay_ms(60);
            }
        }

        for(uint8_t j = 0; j < COLS; j++){

             for (uint8_t i = 0; i < ROWS; i++) {
             matrix_set(j, i, 0);
             _delay_ms(60);
            }
        }
        
        
        // odkomentować do swastyki
        // _delay_ms(1000);
        

       
        
    }
    return 0;
}
