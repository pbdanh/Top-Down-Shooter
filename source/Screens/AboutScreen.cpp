#include "AboutScreen.hpp"

AboutScreen::AboutScreen(StateManager* stateManager) : GameScreen(stateManager)
{
    createGUI();
}

AboutScreen::~AboutScreen()
{
}

void AboutScreen::renderScreen()
{
    SDL_RenderCopy(gWindow->getRenderer(), AssetManager::getInstance()->getTexture("about_screen_background.png"), NULL, NULL);
    renderWidget();
    //render author
    {
        SDL_Texture *text;
        text = AssetManager::getInstance()->getTexture("PhamBaDanh.png");
        SDL_Rect rect;
        SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
        rect.x = SCREEN_WIDTH/2 - rect.w/2;
        rect.y = SCREEN_HEIGHT - 20;
        SDL_RenderCopy(gWindow->getRenderer(), text, NULL, &rect);
    }
}

void AboutScreen::updateScreen(float deltaTime)
{
}

void AboutScreen::handleEvent(const SDL_Event& event)
{
    handleWidgetEvent(event);
}

void AboutScreen::createGUI()
{
    createButton("button_home.png", {1230, 752}, std::bind(&AboutScreen::goToMenu, this));
}

void AboutScreen::goToMenu()
{
    stateManager->switchScreen(StateManager::Screen::StartScreen);
}

