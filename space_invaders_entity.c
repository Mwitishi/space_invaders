#include "space_invaders.h"

//Make a si_entity with specified parameters (like class constructor)
struct si_entity si_entity_mk(SDL_Rect box,SDL_Surface *img,int tpf,int fquan)
{
    struct si_entity ent;

    ent.box=box;
    ent.img=img;
    ent.lastbox=ent.box;
    ent.vx=0;
    ent.vy=0;
    ent.tpf=tpf;
    ent.fquan=fquan;

    return ent;
}

//Draw specified entity on screen
void si_entity_draw(struct si_entity *ent)
{
    SDL_Rect getbox;

    if(ent==NULL)
        return;

    //Set box to retrieve from image
    getbox.x=((tick/ent->tpf)%(ent->fquan))*ent->box.w;
    getbox.y=0;
    getbox.w=ent->box.w;
    getbox.h=ent->box.h;

    //Clean previous position, draw at new position
    SDL_FillRect(screen,&(ent->lastbox),SDL_MapRGB(screen->format,0,0,0));
    SDL_BlitSurface(ent->img,&getbox,screen,&(ent->box));

    //Set lastbox
    ent->lastbox=ent->box;
}

int si_entity_collide(struct si_entity *ent1,struct si_entity *ent2)
{
    if(ent1==NULL||ent2==NULL) return 0;
    if(ent1->box.x>ent2->box.x+ent2->box.w) return 0;
    if(ent2->box.x>ent1->box.x+ent1->box.w) return 0;
    if(ent1->box.y>ent2->box.y+ent2->box.h) return 0;
    if(ent2->box.y>ent1->box.y+ent1->box.h) return 0;

    return 1;
}

void si_entity_dispose(struct si_entity **ent1)
{
    SDL_FillRect(screen,&((**ent1).lastbox),SDL_MapRGB(screen->format,0,0,0));
    free(*ent1);
    *ent1=NULL;
}
