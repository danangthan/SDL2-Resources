#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

#include "Entity.hpp"

Entity::Entity(std::string texFile, SDL_Renderer* renderer)
    :texFile(texFile), renderer(renderer)
{
    SDL_Surface* loadedSurface = IMG_Load(this->texFile.c_str());
    if (loadedSurface == nullptr)
        std::cout << "(Entity) Unable to load image! SDL_image Error: " << IMG_GetError() << std::endl;
    else
    {
        this->tex = SDL_CreateTextureFromSurface(this->renderer, loadedSurface);
        if (this->tex == nullptr)
            std::cout << "(Entity) Unable to create texture from image! SDL_image Error: " << IMG_GetError() << std::endl;
        
        this->texWidth = loadedSurface->w;
        this->texHeight = loadedSurface->h;

        SDL_FreeSurface(loadedSurface);
    }
}

Entity::~Entity()
{
    SDL_DestroyTexture(this->tex);
    this->tex = nullptr;
}
