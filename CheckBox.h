#ifndef CHESS_SFML_CHECKBOX_H
#define CHESS_SFML_CHECKBOX_H

#include <SFML/Graphics.hpp>
#include "IListener.h"

class CheckBox: public sf::Drawable, IListener {
    bool checked = false;
    sf::RectangleShape body;
    sf::Text tick;
    sf::Text text;

public:
    CheckBox(const sf::Vector2f position, std::string text = "");

private:

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    template <class T>
    bool contains(sf::Vector2<T> point) {
        return body.getGlobalBounds().contains(point.x, point.y) || text.getGlobalBounds().contains(point.x, point.y);
    }
    void handleEvent(sf::Event event) override;
};


#endif //CHESS_SFML_CHECKBOX_H
