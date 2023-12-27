#include <CharacterState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>
#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Image.hpp>
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

    addCharacterTexture("Frog", "Blue", 11);
    addBackGroudCharacterTexture("Frog", "Blue");

    addCharacterTexture("Frog", "Green", 11);
    addBackGroudCharacterTexture("Frog", "Green");

    addCharacterTexture("Frog", "Yellow", 11);
    addBackGroudCharacterTexture("Frog", "Yellow");

    addCharacterTexture("Frog", "Pink", 11);
    addBackGroudCharacterTexture("Frog", "Pink");

    mName.setFillColor(sf::Color::Black);
    mName.setCharacterSize(40);
    mName.setOutlineThickness(0.5);
    mName.setFont(context.fonts->get(Fonts::Main));
    mName.setPosition(830, 200);
    
    mName.setString(listName[0]);

    mCharacterSprite.setTexture(mCharacterTexture[0][0]);
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
	playButton->setPosition(1540.f, 950.f);
	playButton->setText("Next", 40);
	playButton->setCallback([this]()
    {
        requestStackPop();
        requestStackPush(States::Map);
    });
    mGUIContainer.pack(backButton);
    mGUIContainer.pack(playButton);
}
void CharacterState::addCharacterTexture(const std::string &nameCharacter, const std::string &color, int numOfPicture){
    std::string nameFile = color + nameCharacter;
    listName.push_back(color + " " + nameCharacter);
    std::vector<sf::Texture> frame;
    sf::Texture texture;
    for (int i = 1; i <= numOfPicture; i++){
        if (!texture.loadFromFile("Media/Textures/Characters/" + nameCharacter + "/" + nameFile + "_" + std::to_string(i) + ".png")) {
            std::cerr << "Error loading image frame" << i << ".png" << std::endl;
            return;
        }
        
        frame.push_back(resizeTexture(texture, sf::Vector2u(240, 240)));
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
    window.draw(mName);
    window.draw(mCharacterSprite);
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
    if (clock.getElapsedTime() >= frameTime){

        mName.setString(listName[typeCharacter]);
        mCharacterSprite.setTexture(mCharacterTexture[typeCharacter][currentFrame]);
        if (++currentFrame >= mCharacterTexture[typeCharacter].size()) currentFrame = 0;
        clock.restart();
    }
    mBackgroundSpriteCharacter.setTexture(mBackgroundTextureCharacter[typeCharacter]);
    return true;
}
sf::Texture CharacterState::resizeTexture(const sf::Texture& originalTexture, const sf::Vector2u& targetSize) {

    sf::Image originalImage = originalTexture.copyToImage();
    sf::Image resizedImage;
    resizedImage.create(targetSize.x, targetSize.y, sf::Color::Transparent);

    float xScale = static_cast<float>(targetSize.x) / originalImage.getSize().x;
    float yScale = static_cast<float>(targetSize.y) / originalImage.getSize().y;

    for (unsigned int x = 0; x < targetSize.x; ++x) {
        for (unsigned int y = 0; y < targetSize.y; ++y) {
            unsigned int origX = static_cast<unsigned int>(x / xScale);
            unsigned int origY = static_cast<unsigned int>(y / yScale);

            sf::Color pixelColor = originalImage.getPixel(origX, origY);
            resizedImage.setPixel(x, y, pixelColor);
        }
    }

    sf::Texture resizedTexture;
    resizedTexture.loadFromImage(resizedImage);
    resizedTexture.setSmooth(false);
    return resizedTexture;
}