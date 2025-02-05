#pragma once
#include <SDL2/SDL.h>
#include <iostream>


struct Coord {
    Coord() : x(0), y(0) {}
    Coord(int p_x, int p_y) : x(p_x), y(p_y) {}

    void print()
    {
        std::cout << x << ", " << y << std::endl;
    }

    int x, y;
    };
