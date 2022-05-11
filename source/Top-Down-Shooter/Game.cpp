#include <iostream>

#include <SDL.h>

#include "Game.hpp"

Window *gWindow = NULL;
bool gQuit = false;

Game::Game()
{
    gWindow = new Window();
    if(!gWindow->init())
    {
        std::cout << "Failed to initialize window" << std::endl;
        gQuit = true;
        return;
    }
    stateManager = new StateManager();
    gQuit = false;
}

Game::~Game()
{
}

void Game::run()
{   
    
	stateManager->switchScreen(StateManager::Screen::StartScreen);
    Uint32 deltaTime = SDL_GetTicks();
	while (!gQuit)
    {
		processInput();
		update((SDL_GetTicks() - deltaTime)/1000.0f);
        deltaTime = SDL_GetTicks();
		render();
	}
}

void Game::processInput()
{
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0)
    {
        if(e.type == SDL_QUIT)
        {
            gQuit = true;
        }
        else
        {
            stateManager->currentScreen->handleEvent(e);
        }
    }
}

void Game::update(float deltaTime)
{
    stateManager->currentScreen->updateScreen(deltaTime);
}

void Game::render()
{
    gWindow->clear();
    renderScreen();
    gWindow->present();
}

void Game::renderScreen()
{
    stateManager->currentScreen->renderScreen();
}