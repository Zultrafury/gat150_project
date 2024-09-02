#pragma once
#include <SDL.h>

class Component
{
public:
    virtual ~Component() = default;
    Component() = default;

    virtual void Draw(SDL_Renderer* renderer, int x, int y, double rotation, double scale)
    {
        
    }
    
    virtual void Update(SDL_Renderer* renderer, int* x, int* y, double& rotation, double& scale)
    {
        
    }

    virtual Component* Clone()
    {
        return new Component(*this);
    }

    virtual bool Destroy()
    {
        return false;
    }
};