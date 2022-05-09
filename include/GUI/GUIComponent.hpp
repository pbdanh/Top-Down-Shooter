#pragma once

#include <SDL.h>

class GUIComponent
{
public:
    GUIComponent();
    ~GUIComponent();

    virtual bool isSelectable() = 0;
	virtual void handleMouseClick(const SDL_Event &e);
protected:
    
};