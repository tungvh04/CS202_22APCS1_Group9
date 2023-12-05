#include <TileSystem.hpp>

Tile::Tile() {

}

Tile::~Tile() {

}

void Tile::draw(sf::RenderWindow& window) {
    tObj.setPosition(pos);
    
    window.draw(tObj);

    //std::cout<<"Huh? "<<pos.x<<' '<<pos.y<<'\n';
}

void Tile::setPos(sf::Vector2f _pos) {
    pos=_pos;

    //std::cout<<"What? "<<_pos.x<<' '<<_pos.y<<'\n';
}

void Tile::setTexture(sf::Texture* _texture) {
    tTexture=_texture;

    tObj.setTexture(*_texture);
    tObj.setTextureRect(sf::IntRect(pos.x,pos.y,Constants::GridSize,Constants::GridSize));
}

void TileSystem::load() {
    std::ifstream inpSize;
    inpSize.open("Media/Textures/Tile/Tile.txt");
    int tileCnt;
    inpSize>>tileCnt;
    inpSize.close();
    //std::cout<<tileCnt<<"i\n";
    //std::cerr<<"i\n";
    //std::fstream checkerValid;

    tTexture.clear();
    
    for (int i=0;i<tileCnt;i++) {
        sf::Texture tmp;
        tmp.loadFromFile("Media/Textures/Tile/Tile"+toString(i)+".png");
        sf::Texture tmp2;
        tTexture.push_back(tmp2);
        tTexture.back()=tmp;
        std::cout<<"Media/Textures/Tile/Tile"+toString(i)+".png"<<"\n";
    }
}

TileSystem::TileSystem() {

}

TileSystem::~TileSystem() {

}

void TileSystem::init() {
    tileContainer.clear();
}

void TileSystem::addTile(Tile* _tile) {
    Tile* tmp=new Tile();
    tileContainer.push_back(tmp);
    tileContainer.back()=_tile;
    delete tmp;
}

void TileSystem::push_back(Tile* _tile) {
    Tile* tmp=new Tile();
    tileContainer.push_back(tmp);
    tileContainer.back()=_tile;
    delete tmp;
}

void TileSystem::pop_front() {
    delete tileContainer.front();
    tileContainer.pop_front();
}

void TileSystem::addTile(sf::Vector2f _pos,int textureID) {
    Tile* tmp=new Tile();
    tileContainer.push_back(tmp);
    tileContainer.back()->setTexture(&tTexture[textureID]);
    tileContainer.back()->setPos(_pos);
}

void TileSystem::draw(sf::RenderWindow& window) {
    //std::cout<<tileContainer.size()<<'\n';
    for (int i=0;i<tileContainer.size();i++) {
        //tileContainer[i]->setTexture(&tTexture[tileContainer[i].getID()]);
        tileContainer[i]->draw(window);
        //std::cout<<i<<": "<<tileContainer[i]->getPos().x<<' '<<tileContainer[i]->getPos().y<<'\n';
    }
}

sf::Vector2f Tile::getPos() {
    return pos;
}

TileBuilderRow::TileBuilderRow() {
    TileSystem::init();
    widthRadius=Constants::TilesRenderedHeight;
    heightRadius=Constants::TilesRenderedWide;
    replaceAmount=Constants::SwapRowWhenLower;
    shiftAmount=Constants::GridSize;
    rowCnt=0;
}

void TileBuilderRow::init() {
    TileSystem::init();
    widthRadius=Constants::TilesRenderedHeight;
    heightRadius=Constants::TilesRenderedWide;
    replaceAmount=Constants::SwapRowWhenLower;
    shiftAmount=Constants::GridSize;
    rowCnt=0;
}

void TileBuilderRow::buildFrontRow(int ID) {
    rowCnt++;
    spawnOrigin.y-=shiftAmount;
    sf::Vector2f tmp=spawnOrigin;
    addTile(tmp,ID);
    for (int i=0;i<widthRadius;i++) {
        tmp.x+=shiftAmount;
        addTile(tmp,ID);
    }
    tmp=spawnOrigin;
    for (int i=0;i<widthRadius;i++) {
        tmp.x-=shiftAmount;
        addTile(tmp,ID);
    }
}

void TileBuilderRow::buildFrontRow() {
    rowCnt++;
    spawnOrigin.y-=shiftAmount;
    sf::Vector2f tmp=spawnOrigin;
    int ID=rand()%getIDSize();
    addTile(tmp,ID);
    for (int i=0;i<widthRadius;i++) {
        tmp.x+=shiftAmount;
        addTile(tmp,ID);
    }
    tmp=spawnOrigin;
    for (int i=0;i<widthRadius;i++) {
        tmp.x-=shiftAmount;
        addTile(tmp,ID);
    }
}

void TileBuilderRow::deleteBackRow() {
    rowCnt--;
    for (int i=0;i<=2*widthRadius;i++) {
        pop_front();
    }
}

void TileBuilderRow::shiftX(int step) {
    spawnOrigin.x+=float(step)*shiftAmount;
}

void TileBuilderRow::shiftY(int step) {
    spawnOrigin.y+=float(step)*shiftAmount;
}

void TileBuilderRow::setOrigin(sf::Vector2f _pos) {
    spawnOrigin=_pos;
}

void TileBuilderRow::setCentre(sf::Vector2f _pos) {
    spawnOrigin=_pos;
    spawnOrigin.x-=Constants::GridSize/float(2);
    spawnOrigin.y-=Constants::GridSize/float(2);
}

int TileSystem::getSize() {
    return tileContainer.size();
}

int TileSystem::getIDSize() {
    return tTexture.size();
}

void TileBuilderRow::buildTillFull() {
    while (rowCnt<heightRadius*2+1) {
        buildFrontRow();
    }
}

void TileBuilderRow::update(sf::Vector2f playerPos) {
    while (playerPos.y-spawnOrigin.y<shiftAmount*replaceAmount) {
        deleteBackRow();
        buildFrontRow();
    }
}