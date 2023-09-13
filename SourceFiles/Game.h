// "namn på uppgiften", DT047G
// Emil Jons 
// filnamn, 2022-12-21
// "kortfattat vad filen innehåller"


#ifndef PROJEKT_GAME_H
#define PROJEKT_GAME_H

#include <SFML/Audio.hpp>
#include "Cube.h"
#include "MovingCube.h"
#include "CubeTower.h"
#include "Menu.h"
#include <random>

/**
 * @brief The main game class
 * @details The main game class that handles all the game logic
 * acts as a controller, or wrapper class.
 */
class Game {
public:
    Game(int width, int height, const std::string& gameTitle, sf::ContextSettings settings);
    void run();
private:
    void initializeElements();
    void handleInputs();
    void updateObjects();
    void drawObjects();
    bool placeCube();
    void gameOver();
    void getHighScore();
    void updateHighScore();
    void placeCubeAnimations();
    void gameOverAnimation();
    void restartGame();


    sf::Color setRandomCubeColor(Cube& cube){
        sf::Color color = sf::Color(colordirstr(gen), colordirstr(gen), colordirstr(gen));
        cube.setFillColor(color);
        return color;
    }

    //game objects
    sf::View view = sf::View(sf::FloatRect(0, 0, 500.f, 500.f));
    sf::RenderWindow window;
    sf::Font font;
    sf::Text scoreText;
    Menu mainMenu;



    //entities
    CubeTower<Cube> cubeTower;
    MovingCube movingCube = MovingCube(sf::Vector2f(0,0));
    Cube floorCube = Cube(sf::Vector2f(330, 330), sf::Vector2f(250, 500));

    //other
    sf::Vector2i mousePos;
    sf::Vector2f mouseWorldPos;
    sf::Color placeColor = sf::Color(colordirstr(gen), colordirstr(gen), colordirstr(gen));
    int incrementCubeAnimationAmount = 0;
    bool incrementCubeAnimation = false;
    int zoomAmount = 0;
    float overHang = 0;
    int highScore = 0;
    bool paused = true;
    bool isGameOver = false;
    int score = 0;

    std::random_device rd = std::random_device();
    std::mt19937 gen = std::mt19937(rd());
    std::uniform_int_distribution<> colordirstr {100, 200};
};


#endif //PROJEKT_GAME_H
