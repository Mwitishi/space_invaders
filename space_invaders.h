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

//Structure for storing entities like the player or the enemies
struct si_entity{
    SDL_Rect box;
    SDL_Rect lastbox;
};

//Declare global variables as extern
#ifndef SPACE_INVADERS_EXTERNS
#define SPACE_INVADERS_EXTERNS

extern SDL_Surface *screen;
extern SDL_Surface *img_enemy;

#endif

//space_invaders_entity.c function declarations


#endif
