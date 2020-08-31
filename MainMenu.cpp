//
// Created by witcher on 8/30/20.
//

#include "MainMenu.h"

MainMenu::MainMenu() {
	body.setFillColor(FillColor);
	body.setOutlineColor(BorderColor);
	body.setOutlineThickness(4);
	body.setPosition(sf::Vector2f(-50,0));
	body.setSize(sf::Vector2f(240, 504));

	icon.setFillColor(FillColor);
	icon.setOutlineColor(BorderColor);
	icon.setOutlineThickness(3);
	icon.setPosition(sf::Vector2f(0, 0));
	icon.setSize(sf::Vector2f(50, 50));

	icon_text.setString(sf::String(std::wstring(L"\uf013")));
	icon_text.setPosition(sf::Vector2f(0, 0));

	remove_icon_text.setString(sf::String(std::wstring(L"\uf013")));
	remove_icon_text.setPosition(sf::Vector2f(240, 252));

}

MainMenu::~MainMenu() {

}

void MainMenu::handleEvent(sf::Event event) {

}