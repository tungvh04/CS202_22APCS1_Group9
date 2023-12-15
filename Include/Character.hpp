#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <Entity.hpp>
#include <ResourceIdentifiers.hpp>
#include <Const.hpp>

#include <SFML/Graphics/Sprite.hpp>

#include <queue>

class Character : public Entity {
public:
    enum Type {
        Player,
    };
    Character(Type type, const TextureHolder& textures);
    virtual unsigned int getCategory() const;
    void pathRequest(sf::Vector2f direction);

private:
    std::queue<sf::Vector2f> mPath;
    float distanceTravelled = 0;
    const float distancePerCommand = Constants::GridSize;
    virtual void updateCurrent(sf::Time dt);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    Type mType;
    sf::Sprite mSprite;
    sf::Vector2f mGridPosition;
};


#endif // CHARACTER_HPP