#include <SFML/Graphics.hpp>
#include "Grid.h"

int main() {
    // Window and grid configuration
    const int cellSize = 10;
    const int gridWidth = 80;
    const int gridHeight = 80;
    const int windowWidth = gridWidth * cellSize;
    const int windowHeight = gridHeight * cellSize;

    // Create SFML window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Game of Life");

    // Create the grid object
    Grid grid(gridWidth, gridHeight, cellSize);

    // Initialize the grid from a file ("test.txt")
    grid.initializeFromFile("test.txt");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Compute the next state of the grid
        grid.computeNextState();

        // Render the grid
        window.clear();
        grid.render(window);
        window.display();

        // Pause to slow down the simulation (100ms)
        sf::sleep(sf::milliseconds(100));
    }

    return 0;
}
