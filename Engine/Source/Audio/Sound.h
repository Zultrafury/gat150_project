#pragma once
#include <cstdarg>
#include <fmod.hpp>
#include <string>

#include "Resources/Resource.h"

class Sound : public Resource
{
public:
    FMOD::Sound* m_sound{ nullptr };

    bool Create(std::string name, ...) override
    {
        va_list args;
        va_start(args, name);
        FMOD::System* audio = va_arg(args, FMOD::System*);
        va_end(args);
 
        return Load(name, audio);
    }

    bool Load(const std::string& filename, FMOD::System* audio)
    {
        audio->createSound(filename.c_str(), FMOD_DEFAULT, 0, &m_sound);
        return true;
    }
};
