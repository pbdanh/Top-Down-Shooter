#pragma once

#include "Player.hpp"
#include "AssetManager.hpp"

class Player2: public Player
{
public:
    Player2(double posX_, double posY_, double degree_);
    ~Player2();
    void handleEvent(const SDL_Event& event);
    void reset();
private:
    bool isLeftDown;
    bool isRightDown;
    bool isUpDown;
    bool isDownDown;
    bool isMDown;
    bool isKP0Down;
};