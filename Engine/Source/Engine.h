#pragma once
#include <fmod.hpp>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

class Engine
{
public:
    int win_w = 1200; int win_h = 900;
    
    SDL_Renderer* renderer = nullptr; FMOD::System* audio = nullptr;
    
    Engine()
    {
        init();
    }

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
        /*
        for (int i = 0; i < SDL_GetNumRenderDrivers(); ++i)
        {
            SDL_RendererInfo info;
            SDL_GetRenderDriverInfo(i,&info);
            std::cout << i << ": " << info.name << "\n";
        }
        */
        renderer = SDL_CreateRenderer(window, 0, 0);

        //SDL_SetRelativeMouseMode(SDL_TRUE);

        // create audio system
        FMOD::System_Create(&audio);

        void* extradriverdata = nullptr;
        audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

        return false;
    }
};
