#include <iostream>
#include <fstream>
#include "JeuDeLaVie.h"
#include "ModeConsole.h"
#include "ModeGraphique.h"
#include <string>

void readGridDimensions(int& width, int& height, const std::string& filename) {
    if (!filename.empty()) {
        std::ifstream file(filename);
        if (file.is_open()) {
            file >> width >> height;
            file.close();
        } else {
            std::cerr << "Impossible d'ouvrir le fichier : " << filename << std::endl;
            exit(1);
        }
    } else {
        std::cout << "Entrez la largeur de la grille (laissez vide pour la valeur par défaut 100) : ";
        std::string widthInput;
        std::getline(std::cin, widthInput);
        if (!widthInput.empty()) {
            width = std::stoi(widthInput);
        }
        std::cout << "Entrez la hauteur de la grille (laissez vide pour la valeur par défaut 100) : ";
        std::string heightInput;
        std::getline(std::cin, heightInput);
        if (!heightInput.empty()) {
            height = std::stoi(heightInput);
        }
    }
}

void chooseModeAndIterations(char& mode, int& iterations) {
    std::cout << "Choisissez le mode (c pour console, g pour graphique) : ";
    std::cin >> mode;
    std::cin.ignore();

    if (mode == 'c') {
        while (true) {
            std::cout << "Entrez le nombre d'itérations : ";
            std::string input;
            std::getline(std::cin, input);
            try {
                iterations = std::stoi(input);
                if (iterations > 0) {
                    break;
                } else {
                    std::cerr << "Veuillez entrer un nombre positif." << std::endl;
                }
            } catch (const std::invalid_argument&) {
                std::cerr << "Entrée invalide. Veuillez entrer un nombre valide." << std::endl;
            }
        }
    } else if (mode == 'g') {
        std::cout << "Entrez le nombre d'itérations (laissez vide pour un arrêt automatique) : ";
        std::string input;
        std::getline(std::cin, input);
        if (!input.empty()) {
            try {
                iterations = std::stoi(input);
                if (iterations <= 0) {
                    std::cerr << "Veuillez entrer un nombre positif." << std::endl;
                    exit(1);
                }
            } catch (const std::invalid_argument&) {
                std::cerr << "Entrée invalide. Veuillez entrer un nombre valide." << std::endl;
                exit(1);
            }
        } else {
            iterations = -1;
        }
    } else {
        std::cerr << "Mode sélectionné invalide." << std::endl;
        exit(1);
    }
}

void runMode(JeuDeLaVie& game, char mode, int iterations) {
    if (mode == 'c') {
        ModeConsole consoleMode(game, iterations);
        consoleMode.deleteOutputFiles();
        consoleMode.run();
    } else if (mode == 'g') {
        ModeGraphique graphicsMode(game, iterations);
        graphicsMode.run();
    }
}

int main() {
    int width = 100, height = 100;
    std::string filename;
    std::cout << "Entrez le nom du fichier pour la grille initiale (laissez vide pour une initialisation aléatoire) : ";
    std::getline(std::cin, filename);

    readGridDimensions(width, height, filename);

    JeuDeLaVie game(width, height);
    if (!filename.empty()) {
        std::ifstream file(filename);
        if (file.is_open()) {
            game.loadGridFromFile(file);
            file.close();
        } else {
            std::cerr << "Impossible d'ouvrir le fichier : " << filename << std::endl;
            return 1;
        }
    } else {
        game.initializeGrid();
    }

    char mode;
    int iterations = -1;
    chooseModeAndIterations(mode, iterations);
    runMode(game, mode, iterations);

    return 0;
}