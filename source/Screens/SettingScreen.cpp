#include "SettingScreen.hpp"

SettingScreen::SettingScreen(StateManager* stateManager) : GameScreen(stateManager)
{
    createGUI();
}

SettingScreen::~SettingScreen()
{
}

void drawRect(SDL_Renderer* renderer, SDL_Rect rect, SDL_Color color);

void SettingScreen::renderScreen()
{
    //load background
    SDL_RenderCopy(gWindow->getRenderer(), AssetManager::getInstance()->getTexture("end_screen_background.png"), NULL, NULL);
    //render settingTime
    {
        SDL_Texture* text ;
        SDL_Rect rect;
        

        
        int settingTime = stateManager->time;
        std::stringstream ss;
        ss << "Time: ";
        ss << settingTime;
        std::string time = ss.str();
        text = AssetManager::getInstance()->getTexturefromText(time+",Monique-RegularRound20.otf,40,255,255,255");
        SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
        rect.x = (SCREEN_WIDTH - rect.w) / 2;
        rect.y = 560;
        SDL_RenderCopy(gWindow->getRenderer(), text, NULL, &rect);
    }
    //render max score
    {
        SDL_Texture* text ;
        SDL_Rect rect;
        
        int maxScore = stateManager->maxScore;
        std::stringstream ss;
        ss << "Score: ";
        if(maxScore == 0)
        {
            ss << "Unlimited";
        }
        else
        {
            ss << maxScore;
        }
        std::string time = ss.str();
        text = AssetManager::getInstance()->getTexturefromText(time+",Monique-RegularRound20.otf,40,255,255,255");
        SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
        rect.x = (SCREEN_WIDTH - rect.w) / 2;
        rect.y = 490;
        SDL_RenderCopy(gWindow->getRenderer(), text, NULL, &rect);
    }
    renderWidget();
    if(stateManager->map == 1)
    {
        SDL_Texture* whiteBorder = AssetManager::getInstance()->getTexture("white_border.png");
        SDL_Rect rect;
        SDL_QueryTexture(whiteBorder, NULL, NULL, &rect.w, &rect.h);
        rect.x = SCREEN_WIDTH/2 - 100 - 320 - 5;
        rect.y = 200 - 5;
        SDL_RenderCopy(gWindow->getRenderer(), whiteBorder, NULL, &rect);
    }
    else
    {
        SDL_Texture* whiteBorder = AssetManager::getInstance()->getTexture("white_border.png");
        SDL_Rect rect;
        SDL_QueryTexture(whiteBorder, NULL, NULL, &rect.w, &rect.h);
        rect.x = SCREEN_WIDTH/2 + 100 - 5;
        rect.y = 200 - 5;
        SDL_RenderCopy(gWindow->getRenderer(), whiteBorder, NULL, &rect);
    }
}

void SettingScreen::updateScreen(float deltaTime)
{
}

void SettingScreen::handleEvent(const SDL_Event& event)
{
    handleWidgetEvent(event);
}

void SettingScreen::createGUI()
{
    createButton("button_start.png", {555, 650}, std::bind(&SettingScreen::goToGame, this));
    createButton("button_home.png", {1230, 752}, std::bind(&SettingScreen::goToMenu, this));
    createButton("button_map1.png", {SCREEN_WIDTH / 2 - 100 - 320, 200}, std::bind(&SettingScreen::selectMap1, this));
    createButton("button_map2.png", {SCREEN_WIDTH / 2 + 100, 200}, std::bind(&SettingScreen::selectMap2, this));
    createButton("button_plus.png", {SCREEN_WIDTH / 2 + 200, 480}, std::bind(&SettingScreen::increaseMaxScore, this));
    createButton("button_minus.png", {SCREEN_WIDTH / 2 -200-50, 480}, std::bind(&SettingScreen::decreaseMaxScore, this));
    createButton("button_plus.png", {SCREEN_WIDTH / 2 + 130, 550}, std::bind(&SettingScreen::increaseTime, this));
    createButton("button_minus.png", {SCREEN_WIDTH / 2 - 130 - 50, 550}, std::bind(&SettingScreen::decreaseTime, this));
}

void SettingScreen::goToMenu()
{
    stateManager->switchScreen(StateManager::Screen::StartScreen);
}

void SettingScreen::goToGame()
{
    stateManager->switchScreen(StateManager::Screen::GamePVP);
}

void SettingScreen::increaseTime()
{
    stateManager->time = std::min(stateManager->time + 15, 300);
}

void SettingScreen::decreaseTime()
{
    stateManager->time = std::max(stateManager->time - 15, 45);
}

void SettingScreen::selectMap1()
{
    stateManager->map = 1;
}

void SettingScreen::selectMap2()
{
    stateManager->map = 2;
}

void SettingScreen::increaseMaxScore()
{
    stateManager->maxScore = stateManager->maxScore + 1;
}

void SettingScreen::decreaseMaxScore()
{
    stateManager->maxScore = std::max(stateManager->maxScore - 1, 0);
}