#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <sstream>
namespace sf {
    class Sprite;
    class Text;
}

template <typename T>
std::string toString(const T& value);

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

float Rand(float l,float r);
int Rand(int l,int r);

#include <Utility.inl>
#endif // UTILITY_HPP