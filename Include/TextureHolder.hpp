#ifndef TEXTURE_HOLDER_HPP
#define TEXTURE_HOLDER_HPP

#include <map>
#include <iostream>
#include <fstream>

#include <Const.hpp>
#include <Utility.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class TextureHolder{
private:
    std::map<int,sf::Texture> container;

    std::string path;
public:
    TextureHolder(std::string _path);

    void load(int id);
    void load(int l,int r); 

    void setPath(std::string path);

    sf::Texture* get(int id);
};

#endif //TEXTURE_HOLDER_HPP