#ifndef SPACE_INVADERS_H
#define SPACE_INVADERS_H

#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#define SPACE_INVADERS_NAME "Space Invaders by Mwitishi"
#define SPACE_INVADERS_VERSION "v0.0"

//Structure for storing entities like the player or the enemies
struct si_entity{
    SDL_Rect box;
    SDL_Rect lastbox;
};

//Declara como externas las variables globales
#ifndef SPACE_INVADERS_EXTERNS
#define SPACE_INVADERS_EXTERNS

#endif

#endif
