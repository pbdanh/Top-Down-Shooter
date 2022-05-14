#include "EndScreen.hpp"

EndScreen::EndScreen(StateManager* stateManager) : GameScreen(stateManager)
{
    createGUI();
}

EndScreen::~EndScreen()
{
}

void drawRect(SDL_Renderer* renderer, SDL_Rect rect, SDL_Color color);

void EndScreen::renderScreen()
{
    //load background
    SDL_RenderCopy(gWindow->getRenderer(), AssetManager::getInstance()->getTexture("end_screen_background.bmp"), NULL, NULL);
    if(stateManager->p1Score > stateManager->p2Score)
    {
        SDL_Rect rect;
        SDL_QueryTexture(AssetManager::getInstance()->getTexture("player_1_wins.png"), NULL, NULL, &rect.w, &rect.h);
        rect.x = (SCREEN_WIDTH - rect.w)/2;
        rect.y = (SCREEN_HEIGHT - rect.h)/2;
        SDL_RenderCopy(gWindow->getRenderer(), AssetManager::getInstance()->getTexture("player_1_wins.png"), NULL, &rect);
    }
    else if(stateManager->p1Score < stateManager->p2Score)
    {
        SDL_Rect rect;
        SDL_QueryTexture(AssetManager::getInstance()->getTexture("player_2_wins.png"), NULL, NULL, &rect.w, &rect.h);
        rect.x = (SCREEN_WIDTH - rect.w)/2;
        rect.y = (SCREEN_HEIGHT - rect.h)/2;
        SDL_RenderCopy(gWindow->getRenderer(), AssetManager::getInstance()->getTexture("player_2_wins.png"), NULL, &rect);
    }
    else
    {
        SDL_Rect rect;
        SDL_QueryTexture(AssetManager::getInstance()->getTexture("draw.png"), NULL, NULL, &rect.w, &rect.h);
        rect.x = (SCREEN_WIDTH - rect.w)/2;
        rect.y = (SCREEN_HEIGHT - rect.h)/2;
        SDL_RenderCopy(gWindow->getRenderer(), AssetManager::getInstance()->getTexture("draw.png"), NULL, &rect);
    }
    renderWidget();
}

void EndScreen::updateScreen(float deltaTime)
{
}

void EndScreen::handleEvent(const SDL_Event& event)
{
    handleWidgetEvent(event);
}

void EndScreen::createGUI()
{
    createButton("button_restart.png", {555, 500}, std::bind(&EndScreen::goToGame, this));
    createButton("button_exit_for_end_screen.png", {555, 570}, []() { gQuit = true; });
    createButton("button_home.png", {1230, 752}, std::bind(&EndScreen::goToMenu, this));
}

void EndScreen::goToMenu()
{
    stateManager->switchScreen(StateManager::Screen::StartScreen);
}

void EndScreen::goToGame()
{
    stateManager->switchScreen(StateManager::Screen::GamePVP);
}

