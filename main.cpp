#include <SFML/Graphics.hpp>
#include "Grid.h"
#include <iostream>
#include <unistd.h>

int main() {
    // Ask the user to provide a file path
    std::string filePath;
    std::cout << "Please enter the path to the initial state file: ";
    std::cin >> filePath;

    // Ask the user to choose a mode
    int mode;
    std::cout << "Tapez 1 pour le Mode Console.\n";
    std::cout << "Tapez 0 pour le Mode Graphique.\n";
    std::cin >> mode;
    int sleep_time;

    if (mode == 1) {
        std::cout << "Erreur" << std::endl;
        return 0;
    } else if (mode == 0) {
        std::cout << "Choissisez la durée entre les itérations (en millisecondes) : ";
        std::cin >> sleep_time;
        sleep_time = sleep_time / 1000;

        // Window and grid configuration
        const int cellSize = 10;

        // Create the grid object
        Grid grid(0, 0, cellSize);  // Les dimensions seront mises à jour par le fichier

        // Initialize the grid from the file provided by the user
        grid.initializeFromFile(filePath);

        // Mettre à jour la taille de la fenêtre en fonction de la grille
        const int windowWidth = grid.getWidth() * cellSize;
        const int windowHeight = grid.getHeight() * cellSize;

        // Create SFML window
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Game of Life");

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

            // Pause
            sleep(sleep_time);
        }
    }

    return 0;
}
