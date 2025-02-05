#pragma once
#include <SDL2/SDL.h>
#include "RenderWindow.hpp"
#include "Math.hpp"
#include "Entity.hpp"

class Background
{
public:
    Background( RenderWindow &p_window, SDL_Texture *p_texture, int p_w, int p_h );
    ~Background();

    void update(float deltaTime, float speed);
    void render(RenderWindow &p_window);
private:
    SDL_Texture *texture;
    Coord position1;
    Coord position2;
    int width;
    int height;
};