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
            color = sf::Color(255, 181, 181);
            break;

        default:
        case INFO:
            color = sf::Color(181, 196, 255);
            break;
    }
    body.setFillColor(color);

    text.setFont(ResourceHolder::Instance().getFont("PT Sans"));
    text.setCharacterSize(15);
    text.setPosition(sf::Vector2f((504 - 300)/2, 5));
    text.setFillColor(sf::Color(0, 0, 0));

    std::vector<std::wstring> words;
    while (content.length() > 0) {
        std::wstring word;
        int pos = content.find_first_of(' ');
        if (pos == std::wstring::npos) {
            word = content;
            content = L"";
        }
        else word = content.substr(0, pos);
        words.push_back(word);
        content = content.substr(pos + 1, content.length() - 1);
    }

    for (auto word: words) {
        sf::Text new_text(text);
        new_text.setString(text.getString() + word + " ");
        if (new_text.getGlobalBounds().height > body.getGlobalBounds().height) {
            break;
        }
        if (new_text.getGlobalBounds().width > body.getGlobalBounds().width)
            text.setString(text.getString() + L"\n" + word + " ");
        else text = new_text;
    }
}

void Notification::setTransparent(bool transparent) {
    if (transparent) {
        color.a = 100;
        text.setFillColor(sf::Color(0, 0, 0, 100));
    }
    else {
        color.a = 255;
        text.setFillColor(sf::Color(0, 0, 0, 255));
    }
    body.setFillColor(color);
}

void Notification::handleEvent(sf::Event event) {
    if (event.type == sf::Event::MouseMoved)
        if (body.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
            clock.restart();
        }
}

bool Notification::isActive() const {
    return active;
}
