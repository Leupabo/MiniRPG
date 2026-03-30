/**
 * @file arrow.h
 * @brief Definition of the Arrow class representing an arrow in the game
 */

#ifndef ARROW_H
#define ARROW_H

#include "entity.h"
#include "Direction.h"
#include <chrono>

/**
 * @class Arrow
 * @brief Class representing an arrow shot in the game
 * 
 * The Arrow class inherits from Entity and implements the behavior of an arrow
 * that moves in a given direction until it encounters an obstacle
 * or goes beyond the map boundaries.
 */
class Arrow : public Entity {
private:
    Direction direction; ///< Direction in which the arrow moves
    int damage;          ///< Damage inflicted by the arrow
    bool active;         ///< Indicates if the arrow is active (in motion)
    double speed;        ///< Movement speed of the arrow
    int oldX, oldY;      ///< Previous coordinates of the arrow

public:
    /**
     * @brief Default constructor
     */
    Arrow();
    
    /**
     * @brief Parameterized constructor
     * @param startX Initial X position of the arrow
     * @param startY Initial Y position of the arrow
     * @param dir Direction in which the arrow moves
     * @param dmg Damage inflicted by the arrow
     * @param spd Movement speed of the arrow
     */
    Arrow(int startX, int startY, Direction dir, int dmg, double spd);
    
    /**
     * @brief Virtual destructor
     */
    virtual ~Arrow() override;

    /**
     * @brief Updates the arrow's position
     * @param map Reference to the game map
     * @param elapsedTime Time elapsed since the last update
     */
    virtual void update(Map& map, std::chrono::duration<double> elapsedTime) override;
    
    /**
     * @brief Checks if the arrow is active
     * @return true if the arrow is active, false otherwise
     */
    bool isActive() const { return active; }

    /**
     * @brief Deactivates the arrow
     */
    void deactivate() { active = false; }
    
    /**
     * @brief Gets the damage inflicted by the arrow
     * @return Damage value
     */
    int getDamage() const { return damage; }
    
    /**
     * @brief Gets the direction of the arrow
     * @return Direction of the arrow
     */
    Direction getDirection() const { return direction; }

    /**
     * @brief Gets the previous X position of the arrow
     * @return Previous X position
     */
    int getOldX() const { return oldX; }
    
    /**
     * @brief Gets the previous Y position of the arrow
     * @return Previous Y position
     */
    int getOldY() const { return oldY; }

    /**
     * @brief Regression test for the Arrow class
     * @return 0 if all tests pass, a positive number otherwise
     */
    static int regressionTest();
};

#endif // ARROW_H