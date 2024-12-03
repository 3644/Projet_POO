#ifndef NEIGHBOURSCHECK_H
#define NEIGHBOURSCHECK_H
#include "Grid.cpp"
#include <array>

#endif 

bool alive(std::array<std::array<int, height>, width>& grid, const int x, const int y) {
    int aliveNeighbors = 0;

    // neighbours check
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            // main cell ignored 
            if (dx == 0 && dy == 0) continue;

            int nx = x + dx;
            int ny = y + dy;

            // verify if neighbours in the right range
            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                aliveNeighbors += (grid[nx][ny] == 1);
            }
        }
    }

    // rules
    if (grid[x][y] == 1 && aliveNeighbors < 2) return false;            // less than 2 alive neigbhours -> dies
    if (grid[x][y] == 1 && (aliveNeighbors == 2 || aliveNeighbors == 3)) return true;  // 2 or 3 alive neighbours -> lives
    if (grid[x][y] == 1 && aliveNeighbors > 3) return false;            // more than 3 alive neighbours -> dies
    if (grid[x][y] == 0 && aliveNeighbors == 3) return true;            // 3 neighbours -> bacome alive 

    return false;  // default case 
}
