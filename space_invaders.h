#ifndef SPACE_INVADERS_H
#define SPACE_INVADERS_H

#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

//Name and version
#define SPACE_INVADERS_NAME "Space Invaders by Mwitishi"
#define SPACE_INVADERS_VERSION "v0.1"

//Folder for storing images
#define SPACE_INVADERS_IMGFOLDER "imgs/"

//Image names (no path)
#define SPACE_INVADERS_ENEMY_IMGS "space_invaders_enemy.png"
#define SPACE_INVADERS_PLAYER_IMGS "space_invaders_player.png"
#define SPACE_INVADERS_SHOT_IMGS "space_invaders_shot.png"

#define SPACE_INVADERS_TICK_RESET 8//Maximum value for tick
#define SPACE_INVADERS_TICK_MS 100//Milliseconds per tick (1s=1000ms)
#define SPACE_INVADERS_SCREEN_X 320//Screen size
#define SPACE_INVADERS_SCREEN_Y 160
#define SPACE_INVADERS_PLAYER_SIZE 16//Entity size
#define SPACE_INVADERS_ENEMY_SIZE 16
#define SPACE_INVADERS_SHOT_W 2
#define SPACE_INVADERS_SHOT_H 6
#define SPACE_INVADERS_LEFT_LIMIT 16//Limits of movement
#define SPACE_INVADERS_RIGHT_LIMIT 304
#define SPACE_INVADERS_ENEMY_QUAN 1//Amount of enemies spawned
#define SPACE_INVADERS_SHOT_QUAN 5//Amount of shots simultaneously possible
#define SPACE_INVADERS_ENEMY_COLS 5//Columns of enemy formation
#define SPACE_INVADERS_PLAYER_V 3//Player speed
#define SPACE_INVADERS_ENEMY_V 2//Enemy speed
#define SPACE_INVADERS_SHOT_V 5//Shot speed
#define SPACE_INVADERS_PLAYER_TPF 2//Ticks per frame, higher->slower animation
#define SPACE_INVADERS_ENEMY_TPF 2
#define SPACE_INVADERS_SHOT_TPF 1
#define SPACE_INVADERS_PLAYER_FQUAN 4//Amount of frames of the animation
#define SPACE_INVADERS_ENEMY_FQUAN 4
#define SPACE_INVADERS_SHOT_FQUAN 2
#define SPACE_INVADERS_SHOT_RELOAD 5//Amount of ticks between shots

//Structure for storing entities like the player or the enemies
struct si_entity{
    int vx;//Horizontal speed
    int vy;//Vertical speed
    int tpf;//Ticks per frame
    int fquan;//Frame amount
    SDL_Rect box;//Current entity position
    SDL_Rect lastbox;//Last drawn position (it's cleared in each screen update)
    SDL_Surface *img;//Entity image
};

//Declare global variables as extern
#ifndef SPACE_INVADERS_EXTERNS
#define SPACE_INVADERS_EXTERNS

extern SDL_Surface *screen;
extern SDL_Surface *img_enemy;
extern SDL_Surface *img_player;
extern struct si_entity *player;
extern struct si_entity **enemies;
extern struct si_entity **shots;
extern int tick;

#endif

//space_invaders_entity.c function declarations
struct si_entity si_entity_mk(SDL_Rect,SDL_Surface*,int,int);
void si_entity_draw(struct si_entity*);
int si_entity_collide(struct si_entity*,struct si_entity*);
void si_entity_dispose(struct si_entity**);

#endif
