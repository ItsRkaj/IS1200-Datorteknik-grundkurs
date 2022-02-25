/* mipslabwork.c
   This file written 2015 by F Lundevall
   This file should be changed by YOU! So add something here:
   This file modified 2015-12-24 by Ture Teknolog
   This file modified update 2015-08-28 by F Lundevall
   Last modified 2018-03-04 by Oliver Wilén & Filip Hedlund
   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
#include <stdbool.h>

int i, j;
int x,y;
int tempx, tempy;
int cooldown;
int boulderspawn;
int randcount;
int timecount;

//Coordinates and activation flags for projectiles
int x1, x2, x3;
int y1, y2, y3;
int pa[3] = {0,0,0};

//Coordinates, activation flags and speeds for boulders
int bx[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int by[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int ba[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int bspeed[14] = {5,5,5,5,5,5,5,5,5,5,5,5,5,5};

//Coordinates, activation flags and delays for explotions
int ex[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int ey[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int ea[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int ew[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int *IO = (volatile int*) 0xbf886100;
	*IO		&= ~0xff;
	TRISD	|= 0x7f0;

	T2CON = 0x0; 			// Stop timer and clear control register
	T2CONSET = 0x0070;		// Set prescaler at 1:256, external clock source
	TMR2 = 0x0; 			// Clear timer register
	PR2 = 31250; 			// Load period register
	IPCSET(2) |= 0x1f;		// Priority/Subpriority
	T2CONSET = 0x8000; 		// Start timer

  //reset variables uesd in labwork
  i = 0;
	j = 0;
	x = 10;
	y = 18;
	tempx = 0;
  tempy = 0;
	cooldown = 0;
	boulderspawn = 0;
	randcount = 0;
	x1 = 0, x2 = 0, x3 = 0;
	y1 = 0, y2 = 0, y3 = 0;
	FR = 100;
	killcount = 1;
	wait2 = 0;
	powerup = 0;
  score = 0;
  timecount = 0;

  int a;
	for(a = 0; a < 14; a++){
		bspeed[a] = bs;
		bx[a] = 0;
		by[a] = 0;
		ba[a] = 0;
		ex[a] = 0;
		ey[a] = 0;
		ea[a] = 0;
		ew[a] = 0;
	}

	int b;
	for(b = 0; b <3; b++)
		pa[b] = 0;

    return;
}

/* This function is called repetitively from the main program */
void labwork( void ){

  timecount++;
  if(timecount == 10*bs){
    timecount = 0;
    score += 1;
  }

	int btn = getbtns();
	int btn2 = btn;
	int	btn3 = btn >> 1;		//up
	int	btn4 = btn >> 2;		//down

  int sw = getsw();
  int sw3 = sw >> 2;  //right
  int sw4 = sw >> 3;  //left

	//clear screen
		for(i = 0; i < 32; i++)
			for(j = 0; j < 128; j++)
				pixel[i][j] = 0;

	//generate boulder
	if(boulderspawn > 0)
		boulderspawn--;
	else{
		boulderspawn = randGen(ssA,ssB); //Sudo random function for determining the distance between boulders

		int k;
		for(k = 0; k < 14; k++){
			if(!ba[k]){
				ba[k] = 1;
				bx[k] = 127;
				by[k] = randGen(8,31); //Sudo random function for determining the y coordinate of boulders
				boulder(bx[k],by[k]);
				break;
			}
		}
	}

//Function for moving boulders that are active
	int l;
	for(l = 0; l < 14; l++){
		if((bx[l] > -6) && (bx[l] < 129) && ba[l]){
			if(bspeed[l] == 0){
				bx[l]--;
				bspeed[l] = bs;
			}
			boulder(bx[l],by[l]);
			bspeed[l]--;
		}else if(bx[l] < 0 && ba[l]){ //Reset boulders that have oved ofscreen
			bx[l] = 0;
			by[l] = 0;
			ba[l] = 0;
		}
	}



	//Boundaries for the car
	if((x+17)>128)
		x--;
	if((y)<8){
		y++;
	}
	if(x<0)
		x++;
	if(y>30){
		y--;
	}

	//Function for shooting and drawing projectiles
	if(cooldown > 0)
		cooldown--;
	if(btn2 & 1){
		hood(x,y);

		if(cooldown == 0){
			if(x1 == 0 && y1 == 0 && !pa[0]){
				x1 = x+18;
				y1 = y-3;
        pa[0] = 1;
				projectile(x1,y1);
			}else if(x2 == 0 && y2 == 0 && !pa[1]){
				x2 = x+18;
				y2 = y-3;
        pa[1] = 1;
				projectile(x2,y2);
			}else if(x3 == 0 && y3 == 0 && !pa[2]){
				x3 = x+18;
				y3 = y-3;
        pa[2] = 1;
				projectile(x3,y3);
			}
			cooldown = FR;
		}
	}

  //Functions for moving active projectiles
	if(x1 < 129 && pa[0]){
		x1++;
		projectile(x1,y1);
	}
  else{ //Remove projectiles that have moved offscreen
    x1 = 0;
    y1 = 0;
    pa[0] = 0;
  }

	if(x2 < 129 && pa[1]){
		x2++;
		projectile(x2,y2);
	}
  else{
    x2 = 0;
    y2 = 0;
    pa[1] = 0;
  }

	if(x3 < 129 && pa[2]){
		x3++;
		projectile(x3,y3);
	}
  else{
    x3 = 0;
    y3 = 0;
    pa[2] = 0;
  }

  //Function for moving the car
	if(btn3 | btn4 | sw4 | sw3){

		if(btn3 & 1){
			tempy++;
			if(tempy == 5){
				y++;
				tempy = 0;
			}
			figure(x,y);
		}

		if(btn4 & 1){
			tempy++;
			if(tempy == 5){
				y--;
				tempy = 0;
			}
			figure(x,y);
		}

		if(sw4 & 1){
			tempx++;
			if(tempx == 7){
				x--;
				tempx = 0;
			}
			figure(x,y);
		}

		if(sw3 & 1){
			tempx++;
			if(tempx == 7){
				x++;
				tempx = 0;
			}
			figure(x,y);
		}
  }
  else
    figure(x,y);

      //Function for powerup leds
  if((PORTE & 0x000000FF) == 0xFF){
		  powerup = 1;
	}

	if(powerup & 1){
		FR = 38; //increases firerate
		PORTE = 0;
		wait2++;

    //Function for blinking leds
	if(wait2 <= 2000 && (wait2%50 <= 25))
		PORTE = 255;
	else
		PORTE = 0;

    //reset to normal fire
	if(wait2>2000){
		PORTE = 0;
		powerup = 0;
		killcount = 1;
		PORTE = 0;
		FR = 90;
		wait2 = 0;
	  }
	}

int m;

for(m = 0; m < 14; m++){
  //Calls gameOver when car is hit by a boulder.
  if(figureIsHit(x,y) && boulderIsHit(bx[m],by[m]) && ba[m] && (bx[m] < (x+18))){
	PORTE = 0; //Reset PORTE;
	explosion(x,y);
	gameover = 1;
	gameOver();
  }
  //Function for detecting a projctile hit on a boulder
  if(boulderIsHit(bx[m],by[m]) && projectileHit(x1,y1) && ba[m] && pa[0]){

  if((ex[m] == 0) && (ey[m] == 0) && !ea[m]){ //Functon for explosion coordiantes
		ex[m] = bx[m];
		ey[m] = by[m];
    ea[m] = 1;
		ew[m] = 10;
	}

  x1 = 0;
	y1 = 0;
  pa[0] = 0;
	bx[m] = 0;
	by[m] = 0;
  ba[m] = 0;

  if(!powerup && ((killcount%5)==0)){ //Increase powerup leds every 5 boulders destroyed
			PORTE = (PORTE<<1)+1;
		}
	killcount++;
  score += 10;
  }
  //Function for detecting a projctile hit on a boulder
  if(boulderIsHit(bx[m],by[m]) && projectileHit(x2,y2) && ba[m] && pa[1]){

	if((ex[m] == 0) && (ey[m] == 0) && !ea[m]){ //Functon for explosion coordiantes
		ex[m] = bx[m];
		ey[m] = by[m];
    ea[m] = 1;
		ew[m] = 10;
	}

  x2 = 0;
	y2 = 0;
  pa[1] = 0;
	bx[m] = 0;
	by[m] = 0;
  ba[m] = 0;

  if(!powerup && ((killcount%5)==0)){ //Increase powerup leds every 5 boulders destroyed
			PORTE = (PORTE<<1)+1;
		}
	killcount++;
  score += 10;
  }
  //Function for detecting a projctile hit on a boulder
  if(boulderIsHit(bx[m],by[m]) && projectileHit(x3,y3) && ba[m] && pa[2]){
   if((ex[m] == 0) && (ey[m] == 0) && !ea[m]){ //Functon for explosion coordiantes
		ex[m] = bx[m];
		ey[m] = by[m];
    ea[m] = 1;
		ew[m] = 10;
	}

  x3 = 0;
	y3 = 0;
  pa[2] = 0;
	bx[m] = 0;
	by[m] = 0;
  ba[m] = 0;

	if(!powerup && ((killcount%5)==0)){ //Increase powerup leds every 5 boulders destroyed
			PORTE = (PORTE<<1)+1;
		}
	killcount++;
  score += 10;
  }

  if(ew[m] > 0){ // Function for drawing explosion
      ew[m]--;
      explosion(ex[m] - 4, ey[m] + 5);
    }else if(ea[m]){ //Reset
		ex[m] = 0;
		ey[m] = 0;
    ea[m] = 0;
    }
  }
	display_update();
}
