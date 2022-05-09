#pragma once

#include "GameScreen.hpp"
#include "Window.hpp"

extern Window* gWindow;

class StartScreen : public GameScreen
{
public:
    StartScreen(StateManager* stateManager);
    ~StartScreen();
    void renderScreen();
    void updateScreen(float deltaTime);
    void handleEvent(const SDL_Event& event);
private:
    SDL_Texture* button;
    SDL_Texture* logo;
    SDL_Texture* textStart;
    SDL_Texture* background;
    void loadMedia();
};