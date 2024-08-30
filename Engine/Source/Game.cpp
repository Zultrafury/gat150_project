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
    // res_t<Texture> tex = ResourceManager::Instance().Get<Texture>("img/coin.png",engine.renderer);
    // res_t<Font> font = ResourceManager::Instance().Get<Font>("Jupiteroid-Regular.ttf",30);
    // Actor coin = Actor(engine.renderer);
    // coin.AddComponent(new SpriteComponent(tex,8,4));
    // coin.AddComponent(new TextComponent(ResourceManager::Instance().Get<Font>("Jupiteroid-Regular.ttf",30)));
    // coin.SetPos(400,400,0);
    // double ticks = -1;
    rapidjson::Document document;
    Json::Load("json.txt", document);
    std::vector<Component*> components;
    components.push_back(new TextComponent(ResourceManager::Instance().Get<Font>("Jupiteroid-Regular.ttf",30),"Coin!",SDL_Color{255,255,255,255}));
    READ_DATA(document,components);
    
    while(true)
    {
        engine.Update();
        if (engine.clockchecks[0])
        {
            components[0]->Draw(engine.renderer,300,400,0,1);
            components[1]->Draw(engine.renderer,600,400,0,1);
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
