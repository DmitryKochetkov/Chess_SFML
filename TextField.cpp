//
// Created by dimedrol on 7/14/20.
//

#include "TextField.h"

TextField::TextField(sf::Vector2f pos, std::string str) {
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

	caret.setSize(sf::Vector2f(40, 3)); //����� 
	caret.setFillColor(sf::Color::Black);
	caret.setPosition(txt.getPosition());
	caret.setRotation(90);
}


void TextField::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(box);
    if (txt.getString() == "")
        target.draw(placeholder);
    else target.draw(txt);
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
	if (event.type == sf::Event::MouseMoved) {
		sf::Vector2f pos(event.mouseMove.x, event.mouseMove.y);
		if (box.getGlobalBounds().contains(pos)) {
			setActive(true);
		}
		else {
			setActive(false);
		}
	}

	if (event.type == sf::Event::TextEntered && active) {
        if (event.text.unicode > 32 && event.text.unicode < 127) {
            txt.setString(txt.getString() + event.text.unicode);

        }
        else if (event.text.unicode == '\b'){
            txt.setString(txt.getString().substring(0, txt.getString().getSize() - 1));
        }

        double x = txt.getLocalBounds().width + 5;
        if (x > box.getSize().x)
            x = box.getSize().x - 5;
        caret.setPosition(txt.getPosition() + sf::Vector2f(x, 0));

        //TODO: escape; setActive по клику
	}

//	if (event.type == sf::Event::TextEntered && active) {
//		sf::String str = txt.getString();
//
//		if (event.text.unicode > 32 && event.text.unicode < 127) {
//			if (str.getSize() < 17) //�� �������. �������� �� �������
//				caret.setPosition(caret.getPosition() + sf::Vector2f(13, 0));
//
//
//			if (event.text.unicode == '\b') { //backspace
//				if (str.getSize() > 0) {
//					length--;
//					str = str.substring(0, str.getSize() - 1);
//					caret.setPosition(caret.getPosition() - sf::Vector2f(13, 0));
//				}
//			}
//			else if (event.text.unicode == '\e') { //escape
//				setActive(false);
//			}
//			else {
//				sf::String sfstr = "";
//				sfstr += event.text.unicode;
//				str += sfstr.toAnsiString(); //���� ���
//			}
//
//			if (str.getSize() == size) return;
//
//			txt.setString(str);
//			length++;
//		}
//	}
}

TextField::~TextField() {

}
