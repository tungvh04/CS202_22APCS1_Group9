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
    sf::Time minTime, maxTime;
};

std::vector<ObstacleData> initializeObstacleData();

#endif //DATATABLE_HPP