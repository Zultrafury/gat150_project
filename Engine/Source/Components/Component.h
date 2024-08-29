#pragma once


class Component
{
public:
    Component() = default;
    ~Component() = default;

    virtual void Draw(SDL_Renderer* renderer, int x, int y);
    virtual void Update();
};