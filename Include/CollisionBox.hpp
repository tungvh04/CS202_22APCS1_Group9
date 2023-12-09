#ifndef COLLISIONBOX_HPP
#define COLLISIONBOX_HPP

#include <Entity.hpp>
#include <Const.hpp>
#include <Utility.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <iostream>
#include <fstream>

class BoundingBox{
private:
    sf::FloatRect boundingBox;

public:
    bool collide(sf::Vector2f x);
    bool collide(BoundingBox &x);

    void setBoundingBox(sf::FloatRect x);
};

#endif //COLLISIONBOX_HPP