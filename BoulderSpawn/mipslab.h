/* mipslab.h
   Header file for all labs.
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson
   Last modified 2018-03-04 by Oliver Wilén & Filip Hedlund
   For copyright and licensing, see file COPYING */

/* Declare display-related functions from mipslabfunc.c */
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
void display_update_menu(void);
uint8_t spi_send_recv(uint8_t data);

/* Declare lab-related functions from mipslabfunc.c */
void labwork(void);
void quicksleep(int cyc);

//Declare project functions from mipslabfunc.c
void gameOver(void);
void Settings(void);
void gameSpeed(void);
void SpawnRate(void);
void Scoreboard(void);

//Declare
extern uint8_t pixel[32][128];

/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];
/* Declare text buffer for display output */
extern char textbuffer[4][16];

//Declare global variables
extern char ingame;
extern char settings;
extern char gamespeed;
extern char spawnrate;
extern char powerup;
extern char gameover;
extern char scoreboard;
extern unsigned long score;
extern unsigned int wait;
extern unsigned int wait2;
extern int bs;
extern int ssA;
extern int ssB;
extern int FR;
extern int killcount;

/* Written as part of i/o lab: getbtns, getsw */
int getbtns(void);
int getsw(void);
