#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"

RenderWindow::RenderWindow( const char* p_title, int p_w, int p_h )
    :window( NULL ), renderer( NULL )
{
    window = SDL_CreateWindow( p_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, p_w, p_h, SDL_WINDOW_ALLOW_HIGHDPI );
    if( window == NULL )
    {
        std::cout << "Window init failed: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
}

RenderWindow::~RenderWindow()
{
    SDL_DestroyWindow( window );
}

SDL_Texture *RenderWindow::loadTexture( const char* p_filePath )
{
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture( renderer, p_filePath );
    if( texture == NULL )
    {
        std::cout << "Failed to load texture: " << SDL_GetError() << std::endl;
    }
    return texture;
}

int RenderWindow::getRefreshRate()
{
    int displayIndex = SDL_GetWindowDisplayIndex( window );
    SDL_DisplayMode mode;
    SDL_GetDisplayMode( displayIndex, 0, &mode );
    return mode.refresh_rate;
}

void RenderWindow::clearWindow()
{
    SDL_RenderClear( renderer );
}

void RenderWindow::render( SDL_Texture* p_texture, SDL_Rect* src, SDL_Rect* dst, SDL_RendererFlip p_flip)
{
    SDL_RenderCopyEx( renderer, p_texture, src, dst, 0, NULL, p_flip );
}

void RenderWindow::render( Entity &p_entity )
{
    SDL_Rect src;
    src.x = p_entity.getCurrentFrame().x; 
    src.y = p_entity.getCurrentFrame().y;
    src.w = p_entity.getCurrentFrame().w;
    src.h = p_entity.getCurrentFrame().h;

    SDL_Rect dst;
    dst.w = p_entity.getCurrentFrame().w;
    dst.h = p_entity.getCurrentFrame().h;
    dst.x = p_entity.getPosition().x;
    dst.y = p_entity.getPosition().y;


    SDL_RenderCopy( renderer, p_entity.getTexture(), &src, &dst );
}

void RenderWindow::display()
{
    SDL_RenderPresent( renderer );
}

void RenderWindow::renderImage( SDL_Surface *p_surface )
{
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = 2160;
    src.h = 1080;

    SDL_Rect dst;
    dst.x = 0;
    dst.y = 0;
    dst.w = 2160;
    dst.h = 1080;


    SDL_Texture *texture = SDL_CreateTextureFromSurface( renderer, p_surface );

    SDL_RenderCopy( renderer, texture, &src, &dst );
    SDL_DestroyTexture( texture );
}

SDL_Renderer *RenderWindow::getRenderer()
{
    return renderer;
}