#include <MapState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>
#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Image.hpp>
TypeMap::ID typeOfMap;
TypeMap::ID setTypeMap(int typeMap){
    switch (typeMap)
    {
    case 0:
        return TypeMap::Spring;
    case 1:
        return TypeMap::Autumn;
    case 2:
        return TypeMap::Winter;
    case 3:
        return TypeMap::Atlantis;
    case 4:
        return TypeMap::Jura;
    default:
        throw "Invalid the type of map!";
    }
}
MapState::MapState(StateStack &stack, Context context)
: State(stack, context)
, mGUIContainer()
{
    mBackgroundSprite.setTexture(context.textures->get(Textures::Map));
    listMap[0].loadFromFile("Media/Textures/Spring.png");
    listMap[1].loadFromFile("Media/Textures/Autumn.png");
    listMap[2].loadFromFile("Media/Textures/Winter.png");
    listMap[3].loadFromFile("Media/Textures/Atlantis.png");
    listMap[4].loadFromFile("Media/Textures/Jura.png");

    mMap.setPosition(470, 100);
    mMap.setScale(0.8, 0.8);
    mMap.setTexture(listMap[0]);

    auto backButton = std::make_shared<GUI::Button>(context);
	backButton->setPosition(70.f, 950.f);
	backButton->setText("Back", 40);
	backButton->setCallback([this]()
    {
        requestStackPop();
        requestStackPush(States::Character);
    });

    auto playButton = std::make_shared<GUI::Button>(context);
	playButton->setPosition(1540.f, 950.f);
	playButton->setText("Play", 40);
	playButton->setCallback([this]()
    {
        requestStackPop();
        requestStackPush(States::Game);
    });
    mGUIContainer.pack(backButton);
    mGUIContainer.pack(playButton);
}
void MapState::draw(){
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(mBackgroundSprite);
    window.draw(mMap);
    window.draw(mGUIContainer);
}
bool MapState::handleEvent(const sf::Event& event){
    if (event.type == sf::Event::KeyPressed){
        if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right){
            if (typeMap < listMap.size() - 1){
                typeMap++;
            }
        }
        else if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left){
            if (typeMap > 0){
                typeMap--;
            }
        }
    }
    mGUIContainer.handleEvent(event);
    return true;
}
bool MapState::update(sf::Time dt){
    mMap.setTexture(listMap[typeMap]);
    //std::cout << typeMap << '\n';
    typeOfMap = setTypeMap(typeMap);
    return true;
}