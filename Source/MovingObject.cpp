#include <MovingObject.hpp>
MovingObject::MovingObject(const sf::Texture& mTexture) : mSprite(mTexture)
{
    mSprite.setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
}
MovingObject::MovingObject(const sf::Texture& mTexture, sf::IntRect bound) : mSprite(mTexture, bound)
{
    mSprite.setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
}
void MovingObject::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(mSprite, states);
}
void MovingObject::setTexture(const sf::Texture& mTexture) {
    mSprite.setTexture(mTexture);
}
sf::FloatRect MovingObject::getBoundingRect() const {
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}
sf::FloatRect MovingObject::getGlobalBounds() const {
    return mSprite.getGlobalBounds();
}