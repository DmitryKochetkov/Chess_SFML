//
// Created by dimedrol on 7/14/20.
//

#include "TextField.h"

TextField::TextField(sf::Vector2f pos, std::wstring str) {
	box.setPosition(pos);
	box.setSize(sf::Vector2f(200, 50));
	box.setFillColor(sf::Color::White);
	box.setOutlineThickness(3);

	placeholder.setPosition(pos + sf::Vector2f(10, 5));
	placeholder.setString(str);
    placeholder.setFont(ResourceHolder::Instance().getFont("PT Sans"));
	placeholder.setFillColor(sf::Color(0, 0, 0, 128));
	placeholder.setCharacterSize(24);

	txt.setPosition(pos + sf::Vector2f(5, 5));
	txt.setFont(ResourceHolder::Instance().getFont("PT Sans"));
	txt.setCharacterSize(24);
	txt.setFillColor(sf::Color::Black);

	setActive(false);

	caret.setSize(sf::Vector2f(40, 3));
	caret.setFillColor(sf::Color::Black);
	caret.setPosition(txt.getPosition());
	caret.setRotation(90);
}


void TextField::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(box);
    if (txt.getString() == "")
        target.draw(placeholder);
    else target.draw(txt);
    if (this->active)
        target.draw(caret);
}


void TextField::setActive(bool arg) {
	active = arg;
	if (active) {
		box.setOutlineColor(sf::Color::Red);
	}
	else {
		box.setOutlineColor(sf::Color::Black);
	}
}

void TextField::handleEvent(sf::Event event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		sf::Vector2f pos(event.mouseButton.x, event.mouseButton.y);
        setActive(box.getGlobalBounds().contains(pos));
	}

	if (event.type == sf::Event::TextEntered && active) {
        switch (event.text.unicode) {
            case '\b':
                txt.setString(txt.getString().substring(0, txt.getString().getSize() - 1));
                break;

            case 27:
                setActive(false);
                break;

            case '\t':
                break;

            default:
                txt.setString(txt.getString() + event.text.unicode);
        }


        double x = txt.getLocalBounds().width + 5;
        if (x > box.getSize().x)
            x = box.getSize().x - 5;
        caret.setPosition(txt.getPosition() + sf::Vector2f(x, 0));
	}
}

TextField::~TextField() {

}
