// "namn på uppgiften", DT047G
// Emil Jons 
// filnamn, 2022-12-21
// "kortfattat vad filen innehåller"


#include <iostream>
#include <fstream>
#include "Game.h"
#include "Constants.h"

Game::Game(const int width, const int height, const std::string& gameTitle, sf::ContextSettings settings)
: window(sf::VideoMode(width, height), gameTitle, sf::Style::Default, settings)
{
    window.setFramerateLimit(60);
}

void Game::run() {
    initializeElements();

    while (window.isOpen()) {
        handleInputs();

        updateObjects();
        drawObjects();
    }
}

void Game::initializeElements() {
    getHighScore();

    cubeTower.topCube().setFillColor(placeColor);
    placeColor = setRandomCubeColor(movingCube);


    floorCube.setFillColor(sf::Color(55, 161, 143));

    if (!font.loadFromFile("Fonts/Roboto-Bold.ttf")){
        throw std::ios_base::failure("Cannot find font file");
    }

    //set score text
    scoreText.setFont(font);
    scoreText.setString(std::to_string(score));
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color(64, 64, 64));

    sf::FloatRect textRect = scoreText.getLocalBounds();
    scoreText.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);

    scoreText.setPosition(int(SCREEN_WIDTH/2), 50);
}

void Game::handleInputs() {
    mousePos = sf::Mouse::getPosition(window);
    mouseWorldPos = window.mapPixelToCoords(mousePos, view);

    //main event loop
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space && !paused) {
                if (isGameOver){
                    restartGame();
                }
                else if(placeCube()){
                    score++;
                    scoreText.setString(std::to_string(score)); // Update the text object's string
                }
                else{
                    gameOver();
                }
            }
            // if key escape is pressed, show pauseMenu
            if (event.key.code == sf::Keyboard::Escape && !isGameOver) {
                if(paused){
                    mainMenu.showPauseMenu(false);
                    paused = false;
                }
                else{
                    mainMenu.showPauseMenu(true);
                    paused = true;
                }
            }
        }
        // Check what button is pressed
        if (event.type == sf::Event::MouseButtonPressed) {
            if (mainMenu.isPlayButtonPressed(mousePos)) {
                mainMenu.showPauseMenu(false);
                paused = false;
            }
            else if (mainMenu.isExitButtonPressed(mousePos)){
                window.close();
            }
            else if (mainMenu.isRestartButtonPressed(mousePos)){
                restartGame();
            }
        }
    }
}


void Game::updateObjects() {

    if(!paused){
        movingCube.move();
    }
    placeCubeAnimations();
    gameOverAnimation();



    /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
        movingCube.setPosition(mouseWorldPos);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        movingCube.increaseYAxis();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        movingCube.decreaseYAxis();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        movingCube.increaseXAxis();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        movingCube.decreaseXAxis();
    }*/
}

void Game::placeCubeAnimations() {
    if (incrementCubeAnimation){
        if (incrementCubeAnimationAmount < 10){
            if(movingCube.getMovingPath()) {
                movingCube.increaseXAxis();
                cubeTower.topCube().increaseXAxis();
            }
            else {
                movingCube.increaseYAxis();
                cubeTower.topCube().increaseYAxis();
            }
            incrementCubeAnimationAmount++;
        }
        else{
            incrementCubeAnimation = false;
            incrementCubeAnimationAmount = 0;
        }
    }
}

void Game::gameOverAnimation() {
    // over the span of 60 frames (i.e 1 sec) zoom out
    if(isGameOver){
        if (zoomAmount < 60) {
            view.zoom(1 + float(score) / 1000);
            view.move(0,score / 2.5);
            zoomAmount++;
        }
    }
}

void Game::drawObjects() {
    window.clear(sf::Color(223, 207, 165));
    window.setView(view);

    window.draw(floorCube);
    // print all cubes in tower using std::for_each
    std::for_each(cubeTower.bottom(), cubeTower.top(), [this](Cube &cube){
        window.draw(cube);
    });
    if(!isGameOver) { window.draw(movingCube); }

    //reset the view to default view to draw hud elements
    window.setView(window.getDefaultView());

    window.draw(scoreText);
    window.draw(mainMenu); // using overridden virtual draw function

    window.display();
}

