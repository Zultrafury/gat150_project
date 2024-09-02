#include <chrono>
#include <iostream>
#include <SDL.h>
#include <fmod.hpp>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Engine.h"
#include "Framework/Enemy.h"
#include "Renderer/Font.h"
#include "Math/Vector2.h"
#include "Math/FVector2.h"
#include "Framework/Particle.h"
#include "Framework/Model.h"
#include "Framework/Star.h"
#include "Framework/Text.h"
#include "LegacyGames.h"
#include "Components/SpriteComponent.h"
#include "Components/TextComponent.h"
#include "Framework/Actor.h"
#include "Input/KeyInput.h"

Engine engine;
LegacyGames lg = LegacyGames();

int main(int argc, char* argv[])
{
    float measures = 0;
    srand(time(NULL));
    int score = 0; int lives = 3; int playerinvuln = 0;
    
    engine.addClock(60);
    engine.addClock(132.3f);
    bool running = true;
    engine.init(&running);
    SDL_ShowCursor(SDL_DISABLE);
    
    while(running)
    {
        engine.Update();
        engine.keys.Update();
        dynamic_cast<TextComponent*>(engine.GetActor("ScoreText").components[0])->localtext.text = std::string("Score: ").append(std::to_string(score));

        if (lives > 0)
        {
            dynamic_cast<TextComponent*>(engine.GetActor("LivesText").components[0])->localtext.text = std::string("Lives: ").append(std::to_string(lives));
        }
        if (engine.clockchecks[0])
        {
            engine.Draw();
            playerinvuln = std::max(playerinvuln-1,0);
            dynamic_cast<TextComponent*>(engine.GetActor("ScoreText").components[0])->localtext.color = SDL_Color{ 255, 255, 255 };
            dynamic_cast<TextComponent*>(engine.GetActor("LivesText").components[0])->localtext.color = SDL_Color{ 255, 255, 255 };

            if (engine.playercollision && playerinvuln < 1 && lives > 0)
            {
                dynamic_cast<AudioComponent*>(engine.Prefab("HitSound").Clone().components[0])->Play();

                engine.playercollision = false;
                lives--;
                playerinvuln = 120;
                std::cout << "Lives: " << lives << std::endl;
            }
            if (playerinvuln > 0)
            {
                dynamic_cast<TextComponent*>(engine.GetActor("ScoreText").components[0])->localtext.color = SDL_Color{ 195, 195, 195 };
                dynamic_cast<TextComponent*>(engine.GetActor("LivesText").components[0])->localtext.color = SDL_Color{ 195, 195, 195 };
            }
        }
        if (engine.clockchecks[1] && lives > 0)
        {
            score += 25;
            measures += 0.25;
            for (int i = 0; i < measures/32+1; ++i)
            {
                Actor clone = engine.Prefab("Enemy").Clone();
                clone.AddSeed(rand());
                engine.actors.push_back(clone);
            }
        }
        if (lives <= 0)
        {
            engine.audiogroup->setPitch(0.5f);
            SDL_ShowCursor(SDL_ENABLE);
            dynamic_cast<TextComponent*>(engine.GetActor("LivesText").components[0])->localtext.text = std::string("GGS (ESC TO EXIT)");
            for (auto& element : engine.actors)
            {
                if (element.name == "Enemy_clone" || element.name == "Player")
                {
                    element.~Actor();
                }
            }
        }
        engine.EndUpdate();
    }

    engine.audio->close();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}
