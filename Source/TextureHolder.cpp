#include <TextureHolder.hpp>

TextureHolder::TextureHolder(std::string _path): path(_path) {
    
}

void TextureHolder::load(int id) {
    container[id].loadFromFile(path+toString(id)+".png");
}

void TextureHolder::load(int l,int r) {
    for (int i=l;i<=r;i++) {
        load(i);
    }
}

void TextureHolder::setPath(std::string _path) {
    path=_path;
}

sf::Texture* TextureHolder::get(int id) {
    return &container[id];
}