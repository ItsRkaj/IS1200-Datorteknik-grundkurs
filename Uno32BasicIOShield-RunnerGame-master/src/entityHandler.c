//-----------------------------
// Written by johvh & davidjo2.
//-----------------------------

#include <stdint.h>
#include "entities.h"
#include "gameHeader.h"

/* Player entity */
#define PLAYER_X 10

/* Obstacle variable */
Obstacle obstacle;
int obstacleAmount = 0;

/* counters */
int timeCounter = 0;
int particleX = 128;
int cloudX = 0;

/* jump variables */
int jumpDelta = 60;

/* Init player */
Player player;


/* initialise obstacle struct */
void createObstacle(){
    Obstacle obs = { .type = STONE, .x = 129, .y = FLOOR_Y_UP, .hitbox = { .width = 3, .height = 3}};
    obstacle = obs;
}

/* Initialise entities */
void entity_init() {
    /* Player variables */
    player.type = PLAYER;
    player.y = FLOOR_Y_UP;
    player.playerScore = 0;
    player.jumping = 0;
    player.crouching = 0;
    player.legDown = 0;
    player.hitbox.width = 4;
    player.hitbox.height = 6;

    /* initialise obstacle */
    createObstacle();
}

/* render player animations */
void renderPlayer(int x, int y){
    /* If leg down and not jumping */
    if(player.legDown && !player.jumping) {
        renderLegDown(x, y, upsideDown);
    /* If leg up and not jumping */
    } else if(!player.legDown && !player.jumping){
        renderLegUp(x, y, upsideDown);
    /* If jumping and over a certain y coordinate */
    } else if(player.jumping && player.y > 25){
        renderJumpingGround(x, y, upsideDown);
    /* If jumping and under a certain y coordinate */
    } else {
        renderJumpingAir(x, y, upsideDown);
    }
}

/* render entities */
void render(EntityType_t type, int x, int y) {
    switch(type) {
        case PLAYER:
            renderPlayer(x, y);
            break;
        case STONE:
            renderStone(x, y);
            break;
    }
}

/* Reset obstacle, evaluate score
   and go to game over screen */
void reset() {
    evalueteScore();
    obstacle.x = 129;
    upsideDown = 0;
    upsideDownValue = 0;
    dimCounter = 50;
    GAMESTATE = 3;
}

/* check for collision between
   player and obstacles */
void checkCollisions(){
    if(PLAYER_X >= obstacle.x &&
    PLAYER_X <= obstacle.x + obstacle.hitbox.width ||
    PLAYER_X  + player.hitbox.width >= (int)obstacle.x &&
    PLAYER_X + player.hitbox.width <= (int)obstacle.x + obstacle.hitbox.width) {
        if(!upsideDown &&
        player.y > obstacle.y - obstacle.hitbox.height) {
            reset();
        } else if(upsideDown &&
        player.y - player.hitbox.height < obstacle.y) {
            reset();
        }
    }
}

/* jumping function */
void playerJump() {
    /* Jump if certain conditions are met. */
    if(jumpDelta >= 27 && dimCounter == 50 &&
        getbtns() == 4 && getsw() == binaryNumber) {
        jumpDelta = 0;
        player.jumping = 1;
        binaryNumber = getRandomInt(DIFFICULTY);
    /* Jump movement with functions */
    } else if(jumpDelta < 27) {
        jumpDelta++;
        if(player.y <= FLOOR_Y_UP && !upsideDown) player.y = (((jumpDelta - 27) * jumpDelta*jumpDelta) / 240) + 29;
        else player.y = -(((jumpDelta - 27) * jumpDelta*jumpDelta) / 240) + 8;
        if(jumpDelta == 20 && dimCounter == 50 && timeCounter % 7 == 1 && GAMESTATE == 2) dimCounter = 0;
    } else if(jumpDelta > 20 && dimCounter < 50){
        jumpDelta++;
        if(!upsideDown) player.y = -(0.015) * (jumpDelta - 20) * (jumpDelta - 52) + 23;
        else player.y = 0.015 * (jumpDelta - 20) * (jumpDelta - 52) + 13;
    /* Jump complete */
    } else{
        if(!upsideDown) player.y = FLOOR_Y_UP;
        else player.y = FLOOR_Y_DOWN;
        jumpDelta = 27;
        player.jumping = 0;
    }
}

void updatePlayer() {
    /* Increment time counter */
    timeCounter++;
    /* Check for player jump */
    playerJump();

    /* Simulate running */
    if(timeCounter % 5 == 0 && player.legDown){
        player.legDown = 0;
    } else if(timeCounter % 5 == 0 && !player.legDown){
        player.legDown = 1;
    }
}

/* Update the obstacle */
void updateObstacles() {
    /* Reset position if outside screen */
    if(obstacle.x < -2){
        SCORE++;
        obstacle.x = 128;
    }
    /* Move obstacle based on score */
    obstacle.x -= 1 + 0.02*SCORE;
    /* Set new floor based on upsdie down state */
    if(upsideDown) {
        obstacle.y = FLOOR_Y_DOWN - 4;
    } else {
        obstacle.y = FLOOR_Y_UP;
    }
}

/* Render everything in the background */
void renderBackground() {
    /* Render clouds */
    if(!upsideDown){
        renderCloud(128 - cloudX, 0);
        renderCloud(150 - cloudX, 2);
        renderCloud(200 - cloudX, 1);
    }
    if(upsideDown){
        /* Render particles */
        renderParticle(particleX, 11);
        renderParticle(particleX - 20, 27);
        renderParticle(particleX - 40, 15);
        renderParticle(particleX - 70, 30);
        renderParticle(particleX - 90, 22);
        renderParticle(particleX - 100, 19);
        renderParticle(particleX - 110, 25);
        renderParticle(particleX - 120, 12);
        /* Render web */
        renderWeb(0);
    }
}

/* update background animations */
void updateBackground(){
    /* Increment and decrement x values for clouds and particles */
    if(timeCounter % 2) particleX--;

    if(timeCounter % 4 == 0) cloudX++;

    if(particleX == 0) particleX = 128;

    if(cloudX == 206) cloudX = 0;
}

/* Render entities and background, and binary digit */
void entities_render() {
    render(obstacle.type, obstacle.x, obstacle.y);
    render(PLAYER,PLAYER_X,player.y);
    renderBackground();
    displayDigit(62,1,binaryNumber);
}

/* Update all entities on the screen, including background */
void entities_update() {
    /* Reset timeout counter (don't want overflow) */
    if(timeCounter > 130) timeCounter = 0;
    /* Update everything */
    updatePlayer();
    updateObstacles();
    updateBackground();
    checkCollisions();
    /* Check collisions */
    checkCollisions();
}
