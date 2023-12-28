#include <DataTables.hpp>

// For std::bind() placeholders _1, _2, ...
using namespace std::placeholders;

std::vector<ObstacleData> initializeObstacleData()
{
	std::vector<ObstacleData> data(Obstacle::Type::TypeCount);

	data[Obstacle::Type::Car].speed = sf::Vector2f(100.f, 0.f);
	data[Obstacle::Type::Car].scaleX = false;
	data[Obstacle::Type::Car].scaleY = true;
	data[Obstacle::Type::Car].texture = Textures::ID::Car;
	data[Obstacle::Type::Car].minTime = sf::seconds(5);
	data[Obstacle::Type::Car].maxTime = sf::seconds(10);

	data[Obstacle::Type::Car1].speed = sf::Vector2f(-100.f, 0.f);
	data[Obstacle::Type::Car1].scaleX = false;
	data[Obstacle::Type::Car1].scaleY = true;
	data[Obstacle::Type::Car1].texture = Textures::ID::Car;
	data[Obstacle::Type::Car1].minTime = sf::seconds(4);
	data[Obstacle::Type::Car1].maxTime = sf::seconds(8);

	return data;
}