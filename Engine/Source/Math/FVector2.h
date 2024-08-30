#pragma once
#include "Vector2.h"

class FVector2
{
public:
    float x, y;

    FVector2()
    {
        x = 0; y = 0;
    }
    FVector2(float xx, float yy)
    {
        x = xx; y = yy;
    }

    FVector2 Normalized()
    {
        float magnitude = sqrtf(powf(x,2) + powf(y,2));
        return FVector2(x/magnitude,y/magnitude);
    }

    float Magnitude()
    {
        return sqrtf(powf(x,2) + powf(y,2));
    }
    /*
    Vector2 asi()
    {
        return {static_cast<int>(round(x)),static_cast<int>(round(y))};
    }
    */
};
