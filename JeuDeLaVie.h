#ifndef JEUDDELAVIE_H
#define JEUDDELAVIE_H

#include <vector>
#include <istream>

class JeuDeLaVie {
public:
    JeuDeLaVie(int width, int height);
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

#endif // JEUDDELAVIE_H