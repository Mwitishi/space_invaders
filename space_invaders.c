#include "space_invaders.h"

//Variables globales
#define SPACE_INVADERS_EXTERNS
SDL_Surface *screen=NULL;

int main(int argc,char **argv)
{
    SDL_Event e1;

    printf("%s %s\n",SPACE_INVADERS_NAME,SPACE_INVADERS_VERSION);

    SDL_Init(SDL_INIT_EVERYTHING);
    screen=SDL_SetVideoMode(640,480,32,SDL_SWSURFACE);

    while(1)
    {
        while(SDL_PollEvent(&e1))
        {
            if(e1.type==SDL_QUIT)
                goto end;
        }

    }

end:
    SDL_FreeSurface(screen);
    SDL_Quit();

    return 0;
}
