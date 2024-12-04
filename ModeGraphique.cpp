#include "ModeGraphique.h"

ModeGraphique::ModeGraphique(JeuDeLaVie& game, int iterations) : game(game), iterations(iterations) {}

void ModeGraphique::run() {
    const int width = game.getGrid().size();
    const int height = game.getGrid()[0].size();
    const float cellSize = 10.0f;

    sf::RenderWindow window(sf::VideoMode(width * cellSize, height * cellSize), "Jeu de la Vie");

    int iteration = 0;
    while ((iterations == -1 || iteration < iterations) && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
        }

        if (!game.updateGrid()) {
            break;
        }
        renderGrid(window);

        sf::sleep(sf::milliseconds(100));
        iteration++;
    }

    // Garder la fenêtre ouverte et afficher la dernière génération
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        renderGrid(window);
    }
}

void ModeGraphique::renderGrid(sf::RenderWindow& window) {
    window.clear();
    const auto& grid = game.getGrid();
    const float cellSize = 10.0f;
    sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));
    for (int x = 0; x < grid.size(); ++x) {
        for (int y = 0; y < grid[0].size(); ++y) {
            if (grid[x][y] == 1) {
                cell.setPosition(x * cellSize, y * cellSize);
                window.draw(cell);
            }
        }
    }
    window.display();
}