#ifndef GRID_H
#define GRID_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

class Grid {
public:
    Grid(int width, int height, int cellSize);
    void initializeFromFile(const std::string& fileName);
    void render(sf::RenderWindow &window);
    void computeNextState(); // Update l'état de la grille

private:
    int width;
    int height;
    int cellSize;
    std::vector<std::vector<int>> cells;
    int countLivingNeighbors(int x, int y) const; // Compter les voisins vivants
};

#endif
