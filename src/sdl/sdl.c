#include "SDL.h"
#include <stdio.h>

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
int main(int argc, char *argv[]) {
    
    printf("Initializing SDL.\n");
    
    /* Initialize defaults, Video and Audio */
    if((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)==-1)) { 
        printf("Could not initialize SDL: %s.\n", SDL_GetError());
        exit(-1);
    }

    printf("SDL initialized.\n");

    printf("Quiting SDL.\n");
    
    /* Shutdown all subsystems */
    SDL_Quit();
    
    printf("Quiting....\n");

    exit(0);
}
