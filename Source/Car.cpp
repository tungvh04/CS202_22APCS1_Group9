#include <Car.hpp>

Car::Car() {

}

Car::~Car() {

}

CarFactory::CarFactory(sf::Vector2f _speedRange,sf::Vector2f _delayRange,sf::Vector2f _spawnPoint) {
    //std::cout<<"Factory created with infomation!!!!\n";
    speedRange=_speedRange;
    //if (speedRange.x>speedRange.y) std::swap(speedRange.x,speedRange.y);
    delayRange=_delayRange;
    if (delayRange.x>delayRange.y) std::swap(delayRange.x,delayRange.y);
    spawnPoint=_spawnPoint;
    isPlaceHolder=false;
    delayCounter=Rand(delayRange.x,delayRange.y);
    //std::cout<<"Spawn Position: "<<spawnPoint.x<<' '<<spawnPoint.y<<'\n';
    //defaultPath="";
    //targetHolder=nullptr;
}

void CarFactory::init(sf::Vector2f _speedRange,sf::Vector2f _delayRange,sf::Vector2f _spawnPoint) {
    //carList.resize(Constants::entityRowLimit)
    //std::cout<<"Factory created with infomation!!!!\n";
    speedRange=_speedRange;
    //if (speedRange.x>speedRange.y) std::swap(speedRange.x,speedRange.y);
    delayRange=_delayRange;
    if (delayRange.x>delayRange.y) std::swap(delayRange.x,delayRange.y);
    spawnPoint=_spawnPoint;
    isPlaceHolder=false;
    delayCounter=Rand(delayRange.x,delayRange.y);
    //std::cout<<"Spawn Position: "<<spawnPoint.x<<' '<<spawnPoint.y<<'\n';
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
    //return;
    if (delayCounter>0.0f) return;
    //std::cout<<"Car created at: "<<spawnPoint.x<<' '<<spawnPoint.y<<'\n';
    carList.resize(carList.size()+1);
    carList.back().setPos(spawnPoint);
    //carList.back().setBoundingBox(boundBox);
    carList.back().setTexture(tTexture);
    carList.back().setSpeed(speedRange);
    delayCounter=Rand(delayRange.x,delayRange.y);
}

void CarFactory::update(sf::Time dt) {
    if (isPlaceHolder) return;
    delayCounter-=dt.asSeconds();
    //std::cout<<delayCounter<<'\n';
    for (int i=0;i<carList.size();i++) {
        carList[i].update(dt);
    }
    spawn();
}

void CarFactory::draw(sf::RenderWindow& window) {
    if (isPlaceHolder) return;
    /*
    Object debugObj;
    debugObj.setTexture(tTexture);
    debugObj.setPos(spawnPoint);
    debugObj.draw(window);
    */
    //std::cout<<"Draw command to second layer\n";
    //std::cout<<carList.size()<<'\n';
    for (int i=0;i<carList.size();i++) {
        carList[i].draw(window);
    }
}

void CarFactoryManager::draw(sf::RenderWindow& window) {
    for (int i=0;i<carTrackList.size();i++) {
        carTrackList[i].draw(window);
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
    shiftAmount=Constants::GridSize;
    replaceAmount=Constants::SwapRowWhenLower;
    heightRadius=Constants::TilesRenderedHeight;
    rowCnt=0;
}

CarFactoryManager::CarFactoryManager() {
    rowCnt=0;
    targetHolder=nullptr;
    isTracked=false;
    shiftAmount=Constants::GridSize;
    replaceAmount=Constants::SwapRowWhenLower;
    heightRadius=Constants::TilesRenderedHeight;
}

void CarFactoryManager::init(sf::Vector2f _speedRange,sf::Vector2f _delayRange,sf::Vector2f _spawnPoint) {
    speedRange.x=Rand(_speedRange.x,_speedRange.y);
    speedRange.y=0;
    //if (speedRange.x>speedRange.y) std::swap(speedRange.x,speedRange.y);
    delayRange=_delayRange;
    if (delayRange.x>delayRange.y) std::swap(delayRange.x,delayRange.y);
    spawnPoint=_spawnPoint;
    defaultPath="";
}

CarFactory::CarFactory() {
    isPlaceHolder=true;
}

void CarFactory::setEmpty() {
    isPlaceHolder=true;
}


void CarFactory::setNotEmpty() {
    isPlaceHolder=false;
}

void CarFactoryManager::setPath(std::string path) {
    defaultPath=path;
}

void CarFactoryManager::setHolder(WorldTextureHolder* holder) {
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

void CarFactoryManager::buildFrontRow() {
    //std::cout<<"!Builded Track "<<rowCnt<<" \n";
    rowCnt++;
    spawnPoint.y-=shiftAmount;
    sf::Vector2f tmp=spawnPoint;
    tmp.x-=Constants::TilesRenderedWide*Constants::GridSize;
    tmp.y-=Constants::GridSize/2.0;
    CarFactory newCarFactory;
    carTrackList.push_back(newCarFactory);
    carTrackList.back().init(speedRange,delayRange,tmp);
    carTrackList.back().setTexture(targetHolder->get());
    
}

void CarFactoryManager::buildEmpty() {
    rowCnt++;
    spawnPoint.y-=shiftAmount;
    CarFactory newCarFactory;
    carTrackList.push_back(newCarFactory);
}

void CarFactoryManager::update(sf::Vector2f playerPos) {
    //std::cout<<rowCnt<<'\n';
    while (playerPos.y-spawnPoint.y<shiftAmount*replaceAmount) {
        deleteBackRow();
        buildFrontRow();
    }
}

void CarFactoryManager::update(sf::Time dt) {
    for (int i=0;i<carTrackList.size();i++) {
        carTrackList[i].update(dt);
    }
    //debug();
}

void CarFactoryManager::deleteBackRow() {
    rowCnt--;
    carTrackList.pop_front();
}

void CarFactoryManager::buildTillFull() {
    while (rowCnt<heightRadius*2+1) {
        buildFrontRow();
    }
}
/*
void Car::draw(sf::RenderWindow& window) {
    Object::draw(window);
    std::cout<<"Car drawed!!!\n";
}
*/