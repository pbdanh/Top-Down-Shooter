#include "GamePVP.hpp"

GamePVP::GamePVP(StateManager* stateManager) : GameScreen(stateManager)
{   
    createPlayers();
}

GamePVP::~GamePVP()
{
}

void GamePVP::renderScreen()
{
    for (auto player : players)
    {
        player->render();
    }
}

void GamePVP::updateScreen(float deltaTime)
{
    for (auto player : players)
    {
        player->update(deltaTime);
    }
}

void GamePVP::handleEvent(const SDL_Event& event)
{
    for (auto player : players)
    {
        player->handleEvent(event);
    }
}

void GamePVP::createPlayers()
{
    players.push_back(new Player1(100, 100, 0));
    players.push_back(new Player2(1100, 700, 180));
}