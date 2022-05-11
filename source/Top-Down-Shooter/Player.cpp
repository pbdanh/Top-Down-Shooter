#include "Player.hpp"

Player::Player(double posX_, double posY_, double degree_)
{
    posX = posX_;
    posY = posY_;
    degrees = degree_;
    isAlive = true;
    moveState = STAND;
    angularVelocity = 0;
}

Player::~Player()
{
    SDL_DestroyTexture(playerTexture);
}

void Player::handleEvent(const SDL_Event& event)
{
}

void Player::update(float deltaTime)
{
    for(auto bullet : bullets)
    {
        bullet->update(deltaTime);
    }
    degrees += angularVelocity * deltaTime;
    if(moveState == GO_FORWARD)
    {
        posX += velocity * std::cos(degrees * M_PI / 180) * deltaTime;
        posY += velocity * std::sin(degrees * M_PI / 180) * deltaTime;
    }
    if(moveState == GO_BACKWARD)
    {
        posX -= velocity / 2 * std::cos(degrees * M_PI / 180) * deltaTime;
        posY -= velocity / 2 * std::sin(degrees * M_PI / 180) * deltaTime;
    }  
}

void Player::render()
{
    for(auto bullet : bullets)
    {
        bullet->render();
    }
    SDL_Rect rect;
    rect.x = posX;
    rect.y = posY;
    SDL_QueryTexture(playerTexture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopyEx(gWindow->getRenderer(), playerTexture, NULL, &rect, degrees, &center, SDL_FLIP_NONE);
}

void Player::shoot()
{

    //recoil
    degrees += rand() % 9 - 4;
    Bullet* bullet = new Bullet(posX + 16 + 30*std::cos((-degrees + angleBetweenGunAndPlayer)*M_PI/180), posY + 22 +30*std::cos((90 + angleBetweenGunAndPlayer - degrees)*M_PI/180), degrees);
    bullets.push_back(bullet);
}