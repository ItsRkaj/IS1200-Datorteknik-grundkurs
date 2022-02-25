//-----------------------------
// Written by johvh & davidjo2.
//-----------------------------

#include "entities.h"
#include <stdint.h>

/* render leg down running animation */
void renderLegDown(int x, int y, int upsideDown){
    if(!upsideDown){
        displayPixel(x,y-3);
        displayPixel(x,y-4);
        displayPixel(x+1,y);
        displayPixel(x+1,y-1);
        displayPixel(x+1,y-2);
        displayPixel(x+1,y-3);
        displayPixel(x+1,y-4);
        displayPixel(x+1,y-5);
        displayPixel(x+2,y-2);
        displayPixel(x+2,y-4);
        displayPixel(x+3,y-1);
        displayPixel(x+3,y-2);

    } else {
        displayPixel(x,y-1);
        displayPixel(x,y-2);
        displayPixel(x+1,y);
        displayPixel(x+1,y-1);
        displayPixel(x+1,y-2);
        displayPixel(x+1,y-3);
        displayPixel(x+1,y-4);
        displayPixel(x+1,y-5);
        displayPixel(x+2,y-1);
        displayPixel(x+2,y-3);
        displayPixel(x+3,y-3);
        displayPixel(x+3,y-4);
    }
}

/* render leg up running animation */
void renderLegUp(int x, int y, int upsideDown){
    if(!upsideDown){
        displayPixel(x,y-3);
        displayPixel(x,y-4);
        displayPixel(x,y-1);
        displayPixel(x+1,y-1);
        displayPixel(x+1,y-2);
        displayPixel(x+1,y-3);
        displayPixel(x+1,y-4);
        displayPixel(x+1,y-5);
        displayPixel(x+2,y);
        displayPixel(x+2,y-1);
        displayPixel(x+2,y-2);
        displayPixel(x+2,y-4);

    } else{
        displayPixel(x,y-1);
        displayPixel(x,y-2);
        displayPixel(x,y-4);
        displayPixel(x+1,y);
        displayPixel(x+1,y-1);
        displayPixel(x+1,y-2);
        displayPixel(x+1,y-3);
        displayPixel(x+1,y-4);
        displayPixel(x+2,y-1);
        displayPixel(x+2,y-3);
        displayPixel(x+2,y-4);
        displayPixel(x+2,y-5);
    }
}

/* render first jumping animation */
void renderJumpingGround(int x, int y, int upsideDown){
    if(!upsideDown){
        displayPixel(x+1,y-1);
        displayPixel(x+1,y-2);
        displayPixel(x+1,y-3);
        displayPixel(x+1,y-4);
        displayPixel(x+2,y-1);
        displayPixel(x+2,y-3);
        displayPixel(x+3,y);
        displayPixel(x+3,y-1);
    } else {
        displayPixel(x+1,y-1);
        displayPixel(x+1,y-2);
        displayPixel(x+1,y-3);
        displayPixel(x+1,y-4);
        displayPixel(x+2,y-2);
        displayPixel(x+2,y-4);
        displayPixel(x+3,y-4);
        displayPixel(x+3,y-5);
    }
}

/* render second jumping animation */
void renderJumpingAir(int x, int y, int upsideDown){
    if(!upsideDown){
        displayPixel(x,y-1);
        displayPixel(x+1,y-1);
        displayPixel(x+1,y-3);
        displayPixel(x+1,y-4);
        displayPixel(x+2,y-1);
        displayPixel(x+2,y-2);
        displayPixel(x+2,y-3);
        displayPixel(x+2,y-4);
        displayPixel(x+2,y-5);
        displayPixel(x+3,y-4);
    } else{
        displayPixel(x,y-4);
        displayPixel(x+1,y-1);
        displayPixel(x+1,y-2);
        displayPixel(x+1,y-4);
        displayPixel(x+2,y);
        displayPixel(x+2,y-1);
        displayPixel(x+2,y-2);
        displayPixel(x+2,y-3);
        displayPixel(x+2,y-4);
        displayPixel(x+3,y-1);
    }
}

/* render stone animation */
void renderStone(int x, int y){
    displayPixel(x,y);
    displayPixel(x,y-1);
    displayPixel(x,y-2);
    displayPixel(x+1,y);
    displayPixel(x+1,y-1);
    displayPixel(x+1,y-2);
    displayPixel(x+2,y);
    displayPixel(x+2,y-1);
    displayPixel(x+2,y-2);
}

/* render cloud */
void renderCloud(int x, int y){
    displayHex(x, y, 0x4);
    displayHex(x+1, y, 0x4);
    displayHex(x+2, y, 0x6);
    displayHex(x+3, y, 0x7);
    displayHex(x+4, y, 0x6);
    displayHex(x+5, y, 0x6);
    displayHex(x+6, y, 0x4);
}

