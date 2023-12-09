#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <Entity.hpp>
#include <Const.hpp>
#include <Utility.hpp>
#include <CollisionBox.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <iostream>
#include <fstream>

class Object{
private:
    sf::Vector2f speed;

    sf::Vector2f pos;

    sf::Texture* tTexture;
    //int tTextureID;

    sf::Sprite tObj;

public:
    void setSpeed(sf::Vector2f x);
    //void setAccel(sf::Vector2f x);
    
    void update(sf::Time dt);
    
    void draw(sf::RenderWindow& window);
    void setPos(sf::Vector2f _pos);
    void setTexture(sf::Texture* _texture);
    void shiftPos(sf::Vector2f _pos);
    sf::Vector2f getPos();
};

#endif //OBJECT_HPP