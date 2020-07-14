//
// Created by dimedrol on 7/8/20.
//

#include "Button.h"

Button::Button(const sf::Vector2f position, const std::wstring &text, sf::Vector2f size) {
    body = sf::RectangleShape(size);
    body.setPosition(position);
    body.setFillColor(sf::Color(255, 255, 255, 255));
    body.setOutlineColor(sf::Color(0, 0, 0));
    body.setOutlineThickness(1.5f);

    this->text.setString(sf::String(text));
    this->text.setFont(ResourceHolder::Instance().getFont("PT Sans"));
    this->text.setCharacterSize(22);
    this->text.setStyle(sf::Text::Bold);
    this->text.setFillColor(sf::Color(0, 0, 0));

    sf::Vector2f offset;
    offset.x = (float)this->text.getGlobalBounds().width;
    offset.y = (float)this->text.getGlobalBounds().height/0.5f;
    this->text.setPosition(position+size*0.5f - offset*0.5f);
}

void Button::setFont(sf::Font &font) {
    text.setFont(font);
}

Button::~Button() {

}

void Button::handleEvent(sf::Event event) {
    if (event.type == sf::Event::MouseMoved) {
        if (this->contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
            body.setOutlineColor(sf::Color::Blue);
        }
        else {
            body.setOutlineColor(sf::Color::Black);
        }
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (this->contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
            body.setFillColor(sf::Color::Blue);
        }
    }
    else body.setFillColor(sf::Color::White);
}




