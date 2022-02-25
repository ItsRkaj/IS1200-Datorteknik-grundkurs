//-----------------------------
// Written by johvh & davidjo2.
//-----------------------------

#include <stdint.h>
#include "gameHeader.h"
#include "entities.h"

/* Accumulator to determine game speed */
int accumulator = 0;
/* "Random" number */
int random = 0;
/* Init the global binary number */
int binaryNumber;

/* upside down variables */
int upsideDown = 0;
int upsideDownValue = 0;
int dimCounter = 50;

/**
 * Rendering method for gamescreen.
*/
void gameScreen(int val, int size) {
    unsigned char hex[16] = {0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80};
    int upsideDownIndex = ((31 - upsideDownValue)/8) + 1;
    int i;
    for (i = 0; i < size; i++) {
        if(i >= ((upsideDownIndex * 128) - 128) && i < (upsideDownIndex * 128)){
            dataArray[i] = hex[((31 - upsideDownValue) % 8)];
        } else{
            dataArray[i] = 0;
        }
    }
}

/**
* Get a "random" number.
*/
int getRandomInt(int i) {
    random = (random*53 + 5) % 7283;
    return random%i;
}

/* change ground dimension */
void changeDimension(){
    if(dimCounter <= 49){
        dimCounter++;
        if(dimCounter <= 20){
            (upsideDown) ? upsideDownValue-- : upsideDownValue++;
        } else if(dimCounter <= 32) {
            if((dimCounter - 20) % 2){
                (upsideDown) ? upsideDownValue-- : upsideDownValue++;
            }
        } else if(dimCounter <= 40){
            if((dimCounter - 32) % 3 == 2){
                (upsideDown) ? upsideDownValue-- : upsideDownValue++;
            }
        } else if(dimCounter <= 49){
            if((dimCounter - 40) % 4 == 3){
                (upsideDown) ? upsideDownValue-- : upsideDownValue++;
            }
        } else{
            if(upsideDown){
                upsideDownValue = 0;
                upsideDown = 0;
                obstacle.x = 135;
            } else {
                upsideDownValue = 31;
                upsideDown = 1;
                obstacle.x = 135;
            }
        }
    }
}

/**
 * Update game, this is the game running loop.
 */
void updateRunning() {
    /* Render game screen */
    gameScreen(0,512);
    /* Accumulator to determine game update speed */
    accumulator++;
    if(accumulator > 14) {
        /* Only update every 14th time we render */
        entities_update();
        changeDimension();
        accumulator = 0;
    }
    /* Render every cycle */
    entities_render();
    /* Update display */
    display_update();
}
