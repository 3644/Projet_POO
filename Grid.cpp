#include "Grid.h"
#include <fstream>
#include <iostream>
#include <sys/stat.h>

// Constructeur pour initialiser la grille
Grid::Grid(int width, int height, int cellSize)
    : width(width), height(height), cellSize(cellSize), cells(height, std::vector<int>(width, 0)) {}

// Méthode pour initialiser la grille à partir d'un fichier
void Grid::initializeFromFile(const std::string& fileName) {
    std::ifstream fichier(fileName);
    std::string getFileName() {
    return fileName;
    }

    if (fichier) {
        fichier >> height >> width;
        cells.resize(height, std::vector<int>(width, 0));

        for (int x = 0; x < height; ++x) {
            for (int y = 0; y < width; ++y) {
                fichier >> cells[x][y];
            }
        }

        fichier.close();
    } else {
        ( "Impossible d'ouvrir le fichier !")
        exit(EXIT_FAILURE);
    }
}

void Grid::createDirectoryAndFile() const {
    // Récupérer le nom du dossier
    std::string baseDirName = getFileName();

    // Ajouter le suffixe "_out" pour le nom du dossier
    std::string modifiedDirName = baseDirName + "_out";

    // Créer le dossier
    if (mkdir(modifiedDirName.c_str(), 0755) == 0) {
        std::cout << "Dossier créé avec succès : " << modifiedDirName << std::endl;
    } else {
        perror("Erreur lors de la création du dossier");
        return; // Arrêter si le dossier n'a pas pu être créé
    }

    // Créer un fichier texte dans ce dossier
    std::string filePath = modifiedDirName + "/" + baseDirName + ".txt";
    std::ofstream outFile(filePath);

    if (outFile) {
        outFile << "Nom du fichier : " << baseDirName << std::endl;
        outFile.close();
        std::cout << "Fichier créé avec succès : " << filePath << std::endl;
    } else {
        std::cerr << "Erreur lors de la création du fichier : " << filePath << std::endl;
    }
}

// Méthode pour dessiner la grille
void Grid::render(sf::RenderWindow &window) {
    sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));

    for (int x = 0; x < height; ++x) {
        for (int y = 0; y < width; ++y) {
            cell.setPosition(y * cellSize, x * cellSize);
            if (cells[x][y] == 1) {
                cell.setFillColor(sf::Color::White); // Cellules vivantes en blanc
            } else {
                cell.setFillColor(sf::Color::Black); // Cellules mortes en noir
            }
            window.draw(cell);
        }
    }
}
