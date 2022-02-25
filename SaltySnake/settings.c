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
void settings(void)
{
    display_clear();
    
    switch (DIFFICULTY) {
        case 1:
            display_string(0, "1. Easy        *");
            display_string(1, "2. Medium       ");
            display_string(2, "3. Hard         ");
            display_string(3, "4. Back");

            break;
        case 2:
            display_string(0, "1. Easy         ");
            display_string(1, "2. Medium      *");
            display_string(2, "3. Hard         ");
            display_string(3, "4. Back");

            break;
        case 3:
            display_string(0, "1. Easy         ");
            display_string(1, "2. Medium       ");
            display_string(2, "3. Hard        *");
            display_string(3, "4. Back");

            break;
            
        default:
            display_string(0, "1. Easy        *");
            display_string(1, "2. Medium       ");
            display_string(2, "3. Hard         ");
            display_string(3, "4. Back");
            break;
    }
    
    int btnstate = getbtns();
    
    if (btnstate & 0x8) {
        DIFFICULTY = 1;
    }
    else if(btnstate & 0x4){
        DIFFICULTY = 2;
    }
    else if(btnstate & 0x2){
        DIFFICULTY = 3;
    }
    else if(btnstate & 0x1){
        GAMESTATE = 1;
    }
    
    display_update();
}
