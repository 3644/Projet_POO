#include "Grid.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <filesystem>  // Pour créer des dossiers

namespace fs = std::filesystem;

int main() {
    // Demander à l'utilisateur de fournir un nom de fichier (sans le chemin complet)
    std::string fileName;
    std::cout << "Donnez le nom du fichier d'état initial (dans le dossier ./etats): ";
    std::cin >> fileName;

    // Construire le chemin complet du fichier
    std::string filePath = "./etats/" + fileName;

    // Demander à l'utilisateur de choisir un mode
    int mode;
    std::cout << "Tapez 1 pour le Mode Console.\n";
    std::cout << "Tapez 0 pour le Mode Graphique.\n";
    std::cin >> mode;

    if (mode == 1) {
        // Mode console
        int iterations;
        std::cout << "Combien d'itérations voulez-vous exécuter ? ";
        std::cin >> iterations;

        // Créer l'objet grille
        Grid grid(0, 0, 1);  // La taille des cellules n'a pas d'importance ici

        // Initialiser la grille à partir du fichier fourni par l'utilisateur
        grid.initializeFromFile(filePath);

        // Créer le dossier de sortie
        std::string outputDir = "./" + fileName + "_out";
        fs::create_directory(outputDir);

        // Effectuer les itérations et écrire chaque état dans un fichier
        for (int i = 0; i < iterations; ++i) {
            // Nom du fichier de sortie pour chaque itération
            std::string outputFilePath = outputDir + "/iteration_" + std::to_string(i) + ".txt";

            // Ouvrir le fichier de sortie
            std::ofstream outputFile(outputFilePath);
            if (outputFile) {
                // Écrire l'état actuel de la grille dans le fichier
                for (int x = 0; x < grid.getHeight(); ++x) {
                    for (int y = 0; y < grid.getWidth(); ++y) {
                        outputFile << grid.getCellState(x, y) << " ";
                    }
                    outputFile << "\n";
                }
                outputFile.close();
            } else {
                std::cout << "Erreur : impossible de créer le fichier " << outputFilePath << std::endl;
                return 1;
            }

            // Calculer le prochain état de la grille
            grid.computeNextState();
        }
    } else if (mode == 0) {
        // Mode graphique
        int sleep_time;
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

    bool paused = false;  // Variable pour contrôler l'état de pause

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::B) {
                    grid.placeBlinker();
                } else if (event.key.code == sf::Keyboard::G) {
                    grid.placeGlider();
                } else if (event.key.code == sf::Keyboard::P) {
                    paused = !paused;  // Basculer l'état de pause
                }
            }
        }

            // Calculer le prochain état de la grille
    if (!paused) {
        // Calculer le prochain état de la grille uniquement si le jeu n'est pas en pause
        grid.computeNextState();
    }

            // Afficher la grille
            window.clear();
            grid.render(window);
            window.display();

            // Pause
        if (!paused) {
            sleep(sleep_time);
        }
    }

    return 0;
}
}