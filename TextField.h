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

public:
    enum Mode {
        TEXT,
        EMAIL,
        LOGIN,
        PASSWORD
    };

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    const wchar_t passwordChar = L'\u2022';
    std::wstring content;
	sf::Text txt;
	sf::Text placeholder;
	sf::RectangleShape box;
	sf::RectangleShape caret;

	void setActive(bool arg);

	bool active = false;

	sf::Clock blinking;
	bool caretVisible = true;
	Mode mode;

public:
	void handleEvent(sf::Event event) override;
	void blink();

	TextField(sf::Vector2f pos, std::wstring str, Mode mode = Mode::TEXT);

	template <class T>
	bool contains(sf::Vector2<T> point) {
		return box.getGlobalBounds().contains(point.x, point.y);
	}

    ~TextField() override;

	std::wstring getContent();
};



#endif //CHESS_SFML_TEXTFIELD_H
