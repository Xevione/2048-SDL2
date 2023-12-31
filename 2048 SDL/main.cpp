#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <SDL.h>
#include "Grid.h"
#include "Texture.h"


int main(int argc, char* argv[])
{
	int windowSize = 500;
	int statut = EXIT_FAILURE;
	bool game = true;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event event;
	
	SDL_RaiseWindow(window);

	window = SDL_CreateWindow("2048", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		windowSize, windowSize, SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	Grid* oGrid = new Grid(renderer);
	oGrid->RandomTile();
	

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Erreur SDL_INIT_VIDEO : %s", SDL_GetError());
		goto Quit;
	}
	if (!window)
	{
		std::cout << "Failed to create window\n";
		return -1;
	}

	//game loop
	while (game = true)
	{
		//texture managment
		TextureManager* Texture = new TextureManager(renderer);
		Texture->initTexture();
		SDL_RenderClear(renderer);
		oGrid->ResetMerge();
		oGrid->Affichage(*Texture);

		//win management
		if (oGrid->Win() == true) {
			SDL_RenderClear(oGrid->renderer);
			TextureManager* Texture = new TextureManager(renderer);
			Texture->initTexture();
			SDL_RenderCopy(oGrid->renderer, Texture->tableTexture[1], NULL, NULL);
			SDL_RenderPresent(oGrid->renderer);
			game = false;
			delete Texture;
			SDL_Delay(2000);
			goto Quit;
		}

		//loose managament
		if (oGrid->Loose() == true) {
			SDL_RenderClear(oGrid->renderer);
			TextureManager* Texture = new TextureManager(renderer);
			Texture->initTexture();
			SDL_RenderCopy(oGrid->renderer, Texture->tableTexture[2], NULL, NULL);
			SDL_RenderPresent(oGrid->renderer);
			game = false;
			delete Texture;
			SDL_Delay(2000);
			goto Quit;
		}

		//input manager
		SDL_WaitEvent(&event);
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
				oGrid->TilePlayDown();
				oGrid->RandomTile();
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
				oGrid->TilePlayUp();
				oGrid->RandomTile();
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
				oGrid->TilePlayLeft();
				oGrid->RandomTile();
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
				oGrid->TilePlayRight();
				oGrid->RandomTile();

			}
		}
		delete Texture;
	}

Quit:
	if (NULL != renderer)
		SDL_DestroyRenderer(renderer);
	if (NULL != window)
		SDL_DestroyWindow(window);
	SDL_Quit();
	delete oGrid;
	return statut;
	
}