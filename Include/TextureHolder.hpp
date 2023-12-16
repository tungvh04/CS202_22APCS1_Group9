#ifndef TEXTURE_HOLDER_HPP
#define TEXTURE_HOLDER_HPP

#include <vector>
#include <iostream>
#include <fstream>

#include <Const.hpp>
#include <Utility.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class WorldTextureHolder{
private:
    std::vector<sf::Texture> container;

    std::string path;
    int carCnt;
public:
    WorldTextureHolder();
    WorldTextureHolder(std::string _path);

    void load();
    void load(int id);
    void load(int l,int r); 

    void setSize(int x);
    void setPath(std::string path);

    sf::Texture* get();
    sf::Texture* get(int id);
    sf::Texture* get(int l,int r);
};

#endif //TEXTURE_HOLDER_HPP