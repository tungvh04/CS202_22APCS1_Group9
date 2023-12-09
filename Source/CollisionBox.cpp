#include <CollisionBox.hpp>

bool BoundingBox::collide(sf::Vector2f x) {
    return boundingBox.contains(x);
}

bool BoundingBox::collide(BoundingBox &x) {
    return boundingBox.intersects(x.boundingBox);
}

void BoundingBox::setBoundingBox(sf::FloatRect x) {
    boundingBox=x;
}