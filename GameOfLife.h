#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <vector>
#include <istream>

class GameOfLife {
public:
    GameOfLife(int width, int height);
    void initializeGrid();
    bool updateGrid();
    void loadGridFromFile(std::istream& input);
    const std::vector<std::vector<int>>& getGrid() const;

private:
    int width;
    int height;
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<int>> newGrid;
};

#endif // GAMEOFLIFE_H