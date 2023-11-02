#pragma once
#include <SDL.h>
#include <string>

class TextureManager
{
	TextureManager();
	SDL_Texture* tableTexture[15];
	string tab[15];

	void initTexture();
};
