/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
static int timeoutcounter = 0;

volatile int *led = (volatile int*) 0xbf886100;
volatile int *port = (volatile int*) 0xbf886110;
int c = 0;


/*__________________________START___________________________*/
//Standard Variables
int i,j;
int scoreCounter = 0;
int direction = 4;
int ranx = 0;
int rany = 0;
int ranS = 0;
int randX[50] = {104, 75, 89, 18, 37, 2, 111, 114, 56, 84, 42, 90, 6, 66, 22, 113, 68, 24, 92, 108, 71, 63, 9, 94, 83, 32, 110, 116, 95, 41, 74, 78, 12, 26, 4, 76, 91, 52, 62, 117, 65, 51, 86, 54, 49, 28, 31, 35, 97, 38, 19, 93, 101, 46, 69, 106, 118, 17, 3, 15, 102, 39, 14, 120, 43, 21, 59, 20, 7, 13, 61, 47, 45, 55, 98, 109, 100, 5, 72, 50, 58, 79, 30, 115, 36, 88, 23, 122, 96, 34, 16, 121, 25, 119, 40, 10, 44, 80, 53, 67, 107, 112, 64, 99, 11, 60, 1, 33, 85, 77, 48, 70, 81, 82, 57, 29, 8, 103, 27, 87, 105, 73};
int randY[25] = {22, 24, 5, 3, 11, 13, 7, 20, 14, 6, 1, 16, 9, 18, 2, 25, 23, 4, 12, 15, 8, 19, 10, 21, 17};
int snakemove = 0;
int snakedirection = 4;

//Start position for player
int playerX=16;
int playerY=64;

//Position for coin
int coinX=16;
int coinY=100;

//Startposition for Enemy
int enemyX=16;
int enemyY=32;


//Set directions
void right(){
    playerY++;
}
void left(){
    playerY--;
}
void up(){
    playerX--;
}
void down(){
    playerX++;
}
void rights(){
    enemyY++;
    if (enemyY >= 121) {
        enemyY = 1;
    }
}
void lefts(){
    enemyY--;
    if (enemyY <= 0) {
        enemyY = 121;
    }
}
void up_s(){
    enemyX--;
    if (enemyX <= 0) {
        enemyX = 25;
    }
}
void downs(){
    enemyX++;
    if (enemyX >= 25) {
        enemyX = 1;
    }
}




/*___________________________END____________________________*/

/* Interrupt Service Routine */
void user_isr( void )
{
    return;
}
int rand_x(void){
    int r;
    if (ranx == 50) {
        ranx = 0;
    }
    if(ranx < 50){
        r = randX[ranx];
    }
    ranx++;
    
    return r;
}
int rand_y(void){
    int r;
    if (rany == 25) {
        rany = 0;
    }
    if(rany < 25){
        r = randY[rany];
    }
    rany++;
    
    return r;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
    //initialize led to zero
    *led &= 0xffffff00;
    
    //initialize port to zero
    *port &= 0xffffff00;
    
    //11->5 = 1
    TRISD &= 0xfe0;
    
    //TimerIntz
    T2CON = 0x0;    //Stops Timer2 and clear control register
    TMR2 = 0x0;     //Clear contents of TMR2
    PR2 = 0x7a12;   //Load PR2 register
    T2CONSET = 0x70;//
    
    IFSCLR(0);      //Clear the interuption flag
    
    IEC(0) = IEC(0) | 0x100;
    IPC(2) = IPC(2) | 0x1F;
    
    //__________________RESETVARIABLES_____________________
    i=0;
    j=0;
    SCORE=0;
    
    direction = 4;

    //Start position for player
    playerX=16;
    playerY=64;

    //Position for coin
    coinX=16;
    coinY=100;

    //Startposition for Enemy
    enemyX=16;
    enemyY=32;
    
    return;
}

/*___________________FUNKTIONER____________________*/
void clear_screen(){
    for(i = 0; i < 32; i++)
        for(j = 0; j < 128; j++)
            pixel[i][j] = 0;
}

void player(playerX,playerY){
    pixel[playerX][playerY] = 1;
    pixel[playerX][playerY+1] = 1;
    pixel[playerX][playerY+2] = 1;
    pixel[playerX][playerY+3] = 1;
    pixel[playerX][playerY+4] = 1;
    
    pixel[playerX+1][playerY] = 1;
    pixel[playerX+1][playerY+1] = 1;
    pixel[playerX+1][playerY+2] = 1;
    pixel[playerX+1][playerY+3] = 1;
    pixel[playerX+1][playerY+4] = 1;
    
    pixel[playerX+2][playerY] = 1;
    pixel[playerX+2][playerY+1] = 1;
    pixel[playerX+2][playerY+2] = 1;
    pixel[playerX+2][playerY+3] = 1;
    pixel[playerX+2][playerY+4] = 1;
    
    pixel[playerX+3][playerY] = 1;
    pixel[playerX+3][playerY+1] = 1;
    pixel[playerX+3][playerY+2] = 1;
    pixel[playerX+3][playerY+3] = 1;
    pixel[playerX+3][playerY+4] = 1;
    
    pixel[playerX+4][playerY] = 1;
    pixel[playerX+4][playerY+1] = 1;
    pixel[playerX+4][playerY+2] = 1;
    pixel[playerX+4][playerY+3] = 1;
    pixel[playerX+4][playerY+4] = 1;
}

