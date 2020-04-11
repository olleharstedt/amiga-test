#ifdef __AMIGA__
#include <exec/types.h>
#include <graphics/gfx.h>
#include <graphics/gfxbase.h>
#include <graphics/gfxmacros.h>
#include <graphics/sprite.h>
#include <clib/graphics_protos.h>
#include <intuition/intuitionbase.h>
#include <hardware/custom.h>
#include <hardware/dmabits.h>
#include <libraries/dos.h>

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/intuition.h>
#else
#include "SDL.h"
#endif

#ifdef __AMIGA__
#define SPRITE SimpleSprite
#else
#define SPRITE SDL_Surface
#endif

/** Similar logic with rcSprite */

#ifdef __AMIGA__
#define MOVE_SPRITE(sprite, rcSprite) MoveSprite(NULL, sprite, rcSprite.x, rcSprite.y)
#else
/** Assumes screen is defined */
#define MOVE_SPRITE(sprite, rcSprite) SDL_BlitSurface(sprite, NULL, screen, rcSprite)
#endif

#ifdef __AMIGA__
#define TEST(x, y, args...) Test2(x, y, args)
#else
#define TEST(x, y, ...) Test(x, y)
#endif

void Test2(int x, int y, int z)
{
    return;
}

void Test(int x, int y)
{
    return;
}


/**
 * Slightly crazy test for macro compatibility layer between Amiga and SDL.
 *
 * Compile with:
 *   m68k-amigaos-gcc macro.c -o macro
 */
int main()
{
    /*
     * Define sprite data
     * Define screen properties
     * Init
     *   Amiga: GfxBase, IntuitionBase
     *   SDL: SDL_Init(VIDEO | AUDIO | etc)
     * Open screen
     * Allocate sprite and get sprite
     * Set sprite colors
     * Loop
     *   Move sprite
     * Cleanup and quit
     */
    return 0;
}
