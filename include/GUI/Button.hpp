#pragma once

#include "GUIComponent.hpp"
#include "AssetManager.hpp"
#include <functional>

class Button: public GUIComponent
{
public:
    Button(const std::string fileName, SDL_Point postition, std::function<void()> callback);
    ~Button();

    bool isSelectable();
    void handleEvent(const SDL_Event& e);
    void render(SDL_Renderer* renderer);

private:
    Mix_Chunk* buttonSound;
    std::string fileName;
    std::function<void()> callback;
};