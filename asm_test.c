/**
 * Test calling ASM from C.
 *
 * Code taken from EAB forum: http://eab.abime.net/showthread.php?t=80274
 *
 * Compile with:
 * vasmm68k_mot -noesc -Fhunk add.s -o add.o
 * vc +aos68k -g -O1 -c99 add.o asm_test.c -o asm_test
 *
 * TODO: Breaks when linking with -lamiga
 */

#include <stdio.h>

#define REG(x,y) __reg(#x) y
#define ASM
#define SAVEDS __saveds

ASM long add( REG(d0, long a), REG(d1, long b) );

int main()
{
    long a, b, s;
    a = 10;
    b = 20;

    s = add(a, b);
    printf("%ld + %ld = %ld\n", a, b, s);
}
