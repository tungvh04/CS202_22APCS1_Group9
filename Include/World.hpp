#ifndef WORLD_HPP
#define WORLD_HPP

#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <SceneNode.hpp>
#include <SpriteNode.hpp> 
#include <Character.hpp>
#include <CommandQueue.hpp>
#include <Command.hpp>
// #include <TileSystem.hpp>
#include <TileManagement.hpp>
#include <GameObject.hpp>
#include <Car.hpp>
#include <CharacterState.hpp>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <vector>
#include <array>
#include <queue>

namespace sf {
    class RenderWindow;
}

std::string IDtoString(TypeMap::ID typeOfMap);

class World : private sf::NonCopyable {
public:
    explicit World(sf::RenderWindow& window);
    void update(sf::Time dt);
    void draw();

    CommandQueue& getCommandQueue();

    bool 	hasAlivePlayer() const;
    
    bool checkCState(int x);

    void setWeather(int x);
    bool isWeather(int x);
    bool checkLastWeatherState(int x);
    void clearWeather();

    std::string getMap();

private:
    void speedUp();
    void slowDown();

    void loadTextures();
    void buildScene();
    void adaptPlayerPosition();
    void adaptPlayerVelocity();
    void handleCollisions();
    sf::FloatRect getBattlefieldBounds() const;
    sf::FloatRect getViewBounds() const;

private:
    enum Layer {
        Background,
        Air,
        LayerCount
    };

    struct SpawnPoint {
		SpawnPoint(Car::Type type, float x, float y): type(type), x(x), y(y){
		
        }

		Car::Type type;
		float x;
		float y;
	};

private:
    // TileBuilderRow tileManager;
    // TileManager tileManager;
    // TileManager mTileManager;
    TileManager* mTileManager;

    sf::RenderWindow& mWindow;
    sf::View mWorldView;
    TextureHolder mTextures;

    SceneNode mSceneGraph;
    std::array<SceneNode*, LayerCount> mSceneLayers;
    CommandQueue mCommandQueue;

    sf::FloatRect mWorldBounds;
    sf::Vector2f mSpawnPosition;
    float mScrollSpeed;
    Character* mPlayerCharacter;
    
    std::vector<TextureHolder*> mTiles;
    sf::Vector2f mOriginGrid;

    int tileCnt;

    std::vector<SpawnPoint> mEnemySpawnPoints;
	std::vector<Car*> mActiveEnemies;

    Animation screenEffect;
    int charState = 0;

    Animation weatherEffect;
    int weatherState,lastWeatherState;
};

#endif // WORLD_HPP