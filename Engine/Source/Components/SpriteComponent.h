#pragma once
#include "Component.h"
#include "Framework/Sprite.h"
#include "Framework/Text.h"

class SpriteComponent : public Component
{
public:
    Sprite localsprite;
    
    SpriteComponent(res_t<Texture>& _tex, int _frames, int _fps, bool _loop)
    {
        localsprite = Sprite(_tex,_frames,_fps,_loop);
    }

    void Draw(SDL_Renderer* renderer, int x, int y, double rotation, double scale) override
    {
        localsprite.Draw(renderer,x,y,rotation,scale);
    }
    void Update(SDL_Renderer* renderer, int* x, int* y, double& rotation, double& scale) override
    {
        
    }

    Component* Clone() override
    {
        return new SpriteComponent(*this);
    }
};