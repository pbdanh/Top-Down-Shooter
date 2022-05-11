#include "GamePVP.hpp"
#include <cmath>
#include <time.h>

SDL_TimerID ID_1;

Uint32 loadAmmo(Uint32 interval, void* param)
{
    int* ammo = reinterpret_cast<int*>(param);
    *ammo = std::min(*ammo + 1, 4);
    std::cout << "load!! " << *ammo << std::endl;
    ID_1 = SDL_AddTimer(1000, loadAmmo, ammo);
}

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

GamePVP::GamePVP(StateManager* stateManager) : GameScreen(stateManager)
{
    loadMedia();
    std::cout << ammo_1;
    ID_1 = SDL_AddTimer(1000, loadAmmo, reinterpret_cast<void*>(&ammo_1));
}

GamePVP::~GamePVP()
{
}

void GamePVP::renderScreen()
{
    SDL_RenderCopy(gWindow->getRenderer(), ground, NULL, NULL);
    SDL_Rect desRect;
    for (auto i : bullets_1)
    {
        desRect.x = i->x;
        desRect.y = i->y;
        desRect.w = 40;
        desRect.h = 6;
        SDL_RenderCopyEx(gWindow->getRenderer(), bullet, NULL, &desRect, i->degree, NULL, SDL_FLIP_NONE);
    }
    for(auto i : bullets_2)
    {
        desRect.x = i->x;
        desRect.y = i->y;
        desRect.w = 40;
        desRect.h = 6;
        SDL_RenderCopyEx(gWindow->getRenderer(), bullet, NULL, &desRect, i->degree, NULL, SDL_FLIP_NONE);
    }
    
    if(isP1Alive)
    {
    desRect.x = x_1;
    desRect.y = y_1;
    desRect.w = 50;
    desRect.h = 43;
    SDL_RenderCopyEx(gWindow->getRenderer(), p1, NULL, &desRect, degrees_1, &center, SDL_FLIP_NONE);
    }
    desRect.x = x_2;
    desRect.y = y_2;
    desRect.w = 50;
    desRect.h = 43;
    SDL_RenderCopyEx(gWindow->getRenderer(), p2, NULL, &desRect, degrees_2, &center, SDL_FLIP_NONE);
    
}

    Uint32 respawn(Uint32 interval, void* param)
    {
        bool *isAlive = reinterpret_cast<bool*>(param);
        *isAlive = true;
    }

void GamePVP::updateScreen(float deltaTime)
{
    degrees_1 += omega_1 * deltaTime;
    if (state_1 == GO_FORWARD)
    {
        x_1 += velocity * deltaTime * std::cos(degrees_1 * M_PI / 180);
        y_1 += velocity * deltaTime * std::sin(degrees_1 * M_PI / 180);
    }
    else if (state_1 == GO_BACKWARD)
    {
        x_1 -= velocity * deltaTime * std::cos(degrees_1 * M_PI / 180);
        y_1 -= velocity * deltaTime * std::sin(degrees_1 * M_PI / 180);
    }
    if(x_1 + 50 > SCREEN_WIDTH)
        {
            x_1 = SCREEN_WIDTH - 50;
        }
        if(x_1 < 0)
        {
            x_1 = 0;
        }
        if(y_1 + 43 > SCREEN_HEIGHT)
        {
            y_1 = SCREEN_HEIGHT - 43;
        }
        if(y_1 < 0)
        {
            y_1 = 0;
        }
    degrees_2 += omega_2 * deltaTime;
    if (state_2 == GO_FORWARD)
    {
        x_2 += velocity * deltaTime * std::cos(degrees_2 * M_PI / 180);
        y_2 += velocity * deltaTime * std::sin(degrees_2 * M_PI / 180);
    }
    else if (state_2 == GO_BACKWARD)
    {
        x_2 -= velocity * deltaTime * std::cos(degrees_2 * M_PI / 180);
        y_2 -= velocity * deltaTime * std::sin(degrees_2 * M_PI / 180);
    }
    if(x_2 + 50 > SCREEN_WIDTH)
        {
            x_2 = SCREEN_WIDTH - 50;
        }
        if(x_2 < 0)
        {
            x_2 = 0;
        }
        if(y_2 + 43 > SCREEN_HEIGHT)
        {
            y_2 = SCREEN_HEIGHT - 43;
        }
        if(y_2 < 0)
        {
            y_2 = 0;
        }
    for (int i = 0; i < bullets_1.size(); i++)
    {
        bullets_1[i]->x += bulletVelocity * deltaTime * std::cos(bullets_1[i]->degree * M_PI / 180);
        bullets_1[i]->y += bulletVelocity * deltaTime * std::sin(bullets_1[i]->degree * M_PI / 180);
        SDL_Rect bullet;
        bullet.x = bullets_1[i]->x;
        bullet.y = bullets_1[i]->y;
        bullet.w = 40;
        bullet.h = 6;
        SDL_Rect p2_hitbox;
        p2_hitbox.x = x_2;
        p2_hitbox.y = y_2;
        p2_hitbox.w = 50;
        p2_hitbox.h = 43;
        if(checkCollision(bullet, p2_hitbox))
        {
            x_2 = 1280-100;
            y_2 = 720-100;
            degrees_2 = 180;
        } 
    }
    for(int i = 0; i < bullets_2.size(); i++)
    {
        bullets_2[i]->x += bulletVelocity * deltaTime * std::cos(bullets_2[i]->degree * M_PI / 180);
        bullets_2[i]->y += bulletVelocity * deltaTime * std::sin(bullets_2[i]->degree * M_PI / 180);
        SDL_Rect bullet;

        bullet.x = bullets_2[i]->x;
        bullet.y = bullets_2[i]->y;
        bullet.w = 40;
        bullet.h = 6;
        SDL_Rect p1_hitbox;
        p1_hitbox.x = x_1;
        p1_hitbox.y = y_1;
        p1_hitbox.w = 50;
        p1_hitbox.h = 43;
        if(checkCollision(bullet, p1_hitbox))
        {
            
            isP1Alive = false;
            
            ID_1 = SDL_AddTimer(3000, respawn, reinterpret_cast<void*>(&isP1Alive));
            std::cout << isP1Alive << std::endl;
            x_1 = 100;
            y_1 = 100;
            degrees_1 = 0;
        }
    }
}

