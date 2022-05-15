#include "EndScreen.hpp"

EndScreen::EndScreen(StateManager* stateManager) : GameScreen(stateManager)
{
    createGUI();
    Mix_Chunk* sound = AssetManager::getInstance()->getSoundBuffer("end_screen_sound.wav");
    if(gSoundOn) Mix_PlayChannel(-1, sound, 0);
    if(!Mix_PausedMusic())
    {
        Mix_PauseMusic();
        timePauseMusic = 5;
    }
    else
    {
        timePauseMusic = -1;
    }
}

EndScreen::~EndScreen()
{
}

void drawRect(SDL_Renderer* renderer, SDL_Rect rect, SDL_Color color);

void EndScreen::renderScreen()
{
    //load background
    SDL_RenderCopy(gWindow->getRenderer(), AssetManager::getInstance()->getTexture("end_screen_background.bmp"), NULL, NULL);
    if(stateManager->p1Score > stateManager->p2Score)
    {
        SDL_Rect rect;
        SDL_QueryTexture(AssetManager::getInstance()->getTexture("player_1_wins.png"), NULL, NULL, &rect.w, &rect.h);
        rect.x = (SCREEN_WIDTH - rect.w)/2;
        rect.y = (SCREEN_HEIGHT - rect.h)/2 - 100;
        SDL_RenderCopy(gWindow->getRenderer(), AssetManager::getInstance()->getTexture("player_1_wins.png"), NULL, &rect);
    }
    else if(stateManager->p1Score < stateManager->p2Score)
    {
        SDL_Rect rect;
        SDL_QueryTexture(AssetManager::getInstance()->getTexture("player_2_wins.png"), NULL, NULL, &rect.w, &rect.h);
        rect.x = (SCREEN_WIDTH - rect.w)/2;
        rect.y = (SCREEN_HEIGHT - rect.h)/2 - 100;
        SDL_RenderCopy(gWindow->getRenderer(), AssetManager::getInstance()->getTexture("player_2_wins.png"), NULL, &rect);
    }
    else
    {
        SDL_Rect rect;
        SDL_QueryTexture(AssetManager::getInstance()->getTexture("draw.png"), NULL, NULL, &rect.w, &rect.h);
        rect.x = (SCREEN_WIDTH - rect.w)/2;
        rect.y = (SCREEN_HEIGHT - rect.h)/2 - 100;
        SDL_RenderCopy(gWindow->getRenderer(), AssetManager::getInstance()->getTexture("draw.png"), NULL, &rect);
    }
    //render player score
    {
        SDL_Texture* text ;
        SDL_Rect rect;
        
        
        
        int player1Score = stateManager->p1Score;
        std::stringstream ss;
        ss << "Player 1: ";
        ss << player1Score;
        std::string score = ss.str();
        text = AssetManager::getInstance()->getTexturefromText(score+",Monique-RegularRound20.otf,30,255,255,255");
        SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
        rect.x = SCREEN_WIDTH / 2 - 120 - rect.w;
        rect.y = 420;
        SDL_RenderCopy(gWindow->getRenderer(), text, NULL, &rect);
    }
    {
        SDL_Texture* text ;
        SDL_Rect rect;
        
        
        
        int player2Score = stateManager->p2Score;
        std::stringstream ss;
        ss << "Player 2: ";
        ss << player2Score;
        std::string score = ss.str();
        text = AssetManager::getInstance()->getTexturefromText(score+",Monique-RegularRound20.otf,30,255,255,255");
        SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
        rect.x = SCREEN_WIDTH / 2 + 120;
        rect.y = 420;
        SDL_RenderCopy(gWindow->getRenderer(), text, NULL, &rect);
    }
    renderWidget();
}

void EndScreen::updateScreen(float deltaTime)
{
    if(timePauseMusic!= -1)
    {
        timePauseMusic -= deltaTime;
        if(timePauseMusic < 0 && Mix_PausedMusic())
        {
            Mix_ResumeMusic();
        }
    }
}

void EndScreen::handleEvent(const SDL_Event& event)
{
    handleWidgetEvent(event);
}

void EndScreen::createGUI()
{
    createButton("button_restart.png", {555, 500}, std::bind(&EndScreen::goToGame, this));
    createButton("button_exit_for_end_screen.png", {555, 570}, []() { gQuit = true; });
    createButton("button_home.png", {1230, 752}, std::bind(&EndScreen::goToMenu, this));
}

void EndScreen::goToMenu()
{
    stateManager->switchScreen(StateManager::Screen::StartScreen);
}

void EndScreen::goToGame()
{
    stateManager->switchScreen(StateManager::Screen::GamePVP);
}

