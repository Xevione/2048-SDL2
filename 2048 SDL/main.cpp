#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <SDL.h>
#include "Grid.h"




int main(int argc, char* argv[])
{
	int windowSize = 1000;
	int statut = EXIT_FAILURE;
	bool Game = true;
	SDL_Window* window = NULL;
	Grid* oGrid = new Grid();
	SDL_Renderer* renderer = NULL;
	SDL_Surface* bomba = NULL;
	SDL_Texture* bombaTexture = NULL;
	bomba = SDL_LoadBMP("src/bomba.bmp");
	

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Erreur SDL_INIT_VIDEO : %s", SDL_GetError());
		goto Quit;
	}

	SDL_RaiseWindow(window);
	

	window = SDL_CreateWindow("2048", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		windowSize, windowSize, SDL_WINDOW_SHOWN);


	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Rect grid;
	grid.x = 250;
	grid.y = 250;
	grid.w = 500;
	grid.h = 500;
	SDL_Rect rect[16];

	for (int i = 0; i < 4 ; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			rect[i * 4 + j].w = 100;
			rect[i * 4 + j].h = 100;
			rect[i * 4 + j].x = 270 + 120 * i;
			rect[i * 4 + j].y = 270 + 120 * j;

		}
	}
	bombaTexture = SDL_CreateTextureFromSurface(renderer, bomba);
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
	SDL_RenderFillRect(renderer, &grid);
	//SDL_RenderDrawRect(renderer, &grid);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0,0);
	SDL_RenderFillRect(renderer, rect);




	SDL_RenderPresent(renderer);
	SDL_Delay(5000);


Quit:
	if (NULL != renderer)
		SDL_DestroyRenderer(renderer);
	if (NULL != window)
		SDL_DestroyWindow(window);
	SDL_Quit();
	delete oGrid;
	return statut;
	
}