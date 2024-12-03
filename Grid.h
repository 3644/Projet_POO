#ifndef GRID_H
#define GRID_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

class Grid {
public:
    Grid(int width, int height, int cellSize);  // Constructeur
    void initializeFromFile(const std::string& fileName);  // Initialiser la grille depuis un fichier
    void render(sf::RenderWindow &window);  // Dessiner la grille sur la fenêtre
    void computeNextState(); // Calculer l'état suivant de la grille

    int getWidth() const { return width; }   // Accesseur pour la largeur
    int getHeight() const { return height; } // Accesseur pour la hauteur
    void placeBlinker();  // Placer un motif "Blinker"
    void placeGlider();  // Placer un motif "Glider"
    int countLivingCells() const;  // Compter le nombre de cellules vivantes
    int getCellState(int x, int y) const; // Obtenir l'état d'une cellule spécifique

private:
    int width;  // Largeur de la grille
    int height; // Hauteur de la grille
    int cellSize; // Taille de chaque cellule pour l'affichage graphique
    std::vector<std::vector<int>> cells;  // Représentation de la grille avec un tableau 2D
    int countLivingNeighbors(int x, int y) const; // Compter les voisins vivants d'une cellule
    static const int obstacle = -1; // Valeur pour représenter les cellules obstacles
};

#endif