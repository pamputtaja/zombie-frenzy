#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <cmath>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Math.hpp"
#include "Utils.hpp"
#include "Character.hpp"
#include "Pumpkin.hpp"
#include "Score.hpp"
#include "Settings.hpp"
#include "Background.hpp"


int main( int argc, char *argv[] )
{
    if ( SDL_Init( SDL_INIT_VIDEO ) != 0) {
        std::cout << "SDL_INIT_VIDEO Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    if ( !IMG_Init( IMG_INIT_PNG ) ) {
        std::cout << "IMG_INIT_PNG Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    if ( !IMG_Init( IMG_INIT_JPG ) ) {
        std::cout << "IMG_INIT_JPG Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    if (TTF_Init() != 0) {
        std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
        return 1;
    }

    RenderWindow *window = new RenderWindow( "ZOMBIE FRENZY 0.2", SCREEN_WIDTH, SCREEN_HEIGHT );

    SDL_Texture *groundTexture = window->loadTexture( "res/gfx/spookyground.png" );
    SDL_Texture *bg = window->loadTexture( "res/gfx/spooky_bg.png" );
    SDL_Texture *bgLayer_1 = window->loadTexture( "res/gfx/spooky_bg_layer.png" );
    SDL_Texture *bgLayer_2 = window->loadTexture( "res/gfx/own_layer.png" );
    SDL_Texture *playerTexture = window->loadTexture( "res/gfx/walking_animated.png" );
    SDL_Texture *pumpkinTexture = window->loadTexture( "res/gfx/pumpkin.png" );

    Background backGround( *window, bg, 2160, 1080 );
    Background backGroundLayer_1( *window, bgLayer_1, 2160, 1080 );
    Background backGroundLayer_2( *window, bgLayer_2, 2160, 1080 );
    Character player( *window, playerTexture, Coord( START_LOC, GROUND_BASE-PLAYER_HEIGHT ), PLAYER_WIDTH, PLAYER_HEIGHT );
    Score score( SCORE_FONT );

    Pumpkin pumpkin( pumpkinTexture, 117, 117 );


    std::vector<Entity> bottomGround;
    for (int i = 0; i < std::ceil(SCREEN_WIDTH/TILE_SIZE); i++) {
        Entity ground( Coord(i*TILE_SIZE, SCREEN_HEIGHT-TILE_SIZE), groundTexture, TILE_SIZE, TILE_SIZE );
        bottomGround.push_back(ground);
    }

    bool gameRunning = true;
    SDL_Event event;

    const float timeStep = 0.01;
    float accumulator = 0.0;
    float currentTime = utils::hireTimeInSeconds();
    const Uint8* state;

    while( gameRunning )
    {
        int startTicks = SDL_GetTicks();
        float newTime = utils::hireTimeInSeconds();
        float frameTime = newTime - currentTime;
        currentTime = newTime;
        accumulator += frameTime;

        while( accumulator >= timeStep ) 
        {
            while( SDL_PollEvent( &event ) )
            {
                if( event.type == SDL_QUIT ) { gameRunning = false; }
            }
            player.handleInput( SDL_GetKeyboardState( NULL ), timeStep*GAME_SPEED );
            player.update( timeStep );
            pumpkin.update( timeStep, GAME_SPEED );
            score.incScore( pumpkin, player );

            backGround.update(timeStep, GAME_SPEED/8);
            backGroundLayer_1.update(timeStep, GAME_SPEED/4);
            backGroundLayer_2.update(timeStep, GAME_SPEED/2);
            accumulator -= timeStep;
        }
        const float alpha = accumulator / timeStep;

        window->clearWindow();
        backGround.render( *window );
        backGroundLayer_1.render( *window );
        backGroundLayer_2.render( *window );

        for( Entity &e : bottomGround ) {
            window->render( e );
        }
        
        player.render( *window );
        pumpkin.render( *window );
        score.render( *window );

        window->display();
        int frameTicks = SDL_GetTicks() - startTicks;
        if( frameTicks < 1000 / window->getRefreshRate()) {
            SDL_Delay( ( 1000 / window->getRefreshRate() ) - frameTicks );
        }
    }


    SDL_DestroyTexture( groundTexture );
    SDL_DestroyTexture( playerTexture );
    SDL_DestroyTexture( pumpkinTexture );
    SDL_DestroyTexture( bg );
    SDL_DestroyTexture( bgLayer_1 );
    SDL_DestroyTexture( bgLayer_2 );
    delete window;
    
    SDL_Quit();
    return 0;
}