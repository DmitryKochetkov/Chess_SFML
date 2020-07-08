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
    std::cout << this->text.getGlobalBounds().width << std::endl; //TODO: зачем это вообще здесь?
}

void Button::setFont(sf::Font &font) {
    text.setFont(font);
}




