#define SPACE_INVADERS_EXTERNS

#include "space_invaders.h"

//Global variables
SDL_Surface *screen=NULL;
SDL_Surface *img_enemy=NULL;
SDL_Surface *img_player=NULL;
struct si_entity *player;
struct si_entity *enemies;
int tick=0;

int main(int argc,char **argv)
{
    uint32_t t1;
    char *str1=NULL;
    SDL_Event e1;
    SDL_Rect r1;
    struct si_entity ent1;

    printf("%s %s\n",SPACE_INVADERS_NAME,SPACE_INVADERS_VERSION);

    SDL_Init(SDL_INIT_EVERYTHING);
    screen=SDL_SetVideoMode(640,480,32,SDL_SWSURFACE);
    str1=(char*)malloc(strlen(SPACE_INVADERS_IMGFOLDER)+strlen(SPACE_INVADERS_ENEMY_IMGS)+1);
    sprintf(str1,"%s%s",SPACE_INVADERS_IMGFOLDER,SPACE_INVADERS_ENEMY_IMGS);
    printf("Opening image %s\n",str1);
    img_enemy=IMG_Load(str1);
    if(img_enemy==NULL)
        printf("Loaded image = NULL\n");

    str1=(char*)malloc(strlen(SPACE_INVADERS_IMGFOLDER)+strlen(SPACE_INVADERS_PLAYER_IMGS)+1);
    sprintf(str1,"%s%s",SPACE_INVADERS_IMGFOLDER,SPACE_INVADERS_PLAYER_IMGS);
    printf("Opening image %s\n",str1);
    img_player=IMG_Load(str1);
    if(img_player==NULL)
        printf("Loaded image = NULL\n");

    r1.w=16;
    r1.h=16;
    r1.x=100;
    r1.y=100;
    ent1=si_entity_mk(r1,img_player);

    //Main loop
    while(1)
    {
        t1=SDL_GetTicks();

        //Event loop, process events
        while(SDL_PollEvent(&e1))
        {
            if(e1.type==SDL_QUIT)
                goto end;
        }

        ent1.box.x++;

        si_entity_draw(&ent1);

        tick=(tick+1)%4;
        while(SDL_GetTicks()-t1<200);
    }

end:
    SDL_FreeSurface(img_enemy);
    SDL_FreeSurface(screen);
    SDL_Quit();

    return 0;
}
