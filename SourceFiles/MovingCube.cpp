//
// Created by emilj on 2022-12-18.
//

#include <cmath>
#include "MovingCube.h"
#include "Constants.h"


MovingCube::MovingCube(const sf::Vector2f &size)
: Cube(size)
{
    setPosition(sf::Vector2f(SCREEN_WIDTH + 50, CUBE_HEIGHT));
}


void MovingCube::move() {
    sf::Vector2f pos = getPosition();
    if (pos.x > SCREEN_WIDTH + 100 || pos.x < -100) {
        toggleDirUpDown();
        toggleDirLeftRight();
    }
    if (dirLeftRight == LEFT && dirUpDown == DOWN){
        setPosition(sf::Vector2f(pos.x - 2, pos.y + 1));
        path = ALONG_X;
    }
    if (dirLeftRight == LEFT && dirUpDown == UP) {
        setPosition(sf::Vector2f(pos.x - 2, pos.y - 1));
        path = ALONG_Y;
    }
    if (dirLeftRight == RIGHT && dirUpDown == DOWN) {
        setPosition(sf::Vector2f(pos.x + 2, pos.y + 1));
        path = ALONG_Y;
    }
    if (dirLeftRight == RIGHT && dirUpDown == UP) {
        setPosition(sf::Vector2f(pos.x + 2, pos.y - 1));
        path = ALONG_X;
    }
}

void MovingCube::toggleDirLeftRight() {
    dirLeftRight = !dirLeftRight;
}

void MovingCube::toggleDirUpDown() {
    dirUpDown = !dirUpDown;
}

float MovingCube::placeCube(const Cube& TopCube) {
    float deltaX = getPosition().x - TopCube.getPosition().x;
    float deltaY = getPosition().y + CUBE_HEIGHT - TopCube.getPosition().y;

    float overHang = std::sqrt((float)pow(deltaX, 2) + (float)pow(deltaY,2));

    resetCubeState(deltaX, deltaY);

    return overHang;
}



void MovingCube::resetCubeState(float deltaX, float deltaY) {
    if (path == ALONG_X){
        //placed before tower an offset is stored of how much the cube is moved
        if (deltaX > 0){
            startOffsetX += deltaX;
            startOffsetY += deltaY;
        }
        setPosition(sf::Vector2f(-50 + startOffsetX, -startHeight++ * CUBE_HEIGHT + startOffsetY));

        dirLeftRight = RIGHT;
    }
    //path along y
    else {
        //placed before tower
        if (deltaX < 0){
            startOffsetX += deltaX;
            startOffsetY += deltaY;
        }
        setPosition(sf::Vector2f(SCREEN_WIDTH + 50 + startOffsetX, -startHeight++ * CUBE_HEIGHT + startOffsetY));

        // Reset the
        dirLeftRight = LEFT;
    }
    dirUpDown = DOWN;
}

bool MovingCube::getMovingPath() const {
    return path;
}

void  MovingCube::resetCubeForNewRound() {
    setPosition(sf::Vector2f(SCREEN_WIDTH + 50, CUBE_HEIGHT));
    setSize(sf::Vector2f(0,0));
    dirUpDown = DOWN;
    dirLeftRight = LEFT;
    startHeight = 0;
    startOffsetX = 0;
    startOffsetY = 0;
}

/*



 void Cube::increaseXAxis() {
    sizeX = sizeX + 0.1;
    setPoints();
}

void Cube::increaseYAxis() {
    sizeY = sizeY + 0.1;
    setPoints();
}

void Cube::decreaseXAxis() {
    (sizeX < -50) ? : sizeX = sizeX - 0.1;
    setPoints();
}

void Cube::decreaseYAxis() {
    (sizeY < -50) ? : sizeY = sizeY - 0.1;
    setPoints();
}

void Cube::setSize(sf::Vector2f size){
    sizeX = size.x;
    sizeY = size.y;
}








 double deltaX = 0;
    double deltaY = 0;
    std::cout << thisCubePos.x << " : " << topCubePos.x << "\n";
    if (dirLeftRight == LEFT){
        deltaX = movingPoint5.x - towerPoint6.x;
        deltaY = movingPoint5.y - towerPoint6.y;
    }
    else if (dirLeftRight == RIGHT) {
        deltaX = movingPoint5.x - towerPoint6.x;
        deltaY = movingPoint5.y - towerPoint6.y;
    }



*/




