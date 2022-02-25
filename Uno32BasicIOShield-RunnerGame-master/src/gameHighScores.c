/* gameHighScores.c
   Written by johvh & davidjo2.
*/

#include <stdint.h>
#include <pic32mx.h>
#include "gameHeader.h"

int HIGH_SCORE_1 = 0;
int HIGH_SCORE_2 = 0;
int HIGH_SCORE_3 = 0;

/* evaluate whether score is new high score */
void evalueteScore(void){
    switch(DIFFICULTY){
        case 4:
            if(SCORE > HIGH_SCORE_1) HIGH_SCORE_1 = SCORE;
            break;
        case 8:
            if(SCORE > HIGH_SCORE_2) HIGH_SCORE_2 = SCORE;
            break;
        case 16:
            if(SCORE > HIGH_SCORE_3) HIGH_SCORE_3 = SCORE;
            break;
    }
}

/* Display content of high score screen */
void highScoresScreen(){
    /* Display high scores */
    displayString(30, 1, "High Scores");
	displayString(7, 2, "easy:");
    displayDigit(39, 2, HIGH_SCORE_1);
    displayString(65, 2, "medium:");
    displayDigit(111, 2, HIGH_SCORE_2);
    displayString(40, 3, "hard: ");
    displayDigit(72, 3, HIGH_SCORE_3);
}

/* Update the high score screen */
void updateHighScores(){
    highScoresScreen();
    display_update();
    if(getbtn1() == 0){
        GAMESTATE = 1;
    }
}
