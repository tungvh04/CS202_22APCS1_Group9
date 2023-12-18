#ifndef MOVINGOBJECT_HPP
#define MOVINGOBJECT_HPP
#include <Entity.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
class MovingObject : public Entity{
    public:
        explicit MovingObject(const sf::Texture& mTexture);
        MovingObject(const sf::Texture& mTexture, sf::IntRect bound);

        void setTexture(const sf::Texture& mTexture);
        virtual sf::FloatRect getBoundingRect() const;
        sf::FloatRect getGlobalBounds() const;

    private:
        sf::Sprite mSprite;
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif