/* mipslabmain.c

   This file written 2015 by Axel Isaksson,
   modified 2015, 2017 by F Lundevall

   Latest update 2017-04-21 by F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <stdio.h>
#include <stdlib.h>
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int easy = 100;
int medium = 50;
int hard = 20;

int DIFFICULTY = 100; //Start with easy
int SCORE = 0;
int GAMESTATE = 1; // Start in Main Menu



int main(void) {
        /*
	  This will set the peripheral bus clock to the same frequency
	  as the sysclock. That means 80 MHz, when the microcontroller
	  is running at 80 MHz. Changed 2017, as recommended by Axel.
	*/
	SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
	while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */
	
	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;
	
	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;
	
	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);
	
	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
        SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;
	
	display_init();
	display_update();
	
	labinit(); /* Do any lab-specific initialization */

    void mainMenu(){
        display_clear();
        
        display_string(1, "NO STEP ON SNEK!");
        display_string(2, "1. Start Game");
        display_string(3, "2. Settings");
        
        int btnstate = getbtns();
        
        if(btnstate & 0x8){
            GAMESTATE = 2;
        }
        else if(btnstate & 0x4){
            GAMESTATE = 3;
            btn_hold();
        }
        
        display_update_menu();
    }

    void settings(void)
    {
        display_clear();
        
        switch (DIFFICULTY) {
            case 100:
                display_string(0, "1. Easy        *");
                display_string(1, "2. Medium       ");
                display_string(2, "3. Hard         ");
                display_string(3, "4. Back");

                break;
            case 50:
                display_string(0, "1. Easy         ");
                display_string(1, "2. Medium      *");
                display_string(2, "3. Hard         ");
                display_string(3, "4. Back");

                break;
            case 20:
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
            DIFFICULTY = easy;
        }
        else if(btnstate & 0x4){
            DIFFICULTY = medium;
        }
        else if(btnstate & 0x2){
            DIFFICULTY = hard;
        }
        else if(btnstate & 0x1){
            GAMESTATE = 1;
        }
        
        display_update_menu();
    }
    
    void btn_hold1(void){
        int btnstate;
        while (1) {
            btnstate = getbtns();
            if ((btnstate & 0x8)== 0) {
                return;
            }
        }
    }
    
    void gameOver(){
        char finalscore = (char)SCORE;
        display_clear();
        
        display_string(0, "      GAME      ");
        display_string(1, "      OVER      ");
        display_string(2, "Score:");
        display_string(3, itoaconv(SCORE));
        
        int btnstate = getbtns();
        
        if (btnstate & 0x8) {
            GAMESTATE = 1;
            btn_hold1();
        }
        
        display_update_menu();
    }
    
	while( 1 )
	{
        if(GAMESTATE == 1) {
            mainMenu();
        } else if(GAMESTATE == 2) {
            labinit();
            while(GAMESTATE == 2){
                labwork();
            }
        } else if(GAMESTATE == 3) {
            settings();
        } else if(GAMESTATE == 4) {
            gameOver();
        }
	}
	return 0;
}
