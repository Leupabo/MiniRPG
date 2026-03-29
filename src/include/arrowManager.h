/**
 * @file arrowManager.h
 * @brief Definition of the ArrowManager class for managing arrows in the game
 */

#ifndef ARROW_MANAGER_H
#define ARROW_MANAGER_H

#include "map.h"
#include "enemy.h"
#include <vector>
#include "arrow.h"
#include <chrono>

/**
 * @class ArrowManager
 * @brief Class responsible for managing all arrows in the game
 * 
 * The ArrowManager class handles the creation, updating, collision detection,
 * and cleanup of arrows shot by the player.
 */
class ArrowManager {
private:
    std::vector<Arrow*> arrows; ///< Collection of active arrows in the game

public:
    /**
     * @brief Default constructor
     */
    ArrowManager() = default;
    
    /**
     * @brief Destructor that cleans up all arrows
     */
    ~ArrowManager();

    /**
     * @brief Updates the position of all arrows
     * @param map Reference to the game map
     * @param elapsedTime Time elapsed since the last update
     */
    void updateArrows(const Map& map, std::chrono::duration<double> elapsedTime);
    
    /**
     * @brief Checks for collisions between arrows and enemies
     * @param enemies Reference to the vector of enemies
     */
    void checkArrowCollisions(std::vector<Enemy>& enemies);
    
    /**
     * @brief Removes inactive arrows from the manager
     */
    void cleanupArrows();
    
    /**
     * @brief Removes all arrows from the manager
     */
    void clearAllArrows();
    
    /**
     * @brief Adds a new arrow to the manager
     * @param arrow Pointer to the arrow to be added
     */
    void addArrow(Arrow* arrow);
    
    /**
     * @brief Gets the collection of active arrows
     * @return Constant reference to the vector of arrow pointers
     */
    const std::vector<Arrow*>& getArrows() const;
};

#endif // ARROW_MANAGER_H