#define SPACE_INVADERS_EXTERNS

#include "space_invaders.h"

//Global variables
SDL_Surface *screen=NULL;
SDL_Surface *img_enemy=NULL;
int tick=0;

int main(int argc,char **argv)
{
    uint32_t t1;
    char *str1;
    SDL_Event e1;
    SDL_Rect r1;

    printf("%s %s\n",SPACE_INVADERS_NAME,SPACE_INVADERS_VERSION);

    SDL_Init(SDL_INIT_EVERYTHING);
    screen=SDL_SetVideoMode(640,480,32,SDL_SWSURFACE);
    str1=(char*)malloc(strlen(SPACE_INVADERS_IMGFOLDER)+strlen(SPACE_INVADERS_ENEMY_IMGS)+1);
    sprintf(str1,"%s%s",SPACE_INVADERS_IMGFOLDER,SPACE_INVADERS_ENEMY_IMGS);
    printf("Opening image %s\n",str1);
    img_enemy=IMG_Load(str1);
    if(img_enemy==NULL)
        printf("Loaded image = NULL\n");

    //Main loop
    while(1)
    {
        t1=SDL_GetTicks();;

        //Event loop, process events
        while(SDL_PollEvent(&e1))
        {
            if(e1.type==SDL_QUIT)
                goto end;
        }

        r1.x=16*tick;
        r1.y=0;
        r1.w=16;
        r1.h=16;
        SDL_FillRect(screen,&r1,SDL_MapRGB(screen->format,0,0,0));
        SDL_BlitSurface(img_enemy,&r1,screen,NULL);
        SDL_Flip(screen);

        tick=(tick+1)%4;
        while(SDL_GetTicks()-t1<200);
    }

end:
    SDL_FreeSurface(img_enemy);
    SDL_FreeSurface(screen);
    SDL_Quit();

    return 0;
}
