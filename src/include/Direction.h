/**
 * @file Direction.h
 * @brief Definition of the Direction enumeration for movement directions in the game
 */

#ifndef _DIRECTION_H
#define _DIRECTION_H

/**
 * @enum Direction
 * @brief Enumeration representing the four cardinal directions
 * 
 * This enumeration defines the four possible movement directions in the game:
 * up, down, left, and right.
 */
enum Direction{
    UP,     ///< Upward direction (typically negative Y)
    DOWN,   ///< Downward direction (typically positive Y)
    LEFT,   ///< Leftward direction (typically negative X)
    RIGHT   ///< Rightward direction (typically positive X)
};

#endif