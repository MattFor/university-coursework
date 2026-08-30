//
// Created by MattFor on 23/04/2025.
//

#pragma once

#ifdef SOUNDLIBRARY_EXPORTS
#define SOUNDLIB_API __declspec(dllexport)
#else
#define SOUNDLIB_API __declspec(dllimport)
#endif

extern "C" SOUNDLIB_API void playTone(float value, int duration_ms);
