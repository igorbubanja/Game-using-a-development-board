/* Authors: Igor Bubanja, Danny Kim */
/* File: deck.c */
/* Purpose: A module used in game.c that is used to randomise the array of numbers (or deck) */
/* Date: 15 October 2015 */

#include "system.h"
#include "pacer.h"
#include <avr/io.h>
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"

/* A utility function to swap two integers */
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* A function to generate a random permutation of deck[] */
void randomise(int deck[], int n)
{
	/* initialise the timer */
    TCCR1A = 0x00;
    TCCR1B = 0x05;
    TCCR1C = 0x00;

    /* Start from the last element and swap one by one. We don't
       need to run for the first element that's why i > 0 */
    int i = n - 1;
    
    while (i > 0)
    {
        /* Pick a random index from 0 to i (NOTE: This method isn't truly random as TCNT1 will be the same each time the program is run,
           but because each player can have an many turns as they want each round will be different) */
        int j = TCNT1 % (i + 1);

        /* Swap deck[i] with the element at random index */
        swap(&deck[i], &deck[j]);
        i--;
    }
}
