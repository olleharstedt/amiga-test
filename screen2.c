#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/intuition.h>

struct IntuitionBase *IntuitionBase;

struct Screen *my_screen;

struct NewScreen my_new_screen=
{
	0, 0, 320, 200, 5,
    DETAILPEN,
    BLOCKPEN,
	NULL,
	CUSTOMSCREEN,
	NULL,
	"MY SCREEN",
	NULL,
	NULL
};

/**
 * Source: http://forum.amiga.org/index.php?topic=66703.0
 *
 * Compile with:
 *   $ vc +aos68k -o screen -lauto -lamiga screen.c
 */
int main(void)
{
	IntuitionBase = (struct IntuitionBase *) OpenLibrary( "intuition.library", 0 );

	if( IntuitionBase == NULL )
		return (RETURN_FAIL);

	my_screen = (struct Screen *) OpenScreen( &my_new_screen );

	if(my_screen == NULL)
	{
		CloseLibrary( (struct Library *) IntuitionBase );
		return (RETURN_FAIL);
	}

	Delay( TICKS_PER_SECOND * 5);	/* changed from 30 seconds to 5 seconds because I am impatient */

	CloseScreen( my_screen );

	CloseLibrary( (struct Library *) IntuitionBase );

	return (RETURN_OK);
}
