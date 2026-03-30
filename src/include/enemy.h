/**
 * @file enemy.h
 * @brief Definition of the Enemy class representing an enemy in the game
 */

#ifndef ENEMY_H
#define ENEMY_H

#include <queue>
#include <vector>
#include <utility>
#include "entity.h"
#include "item.h"
#include "Direction.h"
#include <random>
#include <nlohmann/json.hpp>
#include <chrono>

/**
 * @class Enemy
 * @brief Class representing an enemy in the game
 * 
 * The Enemy class inherits from Entity and implements the behavior of an enemy
 * that can move randomly, follow a target, and attack the player.
 */
class Enemy : public Entity {
private:
    int targetX, targetY;      ///< Coordinates of the target
    bool hasTarget;            ///< Indicates if the enemy has a target
    char normalSymbol;         ///< Symbol displayed when the enemy is in normal state
    char alertSymbol;          ///< Symbol displayed when the enemy is alerted
    double attackCooldown;     ///< Current cooldown for the enemy's attack
    Direction dir;             ///< Current direction of the enemy
    double moveSpeed;          ///< Movement speed of the enemy
    double accumulatedDx = 0.0; ///< Accumulated movement in X direction
    double accumulatedDy = 0.0; ///< Accumulated movement in Y direction

    static constexpr double ATTACK_COOLDOWN_DURATION = 1.0; ///< Duration of the attack cooldown

public:
    /**
     * @brief Default constructor
     */
    Enemy();
    
    /**
     * @brief Parameterized constructor
     * @param startX Initial X position of the enemy
     * @param startY Initial Y position of the enemy
     * @param speed Movement speed of the enemy
     */
    Enemy(int startX, int startY, double speed);
    
    /**
     * @brief Constructor from JSON data
     * @param j JSON object containing enemy data
     */
    Enemy(const nlohmann::json& j);
    
    /**
     * @brief Virtual destructor
     */
    virtual ~Enemy() override;

    /**
     * @brief Gets the current direction of the enemy
     * @return Current direction
     */
    Direction getDir() const {return dir;}

    /**
     * @brief Updates the enemy's state and position
     * @param map Reference to the game map
     * @param elapsedTime Time elapsed since the last update
     */
    virtual void update(Map& map, std::chrono::duration<double> elapsedTime) override;
    
    /**
     * @brief Updates the attack cooldown
     * @param elapsedTime Time elapsed since the last update
     */
    void updateAttackCooldown(std::chrono::duration<double> elapsedTime);
    
    /**
     * @brief Finds a path to the target using pathfinding algorithm
     * @param map Reference to the game map
     * @param targetX X coordinate of the target
     * @param targetY Y coordinate of the target
     * @return Vector of coordinates representing the path to the target
     */
    std::vector<std::pair<int, int>> findPath(const Map& map, int targetX, int targetY);
    
    /**
     * @brief Makes the enemy move randomly
     * @param map Reference to the game map
     * @param elapsedTime Time elapsed since the last update
     */
    void moveRandomly(Map& map, std::chrono::duration<double> elapsedTime);

    /**
     * @brief Sets a target for the enemy to follow
     * @param x X coordinate of the target
     * @param y Y coordinate of the target
     */
    void setTarget(int x, int y);
    
    /**
     * @brief Clears the current target
     */
    void clearTarget();
    
    /**
     * @brief Checks if the enemy is alerted (has a target)
     * @return true if the enemy is alerted, false otherwise
     */
    bool isAlerted() const;

    /**
     * @brief Checks if the enemy can attack
     * @return true if the enemy can attack, false otherwise
     */
    bool canAttack() const;
    
    /**
     * @brief Resets the attack cooldown
     */
    void resetAttackCooldown();
    
    /**
     * @brief Makes the enemy drop an item when defeated
     * @return Pointer to the dropped item, or nullptr if no item is dropped
     */
    Item* dropItem() const;

    /**
     * @brief Converts the enemy to a JSON object
     * @return JSON object representing the enemy
     */
    nlohmann::json toJson() const;

    /**
     * @brief Regression test for the Enemy class
     * @return 0 if all tests pass, a positive number otherwise
     */
    static int regressionTest();
};

#endif // ENEMY_H
