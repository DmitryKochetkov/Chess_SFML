//
// Created by dimedrol on 05.04.2020.
//

#ifndef CHESS_SFML_BUTTON_H
#define CHESS_SFML_BUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "ResourceHolder.h"
#include "IListener.h"


class Button : public sf::Drawable, public IListener {
    sf::RectangleShape body;
    sf::Text text;

public:
    //TODO: Vector2f -> Vector2i
    Button(const sf::Vector2f position, const std::wstring& text, const sf::Vector2f size = sf::Vector2f(200, 50));

    //TODO: исправить ошибки компоновки при выносе в cpp
    template <class T>
    bool contains(sf::Vector2<T> point) {
        return body.getGlobalBounds().contains(point.x, point.y);
    }

    //temporary methods
    void setFont(sf::Font& font);

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        target.draw(body);
        target.draw(text);
    }

public:
    ~Button() override;

    void handleEvent(sf::Event event) override;
};


#endif //CHESS_SFML_BUTTON_H
