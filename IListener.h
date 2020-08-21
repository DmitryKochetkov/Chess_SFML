#include <SFML/Window.hpp>
#ifndef ILISTENER_H
#define ILISTENER_H

class IListener
{
public:
    virtual void handleEvent(sf::Event event) = 0;
    virtual ~IListener() = default;
};
#endif