#include "GameOfLife.h"
#include <iostream>
#include <thread>

void GameOfLife::DebugGrid(const std::vector<int>& grid, const int sizeX, const int sizeY)
{
    for (int i = 0; i < sizeY; ++i)
    {
        for (int j = 0; j < sizeX; j++)
        {
            std::cout << grid[j + sizeX * i] << " ";
        }
        std::cout << '\n';
    }
    std::cout << "\n\n";
}

std::vector<int> GameOfLife::GetNeighborCells(const int cell, const std::vector<int>& grid, const int sizeX, const int sizeY, const bool alive)
{
    std::vector<int> neighbors;

    const int x = cell % sizeX;
    const int y = cell / sizeX;

    for (int neighborsY = -1; neighborsY <= 1; ++neighborsY)
    {
        for (int neighborsX = -1; neighborsX <= 1; ++neighborsX)
        {
            if (neighborsX == 0 && neighborsY == 0)
                continue;
            
            const int neighborX = x + neighborsX;
            const int neighborY = y + neighborsY;
            if (neighborX >= 0 && neighborX < sizeX && neighborY >= 0 && neighborY < sizeY)
                neighbors.push_back(neighborX + neighborY * sizeX);
        }
    }
        

    for (int i = 0; i < neighbors.size(); ++i)
    {
        if ((alive && grid[neighbors[i]] == 0) || (!alive && grid[neighbors[i]] == 1))
        {
            neighbors.erase(neighbors.begin() + i);
            --i;
        }
    }

    return neighbors;
}

void GameOfLife::StartGameOfLife(std::vector<int>& grid, std::vector<int>& aliveCells, const int sizeX, const int sizeY, const int nbIterations)
{
    if (aliveCells.empty()) return;

    for (const int aliveCell : aliveCells)
    {
        grid[aliveCell] = 1;
    }

    DebugGrid(grid, sizeX, sizeY);

    for (int i = 0; i < nbIterations; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000LL));
        std::vector<int> changeCells;
        for (int aliveCell : aliveCells)
        {
            if (GetNeighborCells(aliveCell, grid, sizeX, sizeY, true).size() < 2 || GetNeighborCells(aliveCell, grid, sizeX, sizeY, true).size() > 3)
            {
                changeCells.push_back(aliveCell);
            }

            std::vector<int> deadCells = GetNeighborCells(aliveCell, grid, sizeX, sizeY, false);
            for (int deadCell : deadCells)
            {
                if (GetNeighborCells(deadCell, grid, sizeX, sizeY, true).size() == 3)
                {
                    changeCells.push_back(deadCell);
                }
            }
        }

        for (int changeCell : changeCells)
        {
            if (grid[changeCell] == 1)
            {
                grid[changeCell] = 0;
                for (int k = 0; k < aliveCells.size(); k++)
                {
                    if (aliveCells[k] == changeCell)
                    {
                        aliveCells.erase(aliveCells.begin() + k);
                    }
                }
            }
            else
            {
                grid[changeCell] = 1;
                aliveCells.push_back(changeCell);
            }
        }
        DebugGrid(grid, sizeX, sizeY);
    }
}
