#pragma once

#include <vector>

#include "GameScreen.hpp"
#include "Player.hpp"
#include "Player1.hpp"
#include "Player2.hpp"


extern Window* gWindow;

class GamePVP : public GameScreen
{
public:
    GamePVP(StateManager* stateManager);
    ~GamePVP();
    void renderScreen();
    void updateScreen(float deltaTime);
    void handleEvent(const SDL_Event& event);
private:
    std::vector<Player*> players;
    void createGUI();
    void createPlayers();
    void goToMenu();
};