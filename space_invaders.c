#define SPACE_INVADERS_EXTERNS

#include "space_invaders.h"

//Global variables
SDL_Surface *screen=NULL;
SDL_Surface *img_enemy=NULL;
SDL_Surface *img_player=NULL;
struct si_entity *player=NULL;
struct si_entity **enemies=NULL;
int tick=0;

int space_invaders_event()
{
    SDL_Event e1;

    while(SDL_PollEvent(&e1))
    {
        if(e1.type==SDL_QUIT)
            return 1;

        if(e1.type==SDL_KEYDOWN)
        {
            if(e1.key.keysym.sym==SDLK_LEFT)
                (*player).vx-=SPACE_INVADERS_PLAYER_V;
            if(e1.key.keysym.sym==SDLK_RIGHT)
                (*player).vx+=SPACE_INVADERS_PLAYER_V;
        }

        if(e1.type==SDL_KEYUP)
        {
            if(e1.key.keysym.sym==SDLK_LEFT)
                (*player).vx+=SPACE_INVADERS_PLAYER_V;
            if(e1.key.keysym.sym==SDLK_RIGHT)
                (*player).vx-=SPACE_INVADERS_PLAYER_V;
        }
    }

    return 0;
}

int space_invaders_draw()
{
    int i1;

    si_entity_draw(player);
    for(i1=0;i1<SPACE_INVADERS_ENEMY_QUAN;i1++)
        si_entity_draw(enemies[i1]);

    SDL_Flip(screen);

    return 0;
}

int main(int argc,char **argv)
{
    int i1;
    uint32_t t1;
    char *str1=NULL;
    SDL_Rect r1;

    //Display name and version
    printf("%s %s\n",SPACE_INVADERS_NAME,SPACE_INVADERS_VERSION);

    //Init SDL, create screen
    SDL_Init(SDL_INIT_EVERYTHING);
    screen=SDL_SetVideoMode(320,320,32,SDL_SWSURFACE);

    //Load enemy image
    str1=(char*)malloc(strlen(SPACE_INVADERS_IMGFOLDER)+strlen(SPACE_INVADERS_ENEMY_IMGS)+1);
    sprintf(str1,"%s%s",SPACE_INVADERS_IMGFOLDER,SPACE_INVADERS_ENEMY_IMGS);
    printf("Opening image %s\n",str1);
    img_enemy=IMG_Load(str1);
    if(img_enemy==NULL)
        printf("Loaded image = NULL\n");

    //Load player image
    str1=(char*)malloc(strlen(SPACE_INVADERS_IMGFOLDER)+strlen(SPACE_INVADERS_PLAYER_IMGS)+1);
    sprintf(str1,"%s%s",SPACE_INVADERS_IMGFOLDER,SPACE_INVADERS_PLAYER_IMGS);
    printf("Opening image %s\n",str1);
    img_player=IMG_Load(str1);
    if(img_player==NULL)
        printf("Loaded image = NULL\n");

    //Create player structure
    player=(struct si_entity*)malloc(sizeof(struct si_entity));
    r1.x=152;
    r1.y=280;
    r1.w=16;
    r1.h=16;
    *player=si_entity_mk(r1,img_player,SPACE_INVADERS_PLAYER_TPF,SPACE_INVADERS_PLAYER_FQUAN);

    //Create enemy structures
    enemies=(struct si_entity**)malloc(sizeof(struct si_entity*)*SPACE_INVADERS_ENEMY_QUAN);
    for(i1=0;i1<SPACE_INVADERS_ENEMY_QUAN;i1++)
    {
        enemies[i1]=(struct si_entity*)malloc(sizeof(struct si_entity));
        r1.x=152;
        r1.y=40;
        *(enemies[i1])=si_entity_mk(r1,img_enemy,SPACE_INVADERS_ENEMY_TPF,SPACE_INVADERS_ENEMY_FQUAN);
    }

    //Main loop
    while(1)
    {
        //Get time
        t1=SDL_GetTicks();

        //Process events, if window closed, exit
        if(space_invaders_event()==1)
            goto end;

        //Update player position
        (*player).box.x+=(*player).vx;

        //Draw screen
        space_invaders_draw();

        //Increase tick clock, wait until next tick
        tick=(tick+1)%SPACE_INVADERS_TICK_RESET;
        while(SDL_GetTicks()-t1<SPACE_INVADERS_TICK_MS);
    }

    //Release stuff
end:
    SDL_FreeSurface(img_player);
    SDL_FreeSurface(img_enemy);
    SDL_FreeSurface(screen);
    SDL_Quit();

    return 0;
}
