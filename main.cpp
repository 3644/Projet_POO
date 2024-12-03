#include "Grid.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>

int main() {
    // Demander à l'utilisateur de fournir un nom de fichier (sans le chemin complet)
    std::string fileName;
    std::cout << "Donnez le nom du fichier d'état initial (dans le fichier ./etats): ";
    std::cin >> fileName;

    // Construire le chemin complet du fichier
    std::string filePath = "./etats/" + fileName;

    // Demander à l'utilisateur de choisir un mode
    int mode;
    std::cout << "Tapez 1 pour le Mode Console.\n";
    std::cout << "Tapez 0 pour le Mode Graphique.\n";
    std::cin >> mode;
    int sleep_time;

    if (mode == 1) {
        std::cout << "Erreur" << std::endl;
        return 0;
    } else if (mode == 0) {
        std::cout << "Choisissez la durée entre les itérations (en millisecondes) : ";
        std::cin >> sleep_time;
        sleep_time = sleep_time / 1000;

        // Configuration de la fenêtre et de la grille
        const int cellSize = 35;

        // Créer l'objet grille
        Grid grid(0, 0, cellSize);  // Les dimensions seront mises à jour par le fichier

        // Initialiser la grille à partir du fichier fourni par l'utilisateur
        grid.initializeFromFile(filePath);

        // Mettre à jour la taille de la fenêtre en fonction de la grille
        const int windowWidth = grid.getWidth() * cellSize;
        const int windowHeight = grid.getHeight() * cellSize;

        // Créer la fenêtre SFML
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Game of Life");

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            // Calculer le prochain état de la grille
            grid.computeNextState();

            // Afficher la grille
            window.clear();
            grid.render(window);
            window.display();

            // Pause
            sleep(sleep_time);
        }
    }

    return 0;
}
