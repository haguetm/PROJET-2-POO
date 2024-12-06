#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include "JeuDeLaVie.h"
#include "ModeConsole.h"
#include "ModeGraphique.h"
#include <string>
#include <limits>

const int gridWidth = 80;
const int gridHeight = 80;
const int cellSize = 10;

std::vector<std::vector<int>> grid(gridWidth, std::vector<int>(gridHeight));
std::vector<std::vector<int>> newGrid(gridWidth, std::vector<int>(gridHeight));

void initializeGrid() {
    std::srand(std::time(0));
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            grid[x][y] = std::rand() % 2;
        }
    }
}

void updateGrid() {
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            int aliveNeighbors = 0;
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    if (i == 0 && j == 0) continue;
                    int nx = x + i;
                    int ny = y + j;
                    if (nx >= 0 && nx < gridWidth && ny >= 0 && ny < gridHeight) {
                        aliveNeighbors += grid[nx][ny];
                    }
                }
            }
            if (grid[x][y] == 1) {
                newGrid[x][y] = (aliveNeighbors == 2 || aliveNeighbors == 3) ? 1 : 0;
            } else {
                newGrid[x][y] = (aliveNeighbors == 3) ? 1 : 0;
            }
        }
    }
    grid = newGrid;
}

void renderGrid(sf::RenderWindow &window) {
    window.clear();
    sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            if (grid[x][y] == 1) {
                cell.setPosition(x * cellSize, y * cellSize);
                window.draw(cell);
            }
        }
    }
    window.display();
}

int main() {
    int width = 100, height = 100;
    std::string filename;
    std::cout << "Entrez le nom du fichier pour la grille initiale (laissez vide pour une initialisation aléatoire) : ";
    std::getline(std::cin, filename);
    if (!filename.empty()) {
        std::ifstream file(filename);
        if (file.is_open()) {
            file >> width >> height;
            JeuDeLaVie game(width, height);
            game.loadGridFromFile(file);
            file.close();
            char mode;
            std::cout << "Choisissez le mode (c pour console, g pour graphique) : ";
            std::cin >> mode;
            std::cin.ignore(); // Ignorer le caractère de nouvelle ligne laissé dans le buffer
            int iterations = -1;
            if (mode == 'c') {
                while (true) {
                    std::cout << "Entrez le nombre d'itérations : ";
                    std::string input;
                    std::getline(std::cin, input);
                    try {
                        iterations = std::stoi(input);
                        if (iterations > 0) {
                            break;
                        } else {
                            std::cerr << "Veuillez entrer un nombre positif." << std::endl;
                        }
                    } catch (const std::invalid_argument&) {
                        std::cerr << "Entrée invalide. Veuillez entrer un nombre valide." << std::endl;
                    }
                }
                ModeConsole consoleMode(game, iterations);
                consoleMode.deleteOutputFiles(); // Supprimer les fichiers avant de commencer
                consoleMode.run();
            } else if (mode == 'g') {
                std::cout << "Entrez le nombre d'itérations (laissez vide pour un arrêt automatique) : ";
                std::string input;
                std::getline(std::cin, input);
                if (!input.empty()) {
                    iterations = std::stoi(input);
                }
                ModeGraphique graphicsMode(game, iterations);
                graphicsMode.run();
            } else {
                std::cerr << "Mode sélectionné invalide." << std::endl;
            }
        } else {
            std::cerr << "Impossible d'ouvrir le fichier : " << filename << std::endl;
            return 1;
        }
    } else {
        std::cout << "Entrez la largeur de la grille (laissez vide pour la valeur par défaut 100) : ";
        std::string widthInput;
        std::getline(std::cin, widthInput);
        if (!widthInput.empty()) {
            width = std::stoi(widthInput);
        }
        std::cout << "Entrez la hauteur de la grille (laissez vide pour la valeur par défaut 100) : ";
        std::string heightInput;
        std::getline(std::cin, heightInput);
        if (!heightInput.empty()) {
            height = std::stoi(heightInput);
        }
        JeuDeLaVie game(width, height);
        game.initializeGrid();
        char mode;
        std::cout << "Choisissez le mode (c pour console, g pour graphique) : ";
        std::cin >> mode;
        std::cin.ignore(); // Ignorer le caractère de nouvelle ligne laissé dans le buffer
        int iterations = -1;
        if (mode == 'c') {
            while (true) {
                std::cout << "Entrez le nombre d'itérations : ";
                std::string input;
                std::getline(std::cin, input);
                try {
                    iterations = std::stoi(input);
                    if (iterations > 0) {
                        break;
                    } else {
                        std::cerr << "Veuillez entrer un nombre positif." << std::endl;
                    }
                } catch (const std::invalid_argument&) {
                    std::cerr << "Entrée invalide. Veuillez entrer un nombre valide." << std::endl;
                }
            }
            ModeConsole consoleMode(game, iterations);
            consoleMode.deleteOutputFiles(); // Supprimer les fichiers avant de commencer
            consoleMode.run();
        } else if (mode == 'g') {
            std::cout << "Entrez le nombre d'itérations (laissez vide pour un arrêt automatique) : ";
            std::string input;
            std::getline(std::cin, input);
            if (!input.empty()) {
                iterations = std::stoi(input);
            }
            ModeGraphique graphicsMode(game, iterations);
            graphicsMode.run();
        } else {
            std::cerr << "Mode sélectionné invalide." << std::endl;
        }
    }
    return 0;
}