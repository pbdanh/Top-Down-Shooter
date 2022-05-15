#pragma once

#include "Player.hpp"
#include "AssetManager.hpp"

class Player1: public Player
{
public:
    Player1(double posX_, double posY_, double degree_);
    ~Player1();
    void handleEvent(const SDL_Event& event);
    void reset();
private:
    bool isADown;
    bool isDDown;
    bool isWDown;
    bool isSDown;
    bool isMDown;
    bool isKP0Down;
};