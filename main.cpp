#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include "JeuDeLaVie.h"
#include "ModeConsole.h"
#include "ModeGraphique.h"
#include <string>
#include <limits>

int main() {
    int width = 100, height = 100;
    std::string filename;
    std::cout << "Entrez le nom du fichier pour la grille initiale (laissez vide pour une initialisation aléatoire) : ";
    std::getline(std::cin, filename);
    if (!filename.empty()) {
        std::ifstream file(filename);
        if (file.is_open()) {
            file >> width >> height;
            JeuDeLaVie game(width, height);
            game.loadGridFromFile(file);
            file.close();
            char mode;
            std::cout << "Choisissez le mode (c pour console, g pour graphique) : ";
            std::cin >> mode;
            std::cin.ignore();
            int iterations = -1;
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
                ModeConsole consoleMode(game, iterations);
                consoleMode.deleteOutputFiles();
                consoleMode.run();
            } else if (mode == 'g') {
                std::cout << "Entrez le nombre d'itérations (laissez vide pour un arrêt automatique) : ";
                std::string input;
                std::getline(std::cin, input);
                if (!input.empty()) {
                    iterations = std::stoi(input);
                }
                ModeGraphique graphicsMode(game, iterations);
                graphicsMode.run();
            } else {
                std::cerr << "Mode sélectionné invalide." << std::endl;
            }
        } else {
            std::cerr << "Impossible d'ouvrir le fichier : " << filename << std::endl;
            return 1;
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
        JeuDeLaVie game(width, height);
        game.initializeGrid();
        char mode;
        std::cout << "Choisissez le mode (c pour console, g pour graphique) : ";
        std::cin >> mode;
        std::cin.ignore();
        int iterations = -1;
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
            ModeConsole consoleMode(game, iterations);
            consoleMode.deleteOutputFiles();
            consoleMode.run();
        } else if (mode == 'g') {
            std::cout << "Entrez le nombre d'itérations (laissez vide pour un arrêt automatique) : ";
            std::string input;
            std::getline(std::cin, input);
            if (!input.empty()) {
                iterations = std::stoi(input);
            }
            ModeGraphique graphicsMode(game, iterations);
            graphicsMode.run();
        } else {
            std::cerr << "Mode sélectionné invalide." << std::endl;
        }
    }
    return 0;
}