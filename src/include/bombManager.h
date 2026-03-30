/**
 * @file bombManager.h
 * @brief Definition of the BombManager class for managing bombs in the game
 */

#ifndef BOMBMANAGER_H
#define BOMBMANAGER_H

#include "bomb.h"
#include "enemy.h"
#include "player.h"
#include <vector>
#include <chrono>

/**
 * @class BombManager
 * @brief Class responsible for managing all bombs in the game
 * 
 * The BombManager class handles the creation, updating, explosion detection,
 * and cleanup of bombs placed by the player.
 */
class BombManager {
private:
    std::vector<Bomb*> bombs; ///< Collection of active bombs in the game

public:
    /**
     * @brief Destructor that cleans up all bombs
     */
    ~BombManager();

    /**
     * @brief Updates the state of all bombs
     * @param map Reference to the game map
     * @param elapsedTime Time elapsed since the last update
     */
    void updateBombs(Map& map, std::chrono::duration<double> elapsedTime);
    
    /**
     * @brief Checks for bomb explosions and applies damage to enemies and player
     * @param enemies Reference to the vector of enemies
     * @param player Reference to the player
     */
    void checkBombExplosions(std::vector<Enemy>& enemies, Player& player);
    
    /**
     * @brief Removes inactive bombs from the manager
     */
    void cleanupBombs();
    
    /**
     * @brief Removes all bombs from the manager
     */
    void clearAllBombs();
    
    /**
     * @brief Adds a new bomb to the manager
     * @param bomb Pointer to the bomb to be added
     */
    void addBomb(Bomb* bomb);
    
    /**
     * @brief Gets the collection of active bombs
     * @return Constant reference to the vector of bomb pointers
     */
    const std::vector<Bomb*>& getBombs() const;
};

#endif // BOMBMANAGER_H