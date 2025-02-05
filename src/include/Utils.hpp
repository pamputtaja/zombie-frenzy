#pragma once
#include <SDL2/SDL.h>

namespace utils
{
    inline float hireTimeInSeconds()
    {
        float t = SDL_GetTicks();
        return t/1000;
    }

    inline bool checkCollision(const SDL_Rect &a, const SDL_Rect &b)
    {
        return (a.x < b.x + b.w &&
                a.x + a.w > b.x &&
                a.y < b.y + b.h &&
                a.y + a.h > b.y);
    }
}