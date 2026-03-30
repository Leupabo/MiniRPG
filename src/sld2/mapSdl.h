/**
 * @file mapSdl.h
 * @brief Definition of the SDLGame class for the SDL2-based game renderer
 */

#ifndef _MAPSDL_H
#define _MAPSDL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "game.h"
#include "sprite.h"

/**
 * @class SDLGame
 * @brief Class responsible for rendering the game using SDL2
 * 
 * The SDLGame class handles the graphical representation of the game,
 * including loading sprites, rendering game elements, and managing the game window.
 */
class SDLGame{
    private:
    Game game;                 ///< Game logic instance
    bool swordActive;          ///< Flag indicating if the sword attack is active
    bool gameOver;             ///< Flag indicating if the game is over

    SDL_Window *window;        ///< SDL window
    SDL_Renderer *renderer;    ///< SDL renderer
    SDLSprite font_im;         ///< Font sprite

    SDLSprite floor;           ///< Floor tile sprite
    SDLSprite rock;            ///< Rock/wall tile sprite
    SDLSprite water;           ///< Water tile sprite
    SDLSprite bush;            ///< Bush/tree tile sprite
    SDLSprite heart;           ///< Heart item sprite

    SDLSprite charDown;        ///< Player facing down sprite
    SDLSprite charUp;          ///< Player facing up sprite
    SDLSprite charLeft;        ///< Player facing left sprite
    SDLSprite charRight;       ///< Player facing right sprite

    SDLSprite swordDown;       ///< Sword attack down sprite
    SDLSprite swordUp;         ///< Sword attack up sprite
    SDLSprite swordLeft;       ///< Sword attack left sprite
    SDLSprite swordRight;      ///< Sword attack right sprite

    SDLSprite skelChillDown;   ///< Skeleton enemy idle facing down sprite
    SDLSprite skelChillUp;     ///< Skeleton enemy idle facing up sprite
    SDLSprite skelChillLeft;   ///< Skeleton enemy idle facing left sprite
    SDLSprite skelChillRight;  ///< Skeleton enemy idle facing right sprite

    SDLSprite skelAlertDown;   ///< Skeleton enemy alert facing down sprite
    SDLSprite skelAlertUp;     ///< Skeleton enemy alert facing up sprite
    SDLSprite skelAlertLeft;   ///< Skeleton enemy alert facing left sprite
    SDLSprite skelAlertRight;  ///< Skeleton enemy alert facing right sprite

    SDLSprite arrowDown;       ///< Arrow facing down sprite
    SDLSprite arrowUp;         ///< Arrow facing up sprite
    SDLSprite arrowLeft;       ///< Arrow facing left sprite
    SDLSprite arrowRight;      ///< Arrow facing right sprite

    SDLSprite bomb;            ///< Bomb sprite
    SDLSprite dust;            ///< Explosion dust sprite

    SDLSprite pv_10;           ///< Health bar at 10 HP sprite
    SDLSprite pv_9;            ///< Health bar at 9 HP sprite
    SDLSprite pv_8;            ///< Health bar at 8 HP sprite
    SDLSprite pv_7;            ///< Health bar at 7 HP sprite
    SDLSprite pv_6;            ///< Health bar at 6 HP sprite
    SDLSprite pv_5;            ///< Health bar at 5 HP sprite
    SDLSprite pv_4;            ///< Health bar at 4 HP sprite
    SDLSprite pv_3;            ///< Health bar at 3 HP sprite
    SDLSprite pv_2;            ///< Health bar at 2 HP sprite
    SDLSprite pv_1;            ///< Health bar at 1 HP sprite
    SDLSprite pv_0;            ///< Health bar at 0 HP sprite
    SDLSprite pv_heart;        ///< Health heart icon sprite
    SDLSprite pv_death;        ///< Death icon sprite

    SDLSprite item_bomb;       ///< Bomb item UI sprite
    SDLSprite item_arrow;      ///< Arrow item UI sprite
    SDLSprite item_sword;      ///< Sword item UI sprite
    SDLSprite item_o;          ///< 'O' key UI sprite
    SDLSprite item_p;          ///< 'P' key UI sprite
    SDLSprite item_b;          ///< 'B' key UI sprite

    SDLSprite end_win;         ///< Win screen sprite
    SDLSprite end_lose;        ///< Lose screen sprite

    public:
    /**
     * @brief Default constructor
     */
    SDLGame();
    
    /**
     * @brief Destructor
     */
    ~SDLGame();
    
    /**
     * @brief Displays the player character
     * @param player Reference to the player
     */
    void displayPlayer(const Player &player);
    
    /**
     * @brief Displays the player's sword attack
     * @param player Reference to the player
     */
    void displaySword(const Player &player);
    
    /**
     * @brief Displays all enemies
     * @param enemies Vector of enemy objects
     */
    void displayEnemies(const std::vector<Enemy> enemies);
    
    /**
     * @brief Displays all arrows
     * @param arrows Reference to the vector of arrow pointers
     */
    void displayArrows(const std::vector<Arrow*> &arrows);
    
    /**
     * @brief Displays all bombs
     * @param bombs Reference to the vector of bomb pointers
     * @param map Reference to the game map
     */
    void displayBombs(const std::vector<Bomb*> &bombs, const Map &map);
    
    /**
     * @brief Displays all items
     * @param items Reference to the vector of item pointers
     */
    void displayItems(const std::vector<Item*> &items);
    
    /**
     * @brief Displays the player's health bar
     * @param player Reference to the player
     * @param map Reference to the game map
     */
    void displayPV(const Player &player, const Map &map);
    
    /**
     * @brief Displays the number of remaining enemies
     * @param map Reference to the game map
     */
    void displayNbEnemies(const Map &map);
    
    /**
     * @brief Displays the game controls
     */
    void displayCommands();
    
    /**
     * @brief Displays the end game screen
     */
    void displayEnd();
    
    /**
     * @brief Checks if the game is over
     * @return true if the game is over, false otherwise
     */
    bool isGameOver();
    
    /**
     * @brief Renders the current game state
     */
    void affiche();
    
    /**
     * @brief Main game loop
     */
    void boucle();
};

#endif