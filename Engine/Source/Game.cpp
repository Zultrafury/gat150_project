#include <chrono>
#include <iostream>
#include <SDL.h>
#include <fmod.hpp>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include <vector>

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

Engine engine;
LegacyGames lg = LegacyGames();

int main(int argc, char* argv[])
{
    engine.addClock(60);
    engine.init();
    
    while(true)
    {
        engine.Update();
        if (engine.clockchecks[0])
        {
            engine.Draw();
        }
        engine.EndUpdate();
    }
    
    //lg.spiral(engine.renderer);
    //lg.example(engine.renderer, engine.audio);

    engine.audio->close();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}
