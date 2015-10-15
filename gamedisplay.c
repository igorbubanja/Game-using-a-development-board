/* Authors: Igor Bubanja, Danny Kim */
/* File: game.c */
/* Purpose:A module used for game.c that contains all of the display functions */
 /* Date: 15 October 2015 */



#include "system.h"
#include "pacer.h"
#include <avr/io.h>
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "module1.h"


/* A private function that calculates the outcome of a round based the player's and the opponent's totals. This function is only used in the display_outcome function */
static char *outcome(uint8_t number, uint8_t number2, char max)
{
    if (number <= max && number2 > max) {
        return ("WIN");
    }

    else if (number > max && number2 <= max) {
        return ("LOSE");
    }

    else if (number > max && number2 > max) {
        return ("DRAW");
    }

    else if (number == number2) {
        return ("DRAW");
    }

    else if (number2 > number && number <= max && number2 <= max) {
        return ("LOSE");
    }

    else if (number > number2 && number <= max && number2 <= max) {
        return ("WIN");
    }


    return ("I");

}

/* Displays a character using tinygl */
void display_character(char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text(buffer);
}

/* Displays a string using tinygl */
void display_string(char *string)
{
    tinygl_text(string);
}

/* A function to display the outcome of a round */
void display_outcome(uint8_t number, uint8_t number2, char max)
{
    display_string(outcome(number, number2, max));
}
