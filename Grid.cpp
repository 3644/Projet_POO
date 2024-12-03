#include "Grid.h"
#include <fstream>
#include <iostream>
#include <sys/stat.h>

Grid::Grid(int width, int height, int cellSize)
    : width(width), height(height), cellSize(cellSize), cells(height, std::vector<int>(width, 0)) {}

void Grid::initializeFromFile(const std::string& fileName) {
    std::ifstream fichier(fileName);

    if (fichier) {
        fichier >> height >> width;
        cells.resize(height, std::vector<int>(width, 0));

        for (int x = 0; x < height; ++x) {
            for (int y = 0; y < width; ++y) {
                fichier >> cells[x][y];
            }
        }

        fichier.close();
    } else {
        std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Grid::render(sf::RenderWindow &window) {
    sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));

    for (int x = 0; x < height; ++x) {
        for (int y = 0; y < width; ++y) {
            cell.setPosition(y * cellSize, x * cellSize);
            if (cells[x][y] == 1) {
                cell.setFillColor(sf::Color::White);
            } else {
                cell.setFillColor(sf::Color::Black);
            }
            window.draw(cell);
        }
    }
}

int Grid::countLivingNeighbors(int x, int y) const {
    int aliveNeighbors = 0;

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue; // Ignore the current cell

            int nx = x + dx;
            int ny = y + dy;

            if (nx >= 0 && nx < height && ny >= 0 && ny < width) {
                aliveNeighbors += cells[nx][ny];
            }
        }
    }

    return aliveNeighbors;
}

void Grid::computeNextState() {
    std::vector<std::vector<int>> newCells = cells;

    for (int x = 0; x < height; ++x) {
        for (int y = 0; y < width; ++y) {
            int aliveNeighbors = countLivingNeighbors(x, y);

            // Apply Game of Life rules
            if (cells[x][y] == 1 && aliveNeighbors < 2) {
                newCells[x][y] = 0; // Dies due to underpopulation
            } else if (cells[x][y] == 1 && (aliveNeighbors == 2 || aliveNeighbors == 3)) {
                newCells[x][y] = 1; // Lives
            } else if (cells[x][y] == 1 && aliveNeighbors > 3) {
                newCells[x][y] = 0; // Dies due to overpopulation
            } else if (cells[x][y] == 0 && aliveNeighbors == 3) {
                newCells[x][y] = 1; // Becomes alive due to reproduction
            }
        }
    }

    cells = newCells; // Update the grid to the next state
}
