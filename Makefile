# Variables de compilation
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -I src
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lgtest -lgtest_main -pthread

# Répertoires
SRC_DIR = src
BIN_DIR = bin
TEST_DIR = tests

# Fichiers source
SOURCES = $(SRC_DIR)/main.cpp $(SRC_DIR)/Grid.cpp
HEADERS = $(SRC_DIR)/Grid.h
TEST_SOURCES = $(TEST_DIR)/test_grid.cpp

# Fichiers objets
OBJECTS = $(SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

# Cibles principales
all: $(BIN_DIR)/main

# Programme principal
$(BIN_DIR)/main: $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# Programme de tests
tests: $(BIN_DIR)/tests

$(BIN_DIR)/tests: $(TEST_OBJECTS) $(SRC_DIR)/Grid.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# Règles de compilation pour les fichiers source
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Règles de compilation pour les fichiers de tests
$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -rf $(BIN_DIR)/*.o $(BIN_DIR)/main $(BIN_DIR)/tests
