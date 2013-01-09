#include "space_invaders.h"

struct si_entity si_entity_mk(SDL_Rect box,SDL_Surface *img)
{
    struct si_entity ent;

    ent.box=box;
    ent.img=img;
    ent.lastbox=ent.box;
    ent.vx=0;
    ent.vy=0;

    return ent;
}

void si_entity_draw(struct si_entity *ent)
{
    SDL_Rect getbox;

    getbox.x=tick*ent->box.w;
    getbox.y=0;
    getbox.w=ent->box.w;
    getbox.h=ent->box.h;

    SDL_FillRect(screen,&(ent->lastbox),SDL_MapRGB(screen->format,0,0,0));
    SDL_BlitSurface(ent->img,&getbox,screen,&(ent->box));
    SDL_Flip(screen);

    ent->lastbox=ent->box;
}
