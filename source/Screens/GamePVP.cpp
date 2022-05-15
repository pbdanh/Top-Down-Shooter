#include "GamePVP.hpp"

//TODO: remove
void drawRect(SDL_Renderer* renderer, SDL_Rect rect, SDL_Color color);

GamePVP::GamePVP(StateManager* stateManager) : GameScreen(stateManager)
{   
    player1 = new Player1(50, 50, 90);
    player2 = new Player2(1280-50-30, 800-50-30, -90);
    createGUI();
    if(stateManager->map == 1)
    {
        map = AssetManager::getInstance()->getMap("map_01.data");
    }
    else
    {
        map = AssetManager::getInstance()->getMap("map_02.data");

    }
    timeOut = stateManager->time;
    startingTime = 4;
    Mix_Chunk* startGameSound = AssetManager::getInstance()->getSoundBuffer("3_2_1_go.wav");
    if(gSoundOn) Mix_PlayChannel(-1, startGameSound, 0);
    maxScore = stateManager->maxScore;
    if(maxScore == 0)
    {
        maxScore = 99999;
    }
    pause = false;
}

GamePVP::~GamePVP()
{
}

void GamePVP::renderScreen()
{
    //render background
    if(stateManager->map == 1)
    {
        SDL_RenderCopy(gWindow->getRenderer(), AssetManager::getInstance()->getTexture("map_01.png"), NULL, NULL);
    }
    else
    {
        SDL_RenderCopy(gWindow->getRenderer(), AssetManager::getInstance()->getTexture("map_02.png"), NULL, NULL);
    }
    
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
    //render max score
    {
        std::stringstream ss;
        ss << "Max Score: ";
        if(maxScore == 99999)ss << "Unlimited";
        else ss << maxScore;
        std::string score = ss.str();
        SDL_Texture* text = AssetManager::getInstance()->getTexturefromText(score+",Monique-RegularRound20.otf,30,255,255,255");
        SDL_Rect rect;
        SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
        rect.x = SCREEN_WIDTH/2 - rect.w/2;
        rect.y = 20;
        SDL_RenderCopy(gWindow->getRenderer(), text, NULL, &rect);
    }
    //render starting time
    if(startingTime > 0)
    {
        std::stringstream ss;
        if((int)startingTime == 0)
        {
            ss << "GO!";
        }
        else
        {
            ss << (int)startingTime;
        }
        std::string time = ss.str();
        SDL_Texture* text = AssetManager::getInstance()->getTexturefromText(time+",Monique-RegularRound20.otf,100,255,255,255");
        SDL_Rect rect;
        SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
        rect.x = SCREEN_WIDTH/2 - rect.w/2;
        rect.y = SCREEN_HEIGHT/2 - rect.h/2;
        SDL_RenderCopy(gWindow->getRenderer(), text, NULL, &rect);
    }
    if(pause)
    {
        resumeButton->render();
    }
    else
    {
        pauseButton->render();
    }
}

void GamePVP::updateScreen(float deltaTime)
{
    startingTime -= deltaTime;
    if(startingTime > 0)
    {
        deltaTime = 0;
    }
    else startingTime = -1;
    if(pause)
    {
        deltaTime = 0;
        player1->reset();
    }
    timeOut -= deltaTime;
    if(timeOut < 0)//TODO: 120s
    {
        stateManager->p1Score = player1->getScore();
        stateManager->p2Score = player2->getScore();
        stateManager->switchScreen(StateManager::Screen::EndScreen);
    }
    player1->update(deltaTime, map, player2);
    player2->update(deltaTime, map, player1);
    if(std::max(player1->getScore(), player2->getScore()) >= maxScore)
    {
        stateManager->p1Score = player1->getScore();
        stateManager->p2Score = player2->getScore();
        stateManager->switchScreen(StateManager::Screen::EndScreen);
    }
}

void GamePVP::handleEvent(const SDL_Event& event)
{
    if(!(startingTime > 0))
    {
        
        
        if(pause)
    {
        resumeButton->handleEvent(event);
        if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
        {
            pause = false;
        }
    }
    else
    {
        pauseButton->handleEvent(event);
        if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
        {
            pause = true;
        }
        player1->handleEvent(event);
        player2->handleEvent(event);
    }
    }
    handleWidgetEvent(event);
    
}

void GamePVP::createGUI()
{
    createButton("button_home.png", {1230, 752}, std::bind(&GamePVP::goToMenu, this));
    pauseButton = new Button("button_pause.png", {115, 15}, std::bind(&GamePVP::switchPause, this));
    resumeButton = new Button("button_resume.png", {115, 15}, std::bind(&GamePVP::switchPause, this));
}

void GamePVP::goToMenu()
{
    stateManager->switchScreen(StateManager::Screen::StartScreen);
}

void GamePVP::switchPause()
{
    if(pause)
    {
        pause = false;
    }
    else
    {
        pause = true;
    }
}