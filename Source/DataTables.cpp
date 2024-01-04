#include <DataTables.hpp>

// For std::bind() placeholders _1, _2, ...
using namespace std::placeholders;

std::vector<ObstacleData> initializeObstacleData()
{
	std::vector<ObstacleData> data(Obstacle::Type::TypeCount);

	data[Obstacle::Type::Car].speed = sf::Vector2f(Constants::carSpeed, 0.f);
	data[Obstacle::Type::Car].scaleX = false;
	data[Obstacle::Type::Car].scaleY = true;
	data[Obstacle::Type::Car].texture = Textures::ID::Car;
	data[Obstacle::Type::Car].minTime = sf::seconds(1.5);
	data[Obstacle::Type::Car].maxTime = sf::seconds(2);
	data[Obstacle::Type::Car].groupDelayTime = sf::seconds(5);
	data[Obstacle::Type::Car].groupSpawnAmount = 2;
	data[Obstacle::Type::Car].spawnOffset = 700.f;
	data[Obstacle::Type::Car].passTime = sf::seconds(Constants::WindowWidth/Constants::trainSpeed);

	data[Obstacle::Type::Car1].speed = sf::Vector2f(-Constants::carSpeed, 0.f);
	data[Obstacle::Type::Car1].scaleX = false;
	data[Obstacle::Type::Car1].scaleY = true;
	data[Obstacle::Type::Car1].texture = Textures::ID::Car;
	data[Obstacle::Type::Car1].minTime = sf::seconds(1.6);
	data[Obstacle::Type::Car1].maxTime = sf::seconds(2.8);
	data[Obstacle::Type::Car1].flipHorizontal = true;
	data[Obstacle::Type::Car1].groupDelayTime = sf::seconds(5);
	data[Obstacle::Type::Car1].groupSpawnAmount = 3;
	data[Obstacle::Type::Car1].passTime = sf::seconds(Constants::WindowWidth/Constants::trainSpeed);

	data[Obstacle::Type::Stone].scaleX = false;
	data[Obstacle::Type::Stone].scaleY = true;
	data[Obstacle::Type::Stone].texture = Textures::ID::Stone;
	data[Obstacle::Type::Stone].minDistance = 6;
	data[Obstacle::Type::Stone].maxDistance = 10;

	data[Obstacle::Type::Island].scaleX = true;
	data[Obstacle::Type::Island].scaleY = true;
	data[Obstacle::Type::Island].texture = Textures::ID::Island;
	data[Obstacle::Type::Island].minDistance = 0;
	data[Obstacle::Type::Island].maxDistance = 2;
	//data[Obstacle::Type::Island].killByTime = true;
	//data[Obstacle::Type::Island].killTime = sf::seconds(4);

	data[Obstacle::Type::Train].speed = sf::Vector2f(Constants::trainSpeed, 0.f);
	data[Obstacle::Type::Train].scaleX = false;
	data[Obstacle::Type::Train].scaleY = true;
	data[Obstacle::Type::Train].texture = Textures::ID::Train;
	data[Obstacle::Type::Train].minTime = sf::seconds(Constants::trainCycleTimeLowerBound);
	data[Obstacle::Type::Train].maxTime = sf::seconds(Constants::trainCycleTimeUpperBound);
	data[Obstacle::Type::Train].groupDelayTime = sf::seconds(5);
	data[Obstacle::Type::Train].groupSpawnAmount = 1;
	data[Obstacle::Type::Train].passTime = sf::seconds(Constants::WindowWidth/Constants::trainSpeed);

	data[Obstacle::Type::Train1].speed = sf::Vector2f(-Constants::trainSpeed, 0.f);
	data[Obstacle::Type::Train1].scaleX = false;
	data[Obstacle::Type::Train1].scaleY = true;
	data[Obstacle::Type::Train1].texture = Textures::ID::Train;
	data[Obstacle::Type::Train1].minTime = sf::seconds(Constants::trainCycleTimeLowerBound);
	data[Obstacle::Type::Train1].maxTime = sf::seconds(Constants::trainCycleTimeUpperBound);
	data[Obstacle::Type::Train1].flipHorizontal = true;
	data[Obstacle::Type::Train1].groupDelayTime = sf::seconds(5);
	data[Obstacle::Type::Train1].groupSpawnAmount = 1;
	data[Obstacle::Type::Train1].passTime = sf::seconds(Constants::WindowWidth/Constants::trainSpeed);

	data[Obstacle::Type::TrafficLightRed].scaleX = false;
	data[Obstacle::Type::TrafficLightRed].scaleY = true;
	data[Obstacle::Type::TrafficLightRed].texture = Textures::ID::TrafficLightRed;
	
	data[Obstacle::Type::TrafficLightGreen].scaleX = false;
	data[Obstacle::Type::TrafficLightGreen].scaleY = true;
	data[Obstacle::Type::TrafficLightGreen].texture = Textures::ID::TrafficLightGreen;
	
	data[Obstacle::Type::TrafficLightYellow].scaleX = false;
	data[Obstacle::Type::TrafficLightYellow].scaleY = true;
	data[Obstacle::Type::TrafficLightYellow].texture = Textures::ID::TrafficLightYellow;
	
	return data;
}