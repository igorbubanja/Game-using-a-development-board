#include "system.h"
#include "pacer.h"
#include <avr/io.h>
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"



void display_character(char character);

void display_string(char *string);

void display_outcome(uint8_t number, uint8_t number2, char max);
