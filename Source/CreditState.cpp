#include <CreditState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

CreditState::CreditState(StateStack& stack, Context context)
: State(stack, context)
, mGUIContainer()
{
	mBackgroundSprite.setTexture(context.textures->get(Textures::Credit));

	auto backButton = std::make_shared<GUI::Button>(context);
	backButton->setPosition(70.f, 970.f);
	backButton->setText("Back", 40);
	backButton->setCallback([this]()
    {
        requestStackPop();
    });
	mGUIContainer.pack(backButton);
}

void CreditState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}

bool CreditState::update(sf::Time)
{
	return false;
}

bool CreditState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	return false;
}