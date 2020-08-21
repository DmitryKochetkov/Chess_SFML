#ifndef CHESS_SFML_CHECKBOX_H
#define CHESS_SFML_CHECKBOX_H

#include <SFML/Graphics.hpp>
#include "IListener.h"

class CheckBox: public sf::Drawable, IListener {
    bool checked = false;
    sf::RectangleShape body;
    sf::Text tick;

public:
    CheckBox(const sf::Vector2f position);

private:

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    void handleEvent(sf::Event event) override;
};


#endif //CHESS_SFML_CHECKBOX_H
