#pragma once

#include "Window.hpp"
#include "StartScreen.hpp"

class StateManager;

class Game
{
public:
    Game();
    ~Game();
    void run();
private:
    void processInput();
    void update(float deltaTime);
    void render();

    void renderScreen();
    
    StateManager* stateManager;
};