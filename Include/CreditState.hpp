#ifndef CREDITSTATE_HPP
#define CREDITSTATE_HPP

#include <State.hpp>
#include <Container.hpp>
#include <Button.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <array>

class CreditState : public State{
    public:
        CreditState(StateStack &stack, Context context);
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);
	private:
		sf::Sprite mBackgroundSprite;
		GUI::Container mGUIContainer;
        std::array<sf::Text, 5> mCredit;
};
#endif //CREDITSTATE_HPP