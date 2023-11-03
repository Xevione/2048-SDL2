#include <iostream>
#include "Grid.h"
#include "Case.h"
#include <SDL.h>
#include <vector>
#include <random>
#include "Texture.h"
using namespace std;


Grid::Grid(SDL_Renderer* rendering)
{
    grid = vector<Case>(16);
    iGridSize = grid.size();
    renderer = rendering;
}

void Grid::Affichage(TextureManager Texture) {
    SDL_Rect backgrid;
    backgrid.x = 0;
    backgrid.y = 0;
    backgrid.w = 500;
    backgrid.h = 500;
    SDL_Rect rect[16];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            rect[i * 4 + j].w = 100;
            rect[i * 4 + j].h = 100;
            rect[i * 4 + j].x = 20 + 120 * i;
            rect[i * 4 + j].y = 20 + 120 * j;
        }
    }
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 255, 0);
    SDL_RenderCopy(this->renderer, Texture.tableTexture[0], NULL, &backgrid);
    for (int a = 0; a < 16;a++) {
        if (grid[a].GetValue() == 0) {
            SDL_RenderCopy(this->renderer, Texture.tableTexture[3],NULL, &rect[a]);
        }
        else if (grid[a].GetValue() == 2) {
            SDL_RenderCopy(this->renderer, Texture.tableTexture[4], NULL, &rect[a]);
        }
        else if (grid[a].GetValue() == 4) {
            SDL_RenderCopy(this->renderer, Texture.tableTexture[5], NULL, &rect[a]);
        }
        else if (grid[a].GetValue() == 8) {
            SDL_RenderCopy(this->renderer, Texture.tableTexture[6], NULL, &rect[a]);
        }
        else if (grid[a].GetValue() == 16) {
            SDL_RenderCopy(this->renderer, Texture.tableTexture[7], NULL, &rect[a]);
        }
        else if (grid[a].GetValue() == 32) {
            SDL_RenderCopy(this->renderer, Texture.tableTexture[8], NULL, &rect[a]);
        }
        else if (grid[a].GetValue() == 64) {
            SDL_RenderCopy(this->renderer, Texture.tableTexture[9], NULL, &rect[a]);
        }
        else if (grid[a].GetValue() == 128) {
            SDL_RenderCopy(this->renderer, Texture.tableTexture[10], NULL, &rect[a]);
        }
        else if (grid[a].GetValue() == 256) {
            SDL_RenderCopy(this->renderer, Texture.tableTexture[11], NULL, &rect[a]);
        }
        else if (grid[a].GetValue() == 512) {
            SDL_RenderCopy(this->renderer, Texture.tableTexture[12], NULL, &rect[a]);
        }
        else if (grid[a].GetValue() == 1024) {
            SDL_RenderCopy(this->renderer, Texture.tableTexture[13], NULL, &rect[a]);
        }
        else if (grid[a].GetValue() == 2048) {
            SDL_RenderCopy(this->renderer, Texture.tableTexture[14], NULL, &rect[a]);
        }
    }
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
    SDL_RenderPresent(this->renderer);
}

//Nous donne la position dans le tableau 1 dimension avec les coordonnées 2 dimensions
int Grid::Position(int x, int y)
{
    return (x * 4 + y);
}

// Ajoute des 2 et des 4 aléatoirement dans les emplacements vides
void Grid::RandomTile() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(0, iGridSize - 1);

    uniform_int_distribution<int> distrib4(0, 9);
    for (int i = 0; i < 2; i++) {
        int position = distribution(gen);
        int chance = distrib4(gen);
        if (grid[position].GetValue() == 0) {
            if (chance == 0) {
                grid[position].ChangeValue(4);
            }
            else
            {
                grid[position].ChangeValue(2);
            }
        }
    }

}

void Grid::MergeTile(int x, int y) {
    grid[x].ChangeValue(grid[x].GetValue() * 2);
    grid[y].ChangeValue(0);
}

void Grid::MoveTile(int x, int y)
{
    grid[x].ChangeValue(grid[y].GetValue());
    grid[y].ChangeValue(0);
}


void Grid::ResetMerge()
{
    int pos;
    for (int i = 0; i < iGridSize / 4; i++)
    {
        for (int j = 0; j < iGridSize / 4; j++)
        {
            pos = (Position(i, j));
            grid[pos].merge = false;
        }
    }
}

