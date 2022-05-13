#pragma once

#include <cmath>
#include <vector>
#include <stack>
#include <iomanip>

#include <SDL.h>
#include <SDL_mixer.h>

#include "Window.hpp"
#include "Bullet.hpp"

extern Window* gWindow;
extern bool gDevMode;

class Player
{
    public:
        Player(double posX_, double posY_, double degree_);
        ~Player();
        virtual void handleEvent(const SDL_Event& event);
        void update(float deltaTime, int** map, Player* player_);
        void render();
        enum MoveState
        {
            GO_FORWARD = 1,
            GO_BACKWARD = -1,
            STAND = 0,
        };
        std::vector<Bullet*>& getBullets();
        void increaseScore();
        int getScore();
        void setPos(double posX_, double posY_);
        bool isAlive;
        void renderScore();
        void renderRespawn();
        void renderInfo();
    protected:
        void shoot();
        SDL_Texture* playerTexture;
        SDL_Point center = {16, 22};
        double angleBetweenGunAndPlayer = -17;
        const double velocity = 200;
        const double maxAngularVelocity = 75;
        double posX, posY;
        double degrees;
        double angularVelocity;
        double timeDead;
        MoveState moveState;
        std::vector<Bullet*> bullets;
        bool isCeasefire;
        double timeCeasefire;
        SDL_Rect getHitBox();
        int score;
        bool isProtected;
        double timeProtected;
        int showScore;
        double timeShowInfo;
        int playerNumber;
};