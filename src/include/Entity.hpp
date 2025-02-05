#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Math.hpp"

class Entity
{
public:
    Entity( Coord p_position, SDL_Texture *p_texture, float p_w, float p_h );
    ~Entity();

    SDL_Rect getRect();

    Coord &getPosition() { return position; }
    void setPosition( Coord p_position ) { position = p_position; }
    SDL_Texture *getTexture() { return texture; }
    SDL_Rect getCurrentFrame() { return currentFrame; }
    float getW() { return w; };
    float getH() { return h; };
private:
    Coord position;
    SDL_Rect currentFrame;
    SDL_Texture *texture;
    float w, h;
};