//déplacement et merge des cases
void Grid::TilePlayRight()
{
    int temp;
    int pos;
    for (int i = 0; i < iGridSize / 4; i++)
    {
        for (int j = 0; j < iGridSize / 4; j++)
        {

            pos = (Position(i, j));
            temp = grid[pos].GetValue();

            if (temp != 0)
            {
                if (pos - 1 < i * 4)
                {
                    pos = pos + 1;
                }
                else {
                    if (temp == grid[pos - 1].GetValue())
                    {

                        if (pos - 1 >= 0) {
                            if (grid[pos].merge == false) {
                                MergeTile(pos, pos - 1);
                                grid[pos].merge = true;
                            }
                        }
                    }
                }
            }
            else
            {
                if (pos - 1 < i * 4)
                {
                    pos = pos + 1;
                }
                else
                {
                    if (pos - 1 >= 0) {
                        if (grid[pos - 1].GetValue() != 0)
                        {
                            MoveTile(pos, pos - 1);
                            this->TilePlayRight();
                        }
                    }
                }
            }
        }
    }
}
void Grid::TilePlayLeft()
{
    int temp;
    int pos;
    for (int i = 0; i < iGridSize / 4; i++)
    {
        for (int j = 0; j < iGridSize / 4; j++)
        {
            pos = (Position(i, j));
            temp = grid[pos].GetValue();
            if (temp != 0)
            {
                if (pos + 1 >= (i + 1) * 4)
                {
                    pos = pos + 1;
                }
                else {
                    if (temp == grid[pos + 1].GetValue())
                    {
                        if (pos + 1 <= 15) {
                            if (grid[pos].merge == false) {
                                MergeTile(pos, pos + 1);
                                grid[pos].merge = true;
                            }
                        }
                    }
                }
            }
            else
            {
                if (pos + 1 >= (i + 1) * 4)
                {
                    pos = pos + 1;
                }
                else
                {
                    if (pos + 1 <= 15) {
                        if (grid[pos + 1].GetValue() != 0)
                        {
                            MoveTile(pos, pos + 1);
                            this->TilePlayLeft();
                        }
                    }
                }
            }
        }
    }
}

void Grid::TilePlayUp()
{
    int temp;
    int pos;
    for (int i = 0; i < iGridSize / 4; i++)
    {
        for (int j = 0; j < iGridSize / 4; j++)
        {
            pos = (Position(i, j));
            temp = grid[pos].GetValue();
            if (temp != 0)
            {
                if (pos + 4 > 15)
                {
                    pos = pos + 1;
                }
                else {
                    if (temp == grid[pos + 4].GetValue())
                    {
                        if (pos + 4 <= 15) {
                            if (grid[pos].merge == false) {
                                MergeTile(pos, pos + 4);
                                grid[pos].merge = true;
                            }
                        }
                    }
                }
            }
            else
            {
                if (pos + 4 > 15)
                {
                    pos = pos + 1;
                }
                else
                {
                    if (pos + 4 <= 15) {
                        if (grid[pos + 4].GetValue() != 0)
                        {
                            MoveTile(pos, pos + 4);
                            this->TilePlayUp();
                        }
                    }
                }
            }
        }
    }
}

void Grid::TilePlayDown()
{
    int temp;
    int pos;
    for (int i = 0; i < iGridSize / 4; i++)
    {
        for (int j = 0; j < iGridSize / 4; j++)
        {
            pos = (Position(i, j));
            temp = grid[pos].GetValue();

            if (temp != 0)
            {
                if (pos - 4 < 0)
                {
                    pos = pos + 1;
                }
                else {
                    if (temp == grid[pos - 4].GetValue())
                    {
                        if (pos - 4 >= 0) {
                            if (grid[pos].merge == false) {
                                MergeTile(pos, pos - 4);
                                grid[pos].merge = true;
                            }
                        }
                    }
                }
            }
            else
            {
                if (pos - 4 < 0)
                {
                    pos = pos + 1;
                }
                else
                {

                    if (pos - 4 >= 0) {
                        if (grid[pos - 4].GetValue() != 0)
                        {
                            MoveTile(pos, pos - 4);
                            this->TilePlayDown();
                        }
                    }


                }
            }
        }
    }
}



//Win / Loose conditions


bool Grid::Win() {
    int val;
    int pos;
    for (int i = 0; i < iGridSize / 4; i++)
    {
        for (int j = 0; j < iGridSize / 4; j++)
        {
            pos = (Position(i, j));
            val = grid[pos].GetValue();
            if (val == 2048) {
                return true;
            }
        }
    }
    return false;
}

bool Grid::Loose() {
    int val;
    int pos;
    int compteur = 0;
    for (int i = 0; i < iGridSize / 4; i++)
    {
        for (int j = 0; j < iGridSize / 4; j++)
        {
            pos = (Position(i, j));
            val = grid[pos].GetValue();
            if (val == 0) {
                return false;
            }
            if (val != 2048) {
                if (pos + 1 <= 15) {
                    if (val == grid[pos + 1].GetValue()) {
                        return false;
                    }
                }
                else if (pos - 1 >= 0) {
                    if (val == grid[pos - 1].GetValue()) {
                        return false;
                    }
                }
                else if (pos + 4 <= 15) {
                    if (val == grid[pos + 4].GetValue()) {
                        return false;
                    }
                }
                else if (pos - 4 >= 0) {
                    if (val == grid[pos - 4].GetValue()) {
                        return false;
                    }
                }

            }

        }
    }
    return true;

}
