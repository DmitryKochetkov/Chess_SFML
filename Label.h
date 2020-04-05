//
// Created by dimedrol on 05.04.2020.
//

#ifndef CHESS_SFML_LABEL_H
#define CHESS_SFML_LABEL_H

#include <SFML/Graphics.hpp>


class Label : public sf::Drawable {
    sf::RectangleShape body;
    sf::Text text;

public:
    Label(const sf::Vector2f position, const std::string& text, const sf::Vector2f size = sf::Vector2f(150, 50)) {
        body = sf::RectangleShape(size);
        body.setPosition(position);
        body.setFillColor(sf::Color(255, 255, 255, 0));
        body.setOutlineColor(sf::Color(255, 255, 255));
        body.setOutlineThickness(3.0f);

        sf::Font font;
        font.loadFromFile("../resources/fonts/PT Sans.ttf");

        this->text.setString("text");
        this->text.setFont(font);
        this->text.setPosition(position);
    }

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        target.draw(body);
        target.draw(text);
    }
};


#endif //CHESS_SFML_LABEL_H
