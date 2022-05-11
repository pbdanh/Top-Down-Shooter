#pragma once

#include "Player.hpp"
#include "AssetManager.hpp"

class Player1: public Player
{
public:
    Player1(double posX_, double posY_, double degree_);
    ~Player1();
    void handleEvent(const SDL_Event& event);
};