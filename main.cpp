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

    bool isToric;
    std::cout << "Souhaitez-vous activer le mode torique ? (1 pour oui, 0 pour non) : ";
    std::cin >> isToric;
    grid.setToricMode(isToric); // Activer ou désactiver le mode torique

    int sleep_time;
    std::cout << "Choisissez la durée entre les itérations (en millisecondes) : ";
    std::cin >> sleep_time;

    // Demander à l'utilisateur de choisir un mode (console ou graphique)
    int mode;
    std::cout << "Tapez 1 pour le Mode Console.\n";
    std::cout << "Tapez 0 pour le Mode Graphique.\n";
    std::cin >> mode;

    if (mode == 1) {
        // Mode console
        int iterations;
        std::cout << "Combien d'itérations voulez-vous exécuter ? (Entrez -1 pour une exécution infinie jusqu'à stabilisation) ";
        std::cin >> iterations;

        // Demander à l'utilisateur s'il souhaite un mode manuel ou automatique
        int manualMode;
        std::cout << "Tapez 1 pour le mode manuel (b/g/n pour interagir), ou 0 pour le mode automatique : ";
        std::cin >> manualMode;

        int currentIteration = 0;
        while (iterations == -1 || currentIteration < iterations) {
            if (manualMode == 1) {
                // Mode manuel : demander l'action à effectuer
                char action;
                std::cout << "Entrez 'b' pour ajouter un Blinker, 'g' pour ajouter un Glider, 'o' pour un obstacle, 'n' pour continuer : ";
                std::cin >> action;

                if (action == 'b') {
                    // Ajouter un Blinker à une position spécifique
                    int x, y;
                    std::cout << "Entrez les coordonnées (x, y) pour le Blinker : ";
                    std::cin >> x >> y;
                    grid.placeBlinker(x, y);
                } else if (action == 'g') {
                    // Ajouter un Glider à une position spécifique
                    int x, y;
                    std::cout << "Entrez les coordonnées (x, y) pour le Glider : ";
                    std::cin >> x >> y;
                    grid.placeGlider(x, y);
                } else if (action == 'o') {
                    // Ajouter un obstacle à une position spécifique
                    int x, y, state;
                    std::cout << "Entrez les coordonnées (x, y) et l'état de l'obstacle (2 pour mort, 3 pour vivant) : ";
                    std::cin >> x >> y >> state;
                    grid.placeObstacle(x, y, state);
                } else if (action != 'n') {
                    // Gérer une entrée invalide
                    std::cout << "Action invalide.\n";
                }
            }

            // Calculer le prochain état de la grille
            grid.computeNextState();
            ++currentIteration;

            if (manualMode == 0) {
                usleep(sleep_time * 1000);
            }
        }
    } else if (mode == 0) {
        // Mode graphique
        sf::RenderWindow window(sf::VideoMode(grid.getWidth() * cellSize, grid.getHeight() * cellSize), "Jeu de la vie - Projet POO");

        bool paused = false;

        std::cout << "Mode graphique activé. Utilisez les actions suivantes :\n";
        std::cout << "- Clic gauche : Placer un obstacle mort (état 2).\n";
        std::cout << "- Clic droit : Placer un obstacle vivant (état 3).\n";
        std::cout << "- Touche B : Ajouter un Blinker à la position du curseur.\n";
        std::cout << "- Touche G : Ajouter un Glider à la position du curseur.\n";
        std::cout << "- Touche P : Mettre en pause ou reprendre le jeu.\n";

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    // Fermer la fenêtre si l'utilisateur clique sur la croix
                    window.close();
                } else if (event.type == sf::Event::KeyPressed) {
                    // Obtenir la position actuelle du curseur dans la fenêtre
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    int x = mousePos.y / cellSize;
                    int y = mousePos.x / cellSize;

                    if (x >= 0 && x < grid.getHeight() && y >= 0 && y < grid.getWidth()) {
                        if (event.key.code == sf::Keyboard::B) {
                            grid.placeBlinker(x, y);
                        } else if (event.key.code == sf::Keyboard::G) {
                            grid.placeGlider(x, y);
                        }
                    } else {
                        std::cerr << "Erreur : Le curseur est en dehors des limites de la grille.\n";
                    }

                    if (event.key.code == sf::Keyboard::P) {
                        paused = !paused;  // Basculer l'état de pause
                    }
                } else if (event.type == sf::Event::MouseButtonPressed) {
                    // Gérer les clics de souris pour placer des obstacles
                    int x = event.mouseButton.y / cellSize;
                    int y = event.mouseButton.x / cellSize;

                    if (x >= 0 && x < grid.getHeight() && y >= 0 && y < grid.getWidth()) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            grid.placeObstacle(x, y, 2);  // Obstacle mort
                            std::cout << "Obstacle mort placé à (" << x << ", " << y << ").\n";
                        } else if (event.mouseButton.button == sf::Mouse::Right) {
                            grid.placeObstacle(x, y, 3);  // Obstacle vivant
                            std::cout << "Obstacle vivant placé à (" << x << ", " << y << ").\n";
                        }
                    } else {
                        std::cerr << "Erreur : Les coordonnées du clic sont en dehors des limites de la grille.\n";
                    }
                }
            }

            if (!paused) {
                grid.computeNextState();
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
    }

        return 0;  // Terminer le programme
}
