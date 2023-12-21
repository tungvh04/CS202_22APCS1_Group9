#include <Car.hpp>
#include <DataTables.hpp>
#include <CommandQueue.hpp>
#include <ResourceHolder.hpp>
#include <Utility.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>

namespace
{
	const std::vector<CarData> Table = initializeCarData();
}

Car::Car(Type type, const TextureHolder& textures): mType(type), mSprite(textures.get(Table[type].texture)), mIsMarkedForRemoval(false), mTravelledDistance(0.f), mDirectionIndex(0)
{
	centerOrigin(mSprite);
}

void Car::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

void Car::updateCurrent(sf::Time dt, CommandQueue& commands)
{

	// Update enemy movement pattern; apply velocity
	updateMovementPattern(dt);
	Entity::updateCurrent(dt, commands);
}

unsigned int Car::getCategory() const
{
	return Category::Car;
}

sf::FloatRect Car::getBoundingRect() const
{
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

bool Car::isMarkedForRemoval() const
{
	return mIsMarkedForRemoval;
}

float Car::getMaxSpeed() const
{
	return Table[mType].speed;
}

void Car::updateMovementPattern(sf::Time dt)
{
	// Enemy airplane: Movement pattern
	const std::vector<Direction>& directions = Table[mType].directions;
	if (!directions.empty())
	{
		// Moved long enough in current direction: Change direction
		if (mTravelledDistance > directions[mDirectionIndex].distance)
		{
			mDirectionIndex = (mDirectionIndex + 1) % directions.size();
			mTravelledDistance = 0.f;
		}

		// Compute velocity from direction
		float radians = toRadian(directions[mDirectionIndex].angle + 90.f);
		float vx = getMaxSpeed() * std::cos(radians);
		float vy = getMaxSpeed() * std::sin(radians);

		setVelocity(vx, vy);

		mTravelledDistance += getMaxSpeed() * dt.asSeconds();
	}
}