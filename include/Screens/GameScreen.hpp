#pragma once

#include "SDL.h"
#include "StateManager.hpp"

class GameScreen
{
public:
    GameScreen();
    GameScreen(StateManager* stateManager);
    virtual ~GameScreen();
    virtual void renderScreen();
	virtual void updateScreen(float deltaTime) = 0;

    //TODO: remove
    virtual void loadMedia();
    virtual void handleEvent(const SDL_Event& event);

protected:
    StateManager* stateManager;
};