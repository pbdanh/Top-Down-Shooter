#include <iostream>

#include <SDL.h>

#include "Game.hpp"

Window *gWindow = NULL;;

Game::Game()
{
    gWindow = new Window();
    if(!gWindow->init())
    {
        std::cout << "Failed to initialize window" << std::endl;
        quit = true;
        return;
    }
    stateManager = new StateManager();
    quit = false;
}

Game::~Game()
{
}

void Game::run()
{
	stateManager->switchScreen(StateManager::Screen::StartScreen);
	while (!quit)
	{
		processInput();
		update(200.0f / 60.0f);
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
            quit = true;
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