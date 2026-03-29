#include "sprite.h"
#include "mapSdl.h"
#include <iostream>
#include <SDL.h>

#ifdef _WIN32
#undef main
#endif

int main(int argc, char* argv[])
{
    SDLGame sg;
    sg.boucle();
    return 0;
}