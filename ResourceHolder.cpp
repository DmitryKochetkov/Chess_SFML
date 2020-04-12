//
// Created by dimedrol on 12.04.2020.
//

#include "ResourceHolder.h"

ResourceHolder &ResourceHolder::Instance() {
    static ResourceHolder _instance;
    return _instance;
}

void ResourceHolder::loadTexture(std::string path, std::string name, sf::IntRect crop) {
    sf::Texture texture;
    if (!texture.loadFromFile(path))
        throw std::runtime_error("ResourceHolder failed to load texture " + path);

    if (crop.width != 0 && crop.height != 0)
        texture.loadFromFile(path, crop);

    textures.insert(std::make_pair(name, texture));
}

sf::Texture ResourceHolder::getTexture(std::string name) {
    return textures[name];
}


