/**
 * @file enemyManager.h
 * @brief Definition of the EnemyManager class for managing enemies in the game
 */

#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "enemy.h"
#include "map.h"
#include "player.h"
#include <vector>
#include "itemManager.h"
#include <string>
#include <chrono>

/**
 * @class EnemyManager
 * @brief Class responsible for managing all enemies in the game
 * 
 * The EnemyManager class handles the creation, updating, saving, loading,
 * and cleanup of enemies in the game.
 */
class EnemyManager {
private:
    std::vector<Enemy> enemies;  ///< Collection of active enemies in the game
    int nbEnemies = 28;          ///< Default number of enemies
    
    /**
     * @brief Gets the file path for saving/loading enemies for a specific map
     * @param mapId ID of the map
     * @return String containing the file path
     */
    std::string getEnemiesFilePath(int mapId) const;

    const int MAX_PLACEMENT_ATTEMPTS = 100;    ///< Maximum attempts to place an enemy
    const int DEFAULT_ENEMY_COUNT = 5;         ///< Default number of enemies to create
    const double ENEMY_MOVE_SPEED = 1.0;       ///< Default movement speed for enemies
    const int ENEMY_DETECTION_RANGE = 10;      ///< Range at which enemies can detect the player
    
public:
    /**
     * @brief Default constructor
     */
    EnemyManager();
    
    /**
     * @brief Destructor
     */
    ~EnemyManager();
    
    /**
     * @brief Creates a specified number of enemies on the map
     * @param numberOfEnemies Number of enemies to create
     * @param map Reference to the game map
     * @param player Reference to the player
     */
    void createEnemies(int numberOfEnemies, const Map& map, const Player& player);
    
    /**
     * @brief Saves the current enemies to a file
     * @param mapId ID of the map
     */
    void saveEnemies(int mapId) const;
    
    /**
     * @brief Loads enemies from a file
     * @param mapId ID of the map
     * @param map Reference to the game map
     * @param player Reference to the player
     */
    void loadEnemies(int mapId, const Map& map, const Player& player);
    
    /**
     * @brief Checks if an enemies file exists for a specific map
     * @param mapId ID of the map
     * @return true if the file exists, false otherwise
     */
    bool enemiesFileExists(int mapId) const;
    
    /**
     * @brief Updates all enemies
     * @param map Reference to the game map
     * @param player Reference to the player
     * @param itemManager Reference to the item manager
     * @param elapsedTime Time elapsed since the last update
     */
    void updateEnemies(Map& map, const Player& player, ItemManager& itemManager, std::chrono::duration<double> elapsedTime);
    
    /**
     * @brief Gets the collection of enemies
     * @return Constant reference to the vector of enemies
     */
    const std::vector<Enemy>& getEnemies() const {return enemies;}
    
    /**
     * @brief Gets the number of enemies
     * @return Number of enemies
     */
    const int getNbEnemies() const {return nbEnemies;}
    
    /**
     * @brief Gets a modifiable reference to the enemies vector
     * @return Reference to the vector of enemies
     */
    std::vector<Enemy>& getEnemiesModif() {return enemies;}
    
    /**
     * @brief Cleans up all enemies
     */
    void cleanup();
};

#endif // ENEMY_MANAGER_H