#pragma once
#include <chrono>

class NanoClock
{
public:
    long interval;
    auto startnano = std::chrono::high_resolution_clock::now();
    auto nextnano = std::chrono::high_resolution_clock::now();
    long nanointerval = std::chrono::duration_cast<std::chrono::nanoseconds>(nextnano-startnano).count();

    NanoClock(int fps_)
    {
        interval = 1000000000/fps_;
    }
    NanoClock(float bpm_)
    {
        interval = lroundf((60/bpm_) * 1000000000.f);
    }
    NanoClock(long interval_)
    {
        interval = interval_;
    }

    bool Check()
    {
        nextnano = std::chrono::high_resolution_clock::now();
        nanointerval = std::chrono::duration_cast<std::chrono::nanoseconds>(nextnano-startnano).count();
        if (nanointerval > interval)
        {
            startnano = nextnano;
            return true;
        }
        return false;
    }
};
