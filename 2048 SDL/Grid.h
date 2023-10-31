#pragma once
#include "Case.h"
#include <vector>
#include <string>
using namespace std;

class Grid
{
public:
	vector<Case> grid;
	int iGridSize;

	Grid();

	void Affichage();
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