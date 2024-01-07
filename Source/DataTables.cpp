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
	
	data[Obstacle::Type::Oto].speed = sf::Vector2f(Constants::carSpeed, 0.f);
	data[Obstacle::Type::Oto].scaleX = false;
	data[Obstacle::Type::Oto].scaleY = true;
	data[Obstacle::Type::Oto].texture = Textures::ID::Oto;
	data[Obstacle::Type::Oto].minTime = sf::seconds(1.5);
	data[Obstacle::Type::Oto].maxTime = sf::seconds(2);
	data[Obstacle::Type::Oto].groupDelayTime = sf::seconds(5);
	data[Obstacle::Type::Oto].groupSpawnAmount = 2;
	data[Obstacle::Type::Oto].spawnOffset = 700.f;
	data[Obstacle::Type::Oto].passTime = sf::seconds(Constants::WindowWidth/Constants::trainSpeed);

	data[Obstacle::Type::Oto_1].speed = sf::Vector2f(-Constants::carSpeed, 0.f);
	data[Obstacle::Type::Oto_1].scaleX = false;
	data[Obstacle::Type::Oto_1].scaleY = true;
	data[Obstacle::Type::Oto_1].texture = Textures::ID::Oto;
	data[Obstacle::Type::Oto_1].minTime = sf::seconds(1.6);
	data[Obstacle::Type::Oto_1].maxTime = sf::seconds(2.8);
	data[Obstacle::Type::Oto_1].flipHorizontal = true;
	data[Obstacle::Type::Oto_1].groupDelayTime = sf::seconds(5);
	data[Obstacle::Type::Oto_1].groupSpawnAmount = 3;
	data[Obstacle::Type::Oto_1].passTime = sf::seconds(Constants::WindowWidth/Constants::trainSpeed);

	data[Obstacle::Type::Oto1].speed = sf::Vector2f(Constants::carSpeed, 0.f);
	data[Obstacle::Type::Oto1].scaleX = false;
	data[Obstacle::Type::Oto1].scaleY = true;
	data[Obstacle::Type::Oto1].texture = Textures::ID::Oto1;
	data[Obstacle::Type::Oto1].minTime = sf::seconds(1.5);
	data[Obstacle::Type::Oto1].maxTime = sf::seconds(2);
	data[Obstacle::Type::Oto1].groupDelayTime = sf::seconds(5);
	data[Obstacle::Type::Oto1].groupSpawnAmount = 2;
	data[Obstacle::Type::Oto1].spawnOffset = 700.f;
	data[Obstacle::Type::Oto1].passTime = sf::seconds(Constants::WindowWidth/Constants::trainSpeed);

	data[Obstacle::Type::Oto1_1].speed = sf::Vector2f(-Constants::carSpeed, 0.f);
	data[Obstacle::Type::Oto1_1].scaleX = false;
	data[Obstacle::Type::Oto1_1].scaleY = true;
	data[Obstacle::Type::Oto1_1].texture = Textures::ID::Oto1;
	data[Obstacle::Type::Oto1_1].minTime = sf::seconds(1.6);
	data[Obstacle::Type::Oto1_1].maxTime = sf::seconds(2.8);
	data[Obstacle::Type::Oto1_1].flipHorizontal = true;
	data[Obstacle::Type::Oto1_1].groupDelayTime = sf::seconds(5);
	data[Obstacle::Type::Oto1_1].groupSpawnAmount = 3;
	data[Obstacle::Type::Oto1_1].passTime = sf::seconds(Constants::WindowWidth/Constants::trainSpeed);

	data[Obstacle::Type::Oto2].speed = sf::Vector2f(Constants::carSpeed, 0.f);
	data[Obstacle::Type::Oto2].scaleX = false;
	data[Obstacle::Type::Oto2].scaleY = true;
	data[Obstacle::Type::Oto2].texture = Textures::ID::Oto2;
	data[Obstacle::Type::Oto2].minTime = sf::seconds(1.5);
	data[Obstacle::Type::Oto2].maxTime = sf::seconds(2);
	data[Obstacle::Type::Oto2].groupDelayTime = sf::seconds(5);
	data[Obstacle::Type::Oto2].groupSpawnAmount = 2;
	data[Obstacle::Type::Oto2].spawnOffset = 700.f;
	data[Obstacle::Type::Oto2].passTime = sf::seconds(Constants::WindowWidth/Constants::trainSpeed);

	data[Obstacle::Type::Oto2_1].speed = sf::Vector2f(-Constants::carSpeed, 0.f);
	data[Obstacle::Type::Oto2_1].scaleX = false;

	data[Obstacle::Type::Oto2_1].scaleY = true;
	data[Obstacle::Type::Oto2_1].texture = Textures::ID::Oto2;
	data[Obstacle::Type::Oto2_1].minTime = sf::seconds(1.6);
	data[Obstacle::Type::Oto2_1].maxTime = sf::seconds(2.8);
	data[Obstacle::Type::Oto2_1].flipHorizontal = true;
	data[Obstacle::Type::Oto2_1].groupDelayTime = sf::seconds(5);
	data[Obstacle::Type::Oto2_1].groupSpawnAmount = 3;
	data[Obstacle::Type::Oto2_1].passTime = sf::seconds(Constants::WindowWidth/Constants::trainSpeed);

	data[Obstacle::Type::Stone].scaleX = false;
	data[Obstacle::Type::Stone].scaleY = true;
	data[Obstacle::Type::Stone].texture = Textures::ID::Stone;
	data[Obstacle::Type::Stone].minDistance = 6;
	data[Obstacle::Type::Stone].maxDistance = 10;

	//Tree
	data[Obstacle::Type::Tree].scaleX = true;
	data[Obstacle::Type::Tree].scaleY = true;
	data[Obstacle::Type::Tree].texture = Textures::ID::Tree;
	data[Obstacle::Type::Tree].minDistance = 6;
	data[Obstacle::Type::Tree].maxDistance = 10;

	data[Obstacle::Type::Tree1].scaleX = true;
	data[Obstacle::Type::Tree1].scaleY = true;
	data[Obstacle::Type::Tree1].texture = Textures::ID::Tree1;
	data[Obstacle::Type::Tree1].minDistance = 4;
	data[Obstacle::Type::Tree1].maxDistance = 10;

	data[Obstacle::Type::Tree2].scaleX = true;
	data[Obstacle::Type::Tree2].scaleY = true;
	data[Obstacle::Type::Tree2].texture = Textures::ID::Tree2;
	data[Obstacle::Type::Tree2].minDistance = 4;
	data[Obstacle::Type::Tree2].maxDistance = 10;


	data[Obstacle::Type::Tree3].scaleX = true;
	data[Obstacle::Type::Tree3].scaleY = true;
	data[Obstacle::Type::Tree3].texture = Textures::ID::Tree3;
	data[Obstacle::Type::Tree3].minDistance = 4;
	data[Obstacle::Type::Tree3].maxDistance = 10;

	data[Obstacle::Type::Tree4].scaleX = true;
	data[Obstacle::Type::Tree4].scaleY = true;
	data[Obstacle::Type::Tree4].texture = Textures::ID::Tree4;
	data[Obstacle::Type::Tree4].minDistance = 4;
	data[Obstacle::Type::Tree4].maxDistance = 10;

	data[Obstacle::Type::Tree5].scaleX = true;
	data[Obstacle::Type::Tree5].scaleY = true;
	data[Obstacle::Type::Tree5].texture = Textures::ID::Tree5;
	data[Obstacle::Type::Tree5].minDistance = 4;
	data[Obstacle::Type::Tree5].maxDistance = 10;

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

	data[Obstacle::Type::SpeedUp].scaleX = true;
	data[Obstacle::Type::SpeedUp].scaleY = true;
	data[Obstacle::Type::SpeedUp].texture = Textures::ID::SpeedUp;
	data[Obstacle::Type::SpeedUp].minDistance = 10;
	data[Obstacle::Type::SpeedUp].maxDistance = 40;

	data[Obstacle::Type::SlowDown].scaleX = true;
	data[Obstacle::Type::SlowDown].scaleY = true;
	data[Obstacle::Type::SlowDown].texture = Textures::ID::SlowDown;
	data[Obstacle::Type::SlowDown].minDistance = 10;
	data[Obstacle::Type::SlowDown].maxDistance = 40;
	
	data[Obstacle::Type::IceCream].scaleX = true;
	data[Obstacle::Type::IceCream].scaleY = true;
	data[Obstacle::Type::IceCream].texture = Textures::ID::IceCream;
	data[Obstacle::Type::IceCream].minDistance = 10;
	data[Obstacle::Type::IceCream].maxDistance = 40;

	data[Obstacle::Type::Animal1].speed = sf::Vector2f(-Constants::carSpeed, 0.f);
	data[Obstacle::Type::Animal1].scaleX = false;

	data[Obstacle::Type::Animal1].scaleY = false;
	data[Obstacle::Type::Animal1].hasAnimation = true;
	data[Obstacle::Type::Animal1].animation = Animations::ID::Animal1;
	data[Obstacle::Type::Animal1].texture = Textures::ID::Oto2;
	data[Obstacle::Type::Animal1].minTime = sf::seconds(1.6);
	data[Obstacle::Type::Animal1].maxTime = sf::seconds(2.8);
	data[Obstacle::Type::Animal1].flipHorizontal = true;
	data[Obstacle::Type::Animal1].groupDelayTime = sf::seconds(5);
	data[Obstacle::Type::Animal1].groupSpawnAmount = 1;
	data[Obstacle::Type::Animal1].passTime = sf::seconds(Constants::WindowWidth/Constants::trainSpeed);
	data[Obstacle::Type::Animal1].noTrafficLight = true;

	data[Obstacle::Type::Animal2].speed = sf::Vector2f(-Constants::carSpeed, 0.f);
	data[Obstacle::Type::Animal2].scaleX = false;

	data[Obstacle::Type::Animal2].scaleY = false;
	data[Obstacle::Type::Animal2].hasAnimation = true;
	data[Obstacle::Type::Animal2].animation = Animations::ID::Animal2;
	data[Obstacle::Type::Animal2].texture = Textures::ID::Oto2;
	data[Obstacle::Type::Animal2].minTime = sf::seconds(1.6);
	data[Obstacle::Type::Animal2].maxTime = sf::seconds(2.8);
	data[Obstacle::Type::Animal2].flipHorizontal = true;
	data[Obstacle::Type::Animal2].groupDelayTime = sf::seconds(5);
	data[Obstacle::Type::Animal2].groupSpawnAmount = 1;
	data[Obstacle::Type::Animal2].passTime = sf::seconds(Constants::WindowWidth/Constants::trainSpeed);
	data[Obstacle::Type::Animal2].noTrafficLight = true;

	data[Obstacle::Type::Animal4].speed = sf::Vector2f(-Constants::carSpeed, 0.f);
	data[Obstacle::Type::Animal4].scaleX = false;

	data[Obstacle::Type::Animal4].scaleY = false;
	data[Obstacle::Type::Animal4].hasAnimation = true;
	data[Obstacle::Type::Animal4].animation = Animations::ID::Animal4;
	data[Obstacle::Type::Animal4].texture = Textures::ID::Oto2;
	data[Obstacle::Type::Animal4].minTime = sf::seconds(1.6);
	data[Obstacle::Type::Animal4].maxTime = sf::seconds(2.8);
	data[Obstacle::Type::Animal4].flipHorizontal = true;
	data[Obstacle::Type::Animal4].groupDelayTime = sf::seconds(5);
	data[Obstacle::Type::Animal4].groupSpawnAmount = 1;
	data[Obstacle::Type::Animal4].passTime = sf::seconds(Constants::WindowWidth/Constants::trainSpeed);
	data[Obstacle::Type::Animal4].noTrafficLight = true;

	data[Obstacle::Type::Animal3].speed = sf::Vector2f(-Constants::carSpeed, 0.f);
	data[Obstacle::Type::Animal3].scaleX = false;

	data[Obstacle::Type::Animal3].scaleY = false;
	data[Obstacle::Type::Animal3].hasAnimation = true;
	data[Obstacle::Type::Animal3].animation = Animations::ID::Animal3;
	data[Obstacle::Type::Animal3].texture = Textures::ID::Oto2;
	data[Obstacle::Type::Animal3].minTime = sf::seconds(1.6);
	data[Obstacle::Type::Animal3].maxTime = sf::seconds(2.8);
	data[Obstacle::Type::Animal3].flipHorizontal = true;
	data[Obstacle::Type::Animal3].groupDelayTime = sf::seconds(5);
	data[Obstacle::Type::Animal3].groupSpawnAmount = 1;
	data[Obstacle::Type::Animal3].passTime = sf::seconds(Constants::WindowWidth/Constants::trainSpeed);
	data[Obstacle::Type::Animal3].noTrafficLight = true;

	return data;

}