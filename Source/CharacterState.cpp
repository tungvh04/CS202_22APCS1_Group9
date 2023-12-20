#include <CharacterState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>
#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
CharacterState::CharacterState(StateStack &stack, Context context)
: State(stack, context)
, mGUIContainer()
{
    mBackgroundSprite.setTexture(context.textures->get(Textures::Character));

    addCharacterTexture("Dinosaur", "Blue", 24);
    addBackGroudCharacterTexture("Dinosaur", "Blue");

    addCharacterTexture("Dinosaur", "Green", 24);
    addBackGroudCharacterTexture("Dinosaur", "Green");

    addCharacterTexture("Dinosaur", "Yellow", 24);
    addBackGroudCharacterTexture("Dinosaur", "Yellow");
    

    addCharacterTexture("Dinosaur", "Red", 24);
    addBackGroudCharacterTexture("Dinosaur", "Red");

    addCharacterTexture("Frog", "Yellow", 11);
    addBackGroudCharacterTexture("Frog", "Yellow");

    mCharacterSprite.setTexture(mCharacterTexture[0][0]);
    mCharacterSprite.setScale(10.0f, 10.0f);
    mCharacterSprite.setPosition(830, 500);


    mBackgroundSpriteCharacter.setTexture(mBackgroundTextureCharacter[0]);
    mBackgroundSpriteCharacter.setScale(0.9f, 0.9f);
    mBackgroundSpriteCharacter.setPosition(740, 175);

    auto backButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	backButton->setPosition(70.f, 950.f);
	backButton->setText("Back", 40);
	backButton->setCallback([this]()
    {
        requestStackPop();
        requestStackPush(States::Menu);
    });

    auto playButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	playButton->setPosition(740.f, 850.f);
	playButton->setText("Play", 40);
	playButton->setCallback([this]()
    {
        requestStackPop();
        requestStackPush(States::Game);
    });
    mGUIContainer.pack(backButton);
    mGUIContainer.pack(playButton);

    sf::Texture vehi;
    vehi.loadFromFile("Media/image1x1.png");

    vehicle.setTexture(vehi);
    vehicle.setFrameSize(sf::Vector2i(100, 100));
    vehicle.setNumFrames(12);
    vehicle.setDuration(sf::seconds(1.0f));
    vehicle.setRepeating(true);
    vehicle.setPosition(100, 100);
}
void CharacterState::addCharacterTexture(const std::string &nameCharacter, const std::string &color, int numOfPicture){
    std::string nameFile = color + nameCharacter;
    std::vector<sf::Texture> frame;
    sf::Texture texture;
    for (int i = 1; i <= numOfPicture; i++){
        if (!texture.loadFromFile("Media/Textures/Characters/" + nameCharacter + "/" + nameFile + "_" + std::to_string(i) + ".png")) {
            std::cerr << "Error loading image frame" << i << ".png" << std::endl;
            return;
        }
        frame.push_back(texture);
    }
    mCharacterTexture.push_back(frame);
    return;
}
void CharacterState::addBackGroudCharacterTexture(const std::string &nameCharacter, const std::string &color){
    std::string nameFile = color + nameCharacter;
    sf::Texture texture;
    if (!texture.loadFromFile("Media/Textures/Characters/" + nameCharacter + "/" + nameFile + "BG.png")) {
        std::cerr << "Error loading BG image frame of " << nameFile << ".png" << std::endl;
        return;
    }
    mBackgroundTextureCharacter.push_back(texture);
    return;
}
void CharacterState::draw(){
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(mBackgroundSprite);
    window.draw(mBackgroundSpriteCharacter);
    window.draw(mCharacterSprite);
    window.draw(vehicle);
    window.draw(mGUIContainer);
}
bool CharacterState::handleEvent(const sf::Event& event){
    if (event.type == sf::Event::KeyPressed){
        if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right){
            if (typeCharacter < mBackgroundTextureCharacter.size() - 1){
                typeCharacter++;
            }
        }
        else if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left){
            if (typeCharacter > 0){
                typeCharacter--;
            }
        }
    }
    mGUIContainer.handleEvent(event);
    return true;
}
bool CharacterState::update(sf::Time dt){
    vehicle.update(dt);
    if (clock.getElapsedTime() >= frameTime){
        mCharacterSprite.setTexture(mCharacterTexture[typeCharacter][currentFrame]);
        if (++currentFrame >= mCharacterTexture[typeCharacter].size()) currentFrame = 0;
        clock.restart();
    }
    mBackgroundSpriteCharacter.setTexture(mBackgroundTextureCharacter[typeCharacter]);
    return true;
}
