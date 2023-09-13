//
// Created by emilj on 2022-12-17.
//

#include "Cube.h"



Cube::Cube(const float &sizeX, const float &sizeY) : sizeX(sizeX), sizeY(sizeY), faces(3), points(7), cube(6){
    cube.setOrigin(50,50);
    setFillColor(sf::Color(36, 213, 151));

    faces[0].setFillColor(sf::Color(170, 170, 170, 100));
    faces[1].setFillColor(sf::Color(145, 145, 145, 100));
    faces[2].setFillColor(sf::Color(130, 130, 130, 100));

    for(auto& face: faces){
        face.setPointCount(4);
        face.setOrigin(50,50);
    }

    setPoints();
}

Cube::Cube(const sf::Vector2f &size) : Cube(size.x, size.y) {}

Cube::Cube(const sf::Vector2f &size, const sf::Vector2f &position) : Cube(size) {
    setPosition(sf::Vector2f(position));
}


void Cube::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(cube);
    for(const auto& face: faces){
        target.draw(face);
    }
}


void Cube::setPosition(const sf::Vector2f &position) {
    cube.setPosition(position);
    for(auto& face: faces){
        face.setPosition(position);
    }
}

void Cube::setPoints() {
    points[0] = sf::Vector2f(50.f + sizeX - sizeY, 0.f - sizeX/2 - sizeY/2);
    points[1] = sf::Vector2f( 100.f + sizeX, 25.f - sizeX/2);
    points[2] = sf::Vector2f(100.f + sizeX, 75.f - sizeX/2);
    points[3] = sf::Vector2f(50.f, 100.f);
    points[4] = sf::Vector2f(0.f - sizeY, 75.f - sizeY/2);
    points[5] = sf::Vector2f(0.f - sizeY, 25.f - sizeY/2);
    points[6] = sf::Vector2f (50.f, 50.f);

    for(int i = 0; i < points.size(); i++){
        cube.setPoint(i, points[i]);
    }

    setFacePoints();
}

void Cube::setFacePoints() {
    //top face
    faces[0].setPoint(0, points[0]);
    faces[0].setPoint(1, points[1]);
    faces[0].setPoint(2, points[6]);
    faces[0].setPoint(3, points[5]);

//right face
    faces[2].setPoint(0, points[6]);
    faces[2].setPoint(1, points[1]);
    faces[2].setPoint(2, points[2]);
    faces[2].setPoint(3, points[3]);

//left face
    faces[1].setPoint(0, points[5]);
    faces[1].setPoint(1, points[6]);
    faces[1].setPoint(2, points[3]);
    faces[1].setPoint(3, points[4]);
}

void Cube::increaseXAxis() {
    sizeX = sizeX + 1;
    setPoints();
}

void Cube::increaseYAxis() {
    sizeY = sizeY + 1;
    setPoints();
}

void Cube::decreaseXAxis() {
    (sizeX < -50) ? : sizeX = sizeX - 1;
    setPoints();
}

void Cube::decreaseYAxis() {
    (sizeY < -50) ? : sizeY = sizeY - 1;
    setPoints();
}

void Cube::setSize(const sf::Vector2f& newSize){
    sizeX = newSize.x;
    sizeY = newSize.y;
    setPoints();
}

sf::Vector2f Cube::getSize() const {
    return {sizeX, sizeY};
}

sf::Vector2f Cube::getPosition() const {
    return cube.getPosition();
}

void Cube::setFillColor(const sf::Color& color) {
    cube.setFillColor(color);
}





