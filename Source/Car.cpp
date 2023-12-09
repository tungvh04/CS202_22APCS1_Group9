#include <Car.hpp>

Car::Car() {

}

Car::~Car() {

}

CarFactory::CarFactory(sf::Vector2f _speedRange,sf::Vector2f _delayRange,sf::Vector2f _spawnPoint) {
    speedRange=_speedRange;
    //if (speedRange.x>speedRange.y) std::swap(speedRange.x,speedRange.y);
    delayRange=_delayRange;
    if (delayRange.x>delayRange.y) std::swap(delayRange.x,delayRange.y);
    spawnPoint=_spawnPoint;
    delayCounter=Rand(speedRange.x,speedRange.y);
    //defaultPath="";
    //targetHolder=nullptr;
}
/*
CarFactory::CarFactory(sf::Vector2f _speedRange,sf::Vector2f _delayRange,sf::Vector2f _spawnPoint,int id) {
    speedRange=_speedRange;
    //if (speedRange.x>speedRange.y) std::swap(speedRange.x,speedRange.y);
    delayRange=_delayRange;
    if (delayRange.x>delayRange.y) std::swap(delayRange.x,delayRange.y);
    spawnPoint=_spawnPoint;
    delayCounter=Rand(speedRange.x,speedRange.y);
    defaultPath="";
    targetHolder=nullptr;
    setTexture(id);
}

CarFactory::CarFactory(sf::Vector2f _speedRange,sf::Vector2f _delayRange,sf::Vector2f _spawnPoint,std::string _path) {
    speedRange=_speedRange;
    //if (speedRange.x>speedRange.y) std::swap(speedRange.x,speedRange.y);
    delayRange=_delayRange;
    if (delayRange.x>delayRange.y) std::swap(delayRange.x,delayRange.y);
    spawnPoint=_spawnPoint;
    delayCounter=Rand(speedRange.x,speedRange.y);
    targetHolder=nullptr;
    defaultPath=_path;
}

CarFactory::CarFactory(sf::Vector2f _speedRange,sf::Vector2f _delayRange,sf::Vector2f _spawnPoint,std::string _path,int id) {
    speedRange=_speedRange;
    //if (speedRange.x>speedRange.y) std::swap(speedRange.x,speedRange.y);
    delayRange=_delayRange;
    if (delayRange.x>delayRange.y) std::swap(delayRange.x,delayRange.y);
    spawnPoint=_spawnPoint;
    delayCounter=Rand(speedRange.x,speedRange.y);
    defaultPath=_path;
    targetHolder=nullptr;
    setTexture(id);
}

CarFactory::CarFactory(sf::Vector2f _speedRange,sf::Vector2f _delayRange,sf::Vector2f _spawnPoint,TextureHolder* _targetHolder) {
    speedRange=_speedRange;
    //if (speedRange.x>speedRange.y) std::swap(speedRange.x,speedRange.y);
    delayRange=_delayRange;
    if (delayRange.x>delayRange.y) std::swap(delayRange.x,delayRange.y);
    spawnPoint=_spawnPoint;
    delayCounter=Rand(speedRange.x,speedRange.y);
    targetHolder=_targetHolder;
    defaultPath="";
}

CarFactory::CarFactory(sf::Vector2f _speedRange,sf::Vector2f _delayRange,sf::Vector2f _spawnPoint,TextureHolder* _targetHolder,int id) {
    speedRange=_speedRange;
    //if (speedRange.x>speedRange.y) std::swap(speedRange.x,speedRange.y);
    delayRange=_delayRange;
    if (delayRange.x>delayRange.y) std::swap(delayRange.x,delayRange.y);
    spawnPoint=_spawnPoint;
    delayCounter=Rand(speedRange.x,speedRange.y);
    targetHolder=_targetHolder;
    defaultPath="";
    setTexture(id);
}
*/
/*
void CarFactory::setTexture(int id) {
    if(defaultPath=="") {
        if (targetHolder) {
            tTexture=targetHolder->get(id);
        }
    }
}
*/

void CarFactory::setTexture(sf::Texture* _texture) {
    tTexture=_texture;
}

void CarFactory::spawn() {
    if (delayCounter>0.0f) return;
    carList.resize(carList.size()+1);
    carList.back().setPos(spawnPoint);
    //carList.back().setBoundingBox(boundBox);
    carList.back().setTexture(tTexture);
    carList.back().setSpeed(speedRange);
    delayCounter=Rand(delayRange.x,delayRange.y);
}

void CarFactory::update(sf::Time dt) {
    delayCounter-=dt.asSeconds();
    for (int i=0;i<carList.size();i++) {
        carList[i].update(dt);
    }
}

void CarFactory::draw(sf::RenderWindow& window) {
    for (int i=0;i<carList.size();i++) {
        carList[i].draw(window);
    }
}

CarFactoryManager::CarFactoryManager(sf::Vector2f _speedRange,sf::Vector2f _delayRange,sf::Vector2f _spawnPoint) {
    speedRange=_speedRange;
    //if (speedRange.x>speedRange.y) std::swap(speedRange.x,speedRange.y);
    delayRange=_delayRange;
    if (delayRange.x>delayRange.y) std::swap(delayRange.x,delayRange.y);
    spawnPoint=_spawnPoint;
    defaultPath="";
    targetHolder=nullptr;
    isTracked=false;
}

void CarFactoryManager::setPath(std::string path) {
    defaultPath=path;
}

void CarFactoryManager::setHolder(TextureHolder* holder) {
    targetHolder=holder;
}

void CarFactoryManager::setTrackingPoint(sf::Vector2f _point) {
    trackingPoint=_point;
}
void CarFactoryManager::push_back() {
    carTrackList.emplace_back(speedRange,delayRange,spawnPoint);
}

void CarFactoryManager::pop_front() {
    carTrackList.pop_front();
}

void CarFactoryManager::shiftSpawn(sf::Vector2f dv) {
    spawnPoint+=dv;
}

void CarFactoryManager::shiftTrack(sf::Vector2f dv) {
    trackingPoint+=dv;
}