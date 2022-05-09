#pragma once

#include "GameScreen.hpp"
#include "Window.hpp"
#include <vector>

extern Window* gWindow;

class Bullet
{
public:
    Bullet(int x_, int y_, double degree_): x(x_), y(y_), degree(degree_) {};
    ~Bullet() {};
    int x;
    int y;
    double degree;
};

class GamePVP : public GameScreen
{
public:
    GamePVP(StateManager* stateManager);
    ~GamePVP();
    void renderScreen();
    void updateScreen(float deltaTime);
    void handleEvent(const SDL_Event& event);
    enum moveState
    {
        GO_FORWARD = 1,
        GO_BACKWARD = -1,
        STAND = 0,
    };
private:
    SDL_Point center = {16, 22};
    double phi = -17;
    SDL_Texture* p1;
    double x_1 = 100, y_1 = 100;
    const int velocity = 1;
    double degrees_1 = 0;
    double omega_1 = 0;
    moveState state_1 = STAND;
    //
    SDL_Texture* p2;
    double x_2 = 1280-100, y_2 = 720-100;
    double degrees_2 = 180;
    double omega_2 = 0;
    moveState state_2 = STAND;
    void loadMedia();
    //
    SDL_Texture* bullet;
    const int bulletVelocity = 3;
    std::vector<Bullet*> bullets_1;
    std::vector<Bullet*> bullets_2;
    //
    SDL_Texture* x;
    //
    SDL_Texture* ground;
    Mix_Chunk* bulletSound;
};