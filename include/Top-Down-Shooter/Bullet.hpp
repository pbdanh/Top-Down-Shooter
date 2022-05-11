#pragma once

#include <cmath>

#include <SDL.h>

#include "Window.hpp"
#include "AssetManager.hpp"

extern Window* gWindow;

class Bullet
{
public:
    Bullet(double posX_, double posY_, double degree_);
    ~Bullet();
    void render();
    void update(float deltaTime);
private:
    SDL_Texture* bulletTexture;
    double posX, posY;
    double degree;
    const double velocity = 3;
};