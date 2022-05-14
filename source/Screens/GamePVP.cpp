#include "GamePVP.hpp"

//TODO: remove
void drawRect(SDL_Renderer* renderer, SDL_Rect rect, SDL_Color color);

GamePVP::GamePVP(StateManager* stateManager) : GameScreen(stateManager)
{   
    player1 = new Player1(50, 50, 90);
    player2 = new Player2(1280-50-30, 800-50-30, -90);
    createGUI();
    loadMap();
    timeOut = 120;
}

GamePVP::~GamePVP()
{
}

void GamePVP::renderScreen()
{
    //render background
    SDL_RenderCopy(gWindow->getRenderer(),AssetManager::getInstance()->getTexture("map_test.png"), NULL, NULL);
    
    //TODO: remove
    if(gDevMode)
    {
        for(int i = 0; i < 25; i++)
        {
            for(int j = 0; j < 40; j++)
            {
                if(map[i][j] == 1)
                {
                    SDL_Rect rect;
                    rect.x = j * 32;
                    rect.y = i * 32;
                    rect.w = 32;
                    rect.h = 32;
                    drawRect(gWindow->getRenderer(), rect, {255, 255, 255, 255});
                }
            }
        }
    }
    // std::cout << (int)timeOut << " ";//TODO: 120;
    // std::cout << "Player1: ";
    player1->render();
    // std::cout << "Player2: ";
    player2->render();
    // std::cout << std::endl;
    renderWidget();
    //render time remaining
    {
        std::stringstream ss;
        int minutes = (int)timeOut / 60;
        int seconds = (int)timeOut % 60;
        ss << minutes << ":" << seconds/10 << seconds % 10;
        std::string time = ss.str();
        SDL_Texture* text = AssetManager::getInstance()->getTexturefromText(time+",Monique-RegularRound20.otf,40,255,255,255");
        SDL_Rect rect;
        SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
        rect.x = 20;
        rect.y = 20;
        SDL_RenderCopy(gWindow->getRenderer(), text, NULL, &rect);
    }
}

void GamePVP::updateScreen(float deltaTime)
{
    timeOut -= deltaTime;
    if(timeOut < 0)//TODO: 120s
    {
        stateManager->p1Score = player1->getScore();
        stateManager->p2Score = player2->getScore();
        stateManager->switchScreen(StateManager::Screen::EndScreen);
    }
    player1->update(deltaTime, map, player2);
    player2->update(deltaTime, map, player1);
}

void GamePVP::handleEvent(const SDL_Event& event)
{
    handleWidgetEvent(event);
    player1->handleEvent(event);
    player2->handleEvent(event);
}

void GamePVP::createGUI()
{
    createButton("button_home.png", {1230, 752}, std::bind(&GamePVP::goToMenu, this));
}

void GamePVP::goToMenu()
{
    stateManager->switchScreen(StateManager::Screen::StartScreen);
}

void GamePVP::loadMap()
{
    map = AssetManager::getInstance()->getMap("map_PVP.data");
}