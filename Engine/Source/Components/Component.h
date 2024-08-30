#pragma once


class Component
{
public:
    virtual ~Component() = default;
    Component() = default;

    virtual void Draw(SDL_Renderer* renderer, int x, int y, double rotation, double scale)
    {
        
    }
    virtual void Update()
    {
        
    }
};