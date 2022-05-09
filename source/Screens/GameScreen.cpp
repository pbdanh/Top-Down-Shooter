#include "GameScreen.hpp"
#include <iostream>//TODO: remove
GameScreen::GameScreen()
{
}

GameScreen::GameScreen(StateManager * stateManager) :
	stateManager(stateManager)
{
}

GameScreen::~GameScreen()
{
}

void GameScreen::renderScreen()
{
}

void GameScreen::updateScreen(float deltaTime)
{
}

void GameScreen::loadMedia()
{
}

void GameScreen::handleEvent(const SDL_Event & event)
{
}