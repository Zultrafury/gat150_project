﻿#pragma once
#include <SDL_render.h>
#include <vector>

#include "Math/FVector2.h"

class Model
{
public:
    FVector2 center = FVector2(0,0);
    std::vector<FVector2> vectors;

    Model(FVector2 center_, std::vector<FVector2> vectors_)
    {
        center = center_; vectors = vectors_;
    }

    void Draw(SDL_Renderer* renderer)
    {
        for (int i = 1; i < vectors.size(); ++i)
        {
            SDL_RenderDrawLineF(renderer,round(vectors[i - 1].x + center.x),round(vectors[i - 1].y + center.y),round(vectors[i].x + center.x),round(vectors[i].y + center.y));
        }
    }
};
