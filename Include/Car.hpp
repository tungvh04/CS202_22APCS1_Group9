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

    void debug() {
        sf::Vector2f pos=Object::getPos();
        std::cout<<pos.x<<' '<<pos.y<<'\n';
    }
    //void draw(sf::RenderWindow& window);
};

class CarFactory {
private:
    sf::Vector2f speedRange,delayRange,spawnPoint;

    float delayCounter;

    sf::Texture* tTexture;

    std::vector<Car> carList;

    bool isPlaceHolder;
public:
    CarFactory();
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
    void setEmpty();
    void setNotEmpty();
    void init(sf::Vector2f _speedRange,sf::Vector2f _delayRange,sf::Vector2f _spawnPoint);

    void debug() {
        for (int i=0;i<carList.size();i++) {
            carList[i].debug();
        }
    }
};

class CarFactoryManager {
private:    
    int rowCnt,replaceAmount,heightRadius;

    float shiftAmount;

    sf::Vector2f speedRange,delayRange,spawnPoint,trackingPoint;

    std::string defaultPath;

    WorldTextureHolder* targetHolder=nullptr;

    std::deque<CarFactory> carTrackList;

    bool isTracked;
public:
    CarFactoryManager();
    CarFactoryManager(sf::Vector2f _speedRange,sf::Vector2f _delayRange,sf::Vector2f _spawnPoint);

    void init(sf::Vector2f _speedRange,sf::Vector2f _delayRange,sf::Vector2f _spawnPoint);
    void setPath(std::string path);
    void setHolder(WorldTextureHolder* target);
    void setTrackingPoint(sf::Vector2f point);
    void push_back();
    void pop_front();
    void shiftSpawn(sf::Vector2f dv);
    void shiftTrack(sf::Vector2f dv);
    void update(sf::Time dt);
    void update(sf::Vector2f playerPos);
    void buildFrontRow();
    void buildEmpty();
    void deleteBackRow();
    void buildTillFull();
    void draw(sf::RenderWindow& window);

    void debug() {
        for (int i=0;i<carTrackList.size();i++) {
            carTrackList[i].debug();
        }
    }
};

#endif //CAR_HPP