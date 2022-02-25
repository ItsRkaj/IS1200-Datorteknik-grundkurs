/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */
#include <stdio.h>
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

/* This function is called repetitively from the main program */
void mainMenu( void )
{
    display_clear();
    
    display_string(1, "NO STEP ON SNEK!");
    display_string(2, "1. Start Game");
    display_string(3, "2. Settings");
    
    int btnstate = getbtns();
    
    if(btnstate & 0x8){
        if(DIFFICULTY == 0)
            DIFFICULTY = 1;
        GAMESTATE = 2;
    }
    else if(btnstate & 0x4){
        btn_hold();
        GAMESTATE = 3;
    }
    
    display_update();
}
