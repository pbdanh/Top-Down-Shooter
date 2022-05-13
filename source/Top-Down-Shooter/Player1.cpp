#include "Player1.hpp"

Player1::Player1(double posX_, double posY_, double degree_) : Player(posX_, posY_, degree_)
{
    playerTexture = AssetManager::getInstance()->getTexture("p1.png");
    playerNumber = 1;
}

Player1::~Player1()
{
}

void Player1::handleEvent(const SDL_Event& event)
{
    if(event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_a:
                angularVelocity -= maxAngularVelocity;
                break;
            case SDLK_d:
                angularVelocity += maxAngularVelocity;
                break;
            case SDLK_w:
                moveState = (MoveState)((int)moveState + 1);
                break;
            case SDLK_s:
                moveState = (MoveState)((int)moveState - 1);
                break;
            case SDLK_SPACE:
                if(isAlive)
                {
                    shoot();
                }
                break;
            case SDLK_m:
                showScore += 1;
                break;
            case SDLK_KP_0:
                showScore += 1;
                break;
        }
    }
    else
    {
        if(event.type == SDL_KEYUP && event.key.repeat == 0)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_a:
                    angularVelocity += maxAngularVelocity;
                    break;
                case SDLK_d:
                    angularVelocity -= maxAngularVelocity;
                    break;
                case SDLK_w:
                    moveState = (MoveState)((int)moveState - 1);
                    break;
                case SDLK_s:
                    moveState = (MoveState)((int)moveState + 1);
                    break;
                case SDLK_m:
                showScore -= 1;
                break;
            case SDLK_KP_0:
                showScore -= 1;
                break;
            }
        }
    }
}