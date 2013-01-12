#define SPACE_INVADERS_EXTERNS

#include "space_invaders.h"

//Global variables
SDL_Surface *screen=NULL;
SDL_Surface *img_enemy=NULL;
SDL_Surface *img_player=NULL;
SDL_Surface *img_shot=NULL;
struct si_entity *player=NULL;
struct si_entity **enemies=NULL;
struct si_entity **shots=NULL;
int tick=0;
int reload=0;

int space_invaders_shoot()
{
    int i1;
    SDL_Rect r1;

    //If player is dead
    if(player==NULL)
        return 0;

    //Get NULL shot pointer, return if it's full
    for(i1=0;shots[i1]!=NULL&&i1<SPACE_INVADERS_SHOT_QUAN;i1++);
    if(i1==SPACE_INVADERS_SHOT_QUAN) return 0;

    //If reload is not done
    if(reload!=0)
        return 0;

    r1.x=(*player).box.x+(SPACE_INVADERS_PLAYER_SIZE-SPACE_INVADERS_SHOT_W)/2;
    r1.y=(*player).box.y-SPACE_INVADERS_SHOT_H;
    r1.w=SPACE_INVADERS_SHOT_W;
    r1.h=SPACE_INVADERS_SHOT_H;

    shots[i1]=(struct si_entity*)malloc(sizeof(struct si_entity));
    *(shots[i1])=si_entity_mk(r1,img_shot,SPACE_INVADERS_SHOT_TPF,SPACE_INVADERS_SHOT_FQUAN);
    (*(shots[i1])).vy=-SPACE_INVADERS_SHOT_V;

    reload=SPACE_INVADERS_SHOT_RELOAD;

    return 0;
}

int space_invaders_event()
{
    SDL_Event e1;

    //Loop through all events in the queue
    while(SDL_PollEvent(&e1))
    {
        //Window closing attempt
        if(e1.type==SDL_QUIT)
            return 1;

        //Pressed key
        if(e1.type==SDL_KEYDOWN)
        {
            //Left pressed, set vx to left
            if(e1.key.keysym.sym==SDLK_LEFT)
                (*player).vx-=SPACE_INVADERS_PLAYER_V;
            //Right pressed, set vx to right
            if(e1.key.keysym.sym==SDLK_RIGHT)
                (*player).vx+=SPACE_INVADERS_PLAYER_V;
            if(e1.key.keysym.sym==SDLK_SPACE)
            {
                space_invaders_shoot();
            }
        }

        //Released key
        if(e1.type==SDL_KEYUP)
        {
            //Left released, set vx to right
            if(e1.key.keysym.sym==SDLK_LEFT)
                (*player).vx+=SPACE_INVADERS_PLAYER_V;
            //Right released, set vx to left
            if(e1.key.keysym.sym==SDLK_RIGHT)
                (*player).vx-=SPACE_INVADERS_PLAYER_V;
        }
    }

    return 0;
}

int space_invaders_draw()
{
    int i1;

    //Draw entities
    si_entity_draw(player);
    for(i1=0;i1<SPACE_INVADERS_ENEMY_QUAN;i1++)
        si_entity_draw(enemies[i1]);
    for(i1=0;i1<SPACE_INVADERS_SHOT_QUAN;i1++)
        si_entity_draw(shots[i1]);

    //Update screen
    SDL_Flip(screen);

    return 0;
}

int space_invaders_move()
{
    int i1;

    if(player!=NULL)
    {
        (*player).box.x+=(*player).vx;
        (*player).box.y+=(*player).vy;
        if((*player).box.x<SPACE_INVADERS_LEFT_LIMIT)
            (*player).box.x=SPACE_INVADERS_LEFT_LIMIT;
        if((*player).box.x+SPACE_INVADERS_PLAYER_SIZE>SPACE_INVADERS_RIGHT_LIMIT)
            (*player).box.x=SPACE_INVADERS_RIGHT_LIMIT-SPACE_INVADERS_PLAYER_SIZE;
    }

    for(i1=0;i1<SPACE_INVADERS_ENEMY_QUAN;i1++)
    {
        if(enemies[i1]==NULL)
            continue;
        (*(enemies[i1])).box.x+=(*(enemies[i1])).vx;
        (*(enemies[i1])).box.y+=(*(enemies[i1])).vy;
    }

    for(i1=0;i1<SPACE_INVADERS_SHOT_QUAN;i1++)
    {
        if(shots[i1]==NULL)
            continue;
        (*(shots[i1])).box.x+=(*(shots[i1])).vx;
        (*(shots[i1])).box.y+=(*(shots[i1])).vy;
        if((*(shots[i1])).box.y<0) si_entity_dispose(shots+i1);
    }

    return 0;
}

