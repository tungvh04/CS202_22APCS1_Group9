#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <Entity.hpp>
#include <ResourceIdentifiers.hpp>

#include <SFML/Graphics/Sprite.hpp>

class Character : public Entity {
public:
    enum Type {
        Player,
    };
    Character(Type type, const TextureHolder& textures);

private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    Type mType;
    sf::Sprite mSprite;
};


#endif // CHARACTER_HPP