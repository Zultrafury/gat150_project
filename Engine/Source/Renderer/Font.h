#pragma once
#include <iostream>
#include <string>
#include <SDL_ttf.h>

#include "Resources/Resource.h"

class Font : public Resource
{
public:
    ~Font()
    {
        if (m_ttfFont != nullptr)
        {
            TTF_CloseFont(m_ttfFont);
        }
    }

    bool Create(std::string name, ...) override
    {
        va_list args;
        va_start(args,name);
        int fontSize = va_arg(args, int);
        va_end(args);
 
        return Load(name, fontSize);
    }
    
    bool Load(const std::string& name, int fontSize)
    {
        m_ttfFont = TTF_OpenFont(name.c_str(), fontSize);
        if (m_ttfFont == nullptr)
        {
            std::cerr << "Could not load font: " << name << "\n";
            return false;
        }

        return true;
    }

    _TTF_Font* m_ttfFont{ nullptr };
};
