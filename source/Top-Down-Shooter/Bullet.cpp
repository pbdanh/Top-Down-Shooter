#include "Bullet.hpp"

Bullet::Bullet(double posX_, double posY_, double degree_) : posX(posX_), posY(posY_), degree(degree_)
{
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
}

void Bullet::update(float deltaTime)
{
    posX += velocity * std::cos(degree * M_PI / 180) * deltaTime;
    posY += velocity * std::sin(degree * M_PI / 180) * deltaTime;
}