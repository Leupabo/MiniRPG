/**
 * @file entity.h
 * @brief Definition of the Entity base class for all game entities
 */

#ifndef ENTITY_H
#define ENTITY_H

#include "map.h"
#include <chrono>

/**
 * @class Entity
 * @brief Abstract base class for all game entities
 * 
 * The Entity class serves as the base class for all game objects that have
 * a position, health, and can interact with the game map.
 */
class Entity {
protected:
    int x, y;           ///< Position coordinates of the entity
    char symbol;        ///< Character symbol representing the entity
    int health;         ///< Current health points of the entity
    int maxHealth;      ///< Maximum health points of the entity

public:
    /**
     * @brief Parameterized constructor
     * @param startX Initial X position of the entity
     * @param startY Initial Y position of the entity
     * @param entitySymbol Character symbol representing the entity
     * @param health Initial health points
     * @param maxHealth Maximum health points
     */
    Entity(int startX, int startY, char entitySymbol, int health, int maxHealth);
    
    /**
     * @brief Default constructor
     */
    Entity();
    
    /**
     * @brief Virtual destructor
     */
    virtual ~Entity();
    
    /**
     * @brief Gets the X coordinate of the entity
     * @return X coordinate
     */
    int getX() const { return x; }
    
    /**
     * @brief Gets the Y coordinate of the entity
     * @return Y coordinate
     */
    int getY() const { return y; }
    
    /**
     * @brief Gets the symbol representing the entity
     * @return Character symbol
     */
    char getSymbol() const { return symbol; }
    
    /**
     * @brief Gets the current health of the entity
     * @return Current health points
     */
    int gethealth() const {return health; }
    
    /**
     * @brief Gets the maximum health of the entity
     * @return Maximum health points
     */
    int getMaxHealth() const { return maxHealth; }
    
    /**
     * @brief Sets the position of the entity
     * @param newX New X coordinate
     * @param newY New Y coordinate
     */
    void setPosition(int newX, int newY);
    
    /**
     * @brief Applies damage to the entity
     * @param dmg Amount of damage to apply
     */
    void setDmg(int dmg);
    
    /**
     * @brief Adds health to the entity
     * @param hlt Amount of health to add
     */
    void addHp(int hlt);
    
    /**
     * @brief Moves the entity by a relative amount
     * @param dx Change in X coordinate
     * @param dy Change in Y coordinate
     * @param map Reference to the game map
     * @return true if the move was successful, false otherwise
     */
    bool move(int dx, int dy, const Map& map);
    
    /**
     * @brief Updates the entity's state
     * @param map Reference to the game map
     * @param elapsedTime Time elapsed since the last update
     */
    virtual void update(Map& map, std::chrono::duration<double> elapsedTime) = 0;
};

#endif // ENTITY_H