#ifndef DATATABLE_HPP
#define DATATABLE_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>

#include <ResourceIdentifiers.hpp>

#include <vector>
#include <functional>

struct Direction
{
	Direction(float angle, float distance): angle(angle), distance(distance) {
	
    }

	float angle;
	float distance;
};

struct CarData{
    float speed;
    Textures::ID texture;

    std::vector<Direction> directions;
};

std::vector<CarData> initializeCarData();

#endif //DATATABLE_HPP