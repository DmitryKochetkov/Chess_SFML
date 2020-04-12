//
// Created by dimedrol on 05.04.2020.
//

#ifndef CHESS_SFML_LABEL_H
#define CHESS_SFML_LABEL_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "ResourceHolder.h"


class Label : public sf::Drawable {
    sf::RectangleShape body;
    sf::Text text;
    std::unique_ptr<sf::Font> font; //TODO: убрать этот ужас

public:
    Label(const sf::Vector2f position, const std::string& text, const sf::Vector2f size = sf::Vector2f(200, 100)) {
        body = sf::RectangleShape(size);
        body.setPosition(position);
        body.setFillColor(sf::Color(255, 255, 255, 0));
        body.setOutlineColor(sf::Color(255, 255, 255));
        body.setOutlineThickness(3.0f);

        //TODO: переделать с использованием ResourcesHolder

        font = std::make_unique<sf::Font>();
        font->loadFromFile("../resources/fonts/PT Sans.ttf");

        this->text.setString("text");
        this->text.setFont(*font);
        int x;
        sf::Vector2f offset; 
        offset.x = (float)this->text.getGlobalBounds().width;
        offset.y = (float)this->text.getGlobalBounds().height/0.5f;
        this->text.setPosition(position+size*0.5f - offset*0.5f);
        std::cout << this->text.getGlobalBounds().width << std::endl;
    }

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        target.draw(body);
        target.draw(text);
    }
};


#endif //CHESS_SFML_LABEL_H
