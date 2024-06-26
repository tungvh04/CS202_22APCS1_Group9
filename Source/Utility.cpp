#include <Utility.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <cmath>

void centerOrigin(sf::Sprite& sprite) {
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void centerOrigin(sf::Text& text) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

float Rand(float l,float r) {
    return float(Rand(int(l*1000),int(r*1000)))/1000;
}

int Rand(int l,int r) {
    return (rand()%(r-l+1))+l;
}

float toDegree(float radian)
{
	return 180.f / 3.141592653589793238462643383f * radian;
}

float toRadian(float degree)
{
	return 3.141592653589793238462643383f / 180.f * degree;
}

