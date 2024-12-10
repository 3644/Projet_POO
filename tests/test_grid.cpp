#include "Grid.h"
#include <gtest/gtest.h>

// Test du constructeur
TEST(GridTest, Constructor) {
    Grid grid(10, 10, 5);
    EXPECT_EQ(grid.getWidth(), 10);
    EXPECT_EQ(grid.getHeight(), 10);
}

// Test de l'initialisation depuis un fichier
TEST(GridTest, InitializeFromFile) {
    Grid grid(0, 0, 5);
    grid.initializeFromFile("../etats/test_state.txt");

    EXPECT_EQ(grid.getCellState(1, 1), 1);  // Exemple d'attente
}

TEST(GridTest, CountLivingNeighbors) {
    Grid grid(5, 5, 5);
    grid.initializeFromFile("../etats/test_state.txt");


    // Désactiver le mode torique
    grid.setToricMode(false);

    int count = grid.countLivingNeighbors(1, 1);
    std::cout << "Nombre de voisins vivants pour la cellule (1,1) : " << count << std::endl;

    EXPECT_EQ(count, 4); // On s'attend à 4 voisins vivants
}

// Test de l'évolution de l'état
TEST(GridTest, ComputeNextState) {
    Grid grid(5, 5, 5);
    grid.initializeFromFile("../etats/test_state.txt");
    grid.computeNextState();
    EXPECT_EQ(grid.getCellState(1, 2), 1);  // Exemple d'attente
}

// Point d'entrée pour Google Test
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
