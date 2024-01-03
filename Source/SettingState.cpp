#include <iostream>
#include <SettingState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

SettingState::SettingState(StateStack& stack, Context context)
: State(stack, context)
, mSoundButton(context)
, mGUIContainer()
{
	mBackgroundSprite.setTexture(context.textures->get(Textures::Background));
    mVolume.setFont(context.fonts->get(Fonts::Main));
    mVolume.setCharacterSize(40);
    mVolume.setFillColor(sf::Color::Black);

    float weight = 768*(1 - 0.1*volume);
    mSound1.setTexture(context.textures->get(Textures::Sound1));
    mSound1.setPosition(500, 620);

    mSound2.setTexture(context.textures->get(Textures::Sound2));
    mSound2.setScale(1 - 0.1* volume, 1);
    mSound2.setPosition(500 + 0.1*volume*768, 620);


    circle.setFillColor(sf::Color::Black);
    circle.setPosition(1245, 615);
    circle.setRadius(23);
    
	addButtonLabel(Player::MoveLeft,  200.f, "Move Left", context);
	addButtonLabel(Player::MoveRight, 300.f, "Move Right", context);
	addButtonLabel(Player::MoveUp,    400.f, "Move Up", context);
	addButtonLabel(Player::MoveDown,  500.f, "Move Down", context);
    addButtonLabel(Player::Sound, 600.0f, "Sound", context);

	updateLabel();

	mSoundButton.setPosition(80.f, 600.f);
	mSoundButton.setText("Sound", 30);

	auto backButton = std::make_shared<GUI::Button>(context);
	backButton->setPosition(80.f, 700.f);
	backButton->setText("Back", 30);
	backButton->setCallback([this]()
    {
        // requestStackPop();
		requestStateClear();
        requestStackPush(States::Menu);
    });
	mGUIContainer.pack(backButton);
}

void SettingState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mBackgroundSprite);
    if (isSettingSound == true){
        window.draw(mSound1);
        window.draw(mSound2);
      
        window.draw(circle);
    }
    window.draw(mVolume);
	window.draw(mGUIContainer);
}

bool SettingState::update(sf::Time)
{
	return true;
}

bool SettingState::handleEvent(const sf::Event& event)
{
	bool isKeyBinding = false;
	
    for (std::size_t action = 0; action < Player::ActionCount - 1; ++action)
	{
		if (mBindingButtons[action]->isActive())
		{
			isKeyBinding = true;
			if (event.type == sf::Event::KeyPressed)
			{
				getContext().player->assignKey(static_cast<Player::Action>(action), event.key.code);
				mBindingButtons[action]->deactivate();
			}
			break;
		}
	}
    if (mBindingButtons[Player::Sound]->isActive()){
        isKeyBinding = true;
        isSettingSound = true;
        mVolume.setPosition(500 + 76.8*volume - 23, 550);
        mVolume.setString(toString(10*volume) + "%");
        if (event.type == sf::Event::KeyPressed){
            if (event.key.code == sf::Keyboard::Right)
            {
                if (volume < 10) volume++;
                //Change sound of system...
            }
            else if (event.key.code == sf::Keyboard::Left)
            {
                if (volume >= 1) volume--;
                //Change sound of system...
            }
            else if (event.key.code == sf::Keyboard::Return){
                mBindingButtons[Player::Sound]->deactivate();
                mVolume.setString(toString(10*volume) + "%");
                mVolume.setPosition(500.f, 615.f);
                isSettingSound = false;
                return true;
            }
            mVolume.setPosition(500 + 76.8*volume - 23, 550);
            mVolume.setString(toString(10*volume) + "%");
            
            circle.setPosition(500 + 76.8*volume - 23, 615);
            mSound2.setScale(1 - 0.1* volume, 1);
            mSound2.setPosition(500 + 0.1*volume*768, 620);
        }
    }
	if (isKeyBinding)
		updateLabel();
	else 
    {
		mGUIContainer.handleEvent(event);
    }
	return false;
}

void SettingState::updateLabel()
{
	Player& player = *getContext().player;

	for (std::size_t i = 0; i < Player::ActionCount - 1; ++i)
	{
		sf::Keyboard::Key key = player.getAssignedKey(static_cast<Player::Action>(i));
		mBindingLabels[i]->setText(fromKtoS(key));
	}
}

