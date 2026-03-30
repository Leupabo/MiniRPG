/**
 * @file bomb.h
 * @brief Definition of the Bomb class representing a bomb in the game
 */

#ifndef BOMB_H
#define BOMB_H

#include "entity.h"
#include <chrono>

/**
 * @class Bomb
 * @brief Class representing a bomb that can be placed in the game
 * 
 * The Bomb class inherits from Entity and implements the behavior of a bomb
 * that counts down and explodes after a certain time, causing damage in a radius.
 */
class Bomb : public Entity {
private:
    double timer;          ///< Time remaining before explosion
    int explosionRadius;   ///< Radius of the explosion
    int damage;            ///< Damage inflicted by the explosion
    bool active;           ///< Indicates if the bomb is active
    bool exploding;        ///< Indicates if the bomb is currently exploding

public:
    /**
     * @brief Default constructor
     */
    Bomb();
    
    /**
     * @brief Parameterized constructor
     * @param startX Initial X position of the bomb
     * @param startY Initial Y position of the bomb
     * @param timer Time before explosion in seconds
     * @param radius Radius of the explosion
     * @param dmg Damage inflicted by the explosion
     */
    Bomb(int startX, int startY, double timer, int radius, int dmg);
    
    /**
     * @brief Virtual destructor
     */
    virtual ~Bomb() override;

    /**
     * @brief Updates the bomb's state
     * @param map Reference to the game map
     * @param elapsedTime Time elapsed since the last update
     */
    virtual void update(Map& map, std::chrono::duration<double> elapsedTime) override;
    
    /**
     * @brief Checks if the bomb has finished exploding
     * @return true if the explosion is complete, false otherwise
     */
    bool hasFinishedExploding() const;
    
    /**
     * @brief Checks if the bomb is active
     * @return true if the bomb is active, false otherwise
     */
    bool isActive() const { return active; }
    
    /**
     * @brief Checks if the bomb is currently exploding
     * @return true if the bomb is exploding, false otherwise
     */
    bool isExploding() const { return exploding; }
    
    /**
     * @brief Triggers the bomb explosion
     * @param map Reference to the game map
     */
    void explode(Map& map);
    
    /**
     * @brief Gets the explosion radius
     * @return Radius of the explosion
     */
    int getExplosionRadius() const { return explosionRadius; }
    
    /**
     * @brief Gets the damage inflicted by the explosion
     * @return Damage value
     */
    int getDamage() const { return damage; }
    
    /**
     * @brief Gets the remaining time before explosion
     * @return Time in seconds
     */
    double getTimer() const { return timer; }

    /**
     * @brief Regression test for the Bomb class
     * @return 0 if all tests pass, a positive number otherwise
     */
    static int regressionTest();
};

#endif // BOMB_H