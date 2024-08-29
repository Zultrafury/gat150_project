#pragma once
#include "Component.h"
#include "Framework/Text.h"

class TextComponent : Component
{
public:
    Text localtext = nullptr;
    
    TextComponent(const res_t<Font>& font)
    {
        localtext = Text(font);
    }

    void Draw(SDL_Renderer* renderer, int x, int y) override
    {
        localtext.Create(renderer);
        localtext.Draw(renderer,x,y);
    }
    void Update() override;
};
