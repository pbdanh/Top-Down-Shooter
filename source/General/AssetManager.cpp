#include "AssetManager.hpp"

SDL_Texture* AssetManager::getTexture(const std::string & filename)
{
    SDL_Surface* loadedSurface = IMG_Load(filename.c_str());
    if(loadedSurface == NULL)
    {
        std::cout << "Failed to load image " << filename << "! SDL_image Error: " << IMG_GetError() << std::endl;
        return NULL;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(gWindow->getRenderer(), loadedSurface);
    if(texture == NULL)
    {
        std::cout << "Failed to create texture from " << filename << "! SDL Error: " << SDL_GetError() << std::endl;
        return NULL;
    }
    SDL_FreeSurface(loadedSurface);
    return texture;
}