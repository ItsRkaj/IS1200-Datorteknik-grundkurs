//-----------------------------
// Written by johvh & davidjo2.
//-----------------------------

#include "gameHeader.h"

/* Init all the entities */
void entity_init(void);

/* enum for entities */
typedef enum EntityType {
    PLAYER, OBSTACLE, STONE, MONSTER
} EntityType_t;

/* Hitbox */
typedef struct Hitbox{
    int width;
    int height;
} Hitbox;

/* Monster struct */
typedef struct Monster{
    int x;
} Monster;

/* Player struct */
typedef struct Player {
    enum EntityType type;
    int x;
    int y;
    int playerScore;
    int jumping;
    int crouching;
    int legDown;
    Hitbox hitbox;
} Player;

/* Obstacle struct */
typedef struct Obstacle {
    enum EntityType type;
    double x;
    int y;
    Hitbox hitbox;
} Obstacle;

/* Player and the different update & rendering methods */
extern Player player;
extern Obstacle obstacle;
void renderLegDown(int,int,int);
void renderLegUp(int,int,int);
void renderJumpingGround(int,int,int);
void renderJumpingAir(int,int,int);
void updatePlayer();

/* Environment rendering methods */
void renderStone(int,int);
void renderCloud(int,int);
void renderWeb();
void renderParticle(int,int);
