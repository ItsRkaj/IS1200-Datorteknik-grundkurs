/*sprites.c
	Created by Oliver Wilén & Filip Hedlund
	Last modified 2018-03-04 by Oliver Wilén & Filip Hedlund*/

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
#include <stdbool.h>

//Defines what pixels to write on screen for the car sprite
void figure(x,y){
	pixel[y-2][x+0] = 1;
	pixel[y-3][x+0] = 1;
	pixel[y-4][x+0] = 1;
	pixel[y-5][x+0] = 1;
	pixel[y-6][x+0] = 1;
	pixel[y-7][x+0] = 1;

	pixel[y-1][x+1] = 1;
	pixel[y-2][x+1] = 1;
	pixel[y-3][x+1] = 1;
	pixel[y-4][x+1] = 1;
	pixel[y-5][x+1] = 1;
	pixel[y-6][x+1] = 1;
	pixel[y-7][x+1] = 1;

	pixel[y-0][x+2] = 1;
	pixel[y-3][x+2] = 1;
	pixel[y-4][x+2] = 1;
	pixel[y-5][x+2] = 1;
	pixel[y-6][x+2] = 1;
	pixel[y-7][x+2] = 1;

	pixel[y-0][x+3] = 1;
	pixel[y-3][x+3] = 1;
	pixel[y-4][x+3] = 1;
	pixel[y-5][x+3] = 1;
	pixel[y-6][x+3] = 1;
  pixel[y-7][x+3] = 1;

  pixel[y-1][x+4] = 1;
  pixel[y-2][x+4] = 1;
  pixel[y-3][x+4] = 1;
  pixel[y-4][x+4] = 1;
  pixel[y-7][x+4] = 1;

  pixel[y-2][x+5] = 1;
  pixel[y-3][x+5] = 1;
  pixel[y-4][x+5] = 1;
  pixel[y-7][x+5] = 1;

  pixel[y-2][x+6] = 1;
  pixel[y-3][x+6] = 1;
  pixel[y-4][x+6] = 1;
  pixel[y-7][x+6] = 1;

  pixel[y-2][x+7] = 1;
  pixel[y-3][x+7] = 1;
  pixel[y-4][x+7] = 1;
  pixel[y-5][x+7] = 1;
  pixel[y-6][x+7] = 1;
  pixel[y-7][x+7] = 1;

  pixel[y-2][x+8] = 1;
  pixel[y-3][x+8] = 1;
  pixel[y-4][x+8] = 1;
  pixel[y-7][x+8] = 1;

  pixel[y-2][x+9] = 1;
  pixel[y-3][x+9] = 1;
  pixel[y-4][x+9] = 1;
  pixel[y-7][x+9] = 1;

  pixel[y-2][x+10] = 1;
  pixel[y-3][x+10] = 1;
  pixel[y-4][x+10] = 1;
  pixel[y-6][x+10] = 1;
  pixel[y-7][x+10] = 1;

  pixel[y-1][x+11] = 1;
  pixel[y-2][x+11] = 1;
  pixel[y-3][x+11] = 1;
  pixel[y-4][x+11] = 1;
  pixel[y-5][x+11] = 1;
  pixel[y-6][x+11] = 1;

  pixel[y-0][x+12] = 1;
  pixel[y-3][x+12] = 1;
  pixel[y-4][x+12] = 1;

  pixel[y-0][x+13] = 1;
  pixel[y-3][x+13] = 1;
  pixel[y-4][x+13] = 1;

  pixel[y-1][x+14] = 1;
  pixel[y-2][x+14] = 1;
  pixel[y-3][x+14] = 1;
  pixel[y-4][x+14] = 1;

  pixel[y-2][x+15] = 1;
  pixel[y-3][x+15] = 1;
  pixel[y-4][x+15] = 1;

  pixel[y-2][x+16] = 1;
  pixel[y-3][x+16] = 1;
  pixel[y-4][x+16] = 1;
}

