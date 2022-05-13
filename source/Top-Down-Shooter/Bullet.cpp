#include "Bullet.hpp"

Bullet::Bullet(double posX_, double posY_, double degree_) : posX(posX_), posY(posY_), degree(degree_)
{
    x0 = posX;
    y0 = posY;
    bulletTexture = AssetManager::getInstance()->getTexture("bullet.png");
    Mix_PlayChannel(-1, AssetManager::getInstance()->getSoundBuffer("shoot_sound.wav"), 0);
}

Bullet::~Bullet()
{
}

void Bullet::render()
{
    SDL_Rect rect;
    SDL_QueryTexture(bulletTexture, NULL, NULL, &rect.w, &rect.h);
    rect.x = posX - rect.w / 2;
    rect.y = posY - rect.h / 2;
    SDL_RenderCopyEx(gWindow->getRenderer(), bulletTexture, NULL, &rect, degree, NULL, SDL_FLIP_NONE);
    //TODO: draw hitbox -> will be removed later
    if(gDevMode)
    {
    SDL_QueryTexture(AssetManager::getInstance()->getTexture("x.png"), NULL, NULL, &rect.w, &rect.h);
    rect.x = getHitBox().x - rect.w / 2;
    rect.y = getHitBox().y - rect.h / 2;
    SDL_RenderCopyEx(gWindow->getRenderer(), AssetManager::getInstance()->getTexture("x.png"), NULL, &rect, 0, NULL, SDL_FLIP_NONE);
    }
}

void Bullet::update(float deltaTime)
{
    posX += velocity * std::cos(degree * M_PI / 180) * deltaTime;
    posY += velocity * std::sin(degree * M_PI / 180) * deltaTime;
}

SDL_Point Bullet::getPos()
{
    SDL_Point point;
    point.x = posX;
    point.y = posY;
    return point;
}

SDL_Point Bullet::getHitBox()
{
    SDL_Point point;
    point.x = posX + 20 * std::cos(degree * M_PI / 180);
    point.y = posY + 20 * std::sin(degree * M_PI / 180);
    return point;
}

float Bullet::distanceFromBegin()
{
    return std::sqrt(std::pow(posX - x0, 2) + std::pow(posY - y0, 2));
}