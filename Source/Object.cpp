#include <Object.hpp>

void Object::setSpeed(sf::Vector2f x) {
    speed=x;
}

/*
void Object::setAccel(sf::Vector2f x) {
    accel=x;
}
*/

void Object::update(sf::Time dt) {
    shiftPos(dt.asSeconds()*speed);
}

void Object::draw(sf::RenderWindow& window) {
    tObj.setPosition(pos);
    tObj.setTexture(*tTexture);

    //std::cout<<"Object drawed!!!";
    
    window.draw(tObj);

    //std::cout<<"Huh? "<<pos.x<<' '<<pos.y<<'\n';
}

void Object::setPos(sf::Vector2f _pos) {
    pos=_pos;

    //std::cout<<"What? "<<_pos.x<<' '<<_pos.y<<'\n';
}

void Object::shiftPos(sf::Vector2f _pos) {
    pos+=_pos;

    //std::cout<<"What? "<<_pos.x<<' '<<_pos.y<<'\n';
}


void Object::setTexture(sf::Texture* _texture) {
    tTexture=_texture;

    tObj.setTexture(*tTexture);
    tObj.setTextureRect(sf::IntRect(pos.x,pos.y,Constants::GridSize,Constants::GridSize));
}

sf::Vector2f Object::getPos() {
    return pos;
}
