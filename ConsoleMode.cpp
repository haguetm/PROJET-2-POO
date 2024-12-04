#include "ConsoleMode.h"
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

ConsoleMode::ConsoleMode(GameOfLife& game, int iterations) : game(game), iterations(iterations) {}

void ConsoleMode::run() {
    int iteration = 0;
    while (iterations == -1 || iteration < iterations) {
        if (!game.updateGrid()) {
            break;
        }
        writeToFile(iteration);
        iteration++;
    }
}

void ConsoleMode::writeToFile(int iteration) {
    std::ofstream file("output_" + std::to_string(iteration) + ".txt");
    const auto& grid = game.getGrid();
    for (const auto& row : grid) {
        for (int cell : row) {
            file << cell << " ";
        }
        file << "\n";
    }
    file.close();
}

void ConsoleMode::deleteOutputFiles() {
    for (const auto& entry : fs::directory_iterator(".")) {
        if (entry.path().extension() == ".txt" && entry.path().filename().string().find("output_") == 0) {
            fs::remove(entry.path());
        }
    }
}