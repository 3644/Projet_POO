#include "Grid.h"
#include <fstream>
#include <iostream>

// Constructeur pour initialiser la grille
Grid::Grid(int width, int height, int cellSize)
    : width(width), height(height), cellSize(cellSize), cells(height, std::vector<int>(width, 0)) {}

// Méthode pour initialiser la grille à partir d'un fichier
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

// Méthode pour dessiner la grille
void Grid::render(sf::RenderWindow &window) {
    sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));

    for (int x = 0; x < height; ++x) {
        for (int y = 0; y < width; ++y) {
            cell.setPosition(y * cellSize, x * cellSize);
            if (cells[x][y] == 1) {
                cell.setFillColor(sf::Color::White); // Cellules vivantes en blanc
            } else {
                cell.setFillColor(sf::Color::Black); // Cellules mortes en noir
            }
            window.draw(cell);
        }
    }
}
