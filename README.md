The following guide worked without any problems on my Ubuntu (RockPro64) system:

https://blitterstudio.com/setting-up-an-amiga-cross-compiler/

Must also download NDK and copy includes and libs to relevant folder.

Set path in bash:

    $ export VBCC=~/kod/vbcc

Simple hello world without depencies:

    $ vc +aos68k -o hello helloworld.c

To link with Amiga libs:

    $ vc +aos68k -o screen -lauto -lamiga screen.c
