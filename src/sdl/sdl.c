#include "SDL.h"
#include <stdio.h>

#define TICK_INTERVAL 50

static Uint32 next_time;

Uint32 time_left(void)
{
    Uint32 now;

    now = SDL_GetTicks();
    if(next_time <= now)
        return 0;
    else
        return next_time - now;
}

/**
 * SDL test, not related to Amiga.
 * To be used for macro compatibility layer test.
 *
 * Source:  https://www.libsdl.org/release/SDL-1.2.15/docs/html/guidebasicsinit.html
 *
 * Assumes libsdl1.2-dev is installed on system.
 *
 * Compile with:
 *   gcc sdl.c -o sdl `pkg-config --cflags --libs sdl`
 */
int main(int argc, char *argv[])
{
    SDL_Surface *screen, *temp, *sprite;
    SDL_Rect rcSprite, rcSprite2;
    int colorkey;

    printf("Initializing SDL.\n");

    /* Initialize defaults, Video and Audio */
    if((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)==-1)) { 
        printf("Could not initialize SDL: %s.\n", SDL_GetError());
        exit(-1);
    }

    printf("SDL initialized.\n");

    //screen = SDL_SetVideoMode(320, 256, 8, SDL_SWSURFACE | SDL_FULLSCREEN);
    screen = SDL_SetVideoMode(320, 256, 8, SDL_SWSURFACE);
    if (screen == NULL) {
        fprintf(stderr, "Couldn't set 640x480x8 video mode: %s\n", SDL_GetError());
        exit(1);
    }

    temp   = SDL_LoadBMP("Vikings_walkabout_000.bmp");
    sprite = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
    SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

    rcSprite.x = 30;
    rcSprite.y = 30;
    rcSprite2.x = 0;
    rcSprite2.y = 0;

    short delta_move, ktr1, ktr2, color_reg;
    next_time = SDL_GetTicks() + TICK_INTERVAL;
    for ( ktr1 = 0, delta_move = 1; ktr1 < 6; ktr1++, delta_move = -delta_move) {
        for ( ktr2 = 0; ktr2 < 100; ktr2++) { 
            rcSprite.x  += delta_move;
            rcSprite.y  += delta_move;
            SDL_BlitSurface(sprite, NULL, screen, &rcSprite);
            SDL_UpdateRect(screen, 0, 0, 0, 0);
            SDL_Delay(time_left());
            next_time += TICK_INTERVAL;
        }
    }

    SDL_Delay(2000);

    SDL_FreeSurface(sprite);

    /* Shutdown all subsystems */
    SDL_Quit();

    printf("Quiting....\n");

    exit(0);
}
