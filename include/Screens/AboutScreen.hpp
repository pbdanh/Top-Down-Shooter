#pragma once

#include <functional>
#include "GameScreen.hpp"

class AboutScreen : public GameScreen
{
public:
    AboutScreen(StateManager* stateManager);
    ~AboutScreen();
    void handleEvent(const SDL_Event& event);
    void renderScreen();
    void updateScreen(float deltaTime);
private:
    void createGUI();
    void goToMenu();
    void goToGame();
    double timePauseMusic;
};