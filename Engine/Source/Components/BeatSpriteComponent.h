#pragma once
#include "BeatComponent.h"
#include "Component.h"
#include "Framework/Sprite.h"

class BeatSpriteComponent : public Component, public BeatComponent
{
public:
    Sprite localsprite;
    int beats;
    int currentbeat = 0;
    
    BeatSpriteComponent(res_t<Texture>& _tex, int _frames, int _fps, bool _loop, int _beats)
    {
        localsprite = Sprite(_tex,_frames,_fps,_loop);
        beats = _beats;
    }

    void Draw(SDL_Renderer* renderer, int x, int y, double rotation, double scale) override
    {
        localsprite.Draw(renderer,x,y,rotation,scale);
    }
    void Update(SDL_Renderer* renderer, int* x, int* y, double& rotation, double& scale) override
    {

    }
    void OnBeat() override
    {
        currentbeat++;
        if (currentbeat > beats)
        {
            currentbeat = 1;
            localsprite.currentframe = 0;
        }
    }

    Component* Clone() override
    {
        return new BeatSpriteComponent(*this);
    }
};