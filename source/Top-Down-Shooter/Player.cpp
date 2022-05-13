#include "Player.hpp"


bool checkCollision(SDL_Rect rect, int** map)
{
    SDL_Point topLeft = {rect.x, rect.y};
    SDL_Point topRight = {rect.x + rect.w, rect.y};
    SDL_Point bottomLeft = {rect.x, rect.y + rect.h};
    SDL_Point bottomRight = {rect.x + rect.w, rect.y + rect.h};
    if(map[int(topLeft.y / 32)][int(topLeft.x / 32)] == 1 || map[int(topRight.y / 32)][int(topRight.x / 32)] == 1 || map[int(bottomLeft.y / 32)][int(bottomLeft.x / 32)] == 1 || map[int(bottomRight.y / 32)][int(bottomRight.x / 32)] == 1)
    {
        return true;
    }
    return false;
}

bool checkCollision(SDL_Rect rect1, SDL_Rect rect2)
{
    if(rect1.x + rect1.w < rect2.x || rect1.x > rect2.x + rect2.w || rect1.y + rect1.h < rect2.y || rect1.y > rect2.y + rect2.h)
    {
        return false;
    }
    return true;
}

bool checkCollision(SDL_Rect rect, SDL_Point point)
{
    if(rect.x + rect.w < point.x || rect.x > point.x || rect.y + rect.h < point.y || rect.y > point.y)
    {
        return false;
    }
    return true;
}

bool checkCollisionWindowBorder(SDL_Rect rect)
{
    if(rect.x < 0 || rect.x + rect.w > SCREEN_WIDTH || rect.y < 0 || rect.y + rect.h > SCREEN_HEIGHT)
    {
        return true;
    }
    return false;
}

void drawRect(SDL_Renderer* renderer, SDL_Rect rect, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(renderer, &rect);
}

void drawCircle(SDL_Renderer* renderer, SDL_Point center, int radius, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for(double angle = 0; angle < 2 * M_PI; angle += 0.001)
    {
        int x = center.x + radius * cos(angle);
        int y = center.y + radius * sin(angle);
        SDL_RenderDrawPoint(renderer, x, y);
    }
}

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
    score = 0;
    isProtected = true;
    timeProtected = 4;
}

Player::~Player()
{
    SDL_DestroyTexture(playerTexture);
}

void Player::handleEvent(const SDL_Event& event)
{
}

