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

void Grid::Affichage() {
    fondTexture = SDL_CreateTextureFromSurface(this->renderer, fond);
    t0Texture = SDL_CreateTextureFromSurface(this->renderer, t0);
    t2Texture = SDL_CreateTextureFromSurface(this->renderer, t2);
    t4Texture = SDL_CreateTextureFromSurface(this->renderer, t4);
    t8Texture = SDL_CreateTextureFromSurface(this->renderer, t8);
    t16Texture = SDL_CreateTextureFromSurface(this->renderer, t16);
    t32Texture = SDL_CreateTextureFromSurface(this->renderer, t32);
    t64Texture = SDL_CreateTextureFromSurface(this->renderer, t64);
    t128Texture = SDL_CreateTextureFromSurface(this->renderer, t128);
    t256Texture = SDL_CreateTextureFromSurface(this->renderer, t256);
    t512Texture = SDL_CreateTextureFromSurface(this->renderer, t512);
    t1024Texture = SDL_CreateTextureFromSurface(this->renderer, t1024);
    t2048Texture = SDL_CreateTextureFromSurface(this->renderer, t2048);
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
    SDL_RenderCopy(this->renderer, fondTexture, NULL, &backgrid);
    for (int a = 0; a < 16;a++) {
        if (grid[a].GetValue() == 0) {
            SDL_RenderCopy(this->renderer,t0Texture,NULL, &rect[a]);
        }
        else if (grid[a].GetValue() == 2) {
            SDL_RenderCopy(this->renderer, t2Texture, NULL, &rect[a]);
        }
        else if (grid[a].GetValue() == 4) {
            SDL_RenderCopy(this->renderer, t4Texture, NULL, &rect[a]);
        }
        else if (grid[a].GetValue() == 8) {
            SDL_RenderCopy(this->renderer, t8Texture, NULL, &rect[a]);
        }
        else if (grid[a].GetValue() == 16) {
            SDL_RenderCopy(this->renderer, t16Texture, NULL, &rect[a]);
        }
        else if (grid[a].GetValue() == 32) {
            SDL_RenderCopy(this->renderer, t32Texture, NULL, &rect[a]);
        }
        else if (grid[a].GetValue() == 64) {
            SDL_RenderCopy(this->renderer, t64Texture, NULL, &rect[a]);
        }
        else if (grid[a].GetValue() == 128) {
            SDL_RenderCopy(this->renderer, t128Texture, NULL, &rect[a]);
        }
        else if (grid[a].GetValue() == 256) {
            SDL_RenderCopy(this->renderer, t256Texture, NULL, &rect[a]);
        }
        else if (grid[a].GetValue() == 512) {
            SDL_RenderCopy(this->renderer, t512Texture, NULL, &rect[a]);
        }
        else if (grid[a].GetValue() == 1024) {
            SDL_RenderCopy(this->renderer, t1024Texture, NULL, &rect[a]);
        }
        else if (grid[a].GetValue() == 2048) {
            SDL_RenderCopy(this->renderer, t2048Texture, NULL, &rect[a]);
        }
    }
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
    SDL_RenderPresent(this->renderer);
    SDL_DestroyTexture(fondTexture);
    SDL_DestroyTexture(t0Texture);
    SDL_DestroyTexture(t2Texture);
    SDL_DestroyTexture(t4Texture);
    SDL_DestroyTexture(t8Texture);
    SDL_DestroyTexture(t16Texture);
    SDL_DestroyTexture(t32Texture);
    SDL_DestroyTexture(t64Texture);
    SDL_DestroyTexture(t128Texture);
    SDL_DestroyTexture(t256Texture);
    SDL_DestroyTexture(t512Texture);
    SDL_DestroyTexture(t1024Texture);
    SDL_DestroyTexture(t2048Texture);
}

//Nous donne la position dans le tableau 1 dimension avec les coordonn�es 2 dimensions
int Grid::Position(int x, int y)
{
    return (x * 4 + y);
}

// Ajoute des 2 et des 4 al�atoirement dans les emplacements vides
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

//d�placement et merge des cases
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
