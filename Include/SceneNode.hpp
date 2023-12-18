#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <Category.hpp>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <vector>
#include <deque>
#include <memory>
#include <utility>
#include <set>

struct Command;

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable {

public:
    typedef std::unique_ptr<SceneNode> Ptr;

    explicit SceneNode(Category::Type category = Category::None);
    void attachChild(Ptr child);
    Ptr detachChild(const SceneNode& node);

    void update(sf::Time dt);
    void outOfScreen();
    
    sf::Vector2f getWorldPosition() const;
    sf::Transform getWorldTransform() const;

    void onCommand(const Command& command, sf::Time dt);
    virtual unsigned int getCategory() const;
    virtual sf::FloatRect getBoundingRect() const;

    bool collision(const sf::FloatRect& rect) const ;
    void checkNodeCollision(const sf::FloatRect& rect, std::set<SceneNode*>& collisionNodes);

    virtual bool isDestroyed() const;
    void removeWrecks();

private:
    virtual void updateCurrent(sf::Time dt);
    void updateChildren(sf::Time dt);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const;


    std::deque<Ptr> mChildren;
    SceneNode* mParent;
    Category::Type mDefaultCategory;
};

#endif // SCENENODE_HPP