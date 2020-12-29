//
// Created by witcher on 8/30/20.
//

#ifndef CHESS_SFML_MAINMENU_H
#define CHESS_SFML_MAINMENU_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "ResourceHolder.h"
#include "IListener.h"

class MainMenu : public sf::Drawable , public IListener {
	sf::RectangleShape body;         
	sf::RectangleShape icon;          
	sf::RectangleShape remove_icon;  
	sf::Text icon_text;
	sf::Text remove_icon_text;

	const sf::Color FillColor = sf::Color(105 , 105 , 105); //Gray
	const sf::Color BorderColor = sf::Color::Black;
	const sf::Color BorderColorHover = sf::Color(0, 0, 0);
	const sf::Color TextColor = sf::Color::Black;

public:
	MainMenu::MainMenu();

	template <class T>
	bool contains(sf::Vector2<T> point) {
		return body.getGlobalBounds().contains(point.x, point.y);
	}

	void handleEvent(sf::Event event) override;

	~MainMenu() override;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(body);
		target.draw(icon);
		target.draw(remove_icon);
		target.draw(icon_text);
		target.draw(remove_icon_text);
	}
};


#endif //CHESS_SFML_MAINMENU_H
