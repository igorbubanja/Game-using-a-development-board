/* Authors: Igor Bubanja, Danny Kim */
/* File: game.c */
/* Purpose: A game where two players receive numbers from an array and add it to their total.
 * The player who gets a total closest to 9 without going over wins */
 /* Date: 15 October 2015 */


#include "system.h"
#include "pacer.h"
#include <avr/io.h>
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "display.h"
#include "display.c"
#include "deck.h"
#include "deck.c"

#define PACER_RATE 500
#define MESSAGE_RATE 1
#define MAX_NUMBER '9'


int main(void)
{

    TCCR1A = 0x00;
    TCCR1B = 0x05;
    TCCR1C = 0x00;
    
	/* initialise the array that the players will receive their numbers from */ 
    int deck[] = { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3 };
    randomise(deck, 12);

	/* Initialise the LED */ 
    DDRC |= (1 << 2);           
    DDRC &= ~(1 << 7);

    char number = '0';			//the runnung total
    char number2 = 'G';         //The opponent's total. Number2 is initialised to 'G' so that we can tell if we have received a transmission for the opponents number yet.


    

    system_init();

    tinygl_init(PACER_RATE);    
    tinygl_font_set(&font5x7_1);

    navswitch_init();
    tinygl_text_speed_set(MESSAGE_RATE);

    /* Initialise IR driver */
    ir_uart_init();

    TCCR1A = 0x00;
    TCCR1B = 0x05;
    TCCR1C = 0x00;

    uint8_t index = 0;
    ir_uart_putc(index);
    uint8_t transmitted = 0;

    while (1) {

        tinygl_update();
        navswitch_update();
        
		/* Display '0'. This statement will only run before the NORTH push event occurs */
        if (number == '0') {
            display_character(number);
        }

		/* The funkit is continuously reading the transmission from the other funkit. */
        if (ir_uart_read_ready_p()) {   
            char received = ir_uart_getc();
            if (received == 'Z') { // 'Z' is transmitted when the opponent is ready to end the round. The round only ends when both players are ready to finish.
                tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
                display_outcome(number, number2, MAX_NUMBER);
            } else if (received >= '0') {
                number2 = received;
                PORTC = PORTC | (1 << 2);       //turn blue led on

            } else {
                index = received;

            }
        }


		/* User getting another number from the array and adding it to their total */
        if (navswitch_push_event_p(NAVSWITCH_NORTH) && transmitted == 0) {

            number += deck[index];
            index++;
            ir_uart_putc(index);
            if (number <= MAX_NUMBER) {
                display_character(number);
            } else {
                display_character('X'); //condition when the user's total has exceeded the limit of 9
            }
        }

        /* Transmit the number over IR on a NAVSWITCH_PUSH event. */
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            transmitted = 1;
            ir_uart_putc(number);

        }

		/* Show the outcome of the round with a NAVSWITCH_WEST event */	
        if (navswitch_push_event_p(NAVSWITCH_WEST) && transmitted == 1
            && number2 != 'G') {
            tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
            display_outcome(number, number2, MAX_NUMBER); //display the outcome
            ir_uart_putc('Z'); //transmit 'Z' to tell the opponent that you are ready to end the round
        }


    }


    return 0;

}
