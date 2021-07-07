//
// Created by witcher on 8/21/20.
//

#include "CheckBox.h"
#include "ResourceHolder.h"

CheckBox::CheckBox(const sf::Vector2f position, std::string text) {
    body = sf::RectangleShape(sf::Vector2f(20, 20));
    body.setPosition(position);
    body.setOutlineColor(sf::Color(0, 0, 0, 255));
    body.setOutlineThickness(2.0f);
    tick.setCharacterSize(15);
    tick.setFont(ResourceHolder::Instance().getFont("Font Awesome Solid"));
    tick.setString(L"\uf00c");
    tick.setFillColor(sf::Color(0, 0, 0, 255));

    sf::Vector2f offset;
    offset.x = (float)this->tick.getGlobalBounds().width;
    offset.y = (float)this->tick.getGlobalBounds().height/0.5f;
    this->tick.setPosition(position+body.getSize()*0.5f - offset*0.5f);

    this->text.setString(text);
    this->text.setFillColor(sf::Color(0, 0, 0, 255));
    this->text.setFont(ResourceHolder::Instance().getFont("PT Sans"));
    this->text.setCharacterSize(15);
    this->text.setPosition(position + sf::Vector2f(body.getSize().x + 10, 0));
}

void CheckBox::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(body);
    if (checked) {
        target.draw(tick);
    }
    if (this->text.getString() != "")
        target.draw(text);
}

void CheckBox::handleEvent(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (this->contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
            checked = !checked;
        }
    }
}

bool CheckBox::isChecked() const {
    return checked;
}
