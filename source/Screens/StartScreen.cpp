#include <SDL_image.h>

#include "StartScreen.hpp"

extern bool gQuit;

StartScreen::StartScreen(StateManager* stateManager) : GameScreen(stateManager)
{
    background = AssetManager::getInstance()->getTexture("start_screen_background.png");
    createGUI();
}

StartScreen::~StartScreen()
{
}

void StartScreen::renderScreen()
{
    SDL_RenderCopy(gWindow->getRenderer(), background, NULL, NULL);
    for(auto& component : GUIComponents)
    {
        component->render(gWindow->getRenderer());
    }
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
    createButton("button_music_off.png", {1200, 20}, [](){});
}

void StartScreen::createButton(const std::string fileName, SDL_Point position, std::function<void()> callback)
{
    GUIComponent* button = new Button(fileName, position, callback);
    GUIComponents.push_back(button);
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