void GamePVP::loadMedia()
{
    SDL_Surface* loadedSurface = IMG_Load("media/img/p1.png");
    p1 = SDL_CreateTextureFromSurface(gWindow->getRenderer(), loadedSurface);
    SDL_FreeSurface(loadedSurface);
    loadedSurface = IMG_Load("media/img/p2.png");
    p2 = SDL_CreateTextureFromSurface(gWindow->getRenderer(), loadedSurface);
    SDL_FreeSurface(loadedSurface);
    loadedSurface = IMG_Load("media/img/bullet.png");
    bullet = SDL_CreateTextureFromSurface(gWindow->getRenderer(), loadedSurface);
    SDL_FreeSurface(loadedSurface);
    loadedSurface = IMG_Load("media/img/x.png");
    x = SDL_CreateTextureFromSurface(gWindow->getRenderer(), loadedSurface);
    loadedSurface = IMG_Load("media/img/ground.png");
    ground = SDL_CreateTextureFromSurface(gWindow->getRenderer(), loadedSurface);
    bulletSound = Mix_LoadWAV("media/sound/shoot_sound.wav");
    if(bulletSound == NULL)
    {
        std::cout << "!!";
    }
}

void GamePVP::handleEvent(const SDL_Event& event)
{   
    if(event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        switch(event.key.keysym.sym )
        {
            case SDLK_a:
                omega_1 -= 0.5;
                break;
            case SDLK_d:
                omega_1 += 0.5;
                break;
            case SDLK_w:
                state_1 = moveState(int(state_1) + 1);
                break;
            case SDLK_s:
                state_1 = moveState(int(state_1) - 1);
                break;
            case SDLK_LEFT:
                omega_2 -= 0.5;
                break;
            case SDLK_RIGHT:
                omega_2 += 0.5;
                break;
            case SDLK_UP:
                state_2 = moveState(int(state_2) + 1);
                break;
            case SDLK_DOWN:
                state_2 = moveState(int(state_2) - 1);
                break;
            case SDLK_SPACE:
                if(ammo_1 > 0)
                {
                    ammo_1--;
                    std::cout << ammo_1 << std::endl;
                Mix_PlayChannel(-1, bulletSound, 0);
                bullets_1.push_back(new Bullet(x_1 + 16 + 30*std::cos((-degrees_1 + phi)*M_PI/180) - 20, y_1 + 22 + 30*std::cos((90 + phi - degrees_1) * M_PI / 180) - 3, degrees_1));
                
                }
                break;
            case SDLK_KP_ENTER:
                Mix_PlayChannel(-1, bulletSound, 0);
                bullets_2.push_back(new Bullet(x_2 + 16 + 30*std::cos((-degrees_2 + phi)*M_PI/180) - 20, y_2 + 22 + 30*std::cos((90 + phi - degrees_2) * M_PI / 180) - 3, degrees_2));
                break;
        }
    }
    else
    {
        if(event.type == SDL_KEYUP && event.key.repeat == 0)
        {
            switch(event.key.keysym.sym )
            {
                case SDLK_a:
                    omega_1 += 0.5;
                    break;
                case SDLK_d:
                    omega_1 -= 0.5;
                    break;
                case SDLK_w:
                    state_1 = moveState(int(state_1) - 1);
                    break;
                case SDLK_s:
                    state_1 = moveState(int(state_1) + 1);
                    break;
                case SDLK_LEFT:
                    omega_2 += 0.5;
                    break;
                case SDLK_RIGHT:
                    omega_2 -= 0.5;
                    break;
                case SDLK_UP:
                    state_2 = moveState(int(state_2) - 1);
                    break;
                case SDLK_DOWN:
                    state_2 = moveState(int(state_2) + 1);
                    break;  
                
            }
        }
    }
}