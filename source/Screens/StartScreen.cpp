#include <SDL_image.h>

#include "StartScreen.hpp"

StartScreen::StartScreen(StateManager* stateManager) : GameScreen(stateManager)
{
    loadMedia();
}

StartScreen::~StartScreen()
{
}

void StartScreen::renderScreen()
{
    SDL_Rect desRect;
    SDL_RenderCopy(gWindow->getRenderer(), background, NULL, NULL);
    desRect.x = 532;
    desRect.y = 400;
    desRect.w = 215;
    desRect.h = 315;
    SDL_RenderCopy(gWindow->getRenderer(), button, NULL, &desRect);
    desRect.x = 320;
    desRect.y = 100;
    desRect.w = 640;
    desRect.h = 212;
    SDL_RenderCopy(gWindow->getRenderer(), logo, NULL, &desRect);
}

void StartScreen::updateScreen(float deltaTime)
{
}

void StartScreen::loadMedia()
{
    SDL_Surface* loadedSurface = IMG_Load("media/img/button.png");
    int w, h;
    button = SDL_CreateTextureFromSurface(gWindow->getRenderer(), loadedSurface);
    SDL_QueryTexture(button, NULL, NULL, &w, &h);
    std::cout << w << " " << h << std::endl;
    if(button == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
    }
    loadedSurface = IMG_Load("media/img/logo.png");
    logo = SDL_CreateTextureFromSurface(gWindow->getRenderer(), loadedSurface);
    loadedSurface = IMG_Load("media/img/ground.png");
    background = SDL_CreateTextureFromSurface(gWindow->getRenderer(), loadedSurface);
    TTF_Font* font = TTF_OpenFont("media/fonts/arial.ttf", 500);
    font = TTF_OpenFont("media/fonts/arial.ttf", 200);
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "START", {0, 0, 0});
    textStart = SDL_CreateTextureFromSurface(gWindow->getRenderer(), textSurface);
    SDL_QueryTexture(textStart, NULL, NULL, &w, &h);
    std::cout << w << " " << h << std::endl;
}

void StartScreen::handleEvent(const SDL_Event& event)
{
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if(x >= 555 && x <= 735 && y >= 400 && y <= 487)
        {
            stateManager->switchScreen(StateManager::Screen::GamePVP);
        }
    }
}