/**
 * @file itemManager.h
 * @brief Definition of the ItemManager class for managing items in the game
 */

#ifndef ITEM_MANAGER_H
#define ITEM_MANAGER_H

#include "item.h"
#include "player.h"
#include <vector>
#include <chrono>

/**
 * @class ItemManager
 * @brief Class responsible for managing all items in the game
 * 
 * The ItemManager class handles the creation, updating, collision detection,
 * and cleanup of collectible items in the game.
 */
class ItemManager {
private:
    std::vector<Item*> items; ///< Collection of active items in the game

public:
    /**
     * @brief Default constructor
     */
    ItemManager();
    
    /**
     * @brief Destructor that cleans up all items
     */
    ~ItemManager();

    /**
     * @brief Adds a new item to the manager
     * @param item Pointer to the item to be added
     */
    void addItem(Item* item);
    
    /**
     * @brief Updates all items
     * @param map Reference to the game map
     * @param deltaTime Time elapsed since the last update
     */
    void update(Map& map, std::chrono::duration<double> deltaTime);
    
    /**
     * @brief Checks for collisions between items and the player
     * @param player Reference to the player
     */
    void checkCollisions(Player& player);
    
    /**
     * @brief Removes all items from the manager
     */
    void clearAllItems();
    
    /**
     * @brief Removes expired items from the manager
     */
    void removeExpiredItems();

    /**
     * @brief Gets the collection of active items
     * @return Constant reference to the vector of item pointers
     */
    const std::vector<Item*>& getItems() const { return items; }
};

#endif // ITEM_MANAGER_H