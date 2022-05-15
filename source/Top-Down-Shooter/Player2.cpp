#include "Player2.hpp"

Player2::Player2(double posX_, double posY_, double degree_) : Player(posX_, posY_, degree_)
{
    playerTexture = AssetManager::getInstance()->getTexture("p2.png");
    playerNumber = 2;
    isLeftDown = false;
    isRightDown = false;
    isUpDown = false;
    isDownDown = false;
    isMDown = false;
    isKP0Down = false;
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
                isLeftDown = true;
                break;
            case SDLK_RIGHT:
                angularVelocity += maxAngularVelocity;
                isRightDown = true;
                break;
            case SDLK_UP:
                moveState = (MoveState)((int)moveState + 1);
                isUpDown = true;
                break;
            case SDLK_DOWN:
                moveState = (MoveState)((int)moveState - 1);
                isDownDown = true;
                break;
            case SDLK_KP_ENTER:
                if(isAlive)
                {
                    shoot();
                }
                break;
            case SDLK_m:
                isMDown = true;
                showScore += 1;
                break;
            case SDLK_KP_0:
                isKP0Down = true;
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
                if(isLeftDown)
                {
                    angularVelocity += maxAngularVelocity;
                    isLeftDown = false;
                }
                    break;
                case SDLK_RIGHT:
                if(isRightDown)
                {
                    angularVelocity -= maxAngularVelocity;
                    isRightDown = false;
                }
                    break;
                case SDLK_UP:
                    if(isUpDown)
                    {
                    moveState = (MoveState)((int)moveState - 1);
                    isUpDown = false;
                    }
                    break;
                case SDLK_DOWN:
                    if(isDownDown)
                    {
                    moveState = (MoveState)((int)moveState + 1);
                    isDownDown = false;
                    }
                    break;
                    case SDLK_m:
                    if(isMDown)
                    {
                showScore -= 1;
                isMDown = false;
                    }
                break;
            case SDLK_KP_0:
            if(isKP0Down)
            {
                showScore -= 1;
                isKP0Down = false;
            }
                break;
            }
        }
    }
}

void Player2::reset()
{
    isLeftDown = false;
    isRightDown = false;
    isUpDown = false;
    isDownDown = false;
    isMDown = false;
    isKP0Down = false;
    angularVelocity = 0;
    moveState = STAND;
}