#pragma once

#include <vector>

#include "GameScreen.hpp"
#include "Player.hpp"
#include "Player1.hpp"
#include "Player2.hpp"


extern Window* gWindow;
extern bool gDevMode;

class GamePVP : public GameScreen
{
public:
    GamePVP(StateManager* stateManager);
    ~GamePVP();
    void renderScreen();
    void updateScreen(float deltaTime);
    void handleEvent(const SDL_Event& event);
private:
    int** map;
    Player1* player1;
    Player2* player2;
    void createGUI();
    void goToMenu();
    double timeOut;
    double startingTime;
    int maxScore;
};