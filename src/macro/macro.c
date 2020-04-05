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
 */
int main()
{
    int x, y;
    x = 1;
    y = 2;
    TEST(x, y);
    return 0;
}
