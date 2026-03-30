/**
 * @file sprite.h
 * @brief Definition of the SDLSprite class for handling game sprites
 */

#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/**
 * @class SDLSprite
 * @brief Class for loading, managing, and rendering sprite images using SDL2
 * 
 * The SDLSprite class provides functionality to load images from files,
 * convert them to textures, and render them to the screen.
 */
class SDLSprite
{

private:
    SDL_Surface *m_surface;   ///< SDL surface containing the image data
    SDL_Texture *m_texture;   ///< SDL texture for hardware-accelerated rendering
    bool m_hasChanged;        ///< Flag indicating if the surface has changed and the texture needs updating

public:
    /**
     * @brief Default constructor
     */
    SDLSprite();
    
    /**
     * @brief Destructor
     */
    ~SDLSprite();
    
    /**
     * @brief Copy constructor
     * @param im SDLSprite to copy
     */
    SDLSprite(const SDLSprite &im);
    
    /**
     * @brief Assignment operator
     * @param im SDLSprite to copy
     * @return Reference to this SDLSprite
     */
    SDLSprite &operator=(const SDLSprite &im);

    /**
     * @brief Loads an image from a file
     * @param filename Path to the image file
     * @param renderer SDL renderer to create the texture
     */
    void loadFromFile(const char *filename, SDL_Renderer *renderer);
    
    /**
     * @brief Creates a texture from the current surface
     * @param renderer SDL renderer to create the texture
     */
    void loadFromCurrentSurface(SDL_Renderer *renderer);
    
    /**
     * @brief Draws the sprite to the screen
     * @param renderer SDL renderer to draw with
     * @param x X coordinate to draw at
     * @param y Y coordinate to draw at
     * @param w Width of the drawn sprite (default: original width)
     * @param h Height of the drawn sprite (default: original height)
     */
    void draw(SDL_Renderer *renderer, int x, int y, int w = -1, int h = -1);
    
    /**
     * @brief Gets the SDL texture
     * @return Pointer to the SDL texture
     */
    SDL_Texture* getTexture() const { return m_texture; }
    
    /**
     * @brief Sets a new SDL surface
     * @param surf Pointer to the new SDL surface
     */
    void setSurface(SDL_Surface *surf)  { if (m_surface!=nullptr) SDL_FreeSurface(m_surface); m_surface = surf; }
};

#endif
