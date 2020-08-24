#ifndef CHESS_SFML_NOTIFICATION_H
#define CHESS_SFML_NOTIFICATION_H

#include <SFML/Graphics.hpp>
#include "IListener.h"

class Notification: public sf::Drawable, public IListener {
private:
    sf::Text text;
    sf::RectangleShape body;
    sf::Color color;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::Clock clock;
    void setTransparent(bool transparent);


public:
    enum NotificationType {
        INFO,
        ERROR
    };

    Notification(NotificationType type, std::wstring content);

    void animation() {
        if (clock.getElapsedTime().asMilliseconds() > 3000)
            setTransparent(true);
        else setTransparent(false);
    }

    void handleEvent(sf::Event event) override;
};


#endif //CHESS_SFML_NOTIFICATION_H
