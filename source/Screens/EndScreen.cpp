#include "EndScreen.hpp"

EndScreen::EndScreen(StateManager* stateManager) : GameScreen(stateManager)
{
    
}

EndScreen::~EndScreen()
{
}

void EndScreen::renderScreen()
{
    if(stateManager->p1Score > stateManager->p2Score)
    {
        std::cout << "Player 1 wins!" << std::endl;
    }
    else if(stateManager->p1Score < stateManager->p2Score)
    {
        std::cout << "Player 2 wins!" << std::endl;
    }
    else
    {
        std::cout << "It's a draw!" << std::endl;
    }
}

void EndScreen::updateScreen(float deltaTime)
{
}
