#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <SDL.h>

int main(int argc, char* argv[])
{
	int windowSize = 720;
	int statut = EXIT_FAILURE;
	bool Game = true;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Event event;
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Erreur SDL_INIT_VIDEO : %s", SDL_GetError());
		goto Quit;
	}

	SDL_RaiseWindow(window);


	window = SDL_CreateWindow("2048", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		windowSize, windowSize, SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Delay(5000);



Quit:
	if (NULL != renderer)
		SDL_DestroyRenderer(renderer);
	if (NULL != window)
		SDL_DestroyWindow(window);
	SDL_Quit();
	return statut;
	
}