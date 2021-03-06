#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include <array>

#include "Entity.hpp"

class Text : public Entity
{
public:
    Text(std::string texText, std::array<int, 4> textColour, std::string fontFile, unsigned int fontSize, std::array<int, 4> src, std::array<int, 2> dst, SDL_Renderer* renderer);
    Text(std::string texText, std::array<int, 4> textColour, TTF_Font* font, unsigned int fontSize, std::array<int, 4> src, std::array<int, 2> dst, SDL_Renderer* renderer);
    void closeFont();

    TTF_Font* getFont();
    void changeText(std::string newText);
protected:
    TTF_Font* font = nullptr;
    std::string texText;
    SDL_Color textColour;
    std::string fontFile;
    unsigned int fontSize;
    
};