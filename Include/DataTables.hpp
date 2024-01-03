#ifndef DATATABLE_HPP
#define DATATABLE_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>

#include <ResourceIdentifiers.hpp>

#include <ObstacleManagement.hpp>
#include <TileManagement.hpp>

#include <vector>
#include <functional>

struct ObstacleData {
    sf::Vector2f speed;
    Textures::ID texture;
    sf::Time minTime, maxTime, killTime, groupDelayTime,passTime;
    int minDistance, maxDistance;
    bool scaleX,scaleY;
    bool killByTime = false;
    float rotateAngle = 0;
    bool flipVertical,flipHorizontal = 0;
    int groupSpawnAmount;
    float spawnOffset = 0;
};

std::vector<ObstacleData> initializeObstacleData();

#endif //DATATABLE_HPP