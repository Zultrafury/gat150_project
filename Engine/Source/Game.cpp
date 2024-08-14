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

Engine engine;
LegacyGames lg = LegacyGames();

int main(int argc, char* argv[])
{
    //lg.spiral(engine.renderer);
    lg.example(engine.renderer, engine.audio);

    engine.audio->close();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}
