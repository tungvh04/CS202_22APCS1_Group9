#include <SettingState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

SettingState::SettingState(StateStack& stack, Context context)
: State(stack, context)
, mGUIContainer()
{
	mBackgroundSprite.setTexture(context.textures->get(Textures::Background));
	
	addButtonLabel(Player::MoveLeft,  200.f, "Move Left", context);
	addButtonLabel(Player::MoveRight, 300.f, "Move Right", context);
	addButtonLabel(Player::MoveUp,    400.f, "Move Up", context);
	addButtonLabel(Player::MoveDown,  500.f, "Move Down", context);

	updateLabel();

	auto soundButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	soundButton->setPosition(80.f, 600.f);
	soundButton->setText("Sound", 30);
	soundButton->setCallback([this]()
    {
        requestStackPop();
        requestStackPush(States::Menu);
    });

	auto backButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	backButton->setPosition(80.f, 700.f);
	backButton->setText("Back", 30);
	backButton->setCallback([this]()
    {
        requestStackPop();
        requestStackPush(States::Menu);
    });

	mGUIContainer.pack(soundButton);
	mGUIContainer.pack(backButton);
}

void SettingState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}

bool SettingState::update(sf::Time)
{
	return true;
}

bool SettingState::handleEvent(const sf::Event& event)
{
	bool isKeyBinding = false;
	
	// Iterate through all key binding buttons to see if they are being pressed, waiting for the user to enter a key
	for (std::size_t action = 0; action < Player::ActionCount; ++action)
	{
		if (mBindingButtons[action]->isActive())
		{
			isKeyBinding = true;
			if (event.type == sf::Event::KeyReleased)
			{
				getContext().player->assignKey(static_cast<Player::Action>(action), event.key.code);
				mBindingButtons[action]->deactivate();
			}
			break;
		}
	}

	// If pressed button changed key bindings, update labels; otherwise consider other buttons in container
	if (isKeyBinding)
		updateLabel();
	else
		mGUIContainer.handleEvent(event);

	return false;
}

void SettingState::updateLabel()
{
	// Player& player = *getContext().player;

	// for (std::size_t i = 0; i < Player::ActionCount; ++i)
	// {
	// 	sf::Keyboard::Key key = player.getAssignedKey(static_cast<Player::Action>(i));
	// 	mBindingLabels[i]->setText(toString(key));
	// }
}

void SettingState::addButtonLabel(Player::Action action, float y, const std::string& text, Context context)
{
	mBindingButtons[action] = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	mBindingButtons[action]->setPosition(80.f, y);
	mBindingButtons[action]->setText(text, 30);
	mBindingButtons[action]->setToggle(true);

	mBindingLabels[action] = std::make_shared<GUI::Label>("", *context.fonts);
	mBindingLabels[action]->setPosition(300.f, y + 15.f);

	mGUIContainer.pack(mBindingButtons[action]);
	mGUIContainer.pack(mBindingLabels[action]);
}