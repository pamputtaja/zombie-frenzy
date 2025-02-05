#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Character.hpp"
#include "Settings.hpp"


Character::Character( RenderWindow &p_window, SDL_Texture *p_texture, Coord p_position, int p_w, int p_h )
    : character( p_position, p_texture, p_w, p_h )
{

}

Character::~Character()
{
    SDL_DestroyTexture( texture );
}

void Character::handleInput( const Uint8 *state, float deltaTime )
{
    Coord pos = character.getPosition();
    int step = static_cast<int>(deltaTime);
    if( state[ SDL_SCANCODE_SPACE ] && !isJumping )
    {
        isJumping = true;
        velocityY = JUMP_FORCE*deltaTime;
    }
    character.setPosition(pos);
}

void Character::update( float deltaTime ) {
    Coord pos = character.getPosition();

    if ( isJumping )
    {
        velocityY -= GRAVITY*deltaTime;
        pos.y -= velocityY;
        
        if ( pos.y >= (GROUND_BASE - character.getH()) )
        {
            pos.y = (GROUND_BASE - character.getH());
            isJumping = false;
        }
    }

    if ( pos.x < 0 ) pos.x = 0;
    if ( pos.x > (SCREEN_WIDTH - character.getW()) ) pos.x = SCREEN_WIDTH - character.getW();
    if ( pos.y < 0 ) pos.y = 0;
    if ( pos.y > (GROUND_BASE - character.getH()) ) pos.y = GROUND_BASE - character.getH();
    character.setPosition(pos);

    if( isMoving && !isJumping ) {
        if( (frameTime += deltaTime) > animationSpeed )
        {
            animate();
            frameTime = 0;
        }
    } else {
        currentFrame = Coord(0, 1);
    }
}

void Character::render(RenderWindow& window)
{
    SDL_Rect srcRect;
    srcRect.x = currentFrame.x * character.getW();
    srcRect.y = currentFrame.y * character.getH();
    srcRect.w = character.getW();
    srcRect.h = character.getH();
    SDL_Rect dstRect = character.getRect();
    window.render( character.getTexture(), &srcRect, &dstRect, flip );
}

SDL_Rect Character::getRect()
{
    SDL_Rect rect;
    rect.x = character.getPosition().x;
    rect.y = character.getPosition().y;
    rect.w = character.getW();
    rect.h = character.getH();
    return rect;
}

void Character::animate()
{
    if( currentFrame.x == 0 && currentFrame.y == 0 )
    {
        currentFrame.x = 1;
    }
    else if( currentFrame.x == 1 && currentFrame.y == 0 )
    {
        currentFrame.x = 0;
        currentFrame.y = 1;
    }
    else if( currentFrame.x == 0 && currentFrame.y == 1 )
    {
        currentFrame.x = 1;
    }
    else if( currentFrame.x == 1 && currentFrame.y == 1 )
    {
        currentFrame.x = 0;
        currentFrame.y = 0;
    }
}