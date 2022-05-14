#include "StateManager.hpp"
#include "GameScreen.hpp"
#include "StartScreen.hpp"
#include "GamePVP.hpp"
#include "EndScreen.hpp"

#include <iostream> //TODO:remove

StateManager::StateManager()
{
	isSoundOn = true;
}

StateManager::~StateManager()
{
	delete currentScreen;
	delete nextScreen;
}

void StateManager::switchScreen(Screen newScreen)
{
	if (nextScreen != nullptr)
	{
		//delete nextScreen;
		nextScreen = nullptr;
	}
	switch (newScreen)
	{
	case Screen::StartScreen:
		nextScreen = new StartScreen(this);
		break;
	case Screen::GamePVP:
		nextScreen = new GamePVP(this);
		break;
	case Screen::EndScreen:
		nextScreen = new EndScreen(this);
		break;
	default:
		break;
	}

	if (nextScreen != nullptr)
	{
		std::swap(currentScreen, nextScreen);
	}
}

