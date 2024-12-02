#include <SFML/Graphics.hpp>
#include "Grid.h"

int main() {
    const int cellSize = 10;
    const int windowWidth = 800;
    const int windowHeight = 800;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Game of Life");
    Grid grid(80, 80, cellSize); // Crée une grille de 80x80 cellules

    // Initialise la grille à partir d'un fichier (test.txt)
    grid.initializeFromFile("test.txt");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Rendu de la grille
        window.clear();
        grid.render(window);
        window.display();

        sf::sleep(sf::milliseconds(100)); // Pause pour ralentir le rafraîchissement
    }

    return 0;
}