/* render monster animation */
void renderMonster(int x, int y, int legDown){
    if(legDown){
        displayHex(x, 3, 0xc0);
        displayHex(x+1, 3, 0x40);
        displayHex(x+2, 3, 0x7e);
        displayHex(x+3, 3, 0x26);
        displayHex(x+4, 3, 0xc9);
        displayHex(x+5, 3, 0x9);
        displayHex(x+6, 3, 0x2);
        displayPixel(x+4, y-6);
        displayPixel(x+5, y-6);
        displayPixel(x+6, y-7);
    } else{
        displayHex(x, 3, 0x80);
        displayHex(x+1, 3, 0x80);
        displayHex(x+2, 3, 0xfe);
        displayHex(x+3, 3, 0x7e);
        displayHex(x+4, 3, 0x69);
        displayHex(x+5, 3, 0x49);
        displayHex(x+6, 3, 0x1);
        displayPixel(x+4, y-6);
        displayPixel(x+5, y-6);
        displayPixel(x+6, y-7);
    }
}

/* render corner webs */
void renderWeb(int menu){
    displayHex(0, 3, 0x91);
    displayHex(1, 3, 0x88);
    displayHex(2, 3, 0x22);
    displayHex(3, 3, 0x94);
    displayHex(4, 3, 0x10);
    displayHex(5, 3, 0x28);
    displayHex(6, 3, 0x40);
    displayHex(7, 3, 0x28);
    displayHex(8, 3, 0x80);
    displayHex(9, 3, 0x40);
    displayHex(10, 3, 0x80);
    displayHex(12, 3, 0x80);
    displayHex(17, 3, 0x80);
    displayHex(22, 3, 0x80);

    displayHex(127, 3, 0x5);
    displayHex(126, 3, 0x42);
    displayHex(125, 3, 0x88);
    displayHex(124, 3, 0x4);
    displayHex(123, 3, 0x40);
    displayHex(122, 3, 0x90);
    displayHex(121, 3, 0x40);
    displayHex(120, 3, 0xa0);
    displayHex(118, 3, 0x40);
    displayHex(117, 3, 0x80);
    displayHex(111, 3, 0x80);
    displayHex(107, 3, 0x80);
    displayHex(101, 3, 0x80);

    if(menu){
        displayHex(0, 0, 0x41);
        displayHex(1, 0, 0x22);
        displayHex(2, 0, 0x10);
        displayHex(3, 0, 0x21);
        displayHex(4, 0, 0xa);
        displayHex(5, 0, 0x10);
        displayHex(6, 0, 0x5);
        displayHex(7, 0, 0x2);
        displayHex(8, 0, 0x1);
        displayHex(10, 0, 0x1);
        displayHex(12, 0, 0x2);
        displayHex(17, 0, 0x1);
        displayHex(22, 0, 0x1);

        displayHex(127, 0, 0x91);
        displayHex(126, 0, 0x44);
        displayHex(125, 0, 0x10);
        displayHex(124, 0, 0x24);
        displayHex(123, 0, 0x2);
        displayHex(122, 0, 0x9);
        displayHex(121, 0, 0x8);
        displayHex(120, 0, 0x2);
        displayHex(118, 0, 0x1);
        displayHex(116, 0, 0x2);
        displayHex(112, 0, 0x1);
        displayHex(108, 0, 0x1);
        displayHex(100, 0, 0x1);
    }
}

/* render pixel */
void renderParticle(int x, int y){
    int randomVals1[5] = {0, 0, 0, 0, 0};
    int randomVals2[5] = {1, 1, 1, 1, 1};
    int randomVals3[5] = {0, 0, 0, 0, 0};
    int randomVals4[5] = {-1, -1, -1, -1, -1};
    if(x >= 0){
        int yIndex = x % 20;
        if(yIndex < 5){
            displayPixel(x, (y + randomVals1[yIndex]));
        } else if (yIndex >= 6 && yIndex < 10){
            displayPixel(x, (y + randomVals2[yIndex - 5]));
        } else if (yIndex >= 10 && yIndex < 15){
            displayPixel(x, (y + randomVals3[yIndex - 10]));
        } else{
            displayPixel(x, (y + randomVals4[yIndex - 15]));
        }
    } else {
        int yIndex = (128 + x) % 20;
        if(yIndex < 5){
            displayPixel(128 + x, (y + randomVals1[yIndex]));
        } else if (yIndex >= 6 && yIndex < 10){
            displayPixel(128 + x, (y + randomVals2[yIndex - 5]));
        } else if (yIndex >= 10 && yIndex < 15){
            displayPixel(128 + x, (y + randomVals3[yIndex - 10]));
        } else{
            displayPixel(128 + x, (y + randomVals4[yIndex - 15]));
        }
    }
}
