#ifndef MOVINGOBJECT_HPP
#define MOVINGOBJECT_HPP
#include <Entity.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
class MovingObject : public Entity{
    public:
        explicit MovingObject(sf::Texture& mTexture);
        MovingObject(sf::Texture& mTexture, sf::IntRect bound);


    private:
        sf::Sprite mSprite;
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif