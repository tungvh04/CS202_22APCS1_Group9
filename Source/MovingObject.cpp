#include <MovingObject.hpp>
MovingObject::MovingObject(sf::Texture& mTexture) : mSprite(mTexture)
{
}
MovingObject::MovingObject(sf::Texture& mTexture, sf::IntRect bound) : mSprite(mTexture, bound)
{
}
void MovingObject::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(mSprite, states);
}