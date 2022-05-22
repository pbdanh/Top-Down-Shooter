#include "Item.hpp"

Item::Item(double posX_, double posY_)
{
    ItemTexture = AssetManager::getInstance()->getTexture("item.png");
    rect.x = posX_;
    rect.y = posY_;
    SDL_QueryTexture(ItemTexture, NULL, NULL, &rect.w, &rect.h);
}

Item::~Item()
{
    SDL_DestroyTexture(ItemTexture);
}

void Item::render()
{
    SDL_RenderCopy(gWindow->getRenderer(), ItemTexture, NULL, &rect);
}

SDL_Rect Item::getRect()
{
    return rect;
}