void coin(coinX,coinY){
    //pixel[coinX][coinY] = 1;
    //pixel[coinX][coinY+1] = 1;
    pixel[coinX][coinY+2] = 1;
    //pixel[coinX][coinY+3] = 1;
    //pixel[coinX][coinY+4] = 1;
    
    //pixel[coinX+1][coinY] = 1;
    pixel[coinX+1][coinY+1] = 1;
    //pixel[coinX+1][coinY+2] = 1;
    pixel[coinX+1][coinY+3] = 1;
    //pixel[coinX+1][coinY+4] = 1;
    
    pixel[coinX+2][coinY] = 1;
    //pixel[coinX+2][coinY+1] = 1;
    //pixel[coinX+2][coinY+2] = 1;
    //pixel[coinX+2][coinY+3] = 1;
    pixel[coinX+2][coinY+4] = 1;
    
    //pixel[coinX+3][coinY] = 1;
    pixel[coinX+3][coinY+1] = 1;
    //pixel[coinX+3][coinY+2] = 1;
    pixel[coinX+3][coinY+3] = 1;
    //pixel[coinX+3][coinY+4] = 1;
    
    //pixel[coinX+4][coinY] = 1;
    //pixel[coinX+4][coinY+1] = 1;
    pixel[coinX+4][coinY+2] = 1;
    //pixel[coinX+4][coinY+3] = 1;
    //pixel[coinX+4][coinY+4] = 1;
}

void enemy(enemyX,enemyY){
    //pixel[enemyX][enemyY] = 1;
    pixel[enemyX][enemyY+1] = 1;
    pixel[enemyX][enemyY+2] = 1;
    pixel[enemyX][enemyY+3] = 1;
    pixel[enemyX][enemyY+4] = 1;
    
    pixel[enemyX+1][enemyY] = 1;
    //pixel[enemyX+1][enemyY+1] = 1;
    //pixel[enemyX+1][enemyY+2] = 1;
    //pixel[enemyX+1][enemyY+3] = 1;
    //pixel[enemyX+1][enemyY+4] = 1;
    
    //pixel[enemyX+2][enemyY] = 1;
    pixel[enemyX+2][enemyY+1] = 1;
    pixel[enemyX+2][enemyY+2] = 1;
    pixel[enemyX+2][enemyY+3] = 1;
    //pixel[enemyX+2][enemyY+4] = 1;
    
    //pixel[enemyX+3][enemyY] = 1;
    //pixel[enemyX+3][enemyY+1] = 1;
    //pixel[enemyX+3][enemyY+2] = 1;
    //pixel[enemyX+3][enemyY+3] = 1;
    pixel[enemyX+3][enemyY+4] = 1;
    
    pixel[enemyX+4][enemyY] = 1;
    pixel[enemyX+4][enemyY+1] = 1;
    pixel[enemyX+4][enemyY+2] = 1;
    pixel[enemyX+4][enemyY+3] = 1;
    //pixel[enemyX+4][enemyY+4] = 1;
}

void draw_frame(){
    //Draw Vertical Lines
    for(i = 0; i < 32; i++){
        pixel[i][0] = 1;
        pixel[i][127] = 1;
    }
    //Draw Horizontal Lines
    for(j = 0; j < 128; j++){
        pixel[0][j] = 1;
        pixel[31][j] = 1;
    }
        
}

void set_direction(int n){
    switch (n) {
        case 1:
            left();
            break;
        case 2:
            down();
            break;
        case 3:
            up();
            break;
        case 4:
            right();
            break;
            
        default:
            break;
    }
}
void set_direction_snake(int n){
    switch (n) {
        case 0:
            lefts();
            break;
        case 1:
            downs();
            break;
        case 2:
            up_s();
            break;
        case 3:
            rights();
            break;
            
        default:
            break;
    }
}

/* This function is called repetitively from the main program */
void labwork( void )
{
    //Control Updatespeed
    delay( DIFFICULTY );
    
    //Clears the Display
    clear_screen();
    
    //Set up buttons
    int btnstate = getbtns();
    
    //Draw Frame
    draw_frame();
    
    //Draw player
    player(playerX,playerY);
    coin(coinX,coinY);
    enemy(enemyX,enemyY);
    
    //Snake movement
    if (snakemove++ == 10) {
        snakedirection = (rand_x() % 4);
        snakemove = 0;
    }
    set_direction_snake(snakedirection);
    
    //Player Movement
    //Left
    if(btnstate & 0x8 && (playerX > 1) && direction != 4)
        direction = 1;
    //Down
    else if(btnstate & 0x4 && (playerY > 1) && direction != 3)
        direction = 2;
    //Up
    else if(btnstate & 0x2 && (playerY+4) < 126 && direction != 2)
        direction = 3;
    //Right
    else if(btnstate & 0x1 && (playerX+4) < 30 && direction != 1)
        direction = 4;
    
    //Frame collision system
    if((playerY+4) >= 126 || playerY <= 1 || (playerX+4) >= 30 || playerX <= 1)
        GAMESTATE = 4;
    
    //Set direction of the Snake
    set_direction(direction);
    
    //Coin collition system
    if(((playerX+2 <= coinX+4) && (playerX+2 >= coinX)) &&
       ((playerY+2 <= coinY+4) && (playerY+2 >= coinY))){
        coinY = rand_x();
        coinX = rand_y();
        SCORE += 5000/DIFFICULTY;
    }
    
    //Enemy collition system
    if(((playerX+2 <= enemyX+4) && (playerX+2 >= enemyX)) &&
       ((playerY+2 <= enemyY+4) && (playerY+2 >= enemyY))){
        GAMESTATE = 4;
    }
    
    //Score per tick
    if(scoreCounter++ == 10){
        SCORE += 100/DIFFICULTY;
        scoreCounter = 0;
    }
    
    //Update the display
    display_update();
}
