#include <iostream>

#include <Command.hpp>
#include <SceneNode.hpp>
#include <Foreach.hpp>
#include <Const.hpp>
#include <Utility.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <algorithm>
#include <cassert>
#include <cmath>
using namespace std;
SceneNode::SceneNode(Category::Type category) : mChildren(), mParent(nullptr), mDefaultCategory(category) {}

void SceneNode::attachChild(Ptr child) {
    child->mParent = this;
    mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node) {
    auto found = std::find_if(mChildren.begin(), mChildren.end(), [&] (Ptr& p) {
        return p.get() == &node;
    });
    assert(found != mChildren.end());

    Ptr result = std::move(*found);
    result->mParent = nullptr;
    mChildren.erase(found);
    return result;
}

void SceneNode::update(sf::Time dt) {
    updateCurrent(dt);
    updateChildren(dt);
}

void SceneNode::updateCurrent(sf::Time) {
    // Do nothing by default
}

void SceneNode::updateChildren(sf::Time dt) {
    FOREACH(Ptr& child, mChildren)
        child->update(dt);
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (isHide()) return;
    states.transform *= getTransform();

    drawCurrent(target, states);
    drawChildren(target, states);

    drawBoundingRect(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget&, sf::RenderStates) const {
    // Do nothing by default
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const {
    FOREACH(const Ptr& child, mChildren)
        child->draw(target, states);
}

sf::Vector2f SceneNode::getWorldPosition() const {
    return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const {
    sf::Transform transform = sf::Transform::Identity;

    for (const SceneNode* node = this; node != nullptr; node = node->mParent)
        transform = node->getTransform() * transform;

    return transform;
}

void SceneNode::onCommand(const Command& command, sf::Time dt) {
    if (command.category & getCategory())
        command.action(*this, dt);

    FOREACH(Ptr& child, mChildren)
        child->onCommand(command, dt);
}

unsigned int SceneNode::getCategory() const {
    return mDefaultCategory;
}

void SceneNode::outOfScreen(){
    FOREACH(const Ptr& child, mChildren){
        if (child->getPosition().x > Constants::WindowWidth){
            float height = child->getPosition().y;
            child->setPosition(sf::Vector2f(-100, height));
        }
    }
}

sf::FloatRect SceneNode::getBoundingRect() const {
    return sf::FloatRect();
}

bool SceneNode::collision(const sf::FloatRect& rect) const {
    return getBoundingRect().intersects(rect);
}

void SceneNode::drawBoundingRect(sf::RenderTarget& target, sf::RenderStates) const {
    sf::FloatRect rect = getBoundingRect();

    sf::RectangleShape shape;
    shape.setPosition(sf::Vector2f(rect.left, rect.top));
    shape.setSize(sf::Vector2f(rect.width, rect.height));
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Green);
    shape.setOutlineThickness(1.f);

    target.draw(shape);
}

void SceneNode::checkNodeCollision(const sf::FloatRect& rect, std::set<SceneNode*>& collisionNodes) {
    if (collision(rect))
        collisionNodes.insert(this);
    FOREACH(Ptr& child, mChildren)
        child->checkNodeCollision(rect, collisionNodes);
}

bool SceneNode::isDestroyed() const {
    if (isDestroyedFlag) return true;
    return false;
}

void SceneNode::setDestroy() {
    isDestroyedFlag=true;
}

void SceneNode::removeWrecks() {
    auto wreckfieldBegin = std::remove_if(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::isDestroyed));
    mChildren.erase(wreckfieldBegin, mChildren.end());

    std::for_each(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::removeWrecks));
}

void SceneNode::hide() {
    isHideFlag = true;
}

void SceneNode::show() {
    isHideFlag = false;
}

bool SceneNode::isHide() const {
    return isHideFlag;
}

SceneNode* SceneNode::getParent() {
    return mParent;
}

void SceneNode::setKillTime(sf::Time dt) {
    killByTime=true;
    killTime=dt;
}

bool SceneNode::isKillByTime() const {
    return killByTime;
}

sf::Time SceneNode::getKillTime() const {
    return killTime;
}