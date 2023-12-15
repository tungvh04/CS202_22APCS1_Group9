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
    addCharacterTexture("Dinosaur", "Blue");

    mCharacterSprite.setTexture(mCharacterTexture[0][0]);
    mCharacterSprite.setScale(10.0f, 10.0f);
    mCharacterSprite.setPosition(830, 500);

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
void CharacterState::addCharacterTexture(const std::string &nameCharacter, const std::string &color){
    std::string nameFile = color + nameCharacter;
    std::vector<sf::Texture> frame;
    for (int i = 1; i <= 13; i++){
        sf::Texture texture;
        if (!texture.loadFromFile("Media/Textures/Characters/" + nameCharacter + "/" + nameFile + "_" + std::to_string(i) + ".png")) {
            std::cerr << "Error loading image frame" << i << ".png" << std::endl;
            return;
        }
        frame.push_back(texture);
    }
    mCharacterTexture.push_back(frame);
    return;
}
void CharacterState::draw(){
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());
    window.draw(mBackgroundSprite);
    window.draw(mCharacterSprite);
    window.draw(mGUIContainer);
}
bool CharacterState::handleEvent(const sf::Event& event){
    mGUIContainer.handleEvent(event);
    return true;
}
bool CharacterState::update(sf::Time dt){
    sf::Time frameDuration = sf::seconds(0.5f);
    sf::Time elapsed;
    elapsed += dt;
    while (elapsed >= frameDuration) {
        elapsed -= frameDuration;
        static size_t currentFrame = 0;
        currentFrame = (currentFrame + 1) % mCharacterTexture[0].size();
        mCharacterSprite.setTexture(mCharacterTexture[0][currentFrame]);
    }
    return true;
}
