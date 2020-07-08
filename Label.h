//
// Created by dimedrol on 05.04.2020.
//

#ifndef CHESS_SFML_LABEL_H
#define CHESS_SFML_LABEL_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "ResourceHolder.h"


class Label : public sf::Drawable {
    sf::Text text;

public:
    //TODO: Vector2f -> Vector2i
    Label(const sf::Vector2f position, const std::wstring& text, const sf::Vector2f size = sf::Vector2f(200, 50)) {
        this->text.setString(sf::String(text));
        this->text.setFont(ResourceHolder::Instance().getFont("PT Sans"));
        this->text.setCharacterSize(22);
        this->text.setStyle(sf::Text::Bold);
        this->text.setFillColor(sf::Color(0, 0, 0));
        this->text.setPosition(position);
    }

    //temporary methods
    void setFont(sf::Font& font) {
        text.setFont(font);
    }

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        target.draw(text);
    }
};


#endif //CHESS_SFML_LABEL_H
