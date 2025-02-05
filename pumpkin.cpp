#include "Pumpkin.hpp"


Pumpkin::Pumpkin(SDL_Texture* p_texture, float p_w, float p_h )
{
    for( int i = 0; i < NUMBER_OF_PUMPKINS; i++ ) {
        Coord pos;
        pos.x = i * SCREEN_WIDTH / NUMBER_OF_PUMPKINS + SCREEN_WIDTH + 100;
        pos.y = 600;
        Entity newPumpkin( Coord( pos ), p_texture, 117, 117 );
        pumpkins.push_back( newPumpkin );
    }
}

Pumpkin::~Pumpkin() 
{
    pumpkins.clear();
}

void Pumpkin::update(float deltaTime, float speed ) 
{
    for( unsigned int i = 0; i < pumpkins.size(); i++ ) {
        Coord pos = pumpkins.at( i ).getPosition();
        Coord prev;
        if( i == 0) {
            prev = pumpkins.at( pumpkins.size()-1 ).getPosition();
        } else {
            prev = pumpkins.at( i-1 ).getPosition();
        }
        pos.x -= speed * deltaTime;
        if ( pos.x + pumpkins.at(i).getW() < 0 ) {
            pos.x = prev.x + SCREEN_WIDTH/NUMBER_OF_PUMPKINS + 100;
        }
        pumpkins.at( i ).setPosition( pos );
    }
}

void Pumpkin::render(RenderWindow& p_window)
{
    for( Entity &pumpkin : pumpkins ) {
        p_window.render( pumpkin );
    }
}