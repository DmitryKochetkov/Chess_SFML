//
// Created by dimedrol on 7/14/20.
//

#ifndef CHESS_SFML_TEXTFIELD_H
#define CHESS_SFML_TEXTFIELD_H

#include <string>
#include <SFML/Graphics.hpp>
#include "IListener.h"
#include "ResourceHolder.h"

class TextField: public sf::Drawable, public IListener {
    //TODO: implement and close issue #18

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
	sf::Text txt;
	sf::Text placeholder;
	sf::RectangleShape box;
	sf::RectangleShape caret;

	void setActive(bool arg);

	bool active;

public:
	void handleEvent(sf::Event event) override;

	TextField(sf::Vector2f pos, std::wstring str);

	template <class T>
	bool contains(sf::Vector2<T> point) {
		return box.getGlobalBounds().contains(point.x, point.y);
	}

    ~TextField() override;
};



#endif //CHESS_SFML_TEXTFIELD_H
