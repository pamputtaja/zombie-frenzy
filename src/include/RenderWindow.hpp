#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Entity.hpp"

class RenderWindow
{
public:
    RenderWindow( const char* p_title, int p_w, int p_h );
    ~RenderWindow();

    SDL_Texture *loadTexture( const char* p_filePath );

    int getRefreshRate();

    void clearWindow();
    void render(SDL_Texture* p_texture, SDL_Rect* src, SDL_Rect* dst, SDL_RendererFlip p_flip = SDL_FLIP_NONE);
    void render( Entity &p_entity );
    void display();
    void renderImage( SDL_Surface *p_surface );
    SDL_Renderer *getRenderer();
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
};
