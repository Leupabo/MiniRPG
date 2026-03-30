/**
 * @file player.h
 * @brief Definition of the Player class representing the player character
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "Direction.h"
#include "enemy.h"
#include "arrow.h"
#include "bomb.h"
#include <vector>
#include <chrono>

/**
 * @class Player
 * @brief Class representing the player character in the game
 * 
 * The Player class inherits from Entity and implements the behavior of the player
 * character, including movement, attacks, and special abilities.
 */
class Player : public Entity {
private:
    Direction dir;       ///< Current facing direction of the player
    bool attackP;        ///< Flag indicating if the player is attacking
    int cooldownSword;   ///< Cooldown timer for sword attacks
    int cooldownBow;     ///< Cooldown timer for bow attacks
    int bombCooldown;    ///< Cooldown timer for bomb placement

    static constexpr double COOLDOWN_SWORD_DURATION = 2.0;  ///< Duration of sword attack cooldown in seconds
    static constexpr double COOLDOWN_BOW_DURATION = 1.0;    ///< Duration of bow attack cooldown in seconds
    static constexpr double BOMB_COOLDOWN_DURATION = 5.0;   ///< Duration of bomb placement cooldown in seconds
    static constexpr double BOMB_TIMER = 3.0;               ///< Time before a placed bomb explodes in seconds
    static const int ARROW_DAMAGE = 3;                      ///< Damage inflicted by arrows
    static const int SWORD_DAMAGE = 1;                      ///< Damage inflicted by sword attacks
    static const int BOMB_DAMAGE = 5;                       ///< Damage inflicted by bomb explosions
    static const int BOMB_RADIUS = 2;                       ///< Radius of bomb explosions in tiles

public:
    /**
     * @brief Parameterized constructor
     * @param startX Initial X position of the player
     * @param startY Initial Y position of the player
     */
    Player(int startX, int startY);
    
    /**
     * @brief Default constructor
     */
    Player();
    
    /**
     * @brief Virtual destructor
     */
    virtual ~Player() override;

    /**
     * @brief Gets the current facing direction of the player
     * @return Current direction
     */
    Direction getDir() const {return dir;}
    
    /**
     * @brief Gets the current sword attack cooldown
     * @return Cooldown time remaining for sword attacks
     */
    int getAttackCooldown() const { return cooldownSword; }
    
    /**
     * @brief Gets the current bow attack cooldown
     * @return Cooldown time remaining for bow attacks
     */
    int getBowCooldown() const { return cooldownBow; }
    
    /**
     * @brief Gets the current bomb placement cooldown
     * @return Cooldown time remaining for bomb placement
     */
    int getBombCooldown() const { return bombCooldown; }
    
    /**
     * @brief Checks if the player is dead
     * @return true if the player's health is zero or less, false otherwise
     */
    bool isDead() const { return health <= 0; }

    /**
     * @brief Updates the player's state
     * @param map Reference to the game map
     * @param elapsedTime Time elapsed since the last update
     */
    virtual void update(Map& map, std::chrono::duration<double> elapsedTime) override;

    /**
     * @brief Handles player input
     * @param input Character representing the player's input
     * @param map Reference to the game map
     * @return true if the input was handled, false otherwise
     */
    bool handleInput(char input, Map& map);
    
    /**
     * @brief Performs a sword attack against enemies
     * @param enemies Reference to the vector of enemies
     * @return true if the attack was performed, false otherwise
     */
    bool performAttack(std::vector<Enemy>& enemies);

    /**
     * @brief Checks if the player can perform a sword attack
     * @return true if the player can attack, false otherwise
     */
    bool canAttack() const;
    
    /**
     * @brief Resets the sword attack cooldown
     */
    void resetAttackCooldown();

    /**
     * @brief Checks if the player can shoot an arrow
     * @return true if the player can shoot an arrow, false otherwise
     */
    bool canShootArrow() const;
    
    /**
     * @brief Resets the bow attack cooldown
     */
    void resetBowCooldown();
    
    /**
     * @brief Creates and shoots an arrow
     * @return Pointer to the created arrow
     */
    Arrow* shootArrow();

    /**
     * @brief Checks if the player can place a bomb
     * @return true if the player can place a bomb, false otherwise
     */
    bool canPlaceBomb() const;
    
    /**
     * @brief Resets the bomb placement cooldown
     */
    void resetBombCooldown();
    
    /**
     * @brief Creates and places a bomb
     * @return Pointer to the created bomb
     */
    Bomb* placeBomb();

    /**
     * @brief Regression test for the Player class
     * @return 0 if all tests pass, a positive number otherwise
     */
    static int regressionTest();
};


#endif // PLAYER_H
