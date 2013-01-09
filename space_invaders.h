#ifndef SPACE_INVADERS_H
#define SPACE_INVADERS_H

#include <stdio.h>
#include <time.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#define SPACE_INVADERS_NAME "Space Invaders by Mwitishi"
#define SPACE_INVADERS_VERSION "v0.0"

#define SPACE_INVADERS_IMGFOLDER "imgs/"

#define SPACE_INVADERS_ENEMY_IMGS "space_invaders_enemy.png"
#define SPACE_INVADERS_PLAYER_IMGS "space_invaders_player.png"

#define SPACE_INVADERS_ENEMY_QUAN 1

//Structure for storing entities like the player or the enemies
struct si_entity{
    int vx;
    int vy;
    SDL_Rect box;
    SDL_Rect lastbox;
    SDL_Surface *img;
};

//Declare global variables as extern
#ifndef SPACE_INVADERS_EXTERNS
#define SPACE_INVADERS_EXTERNS

extern SDL_Surface *screen;
extern SDL_Surface *img_enemy;
extern SDL_Surface *img_player;
extern int tick;

#endif

//space_invaders_entity.c function declarations
struct si_entity si_entity_mk(SDL_Rect,SDL_Surface*);
void si_entity_draw(struct si_entity*);

#endif
