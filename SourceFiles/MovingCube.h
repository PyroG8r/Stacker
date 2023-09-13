//
// Created by emilj on 2022-12-18.
//

#ifndef PROJEKT_MOVINGCUBE_H
#define PROJEKT_MOVINGCUBE_H

#include "Cube.h"


/**
 * @brief A cube that moves towards the tower
 * @details The cube starts outside the screen at the top right corner
 * and moves towards the tower when the game starts.
 * The cube moves at a constant speed and changes direction when it is outside the screen.
 * The cube can be placed on top of the tower, and checks the amount of overhang it has.
 * When the cube is placed on the tower, it is reset to its starting position, alternating between top right and top left.
 * 
*/
class MovingCube : public Cube {
public:
    /**
     * @brief Creates a moving cube
     * @param sizeX The width of the cube
     * @param sizeY The height of the cube
     * @details The cube is placed outside the screen at the top right corner
     * and moves towards the tower when the game starts. 
    */
    explicit MovingCube(const sf::Vector2f &size);


    /**
     * @brief Places the cube on the top cube
     * @param onTopOf The cube to place the cube on
     * @return The amount of overhang the cube has
    */
    float placeCube(const Cube& onTopOf);

    /**
     * @brief Returns the direction the cube is moving in
     * @return True if the cube is moving along the y-axis, false if it is moving along the x-axis
    */
    bool getMovingPath() const;

    /**
     * @brief Moves the cube
     * @details Moves the cube in the direction it is moving in
     * and changes the direction if it is outside the screen
    */
    void move();

    /**
     * @brief Resets the cube to its starting position
     * @details The cube is placed to its original position for 
     * use when restarting the game
    */
    void resetCubeForNewRound();


private:
    void toggleDirUpDown();
    void toggleDirLeftRight();
    void resetCubeState(float deltaX, float deltaY);

    enum dirUpDown {UP, DOWN};
    enum dirLeftRight {LEFT, RIGHT};
    enum path {ALONG_X, ALONG_Y};
    bool dirUpDown = DOWN;
    bool dirLeftRight = LEFT;
    bool path = ALONG_X;
    float startHeight = 0;
    float startOffsetX = 0;
    float startOffsetY = 0;

};


#endif //PROJEKT_MOVINGCUBE_H
