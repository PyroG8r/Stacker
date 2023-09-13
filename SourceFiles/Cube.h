//
// Created by emilj on 2022-12-17.
//

#ifndef PROJEKT_CUBE_H
#define PROJEKT_CUBE_H

#include <SFML/Graphics.hpp>


/**
 * @brief A class that represents a cube
 * @details A class that represents a cube and all its faces. 
 * The cube is drawn using sf::ConvexShape.
 * The cube is drawn with the origin in the center of the cube.
 * 
*/
class Cube : public sf::Drawable {
public:
    /**
     * @brief Construct a new Cube object
     * @param sizeX The size of the cube in the x-axis
     * @param sizeY The size of the cube in the y-axis
     * @details The cube is drawn with the origin in the center of the cube.
    */
    explicit Cube(const float &sizeX, float const &sizeY);

    /**
     * @brief Construct a new Cube object
     * @param size The size of the cube
     * @details Uses sf::Vector2f to set the size of the cube.
    */
    explicit Cube(const sf::Vector2f& size);

    /**
     * @brief Construct a new Cube object with a position and size
     * @param size The size of the cube
     * @param position The position of the cube
     */
    explicit Cube(const sf::Vector2f &size, const sf::Vector2f &position);

    /**
     * @brief Sets the position of the cube
     * @param position The position to set the cube to
     * @details Updates the position of the cube and all faces
    */
    void setPosition(const sf::Vector2f& position);

    /**
     * @brief Sets the size of the cube
     * @param newSize The size to set the cube to
     * @details Updates the size of the cube and all faces
    */
    void setSize(const sf::Vector2f& newSize);

    /**
     * @brief Sets the fill color of the cube
     * @param color The color to set the cube to
    */
    void setFillColor(const sf::Color& color);

    /**
     * @brief Get the Size of the cube
     * 
     * @return sf::Vector2f
     * @details Returns the size of the cube
     */
    sf::Vector2f getSize() const;
    
    /**
     * @brief Get the Position of the cube
     * 
     * @return sf::Vector2f 
     * @details Returns the position of the cube
     */
    sf::Vector2f getPosition() const;


    /**
     * @brief Increases the size of the cube in the x-axis
     */
    void increaseXAxis();

    /**
     * @brief Increases the size of the cube in the y-axis
     */
    void increaseYAxis();

    /**
     * @brief Decreases the size of the cube in the x-axis
     */
    void decreaseXAxis();

    /**
     * @brief Decreases the size of the cube in the y-axis
     */
    void decreaseYAxis();

private:

    /**
     * @brief Draws the cube and all faces
     * 
     * @param target , the target to draw to
     * @param states , the states to draw with
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    /**
     * @brief Sets the points of the cube
     * @details Sets the points of the cube and all faces
    */
    void setPoints();

    /**
     * @brief Sets the points of the faces
     * @details Sets the points of the faces
    */
    void setFacePoints();
    float sizeX;
    float sizeY;

    sf::ConvexShape cube;
    std::vector<sf::ConvexShape> faces;
    std::vector<sf::Vector2f> points;


};


#endif //PROJEKT_CUBE_H
