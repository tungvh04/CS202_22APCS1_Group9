#include <Player.hpp>
#include <CommandQueue.hpp>
#include <Character.hpp>
#include <Foreach.hpp>
#include <Const.hpp>

#include <map>
#include <string>
#include <algorithm>

struct CharacterMover {
    CharacterMover(float vx, float vy) : velocity(vx, vy) {}

    void operator() (Character& character, sf::Time) const {
        // character.accelerate(velocity);
        character.pathRequest(velocity);
    }

    sf::Vector2f velocity;
};

Player::Player() {
    // Set initial key bindings
    mKeyBinding[sf::Keyboard::Left] = MoveLeft;
    mKeyBinding[sf::Keyboard::Right] = MoveRight;
    mKeyBinding[sf::Keyboard::Up] = MoveUp;
    mKeyBinding[sf::Keyboard::Down] = MoveDown;

    // Set initial action bindings
    initializeActions();

    // Assign all categories to player's character
    FOREACH(auto& pair, mActionBinding)
        pair.second.category = Category::PlayerCharacter;
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands) {
    if (event.type == sf::Event::KeyPressed) {
        // Check if pressed key appears in key binding, trigger command if so
        auto found = mKeyBinding.find(event.key.code);
        if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
            commands.push(mActionBinding[found->second]);
    }
}

void Player::handleRealtimeInput(CommandQueue& commands) {
    // Traverse all assigned keys and check if they are pressed
    FOREACH(auto pair, mKeyBinding) {
        // If key is pressed, lookup action and trigger corresponding command
        if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
            commands.push(mActionBinding[pair.second]);
    }
}

void Player::assignKey(Action action, sf::Keyboard::Key key) {
    // Remove all keys that already map to action
    for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); ) {
        if (itr->second == action)
            mKeyBinding.erase(itr++);
        else
            ++itr;
    }

    // Insert new binding
    mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const {
    FOREACH(auto pair, mKeyBinding) {
        if (pair.second == action)
            return pair.first;
    }

    return sf::Keyboard::Unknown;
}

void Player::setMissionStatus(MissionStatus status)
{
	mCurrentMissionStatus = status;
}

Player::MissionStatus Player::getMissionStatus() const
{
	return mCurrentMissionStatus;
}

void Player::initializeActions() {
    // const float playerSpeed = 200.f;
    const float playerSpeed = Constants::playerSpeed;

    mActionBinding[MoveLeft].action = derivedAction<Character>(CharacterMover(-playerSpeed, 0.f));
    mActionBinding[MoveRight].action = derivedAction<Character>(CharacterMover(+playerSpeed, 0.f));
    mActionBinding[MoveUp].action = derivedAction<Character>(CharacterMover(0.f, -playerSpeed));
    mActionBinding[MoveDown].action = derivedAction<Character>(CharacterMover(0.f, +playerSpeed));
}

bool Player::isRealtimeAction(Action action) {
    switch (action) {
        case MoveLeft:
        case MoveRight:
        case MoveDown:
        case MoveUp:
            //return true;
            return false;

        default:
            return false;
    }
}