#pragma once
#include <iostream>
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>
#include "Math/Vector2.h"
#include "Resources/Resource.h"

class Texture : public Resource
{
public:
    SDL_Texture* m_texture{ nullptr };
    
    Texture() = default;
    ~Texture()
    {
        if (m_texture != nullptr)
        {
            SDL_DestroyTexture(m_texture);
        }
    }

    bool Create(std::string name, ...) override
    {
        va_list args;
        va_start(args, name);
        SDL_Renderer* renderer = va_arg(args, SDL_Renderer*);
        va_end(args);
 
        return Load(name, renderer);
    }

    bool Load(std::string filename, SDL_Renderer* renderer)
    {
        // load image onto surface
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if (surface == nullptr)
        {
            std::cerr << "Could not load image: " << filename << '\n';
            return false;
        }

        // create texture from surface, texture is a friend class of renderer
        m_texture = SDL_CreateTextureFromSurface(renderer,surface);
        // once texture is created, surface can be freed up
        SDL_FreeSurface(surface);
        if (m_texture == nullptr)
        {
            std::cerr << "Could not create texture: " << filename << '\n';
            return false;
        }

        return true;
    }

    Vector2 GetSize()
    {
        if (m_texture != nullptr)
        {
            // query the texture for the size
            // https://wiki.libsdl.org/SDL2/SDL_QueryTexture
            SDL_Point size;
            SDL_QueryTexture(m_texture, NULL, NULL,&size.x,&size.y);

            return {size.x,size.y};
        }
        return {0,0};
    }
};
