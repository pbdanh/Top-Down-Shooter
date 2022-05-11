#pragma once

#include <SDL.h>
#include "AssetManager.hpp"

class GUIComponent
{
public:
    GUIComponent();
    ~GUIComponent();

    virtual bool isSelectable() = 0;
	virtual void handleEvent(const SDL_Event& e);
    virtual void render(SDL_Renderer* renderer);

protected:
    SDL_Rect rect;
};