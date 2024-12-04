#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include "GameOfLife.h"
#include "ConsoleMode.h"
#include "GraphicsMode.h"
#include <string>
#include <limits>

const int gridWidth = 80;
const int gridHeight = 80;
const float cellSize = 10.0f;

std::vector<std::vector<int>> grid(gridWidth, std::vector<int>(gridHeight));
std::vector<std::vector<int>> newGrid(gridWidth, std::vector<int>(gridHeight));

void initializeGrid() {
    std::srand(std::time(0));
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            grid[x][y] = std::rand() % 2;  // Randomly initialize cells as alive or dead
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
    sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));
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
    int width = 100, height = 100; // Default size
    std::string filename;
    std::cout << "Enter filename for initial grid (leave empty for random initialization): ";
    std::getline(std::cin, filename);
    if (!filename.empty()) {
        std::ifstream file(filename);
        if (file.is_open()) {
            file >> width >> height;
            GameOfLife game(width, height);
            game.loadGridFromFile(file);
            file.close();
            char mode;
            std::cout << "Choose mode (c for console, g for graphics): ";
            std::cin >> mode;
            std::cin.ignore(); // Ignore the newline character left in the buffer
            int iterations = -1;
            if (mode == 'c') {
                while (true) {
                    std::cout << "Enter number of iterations: ";
                    std::string input;
                    std::getline(std::cin, input);
                    try {
                        iterations = std::stoi(input);
                        if (iterations > 0) {
                            break;
                        } else {
                            std::cerr << "Please enter a positive number." << std::endl;
                        }
                    } catch (const std::invalid_argument&) {
                        std::cerr << "Invalid input. Please enter a valid number." << std::endl;
                    }
                }
                ConsoleMode consoleMode(game, iterations);
                consoleMode.deleteOutputFiles(); // Supprimer les fichiers avant de commencer
                consoleMode.run();
            } else if (mode == 'g') {
                std::cout << "Enter number of iterations (leave empty for automatic stop): ";
                std::string input;
                std::getline(std::cin, input);
                if (!input.empty()) {
                    iterations = std::stoi(input);
                }
                GraphicsMode graphicsMode(game, iterations);
                graphicsMode.run();
            } else {
                std::cerr << "Invalid mode selected." << std::endl;
            }
        } else {
            std::cerr << "Could not open file: " << filename << std::endl;
            return 1;
        }
    } else {
        std::cout << "Enter grid width (leave empty for default 100): ";
        std::string widthInput;
        std::getline(std::cin, widthInput);
        if (!widthInput.empty()) {
            width = std::stoi(widthInput);
        }
        std::cout << "Enter grid height (leave empty for default 100): ";
        std::string heightInput;
        std::getline(std::cin, heightInput);
        if (!heightInput.empty()) {
            height = std::stoi(heightInput);
        }
        GameOfLife game(width, height);
        game.initializeGrid();
        char mode;
        std::cout << "Choose mode (c for console, g for graphics): ";
        std::cin >> mode;
        std::cin.ignore(); // Ignore the newline character left in the buffer
        int iterations = -1;
        if (mode == 'c') {
            while (true) {
                std::cout << "Enter number of iterations: ";
                std::string input;
                std::getline(std::cin, input);
                try {
                    iterations = std::stoi(input);
                    if (iterations > 0) {
                        break;
                    } else {
                        std::cerr << "Please enter a positive number." << std::endl;
                    }
                } catch (const std::invalid_argument&) {
                    std::cerr << "Invalid input. Please enter a valid number." << std::endl;
                }
            }
            ConsoleMode consoleMode(game, iterations);
            consoleMode.deleteOutputFiles(); // Supprimer les fichiers avant de commencer
            consoleMode.run();
        } else if (mode == 'g') {
            std::cout << "Enter number of iterations (leave empty for automatic stop): ";
            std::string input;
            std::getline(std::cin, input);
            if (!input.empty()) {
                iterations = std::stoi(input);
            }
            GraphicsMode graphicsMode(game, iterations);
            graphicsMode.run();
        } else {
            std::cerr << "Invalid mode selected." << std::endl;
        }
    }
    return 0;
}