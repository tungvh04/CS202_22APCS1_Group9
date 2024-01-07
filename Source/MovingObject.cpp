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
    // states.transform *= getTransform();
    target.draw(mSprite, states);
}
void MovingObject::setTexture(const sf::Texture& mTexture) {
    mSprite.setTexture(mTexture);
}
sf::FloatRect MovingObject::getBoundingRect() const {
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}
sf::FloatRect MovingObject::getGlobalBounds() const {
    // return mSprite.getGlobalBounds();
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

// void MovingObject::rotate(float angle) {
    // mSprite.rotate(angle);
// }

void MovingObject::flipHorizontal() {
    // mSprite.setScale(-1.0f,1.0f);
    setScale(-1.0f,1.0f);
    //mSprite.setPosition(mSprite.getPosition().x + mSprite.getLocalBounds().width, mSprite.getPosition().y);
}

void MovingObject::flipVertical() {
    // mSprite.setScale(1.0f,-1.0f);
    setScale(1.0f,-1.0f);
    //mSprite.setPosition(mSprite.getPosition().x, mSprite.getPosition().y + mSprite.getLocalBounds().height);
}