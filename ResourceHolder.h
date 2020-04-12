//
// Created by dimedrol on 12.04.2020.
//

#ifndef CHESS_SFML_RESOURCEHOLDER_H
#define CHESS_SFML_RESOURCEHOLDER_H


#include <SFML/Graphics/Texture.hpp>
#include <map>

class ResourceHolder {
private:
    ResourceHolder() = default;
    ResourceHolder& operator=(const ResourceHolder) = delete;

    std::map<std::string, sf::Texture> textures; //TODO: заменить sf::Texture умным указателем на sf::Texture

public:
    ResourceHolder(const ResourceHolder&) = delete;

    static ResourceHolder& Instance();

    void loadTexture(std::string path, std::string name, sf::IntRect crop = sf::IntRect());

    sf::Texture getTexture(std::string name); //TODO: return sf::Texture&
};

#endif //CHESS_SFML_RESOURCEHOLDER_H
