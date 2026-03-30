#include "sprite.h"
#include <iostream>
#include <cstring>
#include <cassert>


using namespace std;

SDLSprite::SDLSprite() : m_surface(nullptr), m_texture(nullptr), m_hasChanged(false)
{
}

SDLSprite::~SDLSprite()
{
    if (m_surface) SDL_FreeSurface(m_surface);
    if (m_texture) SDL_DestroyTexture(m_texture);

    m_surface = nullptr;
    m_texture = nullptr;
    m_hasChanged = false;
}

SDLSprite::SDLSprite(const SDLSprite &im)
{
    
}

SDLSprite &SDLSprite::operator=(const SDLSprite &im)
{
    return *this;
}

void SDLSprite::loadFromFile(const char *filename, SDL_Renderer *renderer)
{
    m_surface = IMG_Load(filename);
    if (m_surface == nullptr)
    {
        string nfn = string("../") + filename;
        cout << "Error: cannot load " << filename << ". Trying " << nfn << endl;
        m_surface = IMG_Load(nfn.c_str());
        if (m_surface == nullptr)
        {
            nfn = string("../") + nfn;
            m_surface = IMG_Load(nfn.c_str());
        }
    }
    if (m_surface == nullptr)
    {
        cout << "Error: cannot load " << filename << endl;
        SDL_Quit();
        exit(1);
    }

    SDL_Surface *surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(m_surface, SDL_PIXELFORMAT_ARGB8888, 0);
    SDL_FreeSurface(m_surface);
    m_surface = surfaceCorrectPixelFormat;

    m_texture = SDL_CreateTextureFromSurface(renderer, surfaceCorrectPixelFormat);
    if (m_texture == NULL)
    {
        cout << "Error: problem to create the texture of " << filename << endl;
        SDL_Quit();
        exit(1);
    }
}

void SDLSprite::loadFromCurrentSurface(SDL_Renderer *renderer)
{
    m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);
    if (m_texture == nullptr)
    {
        cout << "Error: problem to create the texture from surface " << endl;
        SDL_Quit();
        exit(1);
    }
}

void SDLSprite::draw(SDL_Renderer *renderer, int x, int y, int w, int h)
{
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = (w < 0) ? m_surface->w : w;
    r.h = (h < 0) ? m_surface->h : h;

    if (m_hasChanged)
    {
        ok = SDL_UpdateTexture(m_texture, nullptr, m_surface->pixels, m_surface->pitch);

        m_hasChanged = false;
    }

    ok = SDL_RenderCopy(renderer, m_texture, nullptr, &r);
    assert(ok == 0);
}
