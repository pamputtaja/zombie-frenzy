#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "RenderWindow.hpp"
#include "Math.hpp"
#include "Entity.hpp"

class Character
{
public:
    Character( RenderWindow &p_window, SDL_Texture *p_texture, Coord p_position, int p_w, int p_h );
    ~Character();

    void handleInput( const Uint8 *state, float deltaTime );
    void update( float deltaTime);
    void render(RenderWindow &p_window);
    SDL_Rect getRect();
private:
    SDL_Texture *texture;
    Entity character;

    bool isMoving = true;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    Coord currentFrame = Coord(0, 1);
    float frameTime = 0.0f;
    float animationSpeed = 0.1f;
    void animate();

    float velocityY = 0.0f;
    bool isJumping = false;
};