#ifndef CAR_HPP
#define CAR_HPP

#include <Object.hpp>
#include <TextureHolder.hpp>
#include <deque>

class Car : public Object,BoundingBox {
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

    std::vector<Car> carList;
public:
    CarFactory(sf::Vector2f _speedRange,sf::Vector2f _delayRange,sf::Vector2f _spawnPoint);
    /*
    CarFactory(sf::Vector2f _speedRange,sf::Vector2f _delayRange,sf::Vector2f _spawnPoint,int id);
    CarFactory(sf::Vector2f _speedRange,sf::Vector2f _delayRange,sf::Vector2f _spawnPoint,std::string _path);
    CarFactory(sf::Vector2f _speedRange,sf::Vector2f _delayRange,sf::Vector2f _spawnPoint,std::string _path,int id);
    CarFactory(sf::Vector2f _speedRange,sf::Vector2f _delayRange,sf::Vector2f _spawnPoint,TextureHolder* _targetHolder);
    CarFactory(sf::Vector2f _speedRange,sf::Vector2f _delayRange,sf::Vector2f _spawnPoint,TextureHolder* _targetHolder,int id); 
    */
    //void setTexture(int id);
    void setTexture(sf::Texture* _texture);
    void spawn();
    void update(sf::Time dt);
    void draw(sf::RenderWindow& window);
};

class CarFactoryManager {
private:
    sf::Vector2f speedRange,delayRange,spawnPoint,trackingPoint;

    std::string defaultPath;

    WorldTextureHolder* targetHolder=nullptr;

    std::deque<CarFactory> carTrackList;

    bool isTracked;
public:
    CarFactoryManager(sf::Vector2f _speedRange,sf::Vector2f _delayRange,sf::Vector2f _spawnPoint);

    void setPath(std::string path);
    void setHolder(WorldTextureHolder* target);
    void setTrackingPoint(sf::Vector2f point);
    void push_back();
    void pop_front();
    void shiftSpawn(sf::Vector2f dv);
    void shiftTrack(sf::Vector2f dv);
    void update(sf::Time dt);
};

#endif //CAR_HPP