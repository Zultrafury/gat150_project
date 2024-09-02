#pragma once
#include <cstdarg>
#include <fmod.hpp>
#include <string>

#include "Resources/Resource.h"

class Sound : public Resource
{
public:
    bool Create(std::string name, ...) override
    {
        va_list args;
        va_start(args, name);
        m_audio = va_arg(args, FMOD::System*);
        m_audiog = va_arg(args, FMOD::ChannelGroup*);
        bool loop = va_arg(args, bool);
        va_end(args);
 
        return Load(name, loop);
    }

    bool Load(const std::string& filename)
    {
        return Load(filename,false);
    }

    bool Load(const std::string& filename, bool loop)
    {
        if (loop)
        {
            m_audio->createSound(filename.c_str(), FMOD_LOOP_NORMAL, 0, &m_sound);
        }
        else
        {
            m_audio->createSound(filename.c_str(), FMOD_DEFAULT, 0, &m_sound);
        }
        return true;
    }

    FMOD::Sound* m_sound{ nullptr };
    FMOD::System* m_audio{ nullptr };
    FMOD::ChannelGroup* m_audiog{ nullptr };
};