void SettingState::addButtonLabel(Player::Action action, float y, const std::string& text, Context context)
{
	mBindingButtons[action] = std::make_shared<GUI::Button>(context);
	mBindingButtons[action]->setPosition(80.f, y);
	mBindingButtons[action]->setText(text, 30);
	mBindingButtons[action]->setToggle(true);

	mBindingLabels[action] = std::make_shared<GUI::Label>("", *context.fonts);
	mBindingLabels[action]->setColor(sf::Color::Black);
	mBindingLabels[action]->setPosition(500.f, y + 15.f);

	mGUIContainer.pack(mBindingButtons[action]);
	mGUIContainer.pack(mBindingLabels[action]);
}
std::string SettingState::fromKtoS(const sf::Keyboard::Key& key){
	std::string ret;
	switch(key){
    case sf::Keyboard::A :

        ret="A";
        break;
    case sf::Keyboard::B :

        ret="B";
        break;
    case sf::Keyboard::C :

        ret="C";
        break;
    case sf::Keyboard::D :

        ret="D";
        break;
    case sf::Keyboard::E :

        ret="E";
        break;
    case sf::Keyboard::F :

        ret="F";
        break;
    case sf::Keyboard::G :

        ret="G";
        break;
    case sf::Keyboard::H :

        ret="H";
        break;
    case sf::Keyboard::I :

        ret="I";
        break;
    case sf::Keyboard::J :

        ret="J";
        break;
    case sf::Keyboard::K :

        ret="K";
        break;
    case sf::Keyboard::L :

        ret="L";
        break;
    case sf::Keyboard::M :

        ret="M";
        break;
    case sf::Keyboard::N :

        ret="N";
        break;
    case sf::Keyboard::O :

        ret="O";
        break;
    case sf::Keyboard::P :

        ret="P";
        break;
    case sf::Keyboard::Q :

        ret="Q";
        break;
    case sf::Keyboard::R :

        ret="R";
        break;
    case sf::Keyboard::S :

        ret="S";
        break;
    case sf::Keyboard::T :

        ret="T";
        break;
    case sf::Keyboard::U :

        ret="U";
        break;
    case sf::Keyboard::V :

        ret="V";
        break;
    case sf::Keyboard::W :

        ret="W";
        break;
    case sf::Keyboard::X :

        ret="X";
        break;
    case sf::Keyboard::Y :

        ret="Y";
        break;
    case sf::Keyboard::Z :

        ret="Z";
        break;
    case sf::Keyboard::Num0 :

        ret="Num0";
        break;
    case sf::Keyboard::Num1 :

        ret="Num1";
        break;
    case sf::Keyboard::Num2 :

        ret="Num2";
        break;
    case sf::Keyboard::Num3 :

        ret="Num3";
        break;
    case sf::Keyboard::Num4 :

        ret="Num4";
        break;
    case sf::Keyboard::Num5 :

        ret="Num5";
        break;
    case sf::Keyboard::Num6 :

        ret="Num6";
        break;
    case sf::Keyboard::Num7 :

        ret="Num7";
        break;
    case sf::Keyboard::Num8 :

        ret="Num8";
        break;
    case sf::Keyboard::Num9 :

        ret="Num9";
        break;
    case sf::Keyboard::Escape :

        ret="Escape";
        break;
    case sf::Keyboard::LControl :

        ret="LControl";
        break;
    case sf::Keyboard::LShift :

        ret="LShift";
        break;
    case sf::Keyboard::LAlt :

        ret="LAlt";
        break;
    case sf::Keyboard::LSystem :

        ret="LSystem";
        break;
    case sf::Keyboard::RControl :

        ret="RControl";
        break;
    case sf::Keyboard::RShift :

        ret="RShift";
        break;
    case sf::Keyboard::RAlt :

        ret="RAlt";
        break;
    case sf::Keyboard::RSystem :

        ret="RSystem";
        break;
    case sf::Keyboard::Menu :

        ret="Menu";
        break;
    case sf::Keyboard::LBracket :

        ret="LBracket";
        break;
    case sf::Keyboard::RBracket :

        ret="RBracket";
        break;
    case sf::Keyboard::SemiColon :

        ret="SemiColon";
        break;
    case sf::Keyboard::Comma :

        ret="Comma";
        break;
    case sf::Keyboard::Period :

        ret="Period";
        break;
    case sf::Keyboard::Quote :

        ret="Quote";
        break;
    case sf::Keyboard::Slash :

        ret="Slash";
        break;
    case sf::Keyboard::BackSlash :

        ret="BackSlash";
        break;
    case sf::Keyboard::Tilde :

        ret="Tilde";
        break;
    case sf::Keyboard::Equal :

        ret="Equal";
        break;
    case sf::Keyboard::Dash :

        ret="Dash";
        break;
    case sf::Keyboard::Space :

        ret="Space";
        break;
    case sf::Keyboard::Return :

        ret="Return";
        break;
    case sf::Keyboard::BackSpace :

        ret="BackSpace";
        break;
    case sf::Keyboard::Tab :

        ret="Tab";
        break;
    case sf::Keyboard::PageUp :

        ret="PageUp";
        break;
    case sf::Keyboard::PageDown :

        ret="PageDown";
        break;
    case sf::Keyboard::End :

        ret="End";
        break;
    case sf::Keyboard::Home :

        ret="Home";
        break;
    case sf::Keyboard::Insert :

        ret="Insert";
        break;
    case sf::Keyboard::Delete :

        ret="Delete";
        break;
    case sf::Keyboard::Add :

        ret="Add";
        break;
    case sf::Keyboard::Subtract :

        ret="Subtract";
        break;
    case sf::Keyboard::Multiply :

        ret="Multiply";
        break;
    case sf::Keyboard::Divide :

        ret="Divide";
        break;
    case sf::Keyboard::Left :

        ret="Left";
        break;
    case sf::Keyboard::Right :

        ret="Right";
        break;
    case sf::Keyboard::Up :

        ret="Up";
        break;
    case sf::Keyboard::Down :

        ret="Down";
        break;
    case sf::Keyboard::Numpad0 :

        ret="Numpad0";
        break;
    case sf::Keyboard::Numpad1 :

        ret="Numpad1";
        break;
    case sf::Keyboard::Numpad2 :

        ret="Numpad2";
        break;
    case sf::Keyboard::Numpad3 :

        ret="Numpad3";
        break;
    case sf::Keyboard::Numpad4 :

        ret="Numpad4";
        break;
    case sf::Keyboard::Numpad5 :

        ret="Numpad5";
        break;
    case sf::Keyboard::Numpad6 :

        ret="Numpad6";
        break;
    case sf::Keyboard::Numpad7 :

        ret="Numpad7";
        break;
    case sf::Keyboard::Numpad8 :

        ret="Numpad8";
        break;
    case sf::Keyboard::Numpad9 :

        ret="Numpad9";
        break;
    case sf::Keyboard::F1 :

        ret="F1";
        break;
    case sf::Keyboard::F2 :

        ret="F2";
        break;
    case sf::Keyboard::F3 :

        ret="F3";
        break;
    case sf::Keyboard::F4 :

        ret="F4";
        break;
    case sf::Keyboard::F5 :

        ret="F5";
        break;
    case sf::Keyboard::F6 :

        ret="F6";
        break;
    case sf::Keyboard::F7 :

        ret="F7";
        break;
    case sf::Keyboard::F8 :

        ret="F8";
        break;
    case sf::Keyboard::F9 :

        ret="F9";
        break;
    case sf::Keyboard::F10 :

        ret="F10";
        break;
    case sf::Keyboard::F11 :

        ret="F11";
        break;
    case sf::Keyboard::F12 :

        ret="F12";
        break;
    case sf::Keyboard::F13 :

        ret="F13";
        break;
    case sf::Keyboard::F14 :

        ret="F14";
        break;
    case sf::Keyboard::F15 :

        ret="F15";
        break;
    case sf::Keyboard::Pause :

        ret="Pause";
        break;
    case sf::Keyboard::KeyCount :

        ret="KeyCount";
        break;
    default:
        ret="Unknow";
        break;
        }
    return ret;
}