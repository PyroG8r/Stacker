#include <SFML/Window.hpp>
#include <iostream>
#include <ctime>
#include "Game.h"


int main() {
    std::srand(std::time(nullptr));
    const int width = 500;
    const int height = 500;
    const std::string gameTitle = "Stacker";
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    Game game(width, height, gameTitle, settings);
    game.run();
    return 0;
}

