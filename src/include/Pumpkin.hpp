#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "RenderWindow.hpp"
#include "Math.hpp"
#include "Entity.hpp"
#include "Settings.hpp"
#include "Utils.hpp"

class Pumpkin
{
public:
    Pumpkin( SDL_Texture *p_texture, float p_w, float p_h );
    ~Pumpkin();

    void update( float deltaTime, float speed );
    void render( RenderWindow& p_window );
    
    unsigned int getLength() { return pumpkins.size(); }
    std::vector<Entity>& getPumpkins() { return pumpkins; }
private:
    std::vector<Entity> pumpkins;

};