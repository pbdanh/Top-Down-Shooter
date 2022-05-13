#pragma once

#include "GameScreen.hpp"

class EndScreen : public GameScreen
{
public:
    EndScreen(StateManager* stateManager);
    ~EndScreen();
    //void handleEvent(const SDL_Event& event);
    void renderScreen();
    void updateScreen(float deltaTime);
private:
};