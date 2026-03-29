/**
 * @file winTxt.h
 * @brief Definition of the WinTXT class for text mode display
 * 
 * This file contains the definition of the WinTXT class which allows managing
 * a display window in text mode in the console.
 */

#ifndef WINTXT_H
#define WINTXT_H

/**
 * @class WinTXT
 * @brief Class representing a text window as a 2D array of characters
 * 
 * This class allows creating and manipulating a text window in the console.
 * It handles displaying, clearing, and character input.
 */
class WinTXT
{
private:
    int dimx;  //!< Width of the window in characters
    int dimy;  //!< Height of the window in characters
    char *win; //!< Stores the window content in a 1D array but accessed as 2D

public:
    /**
     * @brief Constructor for the WinTXT class
     * @param dx Width of the window in characters
     * @param dy Height of the window in characters
     * 
     * Initializes a text window with dimensions dx×dy.
     */
    WinTXT(int dx, int dy);
    
    /**
     * @brief Destructor for the WinTXT class
     * 
     * Frees the memory allocated for the character array.
     */
    ~WinTXT() { if (win!=nullptr) delete []win; }
    
    /**
     * @brief Clears the window with a specific character
     * @param c Character used to clear the window (space by default)
     * 
     * Fills the entire window with the specified character.
     */
    void clear(char c = ' ');
    
    /**
     * @brief Displays a character at a specific position
     * @param x X coordinate in the window
     * @param y Y coordinate in the window
     * @param c Character to display
     * 
     * Places character c at position (x,y) in the window.
     */
    void print(int x, int y, char c);
    
    /**
     * @brief Displays a string at a specific position
     * @param x X coordinate in the window
     * @param y Y coordinate in the window
     * @param c Pointer to the string to display
     * 
     * Places the string c starting from position (x,y) in the window.
     */
    void print(int x, int y, char *c);
    
    /**
     * @brief Draws the window on the screen
     * @param x Starting X position for display (0 by default)
     * @param y Starting Y position for display (0 by default)
     * 
     * Displays the window content on the screen starting from position (x,y).
     */
    void draw(int x = 0, int y = 0);
    
    /**
     * @brief Pauses execution until a key is pressed
     * 
     * Waits for the user to press a key to continue.
     */
    void pause();
    
    /**
     * @brief Gets a character from keyboard input
     * @return The character that was pressed
     * 
     * Reads a character from the keyboard if a key was pressed.
     */
    char getCh();
};

/**
 * @brief Clears the terminal screen
 * 
 * Erases all content from the terminal window.
 */
void termClear();

#endif
