#ifndef SAVINGSTATE_HPP
#define SAVINGSTATE_HPP

#include <State.hpp>
#include <Container.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class SavingState : public State
{
public:
	SavingState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);


private:
	sf::Text			mSavingText;
	sf::Time			mElapsedTime;
};

#endif // SAVINGSTATE_HPP