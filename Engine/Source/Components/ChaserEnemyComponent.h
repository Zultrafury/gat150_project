#pragma once
#include "Component.h"
#include "Framework/Text.h"
#include "Math/FVector2.h"
#include <cstdlib>
#include <random>
#include <SDL.h>

class ChaserEnemyComponent : public Component
{
public:
    FVector2 position = FVector2(-10.0f,-10.0f);
    int behavior = 0; int sidespawned = 0;
    int lifetime = 0; int seed = 0;
    bool collision = false;
    
    ChaserEnemyComponent()
    {
        init();
    }

    void init()
    {
        int w = 1200; int h = 900;
        behavior = seed%4;
        sidespawned = seed%4;
        switch (sidespawned)
        {
        case 0:
            position.x = static_cast<float>(seed%(w+1));
            break;
        case 1:
            position.x = static_cast<float>(seed%(w+1));
            position.y = static_cast<float>(h+10);
            break;
        case 2:
            position.y = static_cast<float>(seed%(h+1));
            break;
        case 3:
            position.y = static_cast<float>(seed%(h+1));
            position.x = static_cast<float>(w+10);
            break;
        }
    }

    void Draw(SDL_Renderer* renderer, int x, int y, double rotation, double scale) override
    {
        lifetime++;
    }
    
    void Update(SDL_Renderer* renderer, int* x, int* y, double& rotation, double& scale) override
    {
        FVector2 difference; float distance;
        float speed = 0.0004f * ((seed%7)+1);
        int mousex, mousey;
        SDL_GetMouseState(&mousex,&mousey);
        switch (behavior)
        {
            case 0:
                switch (sidespawned)
                {
                case 0:
                    position.x = (sin(static_cast<float>(lifetime + seed)/50)*600)+600;
                    position.y += speed;
                    break;
                case 1:
                    position.x = (sin(static_cast<float>(lifetime + seed)/50)*600)+600;
                    position.y -= speed;
                    break;
                case 2:
                    position.x += speed;
                    position.y = (sin(static_cast<float>(lifetime + seed)/50)*450)+450;
                    break;
                case 3:
                    position.x -= speed;
                    position.y = (sin(static_cast<float>(lifetime + seed)/50)*450)+450;
                    break;
                }
            default:
            difference = FVector2(mousex - position.x, mousey - position.y).Normalized();
            position.x += difference.x * speed;
            position.y += difference.y * speed;
            break;
        }
        *x = position.x; *y = position.y;

        distance = FVector2(mousex - position.x, mousey - position.y).Magnitude();
        if (distance <= 15)
        {
            collision = true;
            lifetime = 6*61;
        }
        else
        {
            collision = false;
        }
    }

    Component* Clone() override
    {
        return new ChaserEnemyComponent(*this);
    }

    void AddSeed(int _seed)
    {
        seed = _seed;
        init();
    }

    bool Destroy() override
    {
        if (lifetime > 9*60)
        {
            return true;
        }
        return false;
    }
};
