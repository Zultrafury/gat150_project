#pragma once
#include <chrono>
#include <thread>

class NanoClock
{
public:
    long interval;
    std::chrono::time_point<std::chrono::steady_clock> startnano = std::chrono::high_resolution_clock::now();
    std::chrono::time_point<std::chrono::steady_clock> nextnano = std::chrono::high_resolution_clock::now();
    long nanointerval = std::chrono::duration_cast<std::chrono::nanoseconds>(nextnano-startnano).count();
    bool running = false;
    //std::thread* counterthread;

    
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

    void Check(bool& checker)
    {
        nextnano = std::chrono::high_resolution_clock::now();
        nanointerval = std::chrono::duration_cast<std::chrono::nanoseconds>(nextnano-startnano).count();
        if (nanointerval > interval)
        {
            startnano = nextnano;
            checker = true;
        }
        else
        {
            checker = false;
        }
    }

    // i tried threads :p
    
    // void Count(bool& monitor)
    // {
    //     while(running)
    //     {
    //         //monitor = Check();
    //         Check(monitor);
    //     }
    // }
    //
    // void StartCount(bool& monitor)
    // {
    //     running = true;
    //     // auto f = [this, &monitor]()
    //     // {
    //     //     while(running)
    //     //     {
    //     //         //monitor = Check();
    //     //         Check(monitor);
    //     //     }
    //     // };
    //     // counterthread = new std::thread(f);
    // }
    //
    // void StopCount()
    // {
    //     running = false;
    //     exit(0);
    // }
};
