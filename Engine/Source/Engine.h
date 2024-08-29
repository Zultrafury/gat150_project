#pragma once
#include <fmod.hpp>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

#include "Core/NanoClock.h"
#include "Physics/Physics.h"

class Engine
{
public:
    int win_w = 1200; int win_h = 900;
    
    SDL_Renderer* renderer = nullptr; FMOD::System* audio = nullptr;

    std::vector<NanoClock> nanoclocks;

    bool clockchecks[16];

    std::unique_ptr<Physics> m_physics;

    Physics& GetPhysics() { return *m_physics; }
    
    Engine() = default;

    bool init()
    {
        // initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cerr << "Error initializing SDL: " << SDL_GetError() << "\n";
            return true;
        }

        // initialize TTF SDL
        if (TTF_Init() < 0)
        {
            std::cerr << "Error initializing SDL TTF: " << SDL_GetError() << "\n";
            return true;
        }

        // initialize Image SDL, supports BMP, JPG, and PNG
        if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0)
        {
            std::cerr << "Error initializing SDL Image: " << SDL_GetError() << std::endl;
            return true;
        }

        // create window
        // returns pointer to window if successful or nullptr if failed
        SDL_Window* window = SDL_CreateWindow("Game Engine",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            win_w, win_h,
            SDL_WINDOW_SHOWN);
        if (window == nullptr)
        {
            std::cerr << "Error creating SDL window: " << SDL_GetError() << "\n";
            SDL_Quit();
            return true;
        }

        // create renderer
        renderer = SDL_CreateRenderer(window, 0, 0);

        // create audio system
        FMOD::System_Create(&audio);

        void* extradriverdata = nullptr;
        audio->init(32, FMOD_INIT_NORMAL, extradriverdata);
        
        return false;
    }

    template<typename T>
    int addClock(T t)
    {
        if (nanoclocks.size() >= 16)
        {
            return 1;
        }
        try
        {
            NanoClock clock = NanoClock(t);
            nanoclocks.push_back(clock);
        }
        catch(std::logic_error e)
        {
            std::cerr << e.what() << '\n';
            return 1;
        }
    }

    void Update()
    {
        //Clock checks
        for (int i = 0; i < nanoclocks.size(); ++i)
        {
            nanoclocks[i].Check(clockchecks[i]);
        }
    }
    
    void Draw()
    {
        
    }
};
