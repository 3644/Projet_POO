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
    void setToricMode(bool isToric) { toric = isToric; } // Activer ou désactiver le mode torique
    int getWidth() const { return width; }   // Accesseur pour la largeur
    int getHeight() const { return height; } // Accesseur pour la hauteur
    void placeBlinker(int x, int y);  // Ajouter des coordonnées explicites
    void placeGlider(int x, int y);  // Ajouter des coordonnées explicites
    int countLivingCells() const;  // Compter le nombre de cellules vivantes
    int getCellState(int x, int y) const; // Obtenir l'état d'une cellule spécifique
    void placeObstacle(int x, int y, int state); // Méthode pour placer un obstacle vivant ou mort
    void placeRandomObstacle(int state); // Déclaration de la méthode pour placer un obstacle de manière aléatoire

private:
    int width;  // Largeur de la grille
    int height; // Hauteur de la grille
    int cellSize; // Taille de chaque cellule pour l'affichage graphique
    std::vector<std::vector<int>> cells;  // Représentation de la grille avec un tableau 2D
    int countLivingNeighbors(int x, int y) const; // Compter les voisins vivants d'une cellule
    bool toric; // Indique si la grille est torique

};

#endif