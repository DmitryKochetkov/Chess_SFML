//
// Created by dimedrol on 12.04.2020.
//

#ifndef CHESS_SFML_RESOURCEHOLDER_H
#define CHESS_SFML_RESOURCEHOLDER_H


#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <memory>
#include <SFML/Graphics/Font.hpp>

class ResourceHolder {
private:
    ResourceHolder() = default;
    ResourceHolder& operator=(const ResourceHolder) = delete;

    std::map<std::string, std::unique_ptr<sf::Texture>> textures;
    std::map<std::string, std::unique_ptr<sf::Font>> fonts;

public:
    ResourceHolder(const ResourceHolder&) = delete;

    static ResourceHolder& Instance();

    void loadTexture(std::string path, std::string name, sf::IntRect crop = sf::IntRect());
    void loadFont(std::string path, std::string name);

    sf::Texture& getTexture(std::string name);
    sf::Font& getFont(std::string name);
};

#endif //CHESS_SFML_RESOURCEHOLDER_H
