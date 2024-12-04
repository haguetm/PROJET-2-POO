#ifndef MODEGRAPHIQUE_H
#define MODEGRAPHIQUE_H

#include "JeuDeLaVie.h"
#include <SFML/Graphics.hpp>

class ModeGraphique {
public:
    ModeGraphique(JeuDeLaVie& game, int iterations);
    void run();

private:
    JeuDeLaVie& game;
    int iterations;
    void renderGrid(sf::RenderWindow& window);
};

#endif // MODEGRAPHIQUE_H