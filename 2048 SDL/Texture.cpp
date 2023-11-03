#include "Texture.h"
#include <SDL.h>
#include <iostream>

TextureManager::TextureManager(SDL_Renderer* rendering) {

	renderer = rendering;

	SDL_Surface* fond = SDL_LoadBMP("src/fond.bmp");
	SDL_Surface* win = SDL_LoadBMP("src/win.bmp");
	SDL_Surface* loose = SDL_LoadBMP("src/loose.bmp");
	SDL_Surface* t0 = SDL_LoadBMP("src/0.bmp");
	SDL_Surface* t2 = SDL_LoadBMP("src/2.bmp");
	SDL_Surface* t4 = SDL_LoadBMP("src/4.bmp");
	SDL_Surface* t8 = SDL_LoadBMP("src/8.bmp");
	SDL_Surface* t16 = SDL_LoadBMP("src/16.bmp");
	SDL_Surface* t32 = SDL_LoadBMP("src/32.bmp");
	SDL_Surface* t64 = SDL_LoadBMP("src/64.bmp");
	SDL_Surface* t128 = SDL_LoadBMP("src/128.bmp");
	SDL_Surface* t256 = SDL_LoadBMP("src/256.bmp");
	SDL_Surface* t512 = SDL_LoadBMP("src/512.bmp");
	SDL_Surface* t1024 = SDL_LoadBMP("src/1024.bmp");
	SDL_Surface* t2048 = SDL_LoadBMP("src/2048.bmp");

	tableSurface = vector<SDL_Surface*>{fond,win, loose, t0, t2, t4, t8, t16, t32, t64, t128, t256, t512, t1024, t2048};

	SDL_Texture* fondTexture = nullptr;
	SDL_Texture* winTexture = nullptr;
	SDL_Texture* looseTexture = nullptr;
	SDL_Texture* t0Texture = nullptr;
	SDL_Texture* t2Texture = nullptr;
	SDL_Texture* t4Texture = nullptr;
	SDL_Texture* t8Texture = nullptr;
	SDL_Texture* t16Texture = nullptr;
	SDL_Texture* t32Texture = nullptr;
	SDL_Texture* t64Texture = nullptr;
	SDL_Texture* t128Texture = nullptr;
	SDL_Texture* t256Texture = nullptr;
	SDL_Texture* t512Texture = nullptr;
	SDL_Texture* t1024Texture = nullptr;
	SDL_Texture* t2048Texture = nullptr;

	tableTexture =vector<SDL_Texture*>{fondTexture,winTexture,looseTexture,t0Texture,t2Texture,t4Texture,t8Texture,t16Texture,t32Texture,t64Texture,t128Texture,t256Texture,t512Texture,t1024Texture,t2048Texture};
}

//initialise les textures dans le tableau
void TextureManager::initTexture() {
	for (int i = 0; i < 15;i++) {
		this->tableTexture[i] = SDL_CreateTextureFromSurface(renderer, this->tableSurface[i]);
	}
}

TextureManager::~TextureManager() {
	for (int i = 0; i < 15; i++) {
		SDL_DestroyTexture(this->tableTexture[i]);
	}
}
