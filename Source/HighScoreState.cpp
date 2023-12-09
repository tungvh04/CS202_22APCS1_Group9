#include <HighScoreState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

HighScoreState::HighScoreState(StateStack& stack, Context context)
: State(stack, context)
, mGUIContainer()
{
	//Example
	highScore[0].first = 123.5;
	highScore[0].second = "Winter";
	highScore[1].first = 123.5;
	highScore[1].second = "Autumn";
	highScore[2].first = 123.5;
	highScore[2].second = "Dinasaur";

	mBackgroundSprite.setTexture(context.textures->get(Textures::HighScore));
	
	auto scoreTop1 = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	scoreTop1->setPosition(650.f, 440.f);
	scoreTop1->setText(toString(highScore[0].first), 40);
	scoreTop1->setCallback([this]()
    {
    });

	auto mapTop1 = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	mapTop1->setPosition(1050.f, 440.f);
	mapTop1->setText(highScore[0].second, 40);
	mapTop1->setCallback([this]()
    {
    });

	auto scoreTop2 = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	scoreTop2->setPosition(650.f, 600.f);
	scoreTop2->setText(toString(highScore[1].first), 40);
	scoreTop2->setCallback([this]()
    {
    });

	auto mapTop2 = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	mapTop2->setPosition(1050.f, 600.f);
	mapTop2->setText(highScore[1].second, 40);
	mapTop2->setCallback([this]()
    {
    });

	auto scoreTop3 = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	scoreTop3->setPosition(650.f, 760.f);
	scoreTop3->setText(toString(highScore[2].first), 40);
	scoreTop3->setCallback([this]()
    {
    });

	auto mapTop3 = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	mapTop3->setPosition(1050.f, 760.f);
	mapTop3->setText(highScore[2].second, 40);
	mapTop3->setCallback([this]()
    {
    });

	auto backButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	backButton->setPosition(70.f, 950.f);
	backButton->setText("Back", 40);
	backButton->setCallback([this]()
    {
        requestStackPop();
        requestStackPush(States::Menu);
    });
	mGUIContainer.pack(scoreTop1);
	mGUIContainer.pack(mapTop1);
	mGUIContainer.pack(scoreTop2);
	mGUIContainer.pack(mapTop2);
	mGUIContainer.pack(scoreTop3);
	mGUIContainer.pack(mapTop3);
	mGUIContainer.pack(backButton);
}

void HighScoreState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}

bool HighScoreState::update(sf::Time)
{
	return true;
}

bool HighScoreState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	return true;
}

void HighScoreState::updateLabel()
{
	// Player& player = *getContext().player;

	// for (std::size_t i = 0; i < Player::ActionCount; ++i)
	// {
	// 	sf::Keyboard::Key key = player.getAssignedKey(static_cast<Player::Action>(i));
	// 	mBindingLabels[i]->setText(toString(key));
	// }
}

void HighScoreState::addButtonLabel(Player::Action action, float y, const std::string& text, Context context)
{
	// mBindingButtons[action] = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	// mBindingButtons[action]->setPosition(80.f, y);
	// mBindingButtons[action]->setText(text, 30);
	// mBindingButtons[action]->setToggle(true);

	// mBindingLabels[action] = std::make_shared<GUI::Label>("", *context.fonts);
	// mBindingLabels[action]->setPosition(300.f, y + 15.f);

	// mGUIContainer.pack(mBindingButtons[action]);
	// mGUIContainer.pack(mBindingLabels[action]);
}