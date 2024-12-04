#include "ModeConsole.h"
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

ModeConsole::ModeConsole(JeuDeLaVie& game, int iterations) : game(game), iterations(iterations) {}

void ModeConsole::run() {
    int iteration = 0;
    while (iterations == -1 || iteration < iterations) {
        if (!game.updateGrid()) {
            break;
        }
        writeToFile(iteration);
        iteration++;
    }
}

void ModeConsole::writeToFile(int iteration) {
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

void ModeConsole::deleteOutputFiles() {
    for (const auto& entry : fs::directory_iterator(".")) {
        if (entry.path().extension() == ".txt" && entry.path().filename().string().find("output_") == 0) {
            fs::remove(entry.path());
        }
    }
}