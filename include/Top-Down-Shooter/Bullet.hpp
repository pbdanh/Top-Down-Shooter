#pragma once

#include <cmath>

#include <SDL.h>
#include <SDL_mixer.h>

#include "Window.hpp"
#include "AssetManager.hpp"

extern Window* gWindow;
extern bool gDevMode;

class Bullet
{
public:
    Bullet(double posX_, double posY_, double degree_);
    ~Bullet();
    void render();
    void update(float deltaTime);
    SDL_Point getPos();
    SDL_Point getHitBox();
    float distanceFromBegin();
private:
    SDL_Texture* bulletTexture;
    double posX, posY;
    double x0, y0;
    double degree;
    const double velocity = 600;
};