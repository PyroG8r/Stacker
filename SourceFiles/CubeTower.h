//
// Created by emilj on 2022-12-18.
//

#ifndef PROJEKT_CUBETOWER_H
#define PROJEKT_CUBETOWER_H

#include "Constants.h"

/**
 * @brief A class that represents a tower of cubes
 * @details The class is a template class that takes a type of cube as a template parameter.
 * The tower is placed in the center of the screen.
*/

template <typename T>
class CubeTower {
public:
    /**
     * @brief Construct a new Cube Tower object
     */
    CubeTower(){
        addCube(sf::Vector2f(0,0), sf::Vector2f(SCREEN_WIDTH/2,SCREEN_WIDTH/2));
    }

    /**
     * @brief Adds a cube to the top of the tower
     * @param size The size of the cube
     * @param position The position of the cube
     */
    void addCube(sf::Vector2f size, sf::Vector2f position){
        cubeTower.emplace_back(size,  position);

    }

    /**
     * @brief Return an iterator to the past-the-end element in the vector container.
     * 
     * @return std::vector<T>::iterator 
     */
    typename std::vector<T>::iterator top(){
        return cubeTower.end();
    }

    /**
     * @brief Get the bottom of the tower
     * 
     * @return Returns an iterator to the bottom of the tower 
     */
    typename std::vector<T>::iterator bottom(){
        return cubeTower.begin();
    }

    /**
     * @brief Get the top cube of the tower
     * 
     * @return T& Returns a reference to the top cube of the tower
     */
    T& topCube(){
        return cubeTower.back();
    }

    /**
     * @brief Reset the tower to its initial state
     * 
     */
    void reset(){
        cubeTower.clear();
        addCube(sf::Vector2f(0,0), sf::Vector2f(SCREEN_WIDTH/2,SCREEN_WIDTH/2));
    }

private:
    std::vector<T> cubeTower;
};


#endif //PROJEKT_CUBETOWER_H
