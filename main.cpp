#include "GameOfLife.h"

int main()
{
    const int nbIterations = 50;
    const int sizeX = 10;
    const int sizeY = 10;
    
    std::vector<int> grid(sizeX * sizeY, 0);
    std::vector<int> aliveCells = {33, 35, 25, 44, 45}; // Glider pattern
    
    GameOfLife::StartGameOfLife(grid, aliveCells, sizeX, sizeY, nbIterations);
    return 0;
}

