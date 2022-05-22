#pragma once

#include <SDL.h>

#include "Window.hpp"
#include "AssetManager.hpp"

extern Window* gWindow;

class Item
{
public:
    Item(double posX_, double posY_);
    ~Item();
    void render();
    SDL_Rect getRect();
private:
    SDL_Texture* ItemTexture;
    SDL_Rect rect;
};