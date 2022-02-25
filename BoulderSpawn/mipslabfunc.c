/* mipslabfunc.c
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson
	 Last modified 2018-03-04 by Oliver Wilén & Filip Hedlund
   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
#include <stdbool.h>
#include <stdlib.h>

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

/* quicksleep:
   A simple function to create a small delay.
   Very inefficient use of computing resources,
   but very handy in some special cases. */
void quicksleep(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 1));
	return SPI2BUF;
}

void display_init(void) {
  DISPLAY_CHANGE_TO_COMMAND_MODE;
	quicksleep(10);
	DISPLAY_ACTIVATE_VDD;
	quicksleep(1000000);

	spi_send_recv(0xAE);
	DISPLAY_ACTIVATE_RESET;
	quicksleep(10);
	DISPLAY_DO_NOT_RESET;
	quicksleep(10);

	spi_send_recv(0x8D);
	spi_send_recv(0x14);

	spi_send_recv(0xD9);
	spi_send_recv(0xF1);

	DISPLAY_ACTIVATE_VBAT;
	quicksleep(10000000);

	spi_send_recv(0xA1);
	spi_send_recv(0xC8);

	spi_send_recv(0xDA);
	spi_send_recv(0x20);

	spi_send_recv(0xAF);
}

void display_string(int line, char *s) {
	int i;
	if(line < 0 || line >= 4)
		return;
	if(!s)
		return;

	for(i = 0; i < 16; i++)
		if(*s) {
			textbuffer[line][i] = *s;
			s++;
		} else
			textbuffer[line][i] = ' ';
}
//Constructs the correct adress to send to the display
void display_update(){
	int x, y, k, value;
	for(y = 0; y < 4; y++){
		DISPLAY_CHANGE_TO_COMMAND_MODE;
		spi_send_recv(0x22);
		spi_send_recv(y);

		spi_send_recv(0x00);
		spi_send_recv(0x10);

		DISPLAY_CHANGE_TO_DATA_MODE;

		for(x = 0; x < 128; x++){
			value = (pixel[y * 8][x]);
			for(k = 1; k < 8; k++){
				value |= (pixel[y * 8 + k][x]) << k;
			}
			spi_send_recv(value);
		}
	}
}

void display_update_menu(void) {
	int i, j, k;
	int c;
	for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;
		spi_send_recv(0x22);
		spi_send_recv(i);

		spi_send_recv(0x0);
		spi_send_recv(0x10);

		DISPLAY_CHANGE_TO_DATA_MODE;

		for(j = 0; j < 16; j++) {
			c = textbuffer[i][j];
			if(c & 0x80)
				continue;

			for(k = 0; k < 8; k++)
				spi_send_recv(font[c*8 + k]);
		}
	}
}


