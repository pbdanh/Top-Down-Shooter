#include "AssetManager.hpp"
#include "Settings.hpp"
#include "Window.hpp"

extern Window* gWindow;

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
	delete singletonInstance;
}

AssetManager * AssetManager::singletonInstance;

AssetManager * AssetManager::getInstance()
{
	if (singletonInstance == NULL)
	{
		singletonInstance = new AssetManager();
	}
	return singletonInstance;
}

SDL_Texture* & AssetManager::getTexture(std::string const & filename)
{
	std::map<std::string, SDL_Texture *> & textureMap = singletonInstance->managerTextures;

	std::map<std::string, SDL_Texture *>::iterator pairFound = textureMap.find(filename);
	if (pairFound != textureMap.end())
	{
		return pairFound->second;
	}
	else
	{
		SDL_Texture* &texture = textureMap[filename];
		SDL_Surface* loadedSurface = IMG_Load((GRAPHICS_PATH + filename).c_str());
		if (loadedSurface == NULL)
		{
			std::cout << "Failed to load image: " << filename << std::endl;
			std::cout << "Error: " << IMG_GetError() << std::endl;
		}
		else
		{
			texture = SDL_CreateTextureFromSurface(gWindow->getRenderer(), loadedSurface);
			SDL_FreeSurface(loadedSurface);
			if(texture == NULL)
			{
				std::cout << "Failed to create texture: " << filename << std::endl;
				std::cout << "Error: " << SDL_GetError() << std::endl;
			}
		}
		return texture;
	}
}

TTF_Font* & AssetManager::getFont(std::string const & filename)
{
	std::map<std::string, TTF_Font*> & fontMap = singletonInstance->managerFonts;

	std::map<std::string, TTF_Font*>::iterator pairFound = fontMap.find(filename);
	if (pairFound != fontMap.end())
	{
		return pairFound->second;
	}
	else
	{
		TTF_Font* & font = fontMap[filename];
		font = TTF_OpenFont((FONTS_PATH + filename).c_str(), 300);
		if (font == NULL)
		{
			std::cout << "Failed to load font: " << filename << std::endl;
			std::cout << "Error: " << TTF_GetError() << std::endl;
		}
		return font;
	}
}

Mix_Chunk * & AssetManager::getSoundBuffer(std::string const & filename)
{
	std::map<std::string, Mix_Chunk *> & soundBufferMap = singletonInstance->managerSoundBuffers;

	std::map<std::string, Mix_Chunk *>::iterator pairFound = soundBufferMap.find(filename);
	if (pairFound != soundBufferMap.end())
	{
		return pairFound->second;
	}
	else
	{
		Mix_Chunk * & soundBuffer = soundBufferMap[filename];
		soundBuffer = Mix_LoadWAV((AUDIO_PATH + filename).c_str());
		if(soundBuffer == NULL)
		{
			std::cout << "Failed to load sound: " << filename << std::endl;
			std::cout << "Error: " << Mix_GetError() << std::endl;
		}
		return soundBuffer;
	}
}