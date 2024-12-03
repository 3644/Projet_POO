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
            } else if (cells[x][y] == obstacle) {
                cell.setFillColor(sf::Color::Red); // Cellules obstacles en rouge
            } else {
                cell.setFillColor(sf::Color::Black);
            }
            window.draw(cell);
        }
    }
}

int Grid::countLivingNeighbors(int x, int y) const {
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int count = 0;

    for (int i = 0; i < 8; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < height && ny >= 0 && ny < width) {
            if (cells[nx][ny] == 1) {
                count++;
            }
        }
    }

    return count;
}

void Grid::computeNextState() {
    std::vector<std::vector<int>> newCells = cells;

    for (int x = 0; x < height; ++x) {
        for (int y = 0; y < width; ++y) {
            if (cells[x][y] == obstacle) {
                continue; // Celles obstacles ne changent pas d'état
            }

            int livingNeighbors = countLivingNeighbors(x, y);

            if (cells[x][y] == 1) { // Cellulle en vie
                if (livingNeighbors < 2 || livingNeighbors > 3) {
                    newCells[x][y] = 0; // Cellule meurs
                }
            } else { // Cellulle est morte
                if (livingNeighbors == 3) {
                    newCells[x][y] = 1; // Cellulle deviens vivante
                }
            }
        }
    }

    cells = newCells; // Mise a jour
}
