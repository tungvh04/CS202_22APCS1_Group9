#include <Application.hpp>
#include <Utility.hpp>
#include <State.hpp>
#include <StateIdentifiers.hpp>
#include <TitleState.hpp>
#include <CharacterState.hpp>
#include <MapState.hpp>
#include <GameState.hpp>
#include <MenuState.hpp>
#include <SettingState.hpp>
#include <HighScoreState.hpp>
#include <CreditState.hpp>
#include <PauseState.hpp>
#include <Const.hpp>


#include <GameOverState.hpp>
#include <CountDownState.hpp>
#include <SavingState.hpp>

#include <GameLevel.hpp>
const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application() : mWindow(sf::VideoMode(Constants::WindowWidth, Constants::WindowHeight), "States", sf::Style::Close), mTextures(), mFonts(), mPlayer(), mMusic(), mSounds(), mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer, mMusic, mSounds)), mStatisticsText(), mStatisticsUpdateTime(), mStatisticsNumFrames(0) {
    mWindow.setKeyRepeatEnabled(false);

    mFonts.load(Fonts::Main, "Media/Fonts/Sansation.ttf");
    
    mTextures.load(Textures::TitleScreen, "Media/Textures/TitleScreen.png");
    mTextures.load(Textures::Background, "Media/Textures/Background.png");
    mTextures.load(Textures::Title, "Media/Textures/Title.png");
    mTextures.load(Textures::Cloud1, "Media/Textures/Cloud1.png");
    mTextures.load(Textures::Cloud2, "Media/Textures/Cloud2.png");
    mTextures.load(Textures::Cloud3, "Media/Textures/Cloud3.png");
    mTextures.load(Textures::Cat, "Media/Textures/Cat.png");
    mTextures.load(Textures::Button, "Media/Textures/Button.png");
    mTextures.load(Textures::ButtonTouch, "Media/Textures/ButtonTouch.png");
    mTextures.load(Textures::ButtonPressed, "Media/Textures/ButtonPressed.png");
    mTextures.load(Textures::Key1, "Media/Textures/Key1.png");
    mTextures.load(Textures::Key2, "Media/Textures/Key2.png");
    mTextures.load(Textures::HighScore, "Media/Textures/HighScore.png");
    mTextures.load(Textures::Character, "Media/Textures/Character.png");
    mTextures.load(Textures::Countdown, "Media/Textures/Countdown.png");
    mTextures.load(Textures::Map, "Media/Textures/Map.png"); 
    mTextures.load(Textures::Credit,"Media/Textures/Credit.png"); 
    mTextures.load(Textures::Sound1, "Media/Textures/Sound1.png"); 
    mTextures.load(Textures::Sound2, "Media/Textures/Sound2.png");
    mTextures.load(Textures::Winter, "Media/Textures/Winter.png");
    mTextures.load(Textures::Autumn, "Media/Textures/Autumn.png");
    mTextures.load(Textures::Spring, "Media/Textures/Spring.png");

    mStatisticsText.setFont(mFonts.get(Fonts::Main));
    mStatisticsText.setPosition(5.f, 5.f);
    mStatisticsText.setCharacterSize(10u);

    registerStates();
    mStateStack.pushState(States::Title);

    mMusic.setVolume(25.f);
}

void Application::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen()) {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;

            processInput();
            update(TimePerFrame);

            if (mStateStack.isEmpty())
                mWindow.close();
        }

        updateStatistics(dt);
        render();
    }
}

void Application::processInput() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        mStateStack.handleEvent(event);

        if (event.type == sf::Event::Closed)
            mWindow.close();
    }
}
void Application::update(sf::Time dt) {
    mStateStack.update(dt);
}

void Application::render() {
    mWindow.clear();

    mStateStack.draw();

    mWindow.setView(mWindow.getDefaultView());
    mWindow.draw(mStatisticsText);

    // sf::Text text;
    // text.setFont(mFonts.get(Fonts::Main));
    // text.setPosition(10.f, 10.f);
    // text.setCharacterSize(20u);
    // text.setString("Level: " + std::to_string(gameLevel.getLevel()));

    // mWindow.draw(text);

    mWindow.display();
}

void Application::updateStatistics(sf::Time dt) {
    mStatisticsUpdateTime += dt;
    mStatisticsNumFrames += 1;

    if (mStatisticsUpdateTime >= sf::seconds(1.0f)) {
        mStatisticsText.setString("FPS: " + toString(mStatisticsNumFrames));

        mStatisticsUpdateTime -= sf::seconds(1.0f);
        mStatisticsNumFrames = 0;
    }
}

void Application::registerStates() {
    mStateStack.registerState<TitleState>(States::Title);
    mStateStack.registerState<MenuState>(States::Menu);
    mStateStack.registerState<CharacterState>(States::Character);
    mStateStack.registerState<MapState>(States::Map);
    mStateStack.registerState<SettingState>(States::Setting);
    mStateStack.registerState<CreditState>(States::Credit);
    mStateStack.registerState<HighScoreState>(States::Score);
    mStateStack.registerState<GameState>(States::Game);
    mStateStack.registerState<PauseState>(States::Pause);
    mStateStack.registerState<GameOverState>(States::GameOver);
    mStateStack.registerState<CountDownState>(States::CountDown);
    mStateStack.registerState<SavingState>(States::Saving);
}