#include "Player1.hpp"

Player1::Player1(double posX_, double posY_, double degree_) : Player(posX_, posY_, degree_)
{
    playerTexture = AssetManager::getInstance()->getTexture("p1.png");
    playerNumber = 1;
    isADown = false;
    isDDown = false;
    isWDown = false;
    isSDown = false;
    isMDown = false;
    isKP0Down = false;
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
                isADown = true;
                break;
            case SDLK_d:
                angularVelocity += maxAngularVelocity;
                isDDown = true;
                break;
            case SDLK_w:
                moveState = (MoveState)((int)moveState + 1);
                isWDown = true;
                break;
            case SDLK_s:
                isSDown = true;
                moveState = (MoveState)((int)moveState - 1);
                break;
            case SDLK_SPACE:
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
                    if(isADown)
                    {
                        angularVelocity += maxAngularVelocity;
                        isADown = false;
                    }
                    break;
                case SDLK_d:
                    if(isDDown)
                    {
                        angularVelocity -= maxAngularVelocity;
                        isDDown = false;
                    }
                    break;
                case SDLK_w:
                    if(isWDown)
                    {
                        moveState = (MoveState)((int)moveState - 1);
                        isWDown = false;
                    }
                    break;
                case SDLK_s:
                    if(isSDown)
                    {
                        moveState = (MoveState)((int)moveState + 1);
                        isSDown = false;
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
                    if(isKP0Down);
                    {
                        showScore -= 1;
                        isKP0Down = false;
                    }
                    break;
            }
        }
    }
}
void Player1::reset()
{
    isADown = false;
    isSDown = false;
    isDDown = false;
    isWDown = false;
    isMDown = false;
    isKP0Down = false;
    angularVelocity = 0;
    moveState = STAND;
}