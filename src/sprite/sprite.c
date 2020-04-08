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

#include <stdio.h>
#include <stdlib.h>

struct GfxBase *GfxBase = NULL;
struct IntuitionBase *IntuitionBase = NULL;
extern struct Custom custom;

/* real boring sprite data */
UWORD sprite_data[] = {
    0, 0,           /* position control           */
    0xffff, 0x0000, /* image data line 1, color 1 */
    0xffff, 0x0000, /* image data line 2, color 1 */
    0x0000, 0xffff, /* image data line 3, color 2 */
    0x0000, 0xffff, /* image data line 4, color 2 */
    0x0000, 0x0000, /* image data line 5, transparent */
    0x0000, 0xffff, /* image data line 6, color 2 */
    0x0000, 0xffff, /* image data line 7, color 2 */
    0xffff, 0xffff, /* image data line 8, color 3 */
    0xffff, 0xffff, /* image data line 9, color 3 */
    0, 0            /* reserved, must init to 0 0 */
};

struct NewScreen my_new_screen=
{
	0, 0, 320, 256, 5,
    DETAILPEN,
    BLOCKPEN,
	0,
	CUSTOMSCREEN,
	NULL,
	"MY SCREEN",
	NULL,
	NULL
};


/**
 * Source: https://wiki.amigaos.net/wiki/Hardware_Sprites
 *
 * Compile with
 *   vc +aos68k -lauto -lamiga sprite.c -o sprite
 * and if linking fails, use
 *   vlink -mrel -bamigahunk -x -Bstatic -Cvbcc -nostdlib $VBCC/targets/m68k-amigaos/lib/startup.o "/tmp/fileOIxFdU.o"   -lauto -lamiga -s -Rshort -L$VBCC/targets/m68k-amigaos/lib -lvc -o sprite
 * with the added -mrel switch.
 * Some info here: https://github.com/Sakura-IT/SonnetAmiga/issues/27
 *
 * Compile with gcc:
 *   m68k-amigaos-gcc sprite.c -o sprite
 * In my case:
 *   /opt/amiga/bin/m68k-amigaos-gcc -I /opt/amiga/m68k-amigaos/ndk-include/ sprite.c -o sprite
 */
int main(int argc, char **argv)
{
    struct SimpleSprite    sprite = {0};
    struct Screen *screen;
    struct ViewPort        *viewport;

    WORD sprite_num;
    SHORT delta_move, ktr1, ktr2, color_reg;
    int return_code; 
    return_code = RETURN_OK;

    // NB: 37 = Kickstart V2.04
    if (NULL == (GfxBase = (struct GfxBase *) OpenLibrary("graphics.library",37L))) {
        return_code = RETURN_FAIL;
    } else {
        if (NULL == (IntuitionBase = (struct IntuitionBase *)OpenLibrary("intuition.library",37L))) {
            return_code = RETURN_FAIL;
        } else {
            /* opened library, need a viewport to render a sprite over. */
            if (NULL == (screen = OpenScreen(&my_new_screen))) {
                return_code = RETURN_FAIL;
            } else {
                viewport = &screen->ViewPort;
                if (-1 == (sprite_num = GetSprite(&sprite, 2))) {
                    return_code = RETURN_WARN;
                } else {
                    /* Calculate the correct base color register number, */
                    /* set up the color registers.                       */
                    color_reg = 16 + ((sprite_num & 0x06) << 1);
                    printf("color_reg=%d\n", color_reg);
                    printf("sprite_num = %d\n", sprite_num);
                    SetRGB4(viewport, color_reg + 1, 12,  3,  8);
                    SetRGB4(viewport, color_reg + 2, 13, 13, 13);
                    SetRGB4(viewport, color_reg + 3,  4,  4, 15);

                    sprite.x = 0;       /* initialize position and size info    */
                    sprite.y = 0;       /* to match that shown in sprite_data   */
                    sprite.height = 9;  /* so system knows layout of data later */

                    /* install sprite data and move sprite to start position. */
                    ChangeSprite(NULL, &sprite, (APTR)sprite_data);
                    MoveSprite(NULL, &sprite, 30, 30);

                    /* move the sprite back and forth. */
                    for ( ktr1 = 0, delta_move = 1; ktr1 < 6; ktr1++, delta_move = -delta_move) {
                        for ( ktr2 = 0; ktr2 < 100; ktr2++) { 
                            MoveSprite(NULL, &sprite, (LONG) (sprite.x + delta_move), (LONG) (sprite.y + delta_move));
                            WaitTOF(); /* one move per video frame */

                            /* Show the effect of turning off sprite DMA. */
                            if (ktr2 == 40) OFF_SPRITE ;
                            if (ktr2 == 60) ON_SPRITE ;
                        }
                    }
                    /* NOTE:  if you turn off the sprite at the wrong time (when it
                     ** is being displayed), the sprite will appear as a vertical bar
                     ** on the screen.  To really get rid of the sprite, you must
                     ** OFF_SPRITE while it is not displayed.  This is hard in a
                     ** multi-tasking system (the solution is not addressed in
                     ** this program).
                     */
                    ON_SPRITE ; /* just to be sure */
                    FreeSprite((WORD) sprite_num);
                }
                CloseScreen(screen);
            }
            CloseLibrary((struct Library *)IntuitionBase);
        }
        CloseLibrary((struct Library *)GfxBase);
    }
    exit(return_code);
}
