#include <HighScoreState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>
#include <iostream>
#include <MapState.hpp>
#include <GameLevel.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

HighScoreState::HighScoreState(StateStack& stack, Context context)
: State(stack, context)
, mGUIContainer()
{
	loadScore();
	//Example
	/*
	highScore[0].first = 234;
	highScore[0].second = "Winter";
	highScore[1].first = 220;
	highScore[1].second = "Autumn";
	highScore[2].first = 123;
	highScore[2].second = "Spring";
	*/

	mBackgroundSprite.setTexture(context.textures->get(Textures::HighScore));
	
	auto scoreTop1 = std::make_shared<GUI::Button>(context);
	scoreTop1->setPosition(650.f, 440.f);
	scoreTop1->setText(toString(highScore[0].first[0]), 40);
	scoreTop1->setCallback([this]()
    {
    });

	auto mapTop1 = std::make_shared<GUI::Button>(context);
	mapTop1->setPosition(1050.f, 440.f);
	mapTop1->setText(highScore[0].second, 40);
	mapTop1->setCallback([this]()
    {
    });

	auto scoreTop2 = std::make_shared<GUI::Button>(context);
	scoreTop2->setPosition(650.f, 600.f);
	scoreTop2->setText(toString(highScore[1].first[0]), 40);
	scoreTop2->setCallback([this]()
    {
    });

	auto mapTop2 = std::make_shared<GUI::Button>(context);
	mapTop2->setPosition(1050.f, 600.f);
	mapTop2->setText(highScore[1].second, 40);
	mapTop2->setCallback([this]()
    {
    });

	auto scoreTop3 = std::make_shared<GUI::Button>(context);
	scoreTop3->setPosition(650.f, 760.f);
	scoreTop3->setText(toString(highScore[2].first[0]), 40);
	scoreTop3->setCallback([this]()
    {
    });

	auto mapTop3 = std::make_shared<GUI::Button>(context);
	mapTop3->setPosition(1050.f, 760.f);
	mapTop3->setText(highScore[2].second, 40);
	mapTop3->setCallback([this]()
    {
    });

	auto backButton = std::make_shared<GUI::Button>(context);
	backButton->setPosition(70.f, 950.f);
	backButton->setText("Back", 40);
	backButton->setCallback([this]()
    {
        requestStackPop();
        // requestStackPush(States::Menu);
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
	
	// int scoreStateScore;
	// std::string scoreStateMapName;
	// saveScore(scoreStateScore,scoreStateMapName);
	loadScore();
	/*
	mGUIContainer.clear();

	Context context=getContext();

	auto scoreTop1 = std::make_shared<GUI::Button>(context);
	scoreTop1->setPosition(650.f, 440.f);
	scoreTop1->setText(toString(highScore[0].first), 40);
	scoreTop1->setCallback([this]()
    {
    });

	auto mapTop1 = std::make_shared<GUI::Button>(context);
	mapTop1->setPosition(1050.f, 440.f);
	mapTop1->setText(highScore[0].second, 40);
	mapTop1->setCallback([this]()
    {
    });

	auto scoreTop2 = std::make_shared<GUI::Button>(context);
	scoreTop2->setPosition(650.f, 600.f);
	scoreTop2->setText(toString(highScore[1].first), 40);
	scoreTop2->setCallback([this]()
    {
    });

	auto mapTop2 = std::make_shared<GUI::Button>(context);
	mapTop2->setPosition(1050.f, 600.f);
	mapTop2->setText(highScore[1].second, 40);
	mapTop2->setCallback([this]()
    {
    });

	auto scoreTop3 = std::make_shared<GUI::Button>(context);
	scoreTop3->setPosition(650.f, 760.f);
	scoreTop3->setText(toString(highScore[2].first), 40);
	scoreTop3->setCallback([this]()
    {
    });

	auto mapTop3 = std::make_shared<GUI::Button>(context);
	mapTop3->setPosition(1050.f, 760.f);
	mapTop3->setText(highScore[2].second, 40);
	mapTop3->setCallback([this]()
    {
    });

	auto backButton = std::make_shared<GUI::Button>(context);
	backButton->setPosition(70.f, 950.f);
	backButton->setText("Back", 40);
	backButton->setCallback([this]()
    {
        requestStackPop();
        // requestStackPush(States::Menu);
    });
	mGUIContainer.pack(scoreTop1);
	mGUIContainer.pack(mapTop1);
	mGUIContainer.pack(scoreTop2);
	mGUIContainer.pack(mapTop2);
	mGUIContainer.pack(scoreTop3);
	mGUIContainer.pack(mapTop3);
	mGUIContainer.pack(backButton);
	*/
	return false;
}

bool HighScoreState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	return false;
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
}

std::string MapID2Name(TypeMap::ID typeMap) {
	switch (typeMap) {
		case TypeMap::ID::Spring: return "Spring";
		case TypeMap::ID::Autumn: return "Autumn";
		case TypeMap::ID::Winter: return "Winter";
		case TypeMap::ID::Atlantis: return "Atlantis";
		case TypeMap::ID::Jura: return "Jura";
		default : throw "Invalid the type of map!";
	}
}

void HighScoreState::loadScore() {
	// std::ifstream in;
	// in.open(Constants::saveScorePath);
	// for (int i=0;i<=2;i++) {
		// in>>highScore[i].first;
		// getline(in,highScore[i].second);
		// std::getline(in,highScore[i].second);
	// }
	// in.close();
	for (int i = 0; i < 5; ++i) {
		highScore[i].first = GameLevel::loadHighScore(TypeMap::ID(i));
		highScore[i].second = MapID2Name(TypeMap::ID(i));
	}
}