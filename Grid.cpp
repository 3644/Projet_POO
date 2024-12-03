#include "Grid.h"
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <cstdlib>  // Pour rand() et srand()
#include <ctime>    // Pour time()

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


void Grid::placeBlinker() {
    // Générer des coordonnées aléatoires dans les limites
    srand(static_cast<unsigned>(time(0)));  // Initialiser le générateur aléatoire
    int x = rand() % (height - 1);  // Assurez-vous qu'il y a assez d'espace pour le Blinker
    int y = rand() % (width - 2);   // Assurez-vous qu'il y a assez d'espace pour le Blinker

    // Placer le motif "Blinker" sur la grille
    cells[x][y] = 1;
    cells[x][y + 1] = 1;
    cells[x][y + 2] = 1;

    // Afficher dans la console les coordonnées où le Blinker est placé
    std::cout << "Blinker placé aux coordonnées (" << x << ", " << y << ")" << std::endl;
}

void Grid::placeGlider() {
    // Générer des coordonnées aléatoires dans les limites
    srand(static_cast<unsigned>(time(0)) + 1); // Ajouter une petite variation pour des valeurs différentes
    int x = rand() % (height - 2); // Assurez-vous qu'il y a assez d'espace pour le Glider
    int y = rand() % (width - 2);  // Assurez-vous qu'il y a assez d'espace pour le Glider

    // Placer le motif "Glider" sur la grille
    cells[x][y + 1] = 1;
    cells[x + 1][y + 2] = 1;
    cells[x + 2][y] = 1;
    cells[x + 2][y + 1] = 1;
    cells[x + 2][y + 2] = 1;

    // Afficher dans la console les coordonnées où le Glider est placé
    std::cout << "Glider placé aux coordonnées (" << x << ", " << y << ")" << std::endl;
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
                continue; // Cellulles obstacles ne changent pas d'état
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
