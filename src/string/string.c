#include <exec/types.h>
#include <stdio.h>
#include <proto/dos.h>

int main()
{
    CONST_STRPTR str = "Hello!\n";
    printf(str);
    printf("Test\n");
}
