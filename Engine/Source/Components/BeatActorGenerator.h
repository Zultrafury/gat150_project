#pragma once
#include <SDL_render.h>

#include "BeatComponent.h"
#include "Component.h"
#include "Framework/Actor.h"

class BeatActorGenerator : public Component
{
public:
    Actor* prefab;
    
    BeatActorGenerator(Actor _prefab)
    {
        prefab = &_prefab;
    }

    void Draw(SDL_Renderer* renderer, int x, int y, double rotation, double scale) override
    {
        
    }

    void Update(SDL_Renderer* renderer, int* x, int* y, double& rotation, double& scale) override
    {
        
    }

    Actor GeneratePrefab()
    {
        return prefab->Clone();
    }

    Component* Clone() override
    {
        return new BeatActorGenerator(*this);
    }
};
