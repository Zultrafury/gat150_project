#pragma once
#include <SDL_render.h>
#include <string>

#include "Renderer/Font.h"

class Text
{
public:
    std::string text = "Untitled text";
    SDL_Color color = SDL_Color{255, 255, 255, 255};
    ~Text()
    {
        if (m_texture != nullptr)
        {
            SDL_DestroyTexture(m_texture);
        }
    }
    Text(res_t<Font> font) : m_font{ font } {};

    void SetFont(res_t<Font> font) { m_font = font; }
    
    bool Create(SDL_Renderer* renderer, const std::string& _text, const SDL_Color& _color)
    {
        // create a surface using the font, text string and color
        text = _text;
        color = _color;
        SDL_Color c = color;
        SDL_Surface* surface = TTF_RenderText_Solid(m_font->m_ttfFont, text.c_str(), c);
        if (surface == nullptr)
        {
            std::cerr << "Could not create surface.\n";
            return false;
        }

        // create a texture from the surface, only textures can render to the renderer
        m_texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (surface == nullptr)
        {
            SDL_FreeSurface(surface);
            std::cerr << "Could not create texture" << SDL_GetError() << "\n";
            return false;
        }


        // free the surface, no longer needed after creating the texture
        SDL_FreeSurface(surface);

        return true;
    }

    bool Create(SDL_Renderer* renderer)
    {
        // create a surface using the font, text string and color
        SDL_Color c = color;
        SDL_Surface* surface = TTF_RenderText_Solid(m_font->m_ttfFont, text.c_str(), c);
        if (surface == nullptr)
        {
            std::cerr << "Could not create surface.\n";
            return false;
        }

        // create a texture from the surface, only textures can render to the renderer
        m_texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (surface == nullptr)
        {
            SDL_FreeSurface(surface);
            std::cerr << "Could not create texture" << SDL_GetError() << "\n";
            return false;
        }


        // free the surface, no longer needed after creating the texture
        SDL_FreeSurface(surface);

        return true;
    }
    
    void Draw(SDL_Renderer* renderer, int x, int y)
    {
        Draw(renderer,x, y,0,1);
    }

    void Draw(SDL_Renderer* renderer, int x, int y, double rotation, double scale)
    {
        // query the texture for the texture width and height
        int _width, _height;
        SDL_QueryTexture(m_texture, nullptr, nullptr, &_width, &_height);
        float width = static_cast<float>(_width) * static_cast<float>(scale);
        float height = static_cast<float>(_height) * static_cast<float>(scale);

        // copy the texture onto the renderer
        SDL_FRect rect{ static_cast<float>(x) - width/2, static_cast<float>(y) - height/2, width, height };
        SDL_RenderCopyExF(renderer, m_texture, NULL, &rect, rotation, NULL, SDL_FLIP_NONE);
    }

private:
    res_t<Font> m_font{ nullptr };
    SDL_Texture* m_texture{ nullptr };
};
