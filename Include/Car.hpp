#ifndef CAR_HPP
#define CAR_HPP

#include <Object.hpp>
#include <TextureHolder.hpp>

class Car : public Object {
private:


public:
    Car();
    ~Car();
};

class CarFactory {
private:
    sf::Vector2f speedRange,delayRange,spawnPoint;

    float delayCounter;

    sf::Texture* tTexture;

    std::string defaultPath;

    TextureHolder* targetHolder=nullptr;

    std::vector<Car> carList;
public:
    CarFactory(sf::Vector2f _speedRange,sf::Vector2f _delayRange,sf::Vector2f _spawnPoint);
    CarFactory(sf::Vector2f _speedRange,sf::Vector2f _delayRange,sf::Vector2f _spawnPoint,int id);
    CarFactory(sf::Vector2f _speedRange,sf::Vector2f _delayRange,sf::Vector2f _spawnPoint,std::string _path);
    CarFactory(sf::Vector2f _speedRange,sf::Vector2f _delayRange,sf::Vector2f _spawnPoint,std::string _path,int id);
    CarFactory(sf::Vector2f _speedRange,sf::Vector2f _delayRange,sf::Vector2f _spawnPoint,TextureHolder* _targetHolder);
    CarFactory(sf::Vector2f _speedRange,sf::Vector2f _delayRange,sf::Vector2f _spawnPoint,TextureHolder* _targetHolder,int id); 

    void setTexture(int id);
    void spawn();
    void update();
};

#endif //CAR_HPP