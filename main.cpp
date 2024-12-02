#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>

const int cellSize = 10; // Taille d'une cellule en pixels
int gridWidth;  // Largeur de la grille (nombre de colonnes)
int gridHeight; // Hauteur de la grille (nombre de lignes)
std::vector<std::vector<int>> grid;

// Fonction pour initialiser la grille à partir d'un fichier
void initializeGridFromFile(const std::string& fileName) {
    std::ifstream fichier(fileName);
    
    if (fichier) {
        // Lecture du nombre de lignes et colonnes à partir de la première ligne
        fichier >> gridHeight >> gridWidth;

        // Redimensionner la grille en fonction des valeurs lues
        grid.resize(gridHeight, std::vector<int>(gridWidth, 0));

        // Lire l'état des cellules
        for (int x = 0; x < gridHeight; ++x) {
            for (int y = 0; y < gridWidth; ++y) {
                fichier >> grid[x][y];
            }
        }

        fichier.close();
    } else {
        std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
        exit(EXIT_FAILURE);
    }
}

// Fonction pour dessiner la grille à l'écran
void renderGrid(sf::RenderWindow& window) {
    window.clear();
    sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f)); // Taille de chaque cellule

    for (int x = 0; x < gridHeight; ++x) {
        for (int y = 0; y < gridWidth; ++y) {
            if (grid[x][y] == 1) {
                cell.setFillColor(sf::Color::White); // Couleur blanche pour les cellules vivantes
            } else {
                cell.setFillColor(sf::Color::Black); // Couleur noire pour les cellules mortes
            }
            cell.setPosition(y * cellSize, x * cellSize);
            window.draw(cell);
        }
    }
    window.display();
}

int main() {
    // Initialiser la grille à partir du fichier "test.txt"
    initializeGridFromFile("/home/bapti/Projets/Projets/Projet_POO/test.txt");

    // Créer une fenêtre SFML en fonction des dimensions de la grille
    sf::RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        renderGrid(window);
        sf::sleep(sf::milliseconds(100)); // Pause de 100ms entre chaque frame
    }

    return 0;
}
