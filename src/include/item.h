/**
 * @file item.h
 * @brief Definition of the Item class and ItemType enumeration
 */

#ifndef ITEM_H
#define ITEM_H

#include "entity.h"
#include <chrono>

/**
 * @enum ItemType
 * @brief Enumeration of different types of items in the game
 */
enum class ItemType {
    HEART   ///< Heart item that restores player health
};

/**
 * @class Item
 * @brief Class representing collectible items in the game
 * 
 * The Item class inherits from Entity and implements the behavior of
 * collectible items that can be picked up by the player to provide
 * various effects.
 */
class Item : public Entity {
private:
    ItemType type;       ///< Type of the item
    int value;           ///< Value or effect strength of the item
    double lifespan;     ///< How long the item remains in the game (in seconds)
    double elapsedTime;  ///< Time elapsed since the item was created

public:
    /**
     * @brief Default constructor
     */
    Item();
    
    /**
     * @brief Parameterized constructor
     * @param x X coordinate of the item
     * @param y Y coordinate of the item
     * @param type Type of the item
     * @param lifespan Duration the item remains in the game (default: 30.0 seconds)
     */
    Item(int x, int y, ItemType type, double lifespan = 30.0);

    /**
     * @brief Virtual destructor
     */
    virtual ~Item() override;

    /**
     * @brief Gets the type of the item
     * @return Type of the item
     */
    ItemType getType() const { return type; }
    
    /**
     * @brief Gets the value of the item
     * @return Value or effect strength
     */
    int getValue() const { return value; }
    
    /**
     * @brief Gets the lifespan of the item
     * @return Lifespan in seconds
     */
    double getLifespan() const { return lifespan; }
    
    /**
     * @brief Gets the elapsed time since the item was created
     * @return Elapsed time in seconds
     */
    double getElapsedTime() const { return elapsedTime; }

    /**
     * @brief Updates the item's state
     * @param map Reference to the game map
     * @param deltaTime Time elapsed since the last update
     */
    virtual void update(Map& map, std::chrono::duration<double> deltaTime) override;

    /**
     * @brief Checks if the item has expired
     * @return true if the item has expired, false otherwise
     */
    bool isExpired() const { return elapsedTime >= lifespan; }

    /**
     * @brief Regression test for the Item class
     * @return 0 if all tests pass, a positive number otherwise
     */
    static int regressionTest();
};

#endif // ITEM_H
