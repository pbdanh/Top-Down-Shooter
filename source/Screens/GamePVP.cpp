#include "GamePVP.hpp"

GamePVP::GamePVP(StateManager* stateManager) : GameScreen(stateManager)
{   
    createPlayers();
    createGUI();
}

GamePVP::~GamePVP()
{
}

void GamePVP::renderScreen()
{
    //render background
    SDL_RenderCopy(gWindow->getRenderer(),AssetManager::getInstance()->getTexture("game_PVP_background.png"), NULL, NULL);
    for (auto player : players)
    {
        player->render();
    }
    renderWidget();
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
    handleWidgetEvent(event);
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

void GamePVP::createGUI()
{
    createButton("button_music_on.png", {1200, 20}, [](){});
    createButton("button_home.png", {1240, 762}, std::bind(&GamePVP::goToMenu, this));
}

void GamePVP::goToMenu()
{
    stateManager->switchScreen(StateManager::Screen::StartScreen);
}