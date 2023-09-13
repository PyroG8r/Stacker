// "namn på uppgiften", DT047G
// Emil Jons 
// filnamn, 2022-12-28
// "kortfattat vad filen innehåller"


#include <iostream>
#include <fstream>
#include "Menu.h"

Menu::Menu() {
    initializePauseMenu();
    initializeGameOverMenu();
}

void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if(isPauseMenuShown) {
        target.draw(play_button);
        target.draw(exit_button);
        for (const auto & text : pauseMenu) {
            target.draw(text);
        }
    }
    if(isGameOverMenuShown) {
        target.draw(restart_button);
        for (const auto & text : gameOverMenu) {
            target.draw(text);
        }
    }
}


void Menu::showPauseMenu(bool input) {
    isPauseMenuShown = input;
}

void Menu::showGameOverMenu(bool input) {
    isGameOverMenuShown = input;
}

bool Menu::isPlayButtonPressed(sf::Vector2i mousePos) {
    if(isPauseMenuShown){
        return isButtonPressed(mousePos, play_button);
    }
    return false;
}

bool Menu::isExitButtonPressed(sf::Vector2i mousePos) {
    if(isPauseMenuShown){
        return isButtonPressed(mousePos, exit_button);
    }
    return false;
}

bool Menu::isRestartButtonPressed(sf::Vector2i mousePos) {
    if(gameOverMenu){
        return isButtonPressed(mousePos, restart_button);
    }
    return false;
}

bool Menu::isButtonPressed(sf::Vector2i mousePos, const sf::RectangleShape& button) {
    if(mousePos.x > (int)button.getPosition().x && mousePos.x < (int)button.getPosition().x + (int)button.getSize().x &&
       mousePos.y > (int)button.getPosition().y && mousePos.y < (int)button.getPosition().y + (int)button.getSize().y) {
        return true;
    }
    return false;
}

void Menu::updateHighScore(int newHighScore) {
    highScore = newHighScore;
    gameOverMenu[1].setString("HIGHSCORE: " + std::to_string(highScore));
}

void Menu::initializePauseMenu() {
    if (!font.loadFromFile("Fonts/Roboto-Bold.ttf")){
        throw std::ios_base::failure("Cannot find font file");
    }
    pauseMenu[0].setFont(font);
    pauseMenu[0].setFillColor(sf::Color::White);
    pauseMenu[0].setString("Play");
    pauseMenu[0].setPosition(sf::Vector2f(200, 150));

    pauseMenu[1].setFont(font);
    pauseMenu[1].setFillColor(sf::Color::White);
    pauseMenu[1].setString("Exit");
    pauseMenu[1].setPosition(sf::Vector2f(200, 250));


    play_button.setSize(sf::Vector2f(100, 50));
    play_button.setFillColor(buttonColor);
    play_button.setPosition(sf::Vector2f(200, 150));

    exit_button.setSize(sf::Vector2f(100, 50));
    exit_button.setFillColor(buttonColor);
    exit_button.setPosition(sf::Vector2f(200, 250));
}

void Menu::initializeGameOverMenu() {
    gameOverMenu[0].setFont(font);
    gameOverMenu[0].setFillColor(sf::Color::White);
    gameOverMenu[0].setString("Restart");
    gameOverMenu[0].setPosition(sf::Vector2f(50, 150));

    gameOverMenu[1].setFont(font);
    gameOverMenu[1].setFillColor(sf::Color(64, 64, 64));
    gameOverMenu[1].setCharacterSize(50);
    //open file highScore.txt and read highScore
    std::ifstream highscoreFile("highScore.txt");
    highscoreFile >> highScore;
    highscoreFile.close();
    gameOverMenu[1].setString("HIGHSCORE: " + std::to_string(highScore));

    //center the text
    sf::FloatRect textRect = gameOverMenu[1].getLocalBounds();
    gameOverMenu[1].setOrigin(textRect.left + textRect.width / 2.0f,
                           textRect.top + textRect.height / 2.0f);

    gameOverMenu[1].setPosition(sf::Vector2f(250, 100));


    restart_button.setSize(sf::Vector2f(100, 50));
    restart_button.setFillColor(buttonColor);
    restart_button.setPosition(sf::Vector2f(50, 150));

}







