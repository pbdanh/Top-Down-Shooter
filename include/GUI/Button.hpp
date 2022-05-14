#pragma once

#include <functional>

#include "GUIComponent.hpp"
#include "AssetManager.hpp"
#include "Window.hpp"

extern Window* gWindow;
extern bool gSoundOn;

class Button: public GUIComponent
{
public:
    Button(const std::string fileName, SDL_Point postition, std::function<void()> callback);
    ~Button();

    bool isSelectable();
    void handleEvent(const SDL_Event& e);
    void render();

private:
    Mix_Chunk* buttonSound;
    std::string fileName;
    std::function<void()> callback;
};