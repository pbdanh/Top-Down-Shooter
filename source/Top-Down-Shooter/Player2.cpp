#include "Player2.hpp"

Player2::Player2(double posX_, double posY_, double degree_) : Player(posX_, posY_, degree_)
{
    playerTexture = AssetManager::getInstance()->getTexture("p2.png");
    playerNumber = 2;
}

Player2::~Player2()
{
}

void Player2::handleEvent(const SDL_Event& event)
{
    if(event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_LEFT:
                angularVelocity -= maxAngularVelocity;
                break;
            case SDLK_RIGHT:
                angularVelocity += maxAngularVelocity;
                break;
            case SDLK_UP:
                moveState = (MoveState)((int)moveState + 1);
                break;
            case SDLK_DOWN:
                moveState = (MoveState)((int)moveState - 1);
                break;
            case SDLK_KP_ENTER:
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
                break;        }
    }
    else
    {
        if(event.type == SDL_KEYUP && event.key.repeat == 0)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_LEFT:
                    angularVelocity += maxAngularVelocity;
                    break;
                case SDLK_RIGHT:
                    angularVelocity -= maxAngularVelocity;
                    break;
                case SDLK_UP:
                    moveState = (MoveState)((int)moveState - 1);
                    break;
                case SDLK_DOWN:
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