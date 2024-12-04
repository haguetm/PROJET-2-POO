#include "GameOfLife.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

GameOfLife::GameOfLife(int width, int height) : width(width), height(height), grid(width, std::vector<int>(height)), newGrid(width, std::vector<int>(height)) {}

void GameOfLife::initializeGrid() {
    std::srand(std::time(0));
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            grid[x][y] = std::rand() % 2;  // Randomly initialize cells as alive or dead
        }
    }
}

bool GameOfLife::updateGrid() {
    bool changed = false;
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            int aliveNeighbors = 0;
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    if (i == 0 && j == 0) continue;
                    int nx = (x + i + width) % width;
                    int ny = (y + j + height) % height;
                    aliveNeighbors += grid[nx][ny];
                }
            }
            if (grid[x][y] == 1) {
                newGrid[x][y] = (aliveNeighbors == 2 || aliveNeighbors == 3) ? 1 : 0;
            } else {
                newGrid[x][y] = (aliveNeighbors == 3) ? 1 : 0;
            }
            if (newGrid[x][y] != grid[x][y]) {
                changed = true;
            }
        }
    }
    grid = newGrid;
    return changed;
}

void GameOfLife::loadGridFromFile(std::istream& input) {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            input >> grid[x][y];
        }
    }
}

const std::vector<std::vector<int>>& GameOfLife::getGrid() const {
    return grid;
}