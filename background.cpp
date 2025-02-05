#include <SDL2/SDL.h>
#include "Background.hpp"

Background::Background( RenderWindow &p_window, SDL_Texture *p_texture, int p_w, int p_h )
    : texture( p_texture ), width( p_w ), height( p_h )
{
    position1 = Coord( 0.0, 0 );
    position2 = Coord( width, 0 );
}

Background::~Background()
{
}

void Background::update(float deltaTime, float speed)
{
    position1.x -= speed * deltaTime;
    position2.x -= speed * deltaTime;

    if (position1.x + width < 0) {
        position1.x = position2.x + width;
    }
    if (position2.x + width < 0) {
        position2.x = position1.x + width;
    }
}

void Background::render(RenderWindow &p_window)
{
    SDL_Rect srcRect = { 0, 0, width, height };
    SDL_Rect dstRect1 = { position1.x, position1.y, width, height };
    SDL_Rect dstRect2 = { position2.x, position2.y, width, height };

    p_window.render(texture, &srcRect, &dstRect1);
    p_window.render(texture, &srcRect, &dstRect2);
}