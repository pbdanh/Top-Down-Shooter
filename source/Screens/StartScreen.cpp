#include <SDL_image.h>

#include "StartScreen.hpp"

extern bool gQuit;

StartScreen::StartScreen(StateManager* stateManager) : GameScreen(stateManager)
{
    createGUI();
}

StartScreen::~StartScreen()
{
}

void StartScreen::renderScreen()
{
    //render Background
    SDL_RenderCopy(gWindow->getRenderer(), AssetManager::getInstance()->getTexture("start_screen_background.png"), NULL, NULL);
    renderWidget();
}

void StartScreen::updateScreen(float deltaTime)
{
}

void StartScreen::handleEvent(const SDL_Event& event)
{ 
    for(auto& component : GUIComponents)
    {
        component->handleEvent(event);
    }
}

void StartScreen::createGUI()
{
    createButton("button_pvp.png", {533, 400}, std::bind(&StartScreen::startPVPGame, this));
    createButton("button_pve.png", {533, 475}, std::bind(&StartScreen::startPVEGame, this));
    createButton("button_exit.png", {533, 550}, []() { gQuit = true; });
    createButton("button_music_on.png", {1200, 20}, [](){});
}

void StartScreen::startPVPGame()
{
    stateManager->switchScreen(StateManager::Screen::GamePVP);
}

void StartScreen::startPVEGame()
{
    //stateManager->switchScreen(StateManager::Screen::GamePVE);
    std::cout << "PVE game not implemented yet" << std::endl;
}

void StartScreen::exitGame()
{
    //stateManager->exitGame();
    std::cout << "Exiting game..." << std::endl;
}