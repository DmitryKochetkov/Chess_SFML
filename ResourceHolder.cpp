//
// Created by dimedrol on 12.04.2020.
//

#include "ResourceHolder.h"

ResourceHolder &ResourceHolder::Instance() {
    static ResourceHolder _instance;
    return _instance;
}

void ResourceHolder::loadTexture(std::string path, std::string name, sf::IntRect crop) {
    std::unique_ptr<sf::Texture> texture(new sf::Texture());
    if (!texture->loadFromFile(path))
        throw std::runtime_error("ResourceHolder failed to load texture " + path);

    if (crop.width != 0 && crop.height != 0)
        texture->loadFromFile(path, crop);

    textures.insert(std::make_pair(name, std::move(texture)));
}

sf::Texture& ResourceHolder::getTexture(std::string name) {
    return *textures[name];
}

void ResourceHolder::loadFont(std::string path, std::string name) {
    std::unique_ptr<sf::Font> font(new sf::Font());
    if (!font->loadFromFile(path))
        throw std::runtime_error("ResourceHolder failed to load font " + path);

    fonts.insert(std::make_pair(name, std::move(font)));
}

sf::Font &ResourceHolder::getFont(std::string name) {
    return *fonts[name];
}
