#pragma once

#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "Window.hpp"

extern Window* gWindow;

class AssetManager
{
public:
    static SDL_Texture* getTexture(const std::string & filename);
private:
};