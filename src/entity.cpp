#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <array>

#include "Entity.hpp"
#include "Animations.hpp"

Entity::Entity(std::string texFile, std::array<int, 4> src, std::array<int, 2> dst, SDL_Renderer* renderer)
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

    this->src->x = src[0];
    this->src->y = src[1];
    this->src->w = src[2];
    this->src->h = src[3];

    this->dst->x = dst[0];
    this->dst->y = dst[1];
    this->dst->w = src[2];
    this->dst->h = src[3];
}

Entity::Entity(std::string texFile, std::nullptr_t, SDL_Renderer* renderer)
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
    this->src = nullptr;
    this->dst = nullptr;
}

Entity::Entity() {}

void Entity::close()
{
    SDL_DestroyTexture(this->tex);
    this->tex = nullptr;
    delete this->src;
    delete this->dst;
}

SDL_Rect* Entity::getSrcRect()
{   
    return src;
}

SDL_Rect* Entity::getDstRect()
{   
    return dst;
}

SDL_Texture* Entity::getTex()
{
    return tex;
}

void Entity::setColour(uint8_t r, uint8_t g, uint8_t b)
{
    SDL_SetTextureColorMod(this->tex, r, g, b);
}

void Entity::setBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(this->tex, blending);
}

void Entity::setAlpha(uint8_t alpha)
{
    SDL_SetTextureAlphaMod(this->tex, alpha);
}


void Entity::setPos(std::array<int, 2> pos)
{
    this->dst->x = pos[0];
    this->dst->y = pos[1];
}

void Entity::setSrc(std::array<int, 4> src)
{
    this->src->x = src[0];
    this->src->y = src[1];
    this->src->w = src[2];
    this->src->h = src[3];

    this->dst->w = src[2];
    this->dst->h = src[3];
}

void Entity::setMoveSpeed(int moveSpeed)
{
    this->moveSpeed = moveSpeed;
}

void Entity::activateBorderCollision(const unsigned int &width, const unsigned int &height)
{
    if (this->dst->x < 0)
        this->dst->x += this->moveSpeed;

    if (this->dst->x + this->src->w > static_cast<int>(width))
        this->dst->x -= this->moveSpeed;

    if (this->dst->y < 0)
        this->dst->y += this->moveSpeed;

    if (this->dst->y + this->src->h > static_cast<int>(height))
        this->dst->y -= this->moveSpeed;
}

bool Entity::collisionWithRect(SDL_Rect* rect)
{
    std::array<int, 2> topLeft = {this->dst->x, this->dst->y};
    std::array<int, 2> topRight = {this->dst->x + this->dst->w, this->dst->y};
    std::array<int, 2> bottomLeft = {this->dst->x, this->dst->y + this->dst->h};
    std::array<int, 2> bottomRight = {this->dst->x + this->dst->w, this->dst->y + this->dst->h};

    std::array<int, 2> rectTopLeft = {rect->x, rect->y};
    std::array<int, 2> rectTopRight = {rect->x + rect->w, rect->y};
    std::array<int, 2> rectBottomRight = {rect->x + rect->w, rect->y + rect->h};

    if (((topLeft[0] >= rectTopLeft[0]) && (topLeft[0] <= rectTopRight[0])) && 
        ((topLeft[1] >= rectTopLeft[1]) && (topLeft[1] <= rectBottomRight[1]))
        )
        return true;
    else if (((topRight[0] >= rectTopLeft[0]) && (topRight[0] <= rectTopRight[0])) && 
        ((topRight[1] >= rectTopLeft[1]) && (topRight[1] <= rectBottomRight[1]))
        )
        return true;
    else if (((bottomLeft[0] >= rectTopLeft[0]) && (bottomLeft[0] <= rectTopRight[0])) && 
        ((bottomLeft[1] >= rectTopLeft[1]) && (bottomLeft[1] <= rectBottomRight[1]))
        )
        return true;
    else if (((bottomRight[0] >= rectTopLeft[0]) && (bottomRight[0] <= rectTopRight[0])) && 
        ((bottomRight[1] >= rectTopLeft[1]) && (bottomRight[1] <= rectBottomRight[1]))
        )
        return true;
    return false;
}

void Entity::move(std::array<int, 2> direction)
{
    this->dst->x += direction[0] * this->moveSpeed;
    this->dst->y += direction[1] * this->moveSpeed;
}

void Entity::animate(Animation &animation)
{
    this->setSrc(
        {animation.getSprites()[animationIterator].x, animation.getSprites()[animationIterator].y,
         animation.getSprites()[animationIterator].w, animation.getSprites()[animationIterator].h}
    );

    this->animationIterator++;

    if (animationIterator == animation.getSprites().size() - 1)
        this->animationIterator = 0;
}