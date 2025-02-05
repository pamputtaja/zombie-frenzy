#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Score.hpp"
#include "Utils.hpp"
#include "Math.hpp"

Score::Score(std::string p_font)
    : color(WHITE), score(0)
{
    font = TTF_OpenFont(p_font.c_str(), 64);
    if (!font) {
        std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
    }
}

Score::~Score() 
{
    TTF_CloseFont(font);
}

void Score::incScore(Pumpkin& p_pumpkin, Character& p_player) 
{
    std::vector<Entity> &pumpkins = p_pumpkin.getPumpkins();
    for( unsigned int i = 0; i < pumpkins.size(); i++ ) {
        if( utils::checkCollision( pumpkins.at(i).getRect(), p_player.getRect() ) ) {
            score += 1;
            pumpkins.at(i).setPosition( Coord( 3000, 600 ) );
        }
    }
} 

void Score::render(RenderWindow& p_window) 
{
    std::string scoreText = "Score: " + std::to_string(score);
    SDL_Texture* textTexture = createTextTexture(p_window, scoreText);
    SDL_Rect textRect = { 10, 10, 0, 0 };
    SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
    SDL_RenderCopy(p_window.getRenderer(), textTexture, NULL, &textRect);
    SDL_DestroyTexture(textTexture);
}

SDL_Texture* Score::createTextTexture(RenderWindow& p_window, const std::string& text) 
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(p_window.getRenderer(), textSurface);
    SDL_FreeSurface(textSurface);
    return textTexture;
}