//Menu for Settings
void Settings(void){
	wait = 0;
	while(settings & 1){

		int btn = getbtns();
		int btn2 = btn;
		int	btn3 = btn >> 1;
		int	btn4 = btn >> 2;

		char view1[] = {'1', '.', ' ', 'B','O','U','L','D','E','R',' ','S','P','E','E','D','\0'};
		char view2[] = {'2', '.', ' ','S','P','A','W','N',' ','R','A','T','E','\0'};
		char view3[] = {'3', '.', ' ','B','A','C','K','\0'};

		display_string(0, view1);
		display_string(1, view2);
		display_string(2, view3);
		display_update_menu();
		wait++;

		if((btn4 & 1) && wait > 200){
			gamespeed = 1;
			settings = 0;
			wait = 0;
			gameSpeed();
		}

		if((btn3 & 1) && wait > 200){
			spawnrate = 1;
			settings = 0;
			wait = 0;
			SpawnRate();
		}

		if((btn2 & 1) && wait > 200){
			settings = 0;
			wait = 0;
		}
	}
}
//Menu for speed of boulders
void gameSpeed(void){
	while(gamespeed & 1){
		int btn = getbtns();
		int btn2 = btn;
		int	btn3 = btn >> 1;
		int	btn4 = btn >> 2;

		char view1[] = {' ','1', '.', ' ','E','A','S','Y','\0'};
		char view1selected[] = {'(','1',')', ' ','E','A','S','Y','\0'};
		char view2[] = {' ','2', '.', ' ','M','E','D','I','U','M','\0'};
		char view2selected[] = {'(','2',')', ' ','M','E','D','I','U','M','\0'};
		char view3[] = {' ','3', '.', ' ','H','A','R','D','\0'};
		char view3selected[] = {'(','3',')', ' ','H','A','R','D','\0'};

		if(bs==6){
			display_string(0, view1selected);
			display_string(1, view2);
			display_string(2, view3);
		}
		else if(bs==5){
			display_string(0, view1);
			display_string(1, view2selected);
			display_string(2, view3);
		}
		else if(bs==4){
			display_string(0, view1);
			display_string(1, view2);
			display_string(2, view3selected);
		}
		else{
			display_string(0, view1);
			display_string(1, view2);
			display_string(2, view3);
		}

		wait++;
		display_update_menu();

		if((btn4 & 1) && wait > 200){
			bs = 6;
			gamespeed = 0;
			settings = 1;
			Settings();
		}

		if((btn3 & 1) && wait > 200){
			bs = 5;
			gamespeed = 0;
			settings = 1;
			Settings();
		}

		if((btn2 & 1) && wait > 200){
			bs = 4;
			gamespeed = 0;
			settings = 1;
			Settings();
		}
	}
}
//Menu for spawnrate of boulders
void SpawnRate(void){
	while(spawnrate & 1){
		int btn = getbtns();
		int btn2 = btn;
		int	btn3 = btn >> 1;
		int	btn4 = btn >> 2;

		char view1[] = {' ','1', '.', ' ','E','A','S','Y','\0'};
		char view1selected[] = {'(','1',')', ' ','E','A','S','Y','\0'};
		char view2[] = {' ','2', '.', ' ','M','E','D','I','U','M','\0'};
		char view2selected[] = {'(','2',')', ' ','M','E','D','I','U','M','\0'};
		char view3[] = {' ','3', '.', ' ','H','A','R','D','\0'};
		char view3selected[] = {'(','3',')', ' ','H','A','R','D','\0'};

		if(ssA==150){
			display_string(0, view1selected);
			display_string(1, view2);
			display_string(2, view3);
		}
		else if(ssA==100){
			display_string(0, view1);
			display_string(1, view2selected);
			display_string(2, view3);
		}
		else if(ssA==50){
			display_string(0, view1);
			display_string(1, view2);
			display_string(2, view3selected);
		}
		else{
			display_string(0, view1);
			display_string(1, view2);
			display_string(2, view3);
		}

		wait++;
		display_update_menu();

		if((btn4 & 1) && wait > 200){
			ssA = 150;
			ssB = 200;
			spawnrate = 0;
			settings = 1;
			Settings();
		}

		if((btn3 & 1) && wait > 200){
			ssA = 100;
			ssB = 150;
			spawnrate = 0;
			settings = 1;
			Settings();
		}

		if((btn2 & 1) && wait > 200){
			ssA = 50;
			ssB = 100;
			spawnrate = 0;
			settings = 1;
			Settings();
		}
	}
}
//Creates a cutscene and calls the scoreboard
void gameOver(){
  int height = 0;
  int wait3 = 200000;
  int wait4 = 500;
  while(gameover){
    if (height <= 32 && wait3 == 0){
      curtain(height - 1);
      height += 4;
      display_update();
      wait3 = 200000;
    }
    else if(height > 32){
      wait4--;
			display_update();
    }
      wait3--;

    if(wait4 == 0)
      gameover = 0;
  }
	scoreboard = 1;
	Scoreboard();
}

//Converts int into char array
#define ITOA_BUFSIZ ( 24 )
char * itoaconv( int num )
{
  register int i, sign;
  static char itoa_buffer[ ITOA_BUFSIZ ];
  static const char maxneg[] = "-2147483648";

  itoa_buffer[ ITOA_BUFSIZ - 1 ] = 0;   /* Insert the end-of-string marker. */
  sign = num;                           /* Save sign. */
  if( num < 0 && num - 1 > 0 )          /* Check for most negative integer */
  {
    for( i = 0; i < sizeof( maxneg ); i += 1 )
    itoa_buffer[ i + 1 ] = maxneg[ i ];
    i = 0;
  }
  else
  {
    if( num < 0 ) num = -num;           /* Make number positive. */
    i = ITOA_BUFSIZ - 2;                /* Location for first ASCII digit. */
    do {
      itoa_buffer[ i ] = num % 10 + '0';/* Insert next digit. */
      num = num / 10;                   /* Remove digit from number. */
      i -= 1;                           /* Move index to next empty position. */
    } while( num > 0 );
    if( sign < 0 )
    {
      itoa_buffer[ i ] = '-';
      i -= 1;
    }
  }
  /* Since the loop always sets the index i to the next empty position,
   * we must add 1 in order to return a pointer to the first occupied position. */
  return( &itoa_buffer[ i + 1 ] );
}

//Genertes the scoreboard
void Scoreboard(void){
	wait = 0;
	int c;
	int d;
	for(c = 0; c < 32; c++)
			for(d = 0; d < 128; d++)
				pixel[c][d] = 0;
	while(scoreboard & 1){

		int btn = getbtns();
		int sw = getsw();

		char view1[] = {' ', ' ', ' ', 'Y','O','U','R',' ','S','C','O','R','E',':','\0'};
		char view2[] = {'P', 'R', 'E','S','S',' ','A','N','Y',' ','B','U','T','T','O','N','\0'};
		char e[] = {' '};

		display_string(0, view1);
		display_string(1, itoaconv(score));
		display_string(2, e);
		display_string(3, view2);
		display_update_menu();
		wait++;

		if((btn | sw) && wait > 200){
			scoreboard = 0;
			wait = 0;
			ingame = 0;
		}
	}
}

//Sudo random generator
static int rand_state;
int rand(void)
{
    rand_state = (rand_state * 1103515245 + 12345) & 0x7fffffff;
    return rand_state;
}

int randGen(int min, int max){
  return rand() % (max+1-min) + min ;
}