int space_invaders_collide()
{
    int i1,i2;

    for(i1=0;i1<SPACE_INVADERS_SHOT_QUAN;i1++)
    {
        if(si_entity_collide(player,shots[i1]))
        {
            si_entity_dispose(shots+i1);
            si_entity_dispose(&player);
        }

        for(i2=0;i2<SPACE_INVADERS_ENEMY_QUAN;i2++)
        {
            if(si_entity_collide(enemies[i2],shots[i1]))
            {
                si_entity_dispose(enemies+i2);
                si_entity_dispose(shots+i1);
            }
        }
    }

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
    screen=SDL_SetVideoMode(SPACE_INVADERS_SCREEN_X,SPACE_INVADERS_SCREEN_Y,32,SDL_SWSURFACE);

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

    //Load shot image
    str1=(char*)malloc(strlen(SPACE_INVADERS_IMGFOLDER)+strlen(SPACE_INVADERS_SHOT_IMGS)+1);
    sprintf(str1,"%s%s",SPACE_INVADERS_IMGFOLDER,SPACE_INVADERS_SHOT_IMGS);
    printf("Opening image %s\n",str1);
    img_shot=IMG_Load(str1);
    if(img_shot==NULL)
        printf("Loaded image = NULL\n");

    //Create player structure
    player=(struct si_entity*)malloc(sizeof(struct si_entity));
    r1.x=(SPACE_INVADERS_SCREEN_X-SPACE_INVADERS_PLAYER_SIZE)/2;
    r1.y=SPACE_INVADERS_SCREEN_Y-2*SPACE_INVADERS_PLAYER_SIZE;
    r1.w=SPACE_INVADERS_PLAYER_SIZE;
    r1.h=SPACE_INVADERS_PLAYER_SIZE;
    *player=si_entity_mk(r1,img_player,SPACE_INVADERS_PLAYER_TPF,SPACE_INVADERS_PLAYER_FQUAN);

    //Create enemy structures
    r1.w=SPACE_INVADERS_ENEMY_SIZE;
    r1.h=SPACE_INVADERS_ENEMY_SIZE;
    enemies=(struct si_entity**)malloc(sizeof(struct si_entity*)*SPACE_INVADERS_ENEMY_QUAN);
    for(i1=0;i1<SPACE_INVADERS_ENEMY_QUAN;i1++)
    {
        enemies[i1]=(struct si_entity*)malloc(sizeof(struct si_entity));
        r1.x=SPACE_INVADERS_ENEMY_SIZE*(2*i1+3);
        r1.y=SPACE_INVADERS_ENEMY_SIZE;
        *(enemies[i1])=si_entity_mk(r1,img_enemy,SPACE_INVADERS_ENEMY_TPF,SPACE_INVADERS_ENEMY_FQUAN);
    }

    //Create shot array
    shots=(struct si_entity**)malloc(sizeof(struct si_entity*)*SPACE_INVADERS_SHOT_QUAN);
    for(i1=0;i1<SPACE_INVADERS_SHOT_QUAN;i1++)
    {
        shots[i1]=NULL;
    }

    //Main loop
    while(1)
    {
        //Get time
        t1=SDL_GetTicks();

        //Process events, if window closed, exit
        if(space_invaders_event()==1)
            goto end;

        //Update entity position
        space_invaders_move();

        space_invaders_collide();

        //Draw screen
        space_invaders_draw();

        //Increase tick clock, decrease reload, wait until next tick
        tick=(tick+1)%SPACE_INVADERS_TICK_RESET;
        if(reload!=0) reload--;
        while(SDL_GetTicks()-t1<SPACE_INVADERS_TICK_MS);
    }

    //Release stuff
end:
    si_entity_dispose(&player);

    for(i1=0;i1<SPACE_INVADERS_ENEMY_QUAN;i1++)
        si_entity_dispose(enemies+i1);
    free(enemies);
    enemies=NULL;

    for(i1=0;i1<SPACE_INVADERS_SHOT_QUAN;i1++)
        si_entity_dispose(shots+i1);
    free(shots);
    shots=NULL;

    SDL_FreeSurface(img_shot);
    SDL_FreeSurface(img_player);
    SDL_FreeSurface(img_enemy);
    SDL_FreeSurface(screen);
    SDL_Quit();

    return 0;
}
