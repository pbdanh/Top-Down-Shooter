#pragma once

#include <functional>
#include "GameScreen.hpp"

class SettingScreen : public GameScreen
{
public:
    SettingScreen(StateManager* stateManager);
    ~SettingScreen();
    void handleEvent(const SDL_Event& event);
    void renderScreen();
    void updateScreen(float deltaTime);
private:
    void createGUI();
    void goToMenu();
    void goToGame();
    void increaseTime();
    void decreaseTime();
    void selectMap1();
    void selectMap2();
    void increaseMaxScore();
    void decreaseMaxScore();
};