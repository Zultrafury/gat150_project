#pragma once
#include "Component.h"
#include "Framework/Text.h"

class MouseStickComponent : public Component
{
public:
    int offx = 0; int offy = 0;

    MouseStickComponent() = default;
    MouseStickComponent(int _offx, int _offy)
    {
        offx = _offx; offy = _offy;
    }

    void Draw(SDL_Renderer* renderer, int x, int y, double rotation, double scale) override
    {
        
    }
    
    void Update(SDL_Renderer* renderer, int* x, int* y, double& rotation, double& scale) override
    {
        SDL_GetMouseState(x,y);
        *x += offx; *y += offy;
    }

    Component* Clone() override
    {
        return new MouseStickComponent(*this);
    }
};