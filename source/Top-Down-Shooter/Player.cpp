#include "Player.hpp"

Player::Player(double posX_, double posY_, double degree_)
{
    posX = posX_;
    posY = posY_;
    degrees = degree_;
    isAlive = true;
    moveState = STAND;
    angularVelocity = 0;
    isCeasefire = false;
    timeCeasefire = 0;
}

Player::~Player()
{
    SDL_DestroyTexture(playerTexture);
}

void Player::handleEvent(const SDL_Event& event)
{
}

void Player::update(float deltaTime, int** map)
{
    std::stack <int> bulletWillBeDestroyed;
    int i = 0;
    for(auto bullet : bullets)
    {
        bullet->update(deltaTime);
        SDL_Point pos = bullet->getPos();
        if(pos.x <= 0 || pos.x >= SCREEN_WIDTH || pos.y <= 0 || pos.y >= SCREEN_HEIGHT)
        {
            bulletWillBeDestroyed.push(i);
        }
        else
        {
            if(map[pos.y/32][pos.x/32] == 1)
            {
                bulletWillBeDestroyed.push(i);
            }
        }
        i++;
    }
    while(!bulletWillBeDestroyed.empty())
    {
        bullets.erase(bullets.begin() + bulletWillBeDestroyed.top());
        bulletWillBeDestroyed.pop();
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
    if(posX + center.x < 0)
    {
        posX = 0 - center.x;
    }
    if(posX + center.x > SCREEN_WIDTH)
    {
        posX = SCREEN_WIDTH - center.x;
    }
    if(posY + center.y < 0)
    {
        posY = 0 - center.y;
    }
    if(posY + center.y > SCREEN_HEIGHT)
    {
        posY = SCREEN_HEIGHT - center.y-1;
    }
    if(isCeasefire)
    {
        timeCeasefire += deltaTime;
        if(timeCeasefire > 0.25)
        {
            isCeasefire = false;
            timeCeasefire = 0;
        }
    }
    if(map[((int)posY+center.y)/32][((int)posX+center.x)/32] == 1)
    {
        if(moveState == GO_FORWARD)
        {
            posX -= velocity * std::cos(degrees * M_PI / 180) * deltaTime;
            posY -= velocity * std::sin(degrees * M_PI / 180) * deltaTime;
        }
        if(moveState == GO_BACKWARD)
        {
            posX += velocity / 2 * std::cos(degrees * M_PI / 180) * deltaTime;
            posY += velocity / 2 * std::sin(degrees * M_PI / 180) * deltaTime;
        }
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
    if(!isCeasefire)
    {
        Bullet* bullet = new Bullet(posX + 16 + 30*std::cos((-degrees + angleBetweenGunAndPlayer)*M_PI/180), posY + 22 +30*std::cos((90 + angleBetweenGunAndPlayer - degrees)*M_PI/180), degrees);
        bullets.push_back(bullet);
        //recoil
        degrees += rand() % 11 - 5;
        isCeasefire = true;
    }
}