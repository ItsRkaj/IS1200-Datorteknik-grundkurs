/*sprites.c
	Created by Oliver Wilén & Filip Hedlund
	Last modified 2018-03-04 by Oliver Wilén & Filip Hedlund*/
#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

//Returns value of swiches
int getsw(void)
{
	return 0xF & (PORTD >> 8);
}

//Returns value of buttons
int getbtns(void)
{
	return 0x7 & (PORTD >> 5);
}
