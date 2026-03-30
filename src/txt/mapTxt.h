/**
 * @file mapTxt.h
 * @brief Header file for text-based map rendering and game loop
 * 
 * This file contains the declaration of functions related to the text-based
 * rendering and game loop for the map component of the game.
 */

#ifndef __MAP_H__
#define __MAP_H__

#include "game.h"

/**
 * @brief Main text-based game loop function
 * @param game Reference to the Game object to be used in the loop
 * 
 * This function implements the main game loop for the text-based version
 * of the game. It handles user input, updates game state, and renders
 * the game map and entities in text mode.
 */
void txtBoucle(Game &game);

#endif