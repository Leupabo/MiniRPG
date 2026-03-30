#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32
#include "winTxt.h"

#include "game.h"

void displayItems(WinTXT &win, const std::vector<Item*> &items) {
    for (const auto& item : items) {
        char symbol;
        switch (item->getType()) {
            case ItemType::HEART:
                symbol = '+';  // Symbole pour représenter un cœur
                break;
            // Ajoutez d'autres cas ici si vous avez d'autres types d'items
            default:
                symbol = '?';  // Symbole par défaut pour les items inconnus
        }
        win.print(item->getX(), item->getY(), symbol);
    }
}

void displayBombs(WinTXT &win, const std::vector<Bomb*> &bombs, const Map &map) {
    for (const auto& bomb : bombs) {
        if (bomb->isExploding()) {
            int centerX = bomb->getX();
            int centerY = bomb->getY();
            int radius = bomb->getExplosionRadius();

            for (int dy = -radius; dy <= radius; dy++) {
                for (int dx = -radius; dx <= radius; dx++) {
                    int x = centerX + dx;
                    int y = centerY + dy;
                    if (map.isWalkable(x, y) && map.getTile(x, y) != TILE_WALL && map.getTile(x, y) != TILE_PORTAL) {
                        win.print(x, y, '*');
                    }
                }
            }
        } else if (bomb->isActive()) {
            win.print(bomb->getX(), bomb->getY(), 'O');
        }
    }
}

void displayMap(WinTXT &win, const Map &map) {
    for (int x = 0; x < map.getWidth(); ++x)
        for (int y = 0; y < map.getHeight(); ++y)
            win.print(x, y, map.getTileChar(x, y));
}

void displayPlayer(WinTXT &win, const Player &player) {
    win.print(player.getX(), player.getY(), player.getSymbol());
}

void displayEnemies(WinTXT &win, const std::vector<Enemy> enemies, const Player &player) {
    for(int i = 0; i < enemies.size(); ++i) win.print(enemies[i].getX(), enemies[i].getY(), enemies[i].getSymbol());
}

void displayArrows(WinTXT &win, const std::vector<Arrow*> &arrows) {
    for (const auto& arrow : arrows) {
        if (arrow->isActive()) {
            win.print(arrow->getX(), arrow->getY(), arrow->getSymbol());
        }
    }
}

void txtAff(WinTXT &win, const Game &game)
{
    const Map &map = game.getCurrentMap();
    const Player &player = game.getPlayer();
    const std::vector<Enemy> &enemies = game.getEnemies();
    const std::vector<Arrow*> &arrows = game.getArrows();
    const std::vector<Bomb*> &bombs = game.getBombs();
    const std::vector<Item*> &items = game.getItems();
    win.clear();
    // Affichage des murs et des pastilles
    displayMap(win, map);
    // Affichage du joueur
    displayPlayer(win, player);
    // Affichage des ennemis
    displayEnemies(win, enemies, player);
    // Affichage des flèches
    displayArrows(win, arrows);
    // Affichage des bombes
    displayBombs(win, bombs, map);
    // Afficher les items
    displayItems(win, items);
    win.draw();
}

void txtBoucle(Game &game)
{
    // Initialiser la fenêtre avec les dimensions de la carte actuelle
    int currentMapId = game.getCurrentMap().getId();
    WinTXT win(game.getCurrentMap().getWidth(), game.getCurrentMap().getHeight());

    bool ok = true;
    int c;

    do
    {
#ifdef _WIN32
        Sleep(100);
#else
        usleep(100000); // 100 ms
#endif // WIN32
        
        // Vérifier si la carte a changé
        if (currentMapId != game.getCurrentMap().getId()) {
            // La carte a changé, on doit recréer la fenêtre avec les nouvelles dimensions
            currentMapId = game.getCurrentMap().getId();
            
            // Sortir de la boucle actuelle pour recréer une nouvelle fenêtre
            ok = false;
            break;
        }
        
        txtAff(win, game);
        game.displayGameInfo();
        game.update();
        
        c = win.getCh();
        switch (c)
        {
        case 'z':
            game.handleInput('z');
            break;
        case 'q':
            game.handleInput('q');
            break;
        case 's':
            game.handleInput('s');
            break;
        case 'd':
            game.handleInput('d');
            break;
        case 'o':
            game.handleInput('o');
            break;
        case 'b':
            game.handleInput('b');
            break;
        case 'p':
            game.handleInput('p');
            break;
        case 'a':
            ok = false;
            break;
        }

    } while (ok);
    
    // Si on a quitté la boucle à cause d'un changement de carte, relancer une nouvelle boucle
    if (!ok && game.isRunning() && c != 'a') {
		termClear();
        txtBoucle(game);
    }
}