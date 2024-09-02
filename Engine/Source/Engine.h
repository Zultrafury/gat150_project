#pragma once
#include <array>
#include <fmod.hpp>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

#include "Core/Json.h"
#include "Core/NanoClock.h"
#include "Input/KeyInput.h"
#include "Physics/Physics.h"

class Engine
{
public:
    int win_w = 1200; int win_h = 900; std::string windowtitle = "Shibble";
    
    SDL_Renderer* renderer = nullptr;

    FMOD::System* audio = nullptr; FMOD::ChannelGroup* audiogroup; float* volume = new float(0.2f);

    std::vector<NanoClock> nanoclocks;

    std::array<bool,16> clockchecks;

    bool* running; bool playercollision = false;

    std::vector<Actor> actors;

    std::vector<Actor> prefabs;

    std::unique_ptr<Physics> m_physics;

    Physics& GetPhysics() { return *m_physics; }

    KeyInput keys = KeyInput();
    
    Engine() = default;

    bool init(bool* _run)
    {
        running = _run;
        
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
        SDL_Window* window = SDL_CreateWindow(windowtitle.c_str(),
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
        audiogroup = nullptr;
        audio->createChannelGroup("Music",&audiogroup);
        audiogroup->setVolume(*volume);
        
        //Initialize physics
        m_physics->Initialize();
        
        //Bind to resource manager
        ResourceManager::Instance().RenderBind(renderer);
        ResourceManager::Instance().ASBind(audio, audiogroup);

        //Load scene.json
        rapidjson::Document document;
        Json::Load("scene.json", document);
        READ_DATA(document,actors);
        READ_DATA(document,prefabs);
        
        return false;
    }

    int addClock(int t)
    {
        if (nanoclocks.size() >= 16)
        {
            return 1;
        }
        NanoClock clock = NanoClock(t);
        nanoclocks.push_back(clock);
        return 0;
    }

    int addClock(float t)
    {
        if (nanoclocks.size() >= 16)
        {
            return 1;
        }
        NanoClock clock = NanoClock(t);
        nanoclocks.push_back(clock);
        return 0;
    }

    void Update()
    {
        SDL_PumpEvents();

        //Load actors
        for (auto& actor : actors)
        {
            actor.renderer = renderer;
        }
        
        //Clock checks
        for (int i = 0; i < nanoclocks.size(); ++i)
        {
            nanoclocks[i].Check(clockchecks[i]);
        }
        
        for (auto& actor : actors)
        {
            if (actor.active)
            {
                actor.Update();
            }
            for (auto& element : actor.components)
            {
                if (dynamic_cast<BeatComponent*>(element) && clockchecks[1])
                {
                    dynamic_cast<BeatComponent*>(element)->OnBeat();
                }
                if (dynamic_cast<ChaserEnemyComponent*>(element))
                {
                    if (dynamic_cast<ChaserEnemyComponent*>(element)->collision)
                    {
                        playercollision = true;
                    }
                }
            }
        }
    }

    Actor Prefab(std::string name)
    {
        for (auto& element : prefabs)
        {
            if (element.name == name)
            {
                return element;
            }
        }
    }

    Actor GetActor(std::string name)
    {
        for (auto& element : actors)
        {
            if (element.name == name)
            {
                return element;
            }
        }
    }

    void EndUpdate()
    {
        audio->update();
        for (auto& element : actors)
        {
            for (auto& c : element.components)
            {
                if (c->Destroy())
                {
                    element.~Actor();
                    break;
                }
            }
        }
        if (keys.GetKey("esc"))
        {
            *running = false;
        }
        if (keys.GetKeyDown("-"))
        {
            volume = new float(std::fmaxf(*volume-0.05f,0));
            audiogroup->setVolume(*volume);
        }
        if (keys.GetKeyDown("="))
        {
            volume = new float(std::fminf(*volume+0.05f,1));
            audiogroup->setVolume(*volume);
        }
    }
    
    void Draw()
    {
        SDL_RenderClear(renderer);
        for (auto element : actors)
        {
            if (element.active)
            {
                element.Draw();
            }
        }
        SDL_RenderPresent(renderer);
    }

    void Exit()
    {
        *running = false;
    }
};
