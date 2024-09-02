#pragma once
#include "Component.h"
#include "Audio/Sound.h"
#include "Framework/Sprite.h"
#include "Framework/Text.h"

class AudioComponent : public Component
{
public:
    res_t<Sound> localsound;
    int timesinceplayed = 0;
    bool playing = false;
    int duration;
    
    AudioComponent(res_t<Sound>& _snd, bool loop, int _duration)
    {
        localsound = _snd;
        duration = _duration;
        if (loop)
        {
            localsound->m_sound->setMode(FMOD_LOOP_NORMAL);
            localsound->m_audiog->setPitch(1.05);
            Play();
        }
        else
        {
            localsound->m_sound->setMode(FMOD_DEFAULT);
        }
    }

    void Draw(SDL_Renderer* renderer, int x, int y, double rotation, double scale) override
    {
        if (playing)
        {
            timesinceplayed++;
        }
    }
    void Update(SDL_Renderer* renderer, int* x, int* y, double& rotation, double& scale) override
    {
        
    }

    Component* Clone() override
    {
        return new AudioComponent(*this);
    }

    void Play()
    {
        if (!playing)
        {
            localsound->m_audio->playSound(localsound->m_sound,localsound->m_audiog,false,nullptr);
            playing = true;
        }
    }
    
    bool Destroy() override
    {
        if (localsound->m_sound->getMode(FMOD_DEFAULT) && timesinceplayed < duration)
        {
            return true;
        }
        return false;
    }
};