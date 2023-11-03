#pragma once
#include <vector>
#include "Case.h"
struct SDL_Renderer;
class TextureManager;
using namespace std;

class Grid
{
public:
	vector<Case> grid;
	int iGridSize;
	SDL_Renderer* renderer;

	Grid(SDL_Renderer* rendering);

	void Affichage(TextureManager Texture);
	void ResetMerge();
	void RandomTile();

	void TilePlayDown();
	void TilePlayUp();
	void TilePlayLeft();
	void TilePlayRight();

	void MergeTile(int x, int y);
	void MoveTile(int x, int y);

	int Position(int x, int y);

	bool Win();

	bool Loose();

};
