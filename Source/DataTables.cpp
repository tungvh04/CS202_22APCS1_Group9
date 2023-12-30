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
	data[Obstacle::Type::Car].minTime = sf::seconds(5);
	data[Obstacle::Type::Car].maxTime = sf::seconds(10);

	data[Obstacle::Type::Car1].speed = sf::Vector2f(-Constants::carSpeed, 0.f);
	data[Obstacle::Type::Car1].scaleX = false;
	data[Obstacle::Type::Car1].scaleY = true;
	data[Obstacle::Type::Car1].texture = Textures::ID::Car;
	data[Obstacle::Type::Car1].minTime = sf::seconds(4);
	data[Obstacle::Type::Car1].maxTime = sf::seconds(8);

	data[Obstacle::Type::Stone].scaleX = true;
	data[Obstacle::Type::Stone].scaleY = true;
	data[Obstacle::Type::Stone].texture = Textures::ID::Road;
	data[Obstacle::Type::Stone].minDistance = 4;
	data[Obstacle::Type::Stone].maxDistance = 7;

	data[Obstacle::Type::Island].scaleX = true;
	data[Obstacle::Type::Island].scaleY = true;
	data[Obstacle::Type::Island].texture = Textures::ID::Island;
	data[Obstacle::Type::Island].minDistance = 4;
	data[Obstacle::Type::Island].maxDistance = 7;
	data[Obstacle::Type::Island].killByTime = true;
	data[Obstacle::Type::Island].killTime = sf::seconds(4);

	data[Obstacle::Type::TrafficLight].scaleX = true;
	data[Obstacle::Type::TrafficLight].scaleY = true;
	data[Obstacle::Type::TrafficLight].texture = Textures::ID::Road;

	data[Obstacle::Type::Train].speed = sf::Vector2f(Constants::trainSpeed, 0.f);
	data[Obstacle::Type::Train].scaleX = false;
	data[Obstacle::Type::Train].scaleY = true;
	data[Obstacle::Type::Train].texture = Textures::ID::Train;
	data[Obstacle::Type::Train].minTime = sf::seconds(Constants::trainCycleTimeLowerBound);
	data[Obstacle::Type::Train].maxTime = sf::seconds(Constants::trainCycleTimeUpperBound);

	data[Obstacle::Type::Train1].speed = sf::Vector2f(-Constants::trainSpeed, 0.f);
	data[Obstacle::Type::Train1].scaleX = false;
	data[Obstacle::Type::Train1].scaleY = true;
	data[Obstacle::Type::Train1].texture = Textures::ID::Train;
	data[Obstacle::Type::Train1].minTime = sf::seconds(Constants::trainCycleTimeLowerBound);
	data[Obstacle::Type::Train1].maxTime = sf::seconds(Constants::trainCycleTimeUpperBound);

	return data;
}