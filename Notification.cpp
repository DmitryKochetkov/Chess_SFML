//
// Created by witcher on 8/22/20.
//

#include "Notification.h"
#include "ResourceHolder.h"

void Notification::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(body);
    target.draw(text);
}

Notification::Notification(Notification::NotificationType type, std::wstring content) {
    body.setSize(sf::Vector2f(300, 70));
    body.setPosition(sf::Vector2f((504 - 300)/2, 5));
    body.setOutlineThickness(2.0f);
    body.setOutlineColor(sf::Color(0, 0, 0));

    switch (type) {
        case ERROR:
            body.setFillColor(sf::Color(255, 181, 181));
            break;

        default:
        case INFO:
            body.setFillColor(sf::Color(181, 196, 255));
            break;
    }

    text.setFont(ResourceHolder::Instance().getFont("PT Sans"));
    text.setCharacterSize(15);
    text.setPosition(sf::Vector2f((504 - 300)/2, 5));
    text.setFillColor(sf::Color(0, 0, 0));
    text.setString(content);
}
