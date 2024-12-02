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

private:
    int width;
    int height;
    int cellSize;
    std::vector<std::vector<int>> cells;
};

#endif
