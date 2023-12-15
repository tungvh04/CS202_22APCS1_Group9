#include <TextureHolder.hpp>

WorldTextureHolder::WorldTextureHolder(std::string _path): path(_path) {
    
}

void WorldTextureHolder::load(int id) {
    container[id].loadFromFile(path+toString(id)+".png");
}

void WorldTextureHolder::load(int l,int r) {
    for (int i=l;i<=r;i++) {
        load(i);
    }
}

void WorldTextureHolder::setPath(std::string _path) {
    path=_path;
}

sf::Texture* WorldTextureHolder::get(int id) {
    return &container[id];
}