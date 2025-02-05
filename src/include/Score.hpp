#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "RenderWindow.hpp"
#include "Character.hpp"
#include "Pumpkin.hpp"

#define BLUE { 0, 0, 255, 255 }
#define RED { 255, 0, 0, 255 }
#define GREEN { 0, 255, 0, 255 }
#define WHITE { 255, 255, 255, 255 }
#define BLACK { 0, 0, 0, 255 }

class Score {
public:
    Score(std::string p_font);
    ~Score();
    void incScore( Pumpkin& p_pumpkin, Character& p_player );
    void render(RenderWindow& p_window);
private:
    TTF_Font* font;
    SDL_Color color;
    int score;
    SDL_Texture* createTextTexture(RenderWindow& p_window, const std::string& text);
};