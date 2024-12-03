#include "Grid.h"
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <cstdlib>  // Pour rand() et srand()
#include <ctime>    // Pour time()

// Constructeur de la classe Grid
Grid::Grid(int width, int height, int cellSize)
    : width(width), height(height), cellSize(cellSize), cells(height, std::vector<int>(width, 0)) {}

// Initialiser la grille à partir d'un fichier fourni par l'utilisateur
void Grid::initializeFromFile(const std::string& fileName) {
    std::ifstream fichier(fileName);

    if (fichier) {
        // Lire les dimensions de la grille
        fichier >> height >> width;
        cells.resize(height, std::vector<int>(width, 0));

        // Lire les états des cellules à partir du fichier
        for (int x = 0; x < height; ++x) {
            for (int y = 0; y < width; ++y) {
                fichier >> cells[x][y];
            }
        }

        fichier.close();  // Fermer le fichier après la lecture
    } else {
        // Gérer l'erreur si le fichier ne peut pas être ouvert
        std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
        exit(EXIT_FAILURE);
    }
}

// Placer un motif "Blinker" sur la grille
void Grid::placeBlinker() {
    srand(static_cast<unsigned>(time(0)));  // Initialiser le générateur aléatoire
    int x = rand() % (height - 1);  // Générer des coordonnées aléatoires dans les limites
    int y = rand() % (width - 2);

    // Placer le motif "Blinker" sur la grille
    cells[x][y] = 1;
    cells[x][y + 1] = 1;
    cells[x][y + 2] = 1;

    // Afficher dans la console les coordonnées où le Blinker est placé
    std::cout << "Blinker placé aux coordonnées (" << x << ", " << y << ")" << std::endl;
}

// Placer un motif "Glider" sur la grille
void Grid::placeGlider() {
    srand(static_cast<unsigned>(time(0)) + 1);  // Ajouter une variation pour des valeurs différentes
    int x = rand() % (height - 2);
    int y = rand() % (width - 2);

    // Placer le motif "Glider" sur la grille
    cells[x][y + 1] = 1;
    cells[x + 1][y + 2] = 1;
    cells[x + 2][y] = 1;
    cells[x + 2][y + 1] = 1;
    cells[x + 2][y + 2] = 1;

    // Afficher dans la console les coordonnées où le Glider est placé
    std::cout << "Glider placé aux coordonnées (" << x << ", " << y << ")" << std::endl;
}

// Obtenir l'état d'une cellule spécifique
int Grid::getCellState(int x, int y) const {
    return cells[x][y];
}

// Dessiner la grille sur la fenêtre SFML
void Grid::render(sf::RenderWindow &window) {
    sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));  // Créer un rectangle pour chaque cellule

    for (int x = 0; x < height; ++x) {
        for (int y = 0; y < width; ++y) {
            cell.setPosition(y * cellSize, x * cellSize);  // Positionner la cellule
            if (cells[x][y] == 1) {
                cell.setFillColor(sf::Color::White);  // Cellule vivante
            } else if (cells[x][y] == obstacle) {
                cell.setFillColor(sf::Color::Red);  // Cellules obstacles en rouge
            } else {
                cell.setFillColor(sf::Color::Black);  // Cellule morte
            }
            window.draw(cell);  // Dessiner la cellule
        }
    }
}

// Compter le nombre de voisins vivants d'une cellule
int Grid::countLivingNeighbors(int x, int y) const {
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int count = 0;

    // Parcourir les 8 voisins potentiels
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

// Calculer l'état suivant de la grille
void Grid::computeNextState() {
    std::vector<std::vector<int>> newCells = cells;
    for (int x = 0; x < height; ++x) {
        for (int y = 0; y < width; ++y) {
            if (cells[x][y] == obstacle) {
                continue;  // Cellulles obstacles ne changent pas d'état
            }

            int livingNeighbors = countLivingNeighbors(x, y);

            if (cells[x][y] == 1) {  // Cellule vivante
                if (livingNeighbors < 2 || livingNeighbors > 3) {
                    newCells[x][y] = 0;  // Cellule meurt par sous-population ou surpopulation
                }
            } else {  // Cellule morte
                if (livingNeighbors == 3) {
                    newCells[x][y] = 1;  // Cellule devient vivante par reproduction
                }
            }
        }
    }

    cells = newCells;  // Mise à jour de la grille avec les nouveaux états
}

// Compter le nombre total de cellules vivantes dans la grille
int Grid::countLivingCells() const {
    int count = 0;
    for (const auto& row : cells) {
        for (int cell : row) {
            if (cell == 1) {
                ++count;
            }
        }
    }
    return count;
}