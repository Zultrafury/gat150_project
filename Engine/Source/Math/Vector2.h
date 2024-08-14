#pragma once
#include "FVector2.h"

class Vector2
{
public:
    int x, y;
    
    Vector2(int xx, int yy)
    {
        x = xx; y = yy;
    }

    /*FVector2 asf()
    {
        return {static_cast<float>(x),static_cast<float>(y)};
    }*/
};