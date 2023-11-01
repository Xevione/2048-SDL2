#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <SDL.h>
#include "Grid.h"


#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77




int main(int argc, char* argv[])
{
	int windowSize = 1000;
	int statut = EXIT_FAILURE;
	bool game = true;
	SDL_Window* window = nullptr;
	Grid* oGrid = new Grid();
	SDL_Renderer* renderer = nullptr;
	

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Erreur SDL_INIT_VIDEO : %s", SDL_GetError());
		goto Quit;
	}

	while (game = true)
	{
		SDL_RaiseWindow(window);
		window = SDL_CreateWindow("2048", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			windowSize, windowSize, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		
		oGrid->RandomTile();
		oGrid->ResetMerge();
		cout << endl;
		if (oGrid->Win() == true) {
			game = false;
			cout << "you won !";
			break;
		}
		if (oGrid->Loose() == true) {
			game = false;
			cout << "you lost !";
			break;
		}
		bool badKey = true;
		while (badKey)
		{
			badKey = false;
			int c = 0;
			switch ((c = _getch()))
			{
			case KEY_UP:
				oGrid->TilePlayUp();
				break;
			case KEY_DOWN:
				oGrid->TilePlayDown();
				break;
			case KEY_RIGHT:
				oGrid->TilePlayRight();
				break;
			case KEY_LEFT:
				oGrid->TilePlayLeft();
				break;
			default:
				badKey = true;
				break;
			}
		}

	}

	delete oGrid;

	


Quit:
	if (NULL != renderer)
		SDL_DestroyRenderer(renderer);
	if (NULL != window)
		SDL_DestroyWindow(window);
	SDL_Quit();
	delete oGrid;
	return statut;
	
}