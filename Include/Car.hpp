#ifndef CAR_HPP
#define CAR_HPP

#include <Entity.hpp>
#include <Command.hpp>
#include <ResourceIdentifiers.hpp>
#include <CommandQueue.hpp>

#include <SFML/Graphics/Sprite.hpp>


class Car : public Entity
{
	public:
		enum Type
		{
			SlowCar,
            FastCar,
            TypeCount
		};


	public:
		Car(Type type, const TextureHolder& textures);

		virtual unsigned int getCategory() const;
		virtual sf::FloatRect getBoundingRect() const;
		virtual bool isMarkedForRemoval() const;
		float getMaxSpeed() const;

	private:
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
		void updateMovementPattern(sf::Time dt);


	private:
		Type mType;
		sf::Sprite mSprite;
		bool mIsMarkedForRemoval;

        float mTravelledDistance;
		std::size_t	mDirectionIndex;
};

#endif // CAR_HPP