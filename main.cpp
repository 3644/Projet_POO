#include "Grid.h"
#include <SFML/Graphics.hpp>  // Pour l'affichage graphique avec SFML
#include <iostream>
#include <fstream>
#include <unistd.h>           // Pour la fonction sleep
#include <filesystem>         // Pour créer des dossiers

namespace fs = std::filesystem;

int main() {
    // Demander à l'utilisateur de fournir un nom de fichier (sans le chemin complet)
    std::string fileName;
    std::cout << "Donnez le nom du fichier d'état initial (dans le dossier ./etats): ";
    std::cin >> fileName;

    // Construire le chemin complet du fichier
    std::string filePath = "./etats/" + fileName;

    // Demander à l'utilisateur de fournir la taille des cellules
    int cellSize;
    std::cout << "Entrez la taille des cellules (en pixels) : ";
    std::cin >> cellSize;

    // Créer l'objet grille
    Grid grid(0, 0, cellSize);  // La taille des cellules est définie par l'utilisateur

    // Initialiser la grille à partir du fichier fourni par l'utilisateur
    grid.initializeFromFile(filePath);

    // Demander à l'utilisateur de choisir un mode (console ou graphique)
    int mode;
    std::cout << "Tapez 1 pour le Mode Console.\n";
    std::cout << "Tapez 0 pour le Mode Graphique.\n";
    std::cin >> mode;

    if (mode == 1) {
        // Mode console
        int iterations;
        std::cout << "Combien d'itérations voulez-vous exécuter ? ";
        std::cin >> iterations;

        // Créer le dossier de sortie pour les fichiers d'état après chaque itération
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
                outputFile.close();  // Fermer le fichier après l'écriture
            } else {
                // Gérer l'erreur si le fichier ne peut pas être créé
                std::cout << "Erreur : impossible de créer le fichier " << outputFilePath << std::endl;
                return 1;  // Arrêter l'exécution en cas d'erreur
            }

            // Calculer le prochain état de la grille
            grid.computeNextState();
        }
    } else if (mode == 0) {
        // Mode graphique
        int sleep_time;
        std::cout << "Choisissez la durée entre les itérations 00 (en millisecondes) : ";
        std::cin >> sleep_time; 

        // Calculer les dimensions de la fenêtre en fonction de la grille et de la taille des cellules
        const int windowWidth = grid.getWidth() * cellSize;
        const int windowHeight = grid.getHeight() * cellSize;

        // Créer la fenêtre SFML pour l'affichage du jeu
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Game of Life");

        bool paused = false;  // Variable pour contrôler l'état de pause

        // Boucle principale de la fenêtre graphique
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    // Fermer la fenêtre si l'utilisateur clique sur la croix
                    window.close();
                } else if (event.type == sf::Event::KeyPressed) {
                    // Gérer les différentes touches pressées par l'utilisateur
                    if (event.key.code == sf::Keyboard::B) {
                        grid.placeBlinker();  // Placer un motif Blinker sur la grille
                    } else if (event.key.code == sf::Keyboard::G) {
                        grid.placeGlider();  // Placer un motif Glider sur la grille
                    } else if (event.key.code == sf::Keyboard::P) {
                        paused = !paused;  // Basculer l'état de pause
                    }
                }
            }

            if (!paused) {
                // Calculer le prochain état de la grille uniquement si le jeu n'est pas en pause
                grid.computeNextState();

                // Calculer le nombre de cellules vivantes et mortes
                int livingCells = grid.countLivingCells();
                int totalCells = grid.getWidth() * grid.getHeight();
                int deadCells = totalCells - livingCells;

                // Afficher dans la console le nombre de cellules vivantes et mortes
                std::cout << "Vivantes: " << livingCells << " | Mortes: " << deadCells << std::endl;
            }

            // Effacer la fenêtre pour un nouvel affichage
            window.clear();
            grid.render(window);  // Dessiner la grille dans la fenêtre
            window.display();  // Afficher le nouveau contenu de la fenêtre

            // Pause entre les itérations pour réguler la vitesse d'affichage
            if (!paused) {
                usleep(sleep_time*1000); //microsecondes en millisecondes
            }
        }

        return 0;  // Terminer le programme
    }
}
