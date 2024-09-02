#pragma once
#include <SDL_render.h>
#include <vector>

#include "Components/ChaserEnemyComponent.h"
#include "Components/Component.h"

class Actor
{
public:
    std::string name;
    bool active = true;
    int x = 0; int y = 0;
    int w = 0; int h = 0;
    double rotation = 0; double scale = 1;
    SDL_Renderer* renderer = nullptr;
    std::vector<Component*> components;
    
    Actor() = default;
    
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

    void Update()
    {
        for (auto c : components)
        {
            c->Update(renderer,&x,&y,rotation,scale);
        }
    }

    Actor Clone()
    {
        Actor clone = Actor(renderer);
        for (auto c : components)
        {
            clone.components.push_back(c->Clone());
        }
        clone.name = name+"_clone";
        clone.rotation = rotation;
        clone.scale = scale;
        return clone;
    }

    void AddSeed(int _seed)
    {
        for (auto c : components)
        {
            ChaserEnemyComponent* e = dynamic_cast<ChaserEnemyComponent*>(c);
            if (e != nullptr)
            {
                e->AddSeed(_seed);
            }
        }
    }
};
