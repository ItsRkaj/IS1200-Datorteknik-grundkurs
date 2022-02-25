//-----------------------------
// Written by johvh & davidjo2.
//-----------------------------

#include <stdint.h>
#include <pic32mx.h>
#include "gameHeader.h"

/* get input from switches */
int getsw(void) {
    return (PORTD & 0xF00) >> 8;
}

/* get input from buttons */
int getbtns(void) {
    return PORTD >> 5 & 0x7;
}

/* get input from first button */
int getbtn1(void){
    return PORTF & 0x2;
}
