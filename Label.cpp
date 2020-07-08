//
// Created by dimedrol on 05.04.2020.
//

#include "Label.h"

Label::Label(const sf::Vector2f position, const std::wstring &text, sf::Vector2f size) {
    this->text.setString(sf::String(text));
    this->text.setFont(ResourceHolder::Instance().getFont("PT Sans"));
    this->text.setCharacterSize(22);
    this->text.setStyle(sf::Text::Bold);
    this->text.setFillColor(sf::Color(0, 0, 0));
    this->text.setPosition(position);
}

void Label::setFont(sf::Font &font) {
    text.setFont(font);
}

