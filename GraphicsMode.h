#ifndef GRAPHICSMODE_H
#define GRAPHICSMODE_H

#include "GameOfLife.h"
#include <SFML/Graphics.hpp>

class GraphicsMode {
public:
    GraphicsMode(GameOfLife& game, int iterations);
    void run();

private:
    GameOfLife& game;
    int iterations;
    void renderGrid(sf::RenderWindow& window);
};

#endif // GRAPHICSMODE_H