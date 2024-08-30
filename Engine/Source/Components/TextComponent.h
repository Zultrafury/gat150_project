#pragma once
#include "Component.h"
#include "Framework/Text.h"

class TextComponent : public Component
{
public:
    Text localtext = nullptr;
    
    TextComponent(const res_t<Font>& font)
    {
        localtext = Text(font);
    }
    TextComponent(const res_t<Font>& font, std::string text, SDL_Color color)
    {
        localtext = Text(font);
        localtext.text = text;
        localtext.color = color;
    }
    
    void Draw(SDL_Renderer* renderer, int x, int y, double rotation, double scale) override
    {
        localtext.Create(renderer);
        localtext.Draw(renderer,x,y,rotation,scale);
    }
    void Update() override
    {
        
    }
};
