
#include "system.h"
#include "pacer.h"
#include <avr/io.h>
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"


// A utility function to swap to integers
void swap (int *a, int *b);

// A function to generate a random permutation of deck[]
void randomise ( int deck[], int n);