//Defines what pixels to write on screen for the car hood sprite
void hood(x,y){
	pixel[y-5][x+12] = 1;
	pixel[y-6][x+13] = 1;
	pixel[y-6][x+14] = 1;
	pixel[y-7][x+15] = 1;
	pixel[y-7][x+16] = 1;
}
//Defines which pixels are used for the hitbox of the car
bool figureIsHit(x,y){
	if(
  pixel[y-2][x-1] == 1|
	pixel[y-3][x-1] == 1|
	pixel[y-4][x-1] == 1|
	pixel[y-5][x-1] == 1|
	pixel[y-6][x-1] == 1|
	pixel[y-7][x-1] == 1|

  pixel[y-1][x+0] == 1|
  pixel[y-8][x+0] == 1|

  pixel[y-0][x+1] == 1|
  pixel[y-8][x+1] == 1|

  pixel[y+1][x+2] == 1|
  pixel[y-8][x+2] == 1|

  pixel[y+1][x+3] == 1|
  pixel[y-8][x+3] == 1|

  pixel[y-0][x+4] == 1|
  pixel[y-8][x+4] == 1|

  pixel[y-1][x+5] == 1|
  pixel[y-8][x+5] == 1|

  pixel[y-1][x+6] == 1|
  pixel[y-8][x+6] == 1|

  pixel[y-1][x+7] == 1|
  pixel[y-8][x+7] == 1|

  pixel[y-1][x+8] == 1|
  pixel[y-8][x+8] == 1|

  pixel[y-1][x+9] == 1|
  pixel[y-8][x+9] == 1|

  pixel[y-1][x+10] == 1|
  pixel[y-8][x+10] == 1|

  pixel[y-0][x+11] == 1|
  pixel[y-7][x+11] == 1|

  pixel[y+1][x+12] == 1|

  pixel[y+1][x+13] == 1|
  pixel[y-5][x+13] == 1|

  pixel[y-0][x+14] == 1|
  pixel[y-5][x+14] == 1|

  pixel[y-1][x+15] == 1|
  pixel[y-5][x+15] == 1|

  pixel[y-1][x+16] == 1|
  pixel[y-5][x+16] == 1|

  pixel[y-2][x+17] == 1|
  pixel[y-3][x+17] == 1|
  pixel[y-4][x+17] == 1
	){
		return true;
	}
	else
		return false;
}

//Defines what pixels to write on screen for the projectile sprite
void projectile(x,y){
	if(x < 128 && x > 0){
	pixel[y-0][x+0] = 1;
	pixel[y-1][x+0] = 1;
	}

	if(x+1 < 128 && x+1 > 0){
	pixel[y-0][x+1] = 1;
	pixel[y-1][x+1] = 1;
	}

	if(x+2 < 128 && x+2 > 0){
	pixel[y-0][x+2] = 1;
	pixel[y-1][x+2] = 1;
	}

	if(x+3 < 128 && x+3 > 0){
	pixel[y-0][x+3] = 1;
	pixel[y-1][x+3] = 1;
	}
}