void Player::update(float deltaTime, int** map, Player* player_ )
{
    std::stack <int> bulletWillBeDestroyed;
    int i = 0;
    for(auto bullet : bullets)
    {
        bullet->update(deltaTime);
        SDL_Point pos = bullet->getHitBox();
        if(pos.x <= 0 || pos.x >= SCREEN_WIDTH || pos.y <= 0 || pos.y >= SCREEN_HEIGHT)
        {
            bulletWillBeDestroyed.push(i);
        }
        else
        {
            if(map[pos.y/32][pos.x/32] == 1)
            {
                bulletWillBeDestroyed.push(i);
                Mix_PlayChannel(0, AssetManager::getInstance()->getSoundBuffer("bullets_hit.wav"), 0);
            }
            if(bullet->distanceFromBegin() > 550)
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
    if(isAlive)
    {
    i = 0;
    for(auto bullet : player_->getBullets())
    {
        if(checkCollision(getHitBox(), bullet->getHitBox()))
        {
            bulletWillBeDestroyed.push(i);
            if(!isProtected)
            {
               
            isAlive = false;
            timeDead = 0;
            
            player_->increaseScore();
            }
        }
        i++;
    }
    while(!bulletWillBeDestroyed.empty())
    {
        player_->getBullets().erase(player_->getBullets().begin() + bulletWillBeDestroyed.top());
        bulletWillBeDestroyed.pop();
         Mix_PlayChannel(0, AssetManager::getInstance()->getSoundBuffer("bullets_hit.wav"), 0);
    }
    degrees += angularVelocity * deltaTime;
    if(moveState == GO_FORWARD)
    {
        posX += velocity * std::cos(degrees * M_PI / 180) * deltaTime;
        if(getHitBox().x < 0 || getHitBox().x + getHitBox().w > SCREEN_WIDTH || checkCollision(getHitBox(), map) || (checkCollision(getHitBox(), player_->getHitBox()) && player_->isAlive))
        {
            posX -= velocity * std::cos(degrees * M_PI / 180) * deltaTime;
        }
        posY += velocity * std::sin(degrees * M_PI / 180) * deltaTime;
        if(getHitBox().y < 0 || getHitBox().y + getHitBox().h > SCREEN_HEIGHT || checkCollision(getHitBox(), map) || (checkCollision(getHitBox(), player_->getHitBox()) && player_->isAlive))
        {
            posY -= velocity * std::sin(degrees * M_PI / 180) * deltaTime;
        }
    }
    if(moveState == GO_BACKWARD)
    {
        posX -= velocity / 2 * std::cos(degrees * M_PI / 180) * deltaTime;
        if(getHitBox().x < 0 || getHitBox().x + getHitBox().w > SCREEN_WIDTH || checkCollision(getHitBox(), map) || (checkCollision(getHitBox(), player_->getHitBox()) && player_->isAlive))
        {
            posX += velocity / 2 * std::cos(degrees * M_PI / 180) * deltaTime;
        }
        posY -= velocity / 2 * std::sin(degrees * M_PI / 180) * deltaTime;
        if(getHitBox().y < 0 || getHitBox().y + getHitBox().h > SCREEN_HEIGHT ||checkCollision(getHitBox(), map) || (checkCollision(getHitBox(), player_->getHitBox()) && player_->isAlive))
        {
            posY += velocity / 2 * std::sin(degrees * M_PI / 180) * deltaTime;
        }
    }
    }
    else
    {
        timeDead += deltaTime;
        if(timeDead > 3)
        {
            isAlive = true;
            isProtected = true;
            timeProtected = 4;
        do
            {
                posX = rand() % SCREEN_WIDTH;
                posY = rand() % SCREEN_HEIGHT;
                setPos(posX, posY);
            } while (checkCollision(getHitBox(), map) || checkCollision(getHitBox(), player_->getHitBox()) || checkCollisionWindowBorder(getHitBox()));
        }
            degrees = rand() % 360;
    
    }
    if(isCeasefire)
    {
        timeCeasefire -= deltaTime;
        if(timeCeasefire < 0)
        {
            isCeasefire = false;
            timeCeasefire = 0.25;
        }
    }
    if(isProtected)
    {
        timeProtected -= deltaTime;
        if(timeProtected < 0)
        {
            isProtected = false;
        }
    }
}

void Player::render()
{
    for(auto bullet : bullets)
    {
        bullet->render();
    }
    if(isAlive)
    {
    SDL_Rect rect;
    rect.x = posX;
    rect.y = posY;
    SDL_QueryTexture(playerTexture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopyEx(gWindow->getRenderer(), playerTexture, NULL, &rect, degrees, &center, SDL_FLIP_NONE);
    if(isProtected)
    {
        SDL_Rect rect;
        SDL_QueryTexture(AssetManager::getInstance()->getTexture("shield.png"), NULL, NULL, &rect.w, &rect.h);
        rect.x = posX + center.x - rect.w / 2;
        rect.y = posY + center.y - rect.h / 2;
        SDL_RenderCopy(gWindow->getRenderer(), AssetManager::getInstance()->getTexture("shield.png"), NULL, &rect);
    }
    if(gDevMode)
    {
        //TODO: drawhitbox and will be removed
        SDL_Rect hitBoxRect = getHitBox();
        drawRect(gWindow->getRenderer(), hitBoxRect, {255, 0, 0, 255});
        //TODO: draw shooting range and will be removed
        drawCircle(gWindow->getRenderer(), {(int)(posX + 16 + 30*std::cos((-degrees + angleBetweenGunAndPlayer)*M_PI/180)), (int)(posY + 22 +30*std::cos((90 + angleBetweenGunAndPlayer - degrees)*M_PI/180))}, 550, {255, 0, 0, 255});
    }
    }
    std::cout << "Score = " << score << " ";
    if (!isAlive)
    {
        std::cout << "Respawning in: " << 3 - timeDead << " ";
    }
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
        timeCeasefire = 0.25;
    }
}

SDL_Rect Player::getHitBox()
{
    SDL_Rect rect;
    rect.x = posX + center.x - 15;
    rect.y = posY + center.y - 15;
    rect.w = 30;
    rect.h = 30;
    return rect;
}

std::vector<Bullet*>& Player::getBullets()
{
    return bullets;
}

void Player::increaseScore()
{
    score++;
}

int Player::getScore()
{
    return score;
}

void Player::setPos(double posX_, double posY_)
{
    posX = posX_;
    posY = posY_;
}