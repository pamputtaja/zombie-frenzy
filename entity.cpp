#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Entity.hpp"

Entity::Entity( Coord p_position, SDL_Texture *p_texture, float p_w, float p_h )
    :texture( p_texture ), position( p_position ), w( p_w ), h( p_h )
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = p_w;
    currentFrame.h = p_h;
}

Entity::~Entity()
{
}

SDL_Rect Entity::getRect()
{
    SDL_Rect rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.w = w;
    rect.h = h;
    return rect;
}