#pragma once
#include <vector>

class GameOfLife
{
public:

    static void DebugGrid(const std::vector<int>& grid, int sizeX, int sizeY);

    static std::vector<int> GetNeighborCells(int cell, const std::vector<int>& grid, int sizeX, int sizeY, bool alive);

    static void StartGameOfLife(std::vector<int>& grid, std::vector<int>& aliveCells, int sizeX, int sizeY, int nbIterations);
};
