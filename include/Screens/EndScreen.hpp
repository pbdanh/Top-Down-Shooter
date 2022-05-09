#pragma once

#include "GameScreen.hpp"

class EndScreen : public GameScreen
{
public:
    EndScreen(StateManager* stateManager);
    ~EndScreen();
    void renderScreen(SDL_Renderer *renderer);
    void updateScreen(float deltaTime);
private:
};