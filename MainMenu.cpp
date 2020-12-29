//
// Created by witcher on 8/30/20.
//

#include "MainMenu.h"

MainMenu::MainMenu() {
	body.setFillColor(FillColor);
	body.setOutlineColor(BorderColor);
	body.setOutlineThickness(3);
	body.setPosition(sf::Vector2f(0,0));
	body.setSize(sf::Vector2f(200,500 ));

	icon.setFillColor(FillColor);
	icon.setOutlineColor(BorderColor);
	icon.setOutlineThickness(3);
	icon.setPosition(sf::Vector2f(0, 0));
	icon.setSize(sf::Vector2f(50, 50));

	remove_icon.setPosition(sf::Vector2f(180, 0));
	remove_icon.setSize(sf::Vector2f(20, 20));
	remove_icon.setFillColor(FillColor);

	icon_text.setString(sf::String(std::wstring(L"\uf0c9")));
	icon_text.setPosition(sf::Vector2f(0, 0));
	icon_text.setCharacterSize(50);
	icon_text.setFillColor(TextColor);
	icon_text.setStyle(sf::Text::Bold);
	icon_text.setFont(ResourceHolder::Instance().getFont("PT Sans"));

	remove_icon_text.setString(sf::String(std::wstring(L"\uf057")));
	remove_icon_text.setPosition(sf::Vector2f(165, 0));
	remove_icon_text.setCharacterSize(50);
	remove_icon_text.setFillColor(TextColor);
	remove_icon_text.setStyle(sf::Text::Bold);
	remove_icon_text.setFont(ResourceHolder::Instance().getFont("PT Sans"));
}

MainMenu::~MainMenu() {

}

void MainMenu::handleEvent(sf::Event event) {

}