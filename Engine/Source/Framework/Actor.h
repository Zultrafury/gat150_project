#pragma once
#include <SDL_render.h>
#include <vector>

#include "Components/Component.h"

class Actor
{
public:
    std::string name;
    int x = 0; int y = 0;
    double rotation = 0; double scale = 1;
    SDL_Renderer* renderer = nullptr;
    std::vector<Component*> components;
    
    Actor(SDL_Renderer* _renderer)
    {
        renderer = _renderer;
    }

    void AddComponent(Component* c)
    {
        components.push_back(c);
    }
    
    void SetPos(int _x, int _y, double _rot)
    {
        x = _x; y = _y;
        rotation = _rot;
    }

    void Move(int _x, int _y, double _rot)
    {
        x += _x; y += _y;
        rotation += _rot;
    }

    void Scale(double _scale)
    {
        scale = _scale;
    }

    void Draw()
    {
        for (auto c : components)
        {
            c->Draw(renderer,x,y,rotation,scale);
        }
    }
};
