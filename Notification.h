#ifndef CHESS_SFML_NOTIFICATION_H
#define CHESS_SFML_NOTIFICATION_H

#include <SFML/Graphics.hpp>

class Notification: public sf::Drawable {
protected:
    //std::vector<sf::Text> lines;
    sf::Text text;
    sf::RectangleShape body;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    enum NotificationType {
        INFO,
        ERROR
    };

    Notification(NotificationType type, std::wstring content);
};


#endif //CHESS_SFML_NOTIFICATION_H
