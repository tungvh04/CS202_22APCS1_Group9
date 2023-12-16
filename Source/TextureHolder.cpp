#include <TextureHolder.hpp>

WorldTextureHolder::WorldTextureHolder(std::string _path): path(_path) {
    
}

WorldTextureHolder::WorldTextureHolder() {
    
}

void WorldTextureHolder::load(int id) {
    container[id].loadFromFile(path+toString(id)+".png");
}

void WorldTextureHolder::load(int l,int r) {
    for (int i=l;i<=r;i++) {
        load(i);
    }
}

void WorldTextureHolder::load() {
    std::ifstream inpSize;
    inpSize.open(path+"Info.txt");
    std::cout<<path+"Info.txt"<<'\n';
    int tileCnt;
    inpSize>>tileCnt;
    inpSize.close();
    carCnt=tileCnt;
    container.resize(tileCnt);
    load(0,tileCnt-1);
    //std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<tileCnt<<'\n';
}

void WorldTextureHolder::setSize(int x) {
    carCnt=x;
}

sf::Texture* WorldTextureHolder::get() {
    return get(0,carCnt-1);
}

void WorldTextureHolder::setPath(std::string _path) {
    path=_path;
}

sf::Texture* WorldTextureHolder::get(int id) {
    return &container[id];
}

sf::Texture* WorldTextureHolder::get(int l,int r) {
    return &container[Rand(l,r)];
}