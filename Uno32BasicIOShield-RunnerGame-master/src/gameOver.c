//-----------------------------
// Written by johvh & davidjo2.
//-----------------------------

#include <stdint.h>
#include "gameHeader.h"

int timer = 0;

/**
* Function to draw the screen that is displayed when losing.
*/
void gameOverScreen(int val, int size) {
	int i;
	for (i = 0; i<size; i++) {
		if(i<128) {
			/* Draw upper border */
			dataArray[i] = 0x1;
		} else if(i>384) {
			/* Draw lower border */
			dataArray[i] = 0x80;
		} else {
			/* Zero the array */
			dataArray[i] = 0x0;
		}
	}
	/* Display strings */
	displayString(32, 1, "Game Over");
	displayString(36, 2, "Score: ");
	displayDigit(36 + 42, 2, SCORE);

	/* Display player and monster */
	renderMonster(10, 29, 1);
	((timer % 100)>50) ? renderLegDown(17, 30, 0) : renderLegUp(17, 30, 0);
}

/*
* Updating loop for the game over screen
*/
void updateGameOver() {
	timer++;
	/* Draw game over screen */
    gameOverScreen(0,512);
	/* update twice. When doing it once there is a chance the display doesn't update. (why??) */
    display_update();
	//display_update();
	/* Display game over for a few seconds */
    //sleep(10000000);

	if(timer > 1200){
		/* Go to menu */
		GAMESTATE = 1;
		SCORE = 0;
		timer = 0;
	}
}
