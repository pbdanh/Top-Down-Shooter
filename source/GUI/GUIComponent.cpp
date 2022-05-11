#include "GUIComponent.hpp"

GUIComponent::GUIComponent()
{
}

GUIComponent::~GUIComponent()
{
}

bool GUIComponent::isSelectable()
{
    return false;
}

void GUIComponent::handleEvent(const SDL_Event& e)
{
}

void GUIComponent::render()
{
}