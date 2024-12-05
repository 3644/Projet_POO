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

// Placer un motif "Blinker" à une position donnée
void Grid::placeBlinker(int x, int y) {
    if (x >= 0 && x < height - 1 && y >= 0 && y < width - 2) { // Vérifier que le Blinker tient dans la grille
        cells[x][y] = 1;
        cells[x][y + 1] = 1;
        cells[x][y + 2] = 1;
        std::cout << "Blinker placé aux coordonnées (" << x << ", " << y << ")" << std::endl;
    } else {
        std::cerr << "Erreur : Le Blinker dépasse les limites de la grille." << std::endl;
    }
}


// Placer un motif "Glider" à une position donnée
void Grid::placeGlider(int x, int y) {
    if (x >= 0 && x < height - 2 && y >= 0 && y < width - 2) { // Vérifier que le Glider tient dans la grille
        cells[x][y + 1] = 1;
        cells[x + 1][y + 2] = 1;
        cells[x + 2][y] = 1;
        cells[x + 2][y + 1] = 1;
        cells[x + 2][y + 2] = 1;
        std::cout << "Glider placé aux coordonnées (" << x << ", " << y << ")" << std::endl;
    } else {
        std::cerr << "Erreur : Le Glider dépasse les limites de la grille." << std::endl;
    }
}


// Obtenir l'état d'une cellule spécifique
int Grid::getCellState(int x, int y) const {
    return cells[x][y];
}

// Dessiner la grille sur la fenêtre SFML
void Grid::render(sf::RenderWindow &window) {
    for (int x = 0; x < height; ++x) {
        for (int y = 0; y < width; ++y) {
            sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f)); // Créer un rectangle pour chaque cellule
            cell.setPosition(y * cellSize, x * cellSize); // Positionner la cellule
            
            if (cells[x][y] == 1) {
                cell.setFillColor(sf::Color::White);  // Cellule vivante
            } else if (cells[x][y] == 2) {
                cell.setFillColor(sf::Color::Red);    // Obstacle mort
            } else if (cells[x][y] == 3) {
                cell.setFillColor(sf::Color::Blue);   // Obstacle vivant
            } else {
                cell.setFillColor(sf::Color::Black);  // Cellule morte
            }

            window.draw(cell); // Dessiner la cellule
        }
    }
}


// Compter le nombre de voisins vivants d'une cellule
int Grid::countLivingNeighbors(int x, int y) const {
    // Tableau des décalages pour les 8 voisins potentiels
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1}; // Variations de l'axe x pour aller vers chaque voisin
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1}; // Variations de l'axe y pour aller vers chaque voisin
    int count = 0;

    // Parcourir les 8 voisins potentiels autour de la cellule (x, y)
    for (int i = 0; i < 8; ++i) {
        int nx = x + dx[i];  // Calculer la coordonnée x du voisin
        int ny = y + dy[i];  // Calculer la coordonnée y du voisin

        // Vérifier si les coordonnées du voisin sont dans les limites de la grille
        if (nx >= 0 && nx < height && ny >= 0 && ny < width) {
            // Si la cellule voisine est vivante (valeur 1) ou obstacle vivant (valeur 3), incrémenter le compteur
            if (cells[nx][ny] == 1 || cells[nx][ny] == 3) {
                count++;
            }
        }
    }
    return count;  // Retourner le nombre de voisins vivants
}


// Calculer l'état suivant de la grille
void Grid::computeNextState() {
    std::vector<std::vector<int>> newCells = cells; // Créer une copie des états actuels

    // Parcourir toutes les cellules de la grille
    for (int x = 0; x < height; ++x) {
        for (int y = 0; y < width; ++y) {
            // Ignorer les cellules obstacles, elles ne changent pas d'état
            if (cells[x][y] == 2 || cells[x][y] == 3) {
                continue;
            }

            // Compter les voisins vivants de la cellule actuelle
            int livingNeighbors = countLivingNeighbors(x, y);

            // Règles pour les cellules vivantes
            if (cells[x][y] == 1) {  // Cellule vivante
                if (livingNeighbors < 2 || livingNeighbors > 3) {
                    newCells[x][y] = 0;  // Cellule meurt par sous-population ou surpopulation
                }
            } else {  // Cellules mortes
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

void Grid::placeObstacle(int x, int y, int state) {
    if (x >= 0 && x < height && y >= 0 && y < width) {
        if (state == 2 || state == 3) {
            cells[x][y] = state;
            std::cout << "Obstacle placé aux coordonnées (" << x << ", " << y << ") avec état " << state << "." << std::endl;
        } else {
            std::cerr << "Erreur : L'état de l'obstacle doit être 2 (mort) ou 3 (vivant)." << std::endl;
        }
    } else {
        std::cerr << "Erreur : Les coordonnées sont en dehors des limites de la grille." << std::endl;
    }
}

void Grid::placeRandomObstacle(int state) {
    srand(static_cast<unsigned>(time(0)) + rand()); // Initialise le générateur aléatoire avec une variation
    int x = rand() % height;
    int y = rand() % width;

    placeObstacle(x, y, state);
}
