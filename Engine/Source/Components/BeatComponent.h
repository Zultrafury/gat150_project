#pragma once


class BeatComponent
{
public:
    virtual ~BeatComponent() = default;
    BeatComponent() = default;

    virtual void OnBeat()
    {
        
    }
};