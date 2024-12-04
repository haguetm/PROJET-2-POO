#ifndef MODECONSOLE_H
#define MODECONSOLE_H

#include "JeuDeLaVie.h"

class ModeConsole {
public:
    ModeConsole(JeuDeLaVie& game, int iterations);
    void run();
    void deleteOutputFiles(); // Déclaration de la nouvelle fonction

private:
    JeuDeLaVie& game;
    int iterations;
    void writeToFile(int iteration);
};

#endif // MODECONSOLE_H