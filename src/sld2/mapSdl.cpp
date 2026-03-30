#include <stdlib.h>
#include <iostream>

#include "mapSdl.h"
#include "Direction.h"

const int SPRITE_SIZE = 32;

SDLGame::SDLGame() : game()
{
    game.initialize();
    swordActive = false;
    gameOver = false;

    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    int dimx = 40, dimy = 20;
    dimx *= SPRITE_SIZE;
    dimy *= SPRITE_SIZE;

    window = SDL_CreateWindow("Zeldo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimx, dimy, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr)
    {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    floor.loadFromFile("data/sprites/Grass_test.png", renderer);
    rock.loadFromFile("data/sprites/Rock.png", renderer);
    water.loadFromFile("data/sprites/Water.png", renderer);
    bush.loadFromFile("data/sprites/Bush.png", renderer);
    heart.loadFromFile("data/sprites/Heart.png", renderer);
    
    charDown.loadFromFile("data/sprites/Char_walk_down.png", renderer);
    charUp.loadFromFile("data/sprites/Char_walk_up.png", renderer);
    charLeft.loadFromFile("data/sprites/Char_walk_left.png", renderer);
    charRight.loadFromFile("data/sprites/Char_walk_right.png", renderer);

    swordDown.loadFromFile("data/sprites/sword_down.png", renderer);
    swordUp.loadFromFile("data/sprites/sword_up.png", renderer);
    swordLeft.loadFromFile("data/sprites/sword_left.png", renderer);
    swordRight.loadFromFile("data/sprites/sword_right.png", renderer);

    skelChillDown.loadFromFile("data/sprites/Skel_chill_down.png", renderer);
    skelChillUp.loadFromFile("data/sprites/Skel_chill_up.png", renderer);
    skelChillLeft.loadFromFile("data/sprites/Skel_chill_left.png", renderer);
    skelChillRight.loadFromFile("data/sprites/Skel_chill_right.png", renderer);

    skelAlertDown.loadFromFile("data/sprites/Skel_alert_down.png", renderer);
    skelAlertUp.loadFromFile("data/sprites/Skel_alert_up.png", renderer);
    skelAlertLeft.loadFromFile("data/sprites/Skel_alert_left.png", renderer);
    skelAlertRight.loadFromFile("data/sprites/Skel_alert_right.png", renderer);

    arrowDown.loadFromFile("data/sprites/arrow_down.png", renderer);
    arrowUp.loadFromFile("data/sprites/arrow_up.png", renderer);
    arrowLeft.loadFromFile("data/sprites/arrow_left.png", renderer);
    arrowRight.loadFromFile("data/sprites/arrow_right.png", renderer);

    bomb.loadFromFile("data/sprites/bomb.png", renderer);
    dust.loadFromFile("data/sprites/Dust.png", renderer);

    pv_10.loadFromFile("data/sprites/10.png", renderer);
    pv_9.loadFromFile("data/sprites/9.png", renderer);
    pv_8.loadFromFile("data/sprites/8.png", renderer);
    pv_7.loadFromFile("data/sprites/7.png", renderer);
    pv_6.loadFromFile("data/sprites/6.png", renderer);
    pv_5.loadFromFile("data/sprites/5.png", renderer);
    pv_4.loadFromFile("data/sprites/4.png", renderer);
    pv_3.loadFromFile("data/sprites/3.png", renderer);
    pv_2.loadFromFile("data/sprites/2.png", renderer);
    pv_1.loadFromFile("data/sprites/1.png", renderer);
    pv_0.loadFromFile("data/sprites/0.png", renderer);
    pv_heart.loadFromFile("data/sprites/pv_heart.png", renderer);
    pv_death.loadFromFile("data/sprites/pv_death.png", renderer);

    item_bomb.loadFromFile("data/sprites/bomb_item.png", renderer);
    item_arrow.loadFromFile("data/sprites/arrow_item.png", renderer);
    item_sword.loadFromFile("data/sprites/sword_item.png", renderer);
    item_o.loadFromFile("data/sprites/o_item.png", renderer);
    item_p.loadFromFile("data/sprites/p_item.png", renderer);
    item_b.loadFromFile("data/sprites/b_item.png", renderer);

    end_lose.loadFromFile("data/sprites/lose.png", renderer);
    end_win.loadFromFile("data/sprites/win.png", renderer);

}

SDLGame::~SDLGame()
{
    game.cleanup();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDLGame::displayPlayer(const Player &player){
    if(!gameOver){
        switch (player.getDir())
        {
        case UP:
            charUp.draw(renderer, player.getX()*SPRITE_SIZE, player.getY()*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
            break;
        case DOWN:
            charDown.draw(renderer, player.getX()*SPRITE_SIZE, player.getY()*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
            break;
        case LEFT:
            charLeft.draw(renderer, player.getX()*SPRITE_SIZE, player.getY()*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
            break;
        case RIGHT:
            charRight.draw(renderer, player.getX()*SPRITE_SIZE, player.getY()*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
            break;
        
        default:
            break;
        }
    }
}

void SDLGame::displaySword(const Player &player){
    if(swordActive){
    switch (player.getDir())
        {
        case UP:
            swordUp.draw(renderer, player.getX()*SPRITE_SIZE, (player.getY()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
            break;
        case DOWN:
            swordDown.draw(renderer, player.getX()*SPRITE_SIZE, (player.getY()+1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
            break;
        case LEFT:
            swordLeft.draw(renderer, (player.getX()-1)*SPRITE_SIZE, player.getY()*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
            break;
        case RIGHT:
            swordRight.draw(renderer, (player.getX()+1)*SPRITE_SIZE, player.getY()*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
            break;
        
        default:
            break;
        }
    }
}

void SDLGame::displayEnemies(const std::vector<Enemy> enemies){
    for(int i = 0; i < enemies.size(); ++i){
        if(enemies[i].getSymbol() == 'E'){
            switch (enemies[i].getDir()){
            case UP:
                skelChillUp.draw(renderer, enemies[i].getX()*SPRITE_SIZE, enemies[i].getY()*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
                break;
            case DOWN:
                skelChillDown.draw(renderer, enemies[i].getX()*SPRITE_SIZE, enemies[i].getY()*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
                break;
            case LEFT:
                skelChillLeft.draw(renderer, enemies[i].getX()*SPRITE_SIZE, enemies[i].getY()*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
                break;
            case RIGHT:
                skelChillRight.draw(renderer, enemies[i].getX()*SPRITE_SIZE, enemies[i].getY()*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
                break;
        
            default:
                break;
            }
        }
    else{
        switch (enemies[i].getDir()){
            case UP:
                skelAlertUp.draw(renderer, enemies[i].getX()*SPRITE_SIZE, enemies[i].getY()*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
                break;
            case DOWN:
                skelAlertDown.draw(renderer, enemies[i].getX()*SPRITE_SIZE, enemies[i].getY()*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
                break;
            case LEFT:
                skelAlertLeft.draw(renderer, enemies[i].getX()*SPRITE_SIZE, enemies[i].getY()*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
                break;
            case RIGHT:
                skelAlertRight.draw(renderer, enemies[i].getX()*SPRITE_SIZE, enemies[i].getY()*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
                break;
        
            default:
                break;
            }
        }
    }
}

void SDLGame::displayArrows(const std::vector<Arrow*> &arrows) {
    for (const auto& arrow : arrows) {
        if (arrow->isActive()) {
            switch (arrow->getDirection())
            {
            case UP:
                arrowUp.draw(renderer, arrow->getX()*SPRITE_SIZE, arrow->getY()*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
                break;
            case DOWN:
                arrowDown.draw(renderer, arrow->getX()*SPRITE_SIZE, arrow->getY()*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
                break;
            case LEFT:
                arrowLeft.draw(renderer, arrow->getX()*SPRITE_SIZE, arrow->getY()*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
                break;
            case RIGHT:
                arrowRight.draw(renderer, arrow->getX()*SPRITE_SIZE, arrow->getY()*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
                break;
            
            default:
                break;
            }
        }
    }
}

void SDLGame::displayBombs(const std::vector<Bomb*> &bombs, const Map &map) {
    for (const auto& bomb_ : bombs) {
        if (bomb_->isExploding()) {
            int centerX = bomb_->getX();
            int centerY = bomb_->getY();
            int radius = bomb_->getExplosionRadius();

            for (int dy = -radius; dy <= radius; dy++) {
                for (int dx = -radius; dx <= radius; dx++) {
                    int x = centerX + dx;
                    int y = centerY + dy;
                    if (map.isWalkable(x, y) && map.getTile(x, y) != TILE_WALL && map.getTile(x, y) != TILE_PORTAL) {
                        dust.draw(renderer, x*SPRITE_SIZE, y*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
                    }
                }
            }
        } else if (bomb_->isActive()) {
            bomb.draw(renderer, bomb_->getX()*SPRITE_SIZE, bomb_->getY()*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        }
    }
}

void SDLGame::displayItems(const std::vector<Item*> &items) {
    for (const auto& item : items) {
        switch (item->getType()) {
            case ItemType::HEART:
                heart.draw(renderer, item->getX()*SPRITE_SIZE, item->getY()*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
                break;
            // Ajoutez d'autres cas ici si vous avez d'autres types d'items
            default:
                break;
        }
    }
}


void SDLGame::displayPV(const Player &player, const Map &map){
    pv_heart.draw(renderer, 0*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
    switch (player.gethealth())
    {
    case 10:
        pv_10.draw(renderer, 1*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 9:
        pv_9.draw(renderer, 1*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 8:
        pv_8.draw(renderer, 1*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 7:
        pv_7.draw(renderer, 1*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 6:
        pv_6.draw(renderer, 1*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 5:
        pv_5.draw(renderer, 1*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 4:
        pv_4.draw(renderer, 1*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 3:
        pv_3.draw(renderer, 1*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 2:
        pv_2.draw(renderer, 1*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 1:
        pv_1.draw(renderer, 1*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 0:
        pv_0.draw(renderer, 1*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    
    default:
        pv_0.draw(renderer, 1*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    }
}

void SDLGame::displayNbEnemies(const Map &map){
    pv_death.draw(renderer, (map.getWidth()-3)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
    switch (game.getEnemyManager().getNbEnemies())
    {
    case 28:
        pv_2.draw(renderer, (map.getWidth()-2)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        pv_8.draw(renderer, (map.getWidth()-1)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 27:
        pv_2.draw(renderer, (map.getWidth()-2)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        pv_7.draw(renderer, (map.getWidth()-1)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 26:
        pv_2.draw(renderer, (map.getWidth()-2)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        pv_6.draw(renderer, (map.getWidth()-1)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 25:
        pv_2.draw(renderer, (map.getWidth()-2)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        pv_5.draw(renderer, (map.getWidth()-1)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 24:
        pv_2.draw(renderer, (map.getWidth()-2)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        pv_4.draw(renderer, (map.getWidth()-1)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 23:
        pv_2.draw(renderer, (map.getWidth()-2)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        pv_3.draw(renderer, (map.getWidth()-1)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 22:
        pv_2.draw(renderer, (map.getWidth()-2)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        pv_2.draw(renderer, (map.getWidth()-1)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 21:
        pv_2.draw(renderer, (map.getWidth()-2)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        pv_1.draw(renderer, (map.getWidth()-1)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 20:
        pv_2.draw(renderer, (map.getWidth()-2)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        pv_0.draw(renderer, (map.getWidth()-1)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 19:
        pv_1.draw(renderer, (map.getWidth()-2)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        pv_9.draw(renderer, (map.getWidth()-1)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 18:
        pv_1.draw(renderer, (map.getWidth()-2)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        pv_8.draw(renderer, (map.getWidth()-1)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 17:
        pv_1.draw(renderer, (map.getWidth()-2)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        pv_7.draw(renderer, (map.getWidth()-1)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 16:
        pv_1.draw(renderer, (map.getWidth()-2)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        pv_6.draw(renderer, (map.getWidth()-1)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 15:
        pv_1.draw(renderer, (map.getWidth()-2)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        pv_5.draw(renderer, (map.getWidth()-1)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 14:
        pv_1.draw(renderer, (map.getWidth()-2)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        pv_4.draw(renderer, (map.getWidth()-1)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 13:
        pv_1.draw(renderer, (map.getWidth()-2)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        pv_3.draw(renderer, (map.getWidth()-1)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 12:
        pv_1.draw(renderer, (map.getWidth()-2)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        pv_2.draw(renderer, (map.getWidth()-1)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 11:
        pv_1.draw(renderer, (map.getWidth()-2)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        pv_1.draw(renderer, (map.getWidth()-1)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 10:
        pv_1.draw(renderer, (map.getWidth()-2)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        pv_0.draw(renderer, (map.getWidth()-1)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 9:
        pv_0.draw(renderer, (map.getWidth()-2)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        pv_9.draw(renderer, (map.getWidth()-1)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 8:
        pv_0.draw(renderer, (map.getWidth()-2)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        pv_8.draw(renderer, (map.getWidth()-1)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 7:
        pv_0.draw(renderer, (map.getWidth()-2)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        pv_7.draw(renderer, (map.getWidth()-1)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 6:
        pv_0.draw(renderer, (map.getWidth()-2)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        pv_6.draw(renderer, (map.getWidth()-1)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 5:
        pv_0.draw(renderer, (map.getWidth()-2)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        pv_5.draw(renderer, (map.getWidth()-1)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 4:
        pv_0.draw(renderer, (map.getWidth()-2)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        pv_4.draw(renderer, (map.getWidth()-1)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 3:
        pv_0.draw(renderer, (map.getWidth()-2)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        pv_3.draw(renderer, (map.getWidth()-1)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 2:
        pv_0.draw(renderer, (map.getWidth()-2)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        pv_2.draw(renderer, (map.getWidth()-1)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 1:
        pv_0.draw(renderer, (map.getWidth()-2)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        pv_1.draw(renderer, (map.getWidth()-1)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    case 0:
        pv_0.draw(renderer, (map.getWidth()-2)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        pv_0.draw(renderer, (map.getWidth()-1)*SPRITE_SIZE, (map.getHeight()-1)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        break;
    default:
        break;
    }

}

void SDLGame::displayCommands(){
    item_bomb.draw(renderer, 33*SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE);
    item_p.draw(renderer, 34*SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE);
    item_arrow.draw(renderer, 35*SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE);
    item_b.draw(renderer, 36*SPRITE_SIZE, 0, SPRITE_SIZE);
    item_sword.draw(renderer, 37*SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE);
    item_o.draw(renderer, 38*SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE);
}

void SDLGame::displayEnd(){
    const EnemyManager &enemyManager = game.getEnemyManager();
    if(gameOver){
        if(enemyManager.getNbEnemies() <= 0){
            end_win.draw(renderer, 480, 160, 320, 320);
        }
        else{
            end_lose.draw(renderer, 480, 160, 320, 320);
        }
    }
}

void SDLGame::affiche(){
    int x,y;
    const Map &map = game.getCurrentMap();
    const Player &player = game.getPlayer();
    const std::vector<Enemy> &enemies = game.getEnemies();
    const std::vector<Arrow*> &arrows = game.getArrows();
    const std::vector<Bomb*> &bombs = game.getBombs();
    const std::vector<Item*> &items = game.getItems();

    floor.draw(renderer,0,0,1280,640);
    for(x = 0; x < map.getWidth(); ++x){
        for(y = 0; y < map.getHeight(); ++y){
            if(map.getTile(x,y) == TILE_WALL){
                rock.draw(renderer, x*SPRITE_SIZE,y*SPRITE_SIZE,SPRITE_SIZE,SPRITE_SIZE);
            }
            if(map.getTile(x,y) == TILE_TREE){
                bush.draw(renderer, x*SPRITE_SIZE,y*SPRITE_SIZE,SPRITE_SIZE,SPRITE_SIZE);
            }
            if(map.getTile(x,y) == TILE_WATER){
                water.draw(renderer, x*SPRITE_SIZE,y*SPRITE_SIZE,SPRITE_SIZE,SPRITE_SIZE);
            }
        }
    }

    displayPlayer(player);
    displayEnemies(enemies);
    displayArrows(arrows);
    displayBombs(bombs, map);
    displayItems(items);
    if(swordActive){
        displaySword(player);
    }
    displayPV(player, map);
    displayNbEnemies(map);
    displayCommands();

    if(gameOver){
        displayEnd();
    }
}

bool SDLGame::isGameOver(){
    const Player &player = game.getPlayer();
    const EnemyManager &enemyManager = game.getEnemyManager();
    return ((player.gethealth() == 0) || (enemyManager.getNbEnemies() <= 0));
}


void SDLGame::boucle(){
    SDL_Event events;
    bool quit = false;

    Uint32 t = SDL_GetTicks(), nt;
    Uint32 cooldown_display_sword_start, cooldown_display_sword_end;

    // tant que ce n'est pas la fin ...
    while (!quit)
    {
        gameOver = isGameOver();

        if(!gameOver){
            nt = SDL_GetTicks();
            if (nt - t > 200)
            {
                game.update();
                t = nt;
            }
        }

        // tant qu'il y a des évenements à traiter (cette boucle n'est pas bloquante)
        while (SDL_PollEvent(&events))
        {
            if (events.type == SDL_QUIT)
                quit = true; // Si l'utilisateur a clique sur la croix de fermeture
            else if (events.type == SDL_KEYDOWN)
            { // Si une touche est enfoncee
                switch (events.key.keysym.scancode)
                {
                case SDL_SCANCODE_A:
                    game.handleInput('q');
                    break;
                case SDL_SCANCODE_D:
                    game.handleInput('d');
                    break;
                case SDL_SCANCODE_W:
                    game.handleInput('z');
                    break;
                case SDL_SCANCODE_S:
                    game.handleInput('s');
                    break;
                case SDL_SCANCODE_O:
                    if(game.getPlayer().canAttack()) {
                        game.handleInput('o');
                        cooldown_display_sword_start = SDL_GetTicks();
                        swordActive = true;
                    }
                    break;
                case SDL_SCANCODE_B:
                    game.handleInput('b');
                    break;
                case SDL_SCANCODE_P:
                    game.handleInput('p');
                    break;
                case SDL_SCANCODE_Q:
                    quit = true;
                    break;
                default:
                    break;
                }
            }
        }
        affiche();

        SDL_RenderPresent(renderer);

        if(swordActive){
            cooldown_display_sword_end = SDL_GetTicks();
            if(cooldown_display_sword_end - cooldown_display_sword_start > 150){
                swordActive = false;
            }
        }
    }
}