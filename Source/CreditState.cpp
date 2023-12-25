#include <CreditState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

CreditState::CreditState(StateStack& stack, Context context)
: State(stack, context)
, mGUIContainer()
{
	mBackgroundSprite.setTexture(context.textures->get(Textures::Credit));

    for (int i = 0; i < 5; i++){
        mCredit[i].setFillColor(sf::Color::Black);
        mCredit[i].setFont(context.fonts->get(Fonts::Main));
        mCredit[i].setCharacterSize(40);
        mCredit[i].setPosition(800, 400 + 100*i);
    }
    mCredit[0].setString("Ngo Hoang Bao Thach");
    mCredit[1].setString("Nguyen Minh Luan");
    mCredit[2].setString("Tran Nhat Thanh");
    mCredit[3].setString("Le Van Cuong");
    mCredit[4].setString("Vu Hoang Tung");

	auto backButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	backButton->setPosition(70.f, 950.f);
	backButton->setText("Back", 40);
	backButton->setCallback([this]()
    {
        requestStackPop();
        requestStackPush(States::Menu);
    });
	mGUIContainer.pack(backButton);
}

void CreditState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mBackgroundSprite);
    for (int i = 0; i < 5; i++) window.draw(mCredit[i]);
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