#include "winTxt.h"
#include "mapTxt.h"
#include <iostream>

int main(int argc, char **argv)
{
    termClear();
    Game game;
    game.initialize();
    txtBoucle(game);
    game.cleanup(); // Supprimer le dossier enemies à la fin du programme
    termClear();
    return 0;
}