//
// Created by MattFor on 23/04/2025.
//

#include <thread>
#include <windows.h>
#include <algorithm>

#include "../include/SOUNDLIB.hpp"

void playTone(const int value, const int duration_ms)
{
    if (duration_ms < 0)
    {
        return;
    }

    std::thread([value, duration_ms]
    {
        constexpr int minFrequency = 1;
        constexpr int maxFrequency = 5000;

        int frequency = minFrequency + value * (maxFrequency - minFrequency) / 120;
        frequency     = std::clamp(frequency, minFrequency, maxFrequency);

        Beep(frequency, std::max(duration_ms, 10));
    }).detach();
}

void playTone(const float value, const int duration_ms)
{
    playTone(static_cast<int>(value), duration_ms);
}
