/**
 * @file game.h
 * @brief Definition of the Game class that manages the main game logic
 */

#ifndef GAME_H
#define GAME_H

#include "map.h"
#include "player.h"
#include "enemyManager.h"
#include "arrowManager.h"
#include "bombManager.h"
#include "itemManager.h"
#include <vector>
#include <chrono>

/**
 * @class Game
 * @brief Main class that manages the game state and logic
 * 
 * The Game class coordinates all game components including the map, player,
 * enemies, arrows, bombs, and items. It handles game initialization, updates,
 * input processing, and cleanup.
 */
class Game {
private:
    Map currentMap;                                  ///< Current game map
    Player player;                                   ///< Player character
    EnemyManager enemyManager;                       ///< Manager for all enemies
    bool gameRunning;                                ///< Flag indicating if the game is running
    ArrowManager arrowManager;                       ///< Manager for all arrows
    BombManager bombManager;                         ///< Manager for all bombs
    ItemManager itemManager;                         ///< Manager for all items

    std::chrono::steady_clock::time_point lastUpdateTime; ///< Time of the last update
    std::chrono::duration<double> deltaTime;              ///< Time elapsed since the last update

    /**
     * @brief Handles player transition through a portal
     * @param portal Pointer to the portal being used
     */
    void handlePortalTransition(const Portal* portal);

    const int INITIAL_MAP_ID = 1;        ///< ID of the initial map
    const int INITIAL_PLAYER_X = 1;      ///< Initial X position of the player
    const int INITIAL_PLAYER_Y = 1;      ///< Initial Y position of the player
    const int DEFAULT_ENEMY_COUNT = 7;   ///< Default number of enemies per map
    const int PLAYER_DAMAGE = 1;         ///< Default damage dealt by the player
    const int ENEMY_DAMAGE = 1;          ///< Default damage dealt by enemies
public:
    /**
     * @brief Default constructor
     */
    Game();
    
    /**
     * @brief Destructor
     */
    ~Game();

    /**
     * @brief Initializes the game
     * @return true if initialization was successful, false otherwise
     */
    bool initialize();
    
    /**
     * @brief Cleans up game resources
     */
    void cleanup();

    /**
     * @brief Updates the game state
     */
    void update();
    
    /**
     * @brief Handles player input
     * @param input Character representing the player's input
     * @return true if the input was handled, false otherwise
     */
    bool handleInput(char input);
    
    /**
     * @brief Handles player attack actions
     */
    void handlePlayerAttack();

    /**
     * @brief Loads a map by its ID
     * @param mapId ID of the map to load
     * @return true if the map was loaded successfully, false otherwise
     */
    bool loadMap(int mapId);

    /**
     * @brief Updates all arrows
     */
    void updateArrows();
    
    /**
     * @brief Checks for collisions between arrows and other entities
     */
    void checkArrowCollisions();
    
    /**
     * @brief Cleans up inactive arrows
     */
    void cleanupArrows();

    /**
     * @brief Updates all bombs
     */
    void updateBombs();
    
    /**
     * @brief Checks for collisions between bomb explosions and entities
     */
    void checkBombCollisions();
    
    /**
     * @brief Cleans up inactive bombs
     */
    void cleanupBombs();

    /**
     * @brief Updates all items
     */
    void updateItems();
    
    /**
     * @brief Checks for collisions between the player and items
     */
    void checkItemCollisions();
    
    /**
     * @brief Cleans up collected items
     */
    void cleanupItems();
    
    /**
     * @brief Gets the current map
     * @return Constant reference to the current map
     */
    const Map& getCurrentMap() const { return currentMap; }
    
    /**
     * @brief Gets the player
     * @return Constant reference to the player
     */
    const Player& getPlayer() const { return player; }
    
    /**
     * @brief Gets all enemies
     * @return Constant reference to the vector of enemies
     */
    const std::vector<Enemy>& getEnemies() const { return enemyManager.getEnemies(); }
    
    /**
     * @brief Gets all arrows
     * @return Constant reference to the vector of arrow pointers
     */
    const std::vector<Arrow*>& getArrows() const { return arrowManager.getArrows(); }
    
    /**
     * @brief Gets all bombs
     * @return Constant reference to the vector of bomb pointers
     */
    const std::vector<Bomb*>& getBombs() const { return bombManager.getBombs(); }
    
    /**
     * @brief Gets all items
     * @return Constant reference to the vector of item pointers
     */
    const std::vector<Item*>& getItems() const { return itemManager.getItems(); }
    
    /**
     * @brief Gets the enemy manager
     * @return Constant reference to the enemy manager
     */
    const EnemyManager& getEnemyManager() const { return enemyManager;}
    
    /**
     * @brief Checks if the game is running
     * @return true if the game is running, false otherwise
     */
    bool isRunning() const { return gameRunning; }
    
    /**
     * @brief Gets the time elapsed since the last update
     * @return Time duration since the last update
     */
    std::chrono::duration<double> getDeltaTime() const { return deltaTime; }

    /**
     * @brief Sets the game running state
     * @param running New running state
     */
    void setRunning(bool running);
    
    /**
     * @brief Displays game information
     */
    void displayGameInfo() const;

    /**
     * @brief Calculates the time elapsed since the last update
     */
    void calculateDeltaTime();
};

#endif // GAME_H