//Defines which pixels are used for the hitbox of the projectile sprite
bool projectileHit(x,y){
	if(pixel[y-0][x-1] == 1 | pixel[y-1][x-1] == 1)
		if(x-1 < 128 && x-1 > 0)
			return true;

	if(pixel[y+1][x+0] == 1 | pixel[y-2][x+0] == 1)
		if(x+0 < 128 && x+0 > 0)
			return true;

	if(pixel[y+1][x+1] == 1 | pixel[y-2][x+1] == 1)
		if(x+1 < 128 && x+1 > 0)
			return true;

	if(pixel[y+1][x+2] == 1 | pixel[y-2][x+2] == 1)
		if(x+2 < 128 && x+2 > 0)
			return true;

	if(pixel[y+1][x+3] == 1 | pixel[y-2][x+3] == 1)
		if(x+3 < 128 && x+3 > 0)
			return true;

	if(pixel[y-0][x+4] == 1 | pixel[y-1][x+4] == 1)
		if(x+4 < 128 && x+4 > 0)
			return true;

	else
		return false;
}
//Defines what pixels to write on screen for the boulder sprite
void boulder(x,y){
	if(x+0 < 128 && x+0 > 0){
  pixel[y-2][x+0] = 1;
	pixel[y-3][x+0] = 1;
	pixel[y-4][x+0] = 1;
  pixel[y-5][x+0] = 1;
	pixel[y-6][x+0] = 1;
	}

	if(x+1 < 128 && x+1 > 0){
  pixel[y-1][x+1] = 1;
  pixel[y-2][x+1] = 1;
  pixel[y-3][x+1] = 1;
  pixel[y-4][x+1] = 1;
  pixel[y-5][x+1] = 1;
  pixel[y-6][x+1] = 1;
  pixel[y-7][x+1] = 1;
	}

	if(x+2 < 128 && x+2 > 0){
  pixel[y-0][x+2] = 1;
  pixel[y-1][x+2] = 1;
  pixel[y-2][x+2] = 1;
  pixel[y-3][x+2] = 1;
  pixel[y-4][x+2] = 1;
  pixel[y-5][x+2] = 1;
  pixel[y-6][x+2] = 1;
  pixel[y-7][x+2] = 1;
	}

	if(x+3 < 128 && x+3 > 0){
  pixel[y-0][x+3] = 1;
  pixel[y-1][x+3] = 1;
  pixel[y-2][x+3] = 1;
  pixel[y-3][x+3] = 1;
  pixel[y-4][x+3] = 1;
  pixel[y-5][x+3] = 1;
  pixel[y-6][x+3] = 1;
  pixel[y-7][x+3] = 1;
  pixel[y-8][x+3] = 1;
	}

	if(x+4 < 128 && x+4 > 0){
  pixel[y-0][x+4] = 1;
  pixel[y-1][x+4] = 1;
  pixel[y-2][x+4] = 1;
  pixel[y-3][x+4] = 1;
  pixel[y-4][x+4] = 1;
  pixel[y-5][x+4] = 1;
  pixel[y-6][x+4] = 1;
  pixel[y-7][x+4] = 1;
  pixel[y-8][x+4] = 1;
	}

	if(x+5 < 128 && x+5 > 0){
  pixel[y-0][x+5] = 1;
  pixel[y-1][x+5] = 1;
	pixel[y-2][x+5] = 1;
  pixel[y-3][x+5] = 1;
  pixel[y-4][x+5] = 1;
  pixel[y-5][x+5] = 1;
  pixel[y-6][x+5] = 1;
  pixel[y-7][x+5] = 1;
	}

	if(x+6 < 128 && x+6 > 0){
	pixel[y-1][x+6] = 1;
  pixel[y-2][x+6] = 1;
  pixel[y-3][x+6] = 1;
  pixel[y-4][x+6] = 1;
  pixel[y-5][x+6] = 1;
  pixel[y-6][x+6] = 1;
  pixel[y-7][x+6] = 1;
	}

	if(x+7 < 128 && x+7 > 0){
  pixel[y-3][x+7] = 1;
	pixel[y-4][x+7] = 1;
  pixel[y-5][x+7] = 1;
  pixel[y-6][x+7] = 1;
	}
}
//Defines which pixels are used for the hitbox of the boulder sprite
bool boulderIsHit(x,y){
	if(pixel[y-2][x-1] == 1 | pixel[y-3][x-1] == 1 | pixel[y-4][x-1] == 1 | pixel[y-5][x-1] == 1 | pixel[y-6][x-1] == 1)
			if(x-1 < 128 && x-1 > 0)
				return true;

	if(pixel[y-1][x+0] == 1 | pixel[y-7][x+0] == 1)
			if(x+0 < 128 && x+0 > 0)
				return true;

  if(pixel[y-0][x+1] == 1 | pixel[y-8][x+1] == 1)
			if(x+1 < 128 && x+1 > 0)
				return true;

	if(pixel[y+1][x+2] == 1 | pixel[y-8][x+2] == 1)
	 		if(x+2 < 128 && x+2 > 0)
				return true;

	if(pixel[y+1][x+3] == 1 | pixel[y-9][x+3] == 1)
	 		if(x+3 < 128 && x+3 > 0)
				return true;

	if(pixel[y+1][x+4] == 1 | pixel[y-9][x+4] == 1)
			if(x+4 < 128 && x+4 > 0)
				return true;

	if(pixel[y+1][x+5] == 1 | pixel[y-8][x+5] == 1)
			if(x+5 < 128 && x+5 > 0)
				return true;

	if(pixel[y-0][x+6] == 1 | pixel[y-8][x+6] == 1)
			if(x+6 < 128 && x+6 > 0)
				return true;

	if(pixel[y-2][x+7] == 1 | pixel[y-7][x+7] == 1)
			if(x+7 < 128 && x+7 > 0)
				return true;

	if(pixel[y-3][x+8] == 1 | pixel[y-4][x+8] == 1 | pixel[y-5][x+8] == 1 | pixel[y-6][x+8] == 1)
	 		if(x+8 < 128 && x+8 > 0)
				return true;

		else
			return false;
}
//Defines what pixels to write on screen for the explosion sprite
void explosion(x,y){
	if(x < 128 && x > 0 && y-11 < 32 && y-11 > 0)
	pixel[y-11][x+0] = 1;

	if(x+3 < 128 && x+3 > 0 && y-12 < 32 && y-12 > 0)
  pixel[y-12][x+3] = 1;

	if(x+3 < 128 && x+3 > 0 && y-13 < 32 && y-13 > 0)
  pixel[y-13][x+3] = 1;

	if(x+4 < 128 && x+4 > 0 && y-4 < 32 && y-4 > 0)
  pixel[y-4][x+4] = 1;

	if(x+4 < 128 && x+4 > 0 && y-5 < 32 && y-5 > 0)
  pixel[y-5][x+4] = 1;

	if(x+4 < 128 && x+4 > 0 && y-11 < 32 && y-11 > 0)
  pixel[y-11][x+4] = 1;

	if(x+4 < 128 && x+4 > 0 && y-12 < 32 && y-12 > 0)
  pixel[y-12][x+4] = 1;

	if(x+5 < 128 && x+5 > 0 && y-5 < 32 && y-5 > 0)
  pixel[y-5][x+5] = 1;

	if(x+5 < 128 && x+5 > 0 && y-6 < 32 && y-6 > 0)
  pixel[y-6][x+5] = 1;

	if(x+5 < 128 && x+5 > 0 && y-10 < 32 && y-10 > 0)
  pixel[y-10][x+5] = 1;

	if(x+5 < 128 && x+5 > 0 && y-11 < 32 && y-11 > 0)
  pixel[y-11][x+5] = 1;

	if(x+8 < 128 && x+8 > 0 && y-6 < 32 && y-6 > 0)
  pixel[y-6][x+8] = 1;

	if(x+9 < 128 && x+9 > 0 && y-12 < 32 && y-12 > 0)
  pixel[y-12][x+9] = 1;

	if(x+10 < 128 && x+10 > 0 && y-13 < 32 && y-13 > 0)
  pixel[y-13][x+10] = 1;

	if(x+10 < 128 && x+10 > 0 && y-14 < 32 && y-14 > 0)
  pixel[y-14][x+10] = 1;

	if(x+11 < 128 && x+11 > 0 && y-2 < 32 && y-2 > 0)
  pixel[y-2][x+11] = 1;

	if(x+11 < 128 && x+11 > 0 && y-3 < 32 && y-3 > 0)
  pixel[y-3][x+11] = 1;

	if(x+12 < 128 && x+12 > 0 && y-1 < 32 && y-1 > 0)
  pixel[y-1][x+12] = 1;

	if(x+12 < 128 && x+12 > 0 && y-2 < 32 && y-2 > 0)
  pixel[y-2][x+12] = 1;

	if(x+12 < 128 && x+12 > 0 && y-10 < 32 && y-10 > 0)
  pixel[y-10][x+12] = 1;

	if(x+13 < 128 && x+13 > 0 && y-0 < 32 && y-0 > 0)
  pixel[y-0][x+13] = 1;

	if(x+13 < 128 && x+13 > 0 && y-7 < 32 && y-7 > 0)
  pixel[y-7][x+13] = 1;

	if(x+13 < 128 && x+13 > 0 && y-10 < 32 && y-10 > 0)
  pixel[y-10][x+13] = 1;

	if(x+13 < 128 && x+13 > 0 && y-11 < 32 && y-11 > 0)
  pixel[y-11][x+13] = 1;

	if(x+14 < 128 && x+14 > 0 && y-6 < 32 && y-6 > 0)
  pixel[y-6][x+14] = 1;

	if(x+14 < 128 && x+14 > 0 && y-7 < 32 && y-7 > 0)
  pixel[y-7][x+14] = 1;

	if(x+14 < 128 && x+14 > 0 && y-11 < 32 && y-11 > 0)
  pixel[y-11][x+14] = 1;

	if(x+14 < 128 && x+14 > 0 && y-12 < 32 && y-12 > 0)
  pixel[y-12][x+14] = 1;

	if(x+15 < 128 && x+15 > 0 && y-6 < 32 && y-6 > 0)
  pixel[y-6][x+15] = 1;

	if(x+15 < 128 && x+15 > 0 && y-12 < 32 && y-12 > 0)
  pixel[y-12][x+15] = 1;

	if(x+19 < 128 && x+19 > 0 && y-7 < 32 && y-7 > 0)
  pixel[y-7][x+19] = 1;
}
//Function for drawing the curtain sprite
void curtain(y){
	int w;
	for(w = 0; w < 128; w += 8){
		if(y < 32 && y > 0){
			pixel[y-0][w+0] = 0;
			pixel[y-0][w+1] = 0;
			pixel[y-0][w+2] = 1;
			pixel[y-0][w+3] = 1;
			pixel[y-0][w+4] = 1;
			pixel[y-0][w+5] = 1;
			pixel[y-0][w+6] = 1;
			pixel[y-0][w+7] = 0;
			}

		if(y-1 < 32 && y-1 > 0){
			pixel[y-1][w+0] = 0;
			pixel[y-1][w+1] = 1;
			pixel[y-1][w+2] = 1;
			pixel[y-1][w+3] = 1;
			pixel[y-1][w+4] = 1;
			pixel[y-1][w+5] = 1;
			pixel[y-1][w+6] = 1;
			pixel[y-1][w+7] = 1;
			}

		if(y-2 < 32 && y-2 > 0){
			pixel[y-2][w+0] = 0;
			pixel[y-2][w+1] = 1;
			pixel[y-2][w+2] = 1;
			pixel[y-2][w+3] = 1;
			pixel[y-2][w+4] = 1;
			pixel[y-2][w+5] = 1;
			pixel[y-2][w+6] = 1;
			pixel[y-2][w+7] = 1;
			}

		if(y-3 < 32 && y-3 > 0){
			pixel[y-3][w+0] = 0;
			pixel[y-3][w+1] = 1;
			pixel[y-3][w+2] = 0;
			pixel[y-3][w+3] = 0;
			pixel[y-3][w+4] = 0;
			pixel[y-3][w+5] = 0;
			pixel[y-3][w+6] = 0;
			pixel[y-3][w+7] = 1;
			}
		}
	}
