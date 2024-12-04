#ifndef CONSOLEMODE_H
#define CONSOLEMODE_H

#include "GameOfLife.h"

class ConsoleMode {
public:
    ConsoleMode(GameOfLife& game, int iterations);
    void run();
    void deleteOutputFiles(); // Déclaration de la nouvelle fonction

private:
    GameOfLife& game;
    int iterations;
    void writeToFile(int iteration);
};

#endif // CONSOLEMODE_H