bool Game::placeCube() {
    Cube topCube = cubeTower.topCube();
    sf::Vector2f placedCubePosition(movingCube.getPosition());
    sf::Vector2f newCubeSize(movingCube.getSize());

    overHang = movingCube.placeCube(topCube);

    //moving along x placed "under" tower
    if (!movingCube.getMovingPath() && placedCubePosition.x < topCube.getPosition().x){
        newCubeSize.x -= overHang;
        placedCubePosition = topCube.getPosition();
        placedCubePosition.y = placedCubePosition.y - CUBE_HEIGHT;
    }
    //moving along x placed "above" tower
    else if (!movingCube.getMovingPath() && placedCubePosition.x > topCube.getPosition().x){
        newCubeSize.x -= overHang;
    }
    //moving along y placed "above" tower
    else if (movingCube.getMovingPath() && placedCubePosition.x < topCube.getPosition().x){
        newCubeSize.y -= overHang;
    }
    //moving along y placed "under" tower
    else if (movingCube.getMovingPath() && placedCubePosition.x > topCube.getPosition().x){
        newCubeSize.y -= overHang;
        placedCubePosition = topCube.getPosition();
        placedCubePosition.y = placedCubePosition.y - CUBE_HEIGHT;
    }

    //cube is placed perfect
    else if (placedCubePosition.x == topCube.getPosition().x){
        incrementCubeAnimation = true;
    }

    //fails to place cube
    if (newCubeSize.x < -CUBE_SIZE || newCubeSize.y < -CUBE_SIZE ){
        return false;
    }
    //move camera 1 cube height up
    view.move(0,- CUBE_HEIGHT);
    cubeTower.addCube(newCubeSize, placedCubePosition);
    movingCube.setSize(newCubeSize);

    //set color of the cubes



    /*cubeTower.topCube().setFillColor(placeColor);
    placeColor = sf::Color(colordirstr(gen), colordirstr(gen), colordirstr(gen));
    movingCube.setFillColor(placeColor);*/


    cubeTower.topCube().setFillColor(placeColor);
    placeColor = setRandomCubeColor(movingCube);


    return true;
}

void Game::gameOver() {
    isGameOver = true;
    if (score > highScore){updateHighScore();}

    paused = true;
    mainMenu.showGameOverMenu(true);

}

void Game::getHighScore() {
    //read highScore from file with error handling
    std::ifstream highScoreFile;
    highScoreFile.open("highScore.txt");
    if (highScoreFile.is_open()){
        highScoreFile >> highScore;
        highScoreFile.close();
    }
}

void Game::updateHighScore() {
    highScore = score;
    std::ofstream highScoreFile;
    highScoreFile.open("highScore.txt");
    if (highScoreFile.is_open()){
        highScoreFile << highScore;
        highScoreFile.close();
        mainMenu.updateHighScore(highScore);
    }
    else {
        throw std::ios_base::failure("Cannot create highscore file");
    }
}

void Game::restartGame() {
    //reset game objects
    cubeTower.reset();
    view.reset(sf::FloatRect(0, 0, 500.f, 500.f));
    movingCube.resetCubeForNewRound();

    //reset game properties
    score = 0;
    scoreText.setString(std::to_string(score));
    isGameOver = false;
    zoomAmount = 0;
    paused = false;

    mainMenu.showGameOverMenu(false);
}








/*std::cout << "Place Pos X " <<  placedPos.x << " Y " << placedPos.y << "\n";
std::cout << "Size X " <<  movingCube.getSizeX() << " Y " << movingCube.getSizeY() << "\n";
std::cout << "Size X " <<  newSize.x << " Y " << newSize.y << "\n";
//newSize.x = ceil(newSize.x);
//newSize.y = ceil(newSize.y);
//std::cout << "Size X " <<  newSize.x << " Y " << newSize.y << "\n";*/



/*rectangleShape.setPosition(cubeTower.topCube().getPosition().x,cubeTower.topCube().getPosition().y + 50);
            rectangleShape.setPoint(0, sf::Vector2f(cubeTower.topCube().getPoint(7).x, cubeTower.topCube().getPoint(7).y - 1));
            rectangleShape.setPoint(1, sf::Vector2f(cubeTower.topCube().getPoint(3).x + 1, cubeTower.topCube().getPoint(3).y));
            rectangleShape.setPoint(2, sf::Vector2f(cubeTower.topCube().getPoint(4).x, cubeTower.topCube().getPoint(4).y + 1));
            rectangleShape.setPoint(3, sf::Vector2f(cubeTower.topCube().getPoint(5).x - 1, cubeTower.topCube().getPoint(5).y));*/


/*rectangleShape.setPointCount(4);
    rectangleShape.setPoint(0,sf::Vector2f(50,0));
    rectangleShape.setPoint(1,sf::Vector2f(100,25));
    rectangleShape.setPoint(2,sf::Vector2f(50,50));
    rectangleShape.setPoint(3,sf::Vector2f(0,25));
    rectangleShape.setPosition(50,50);*/


