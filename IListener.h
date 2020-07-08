#include <SFML/Window.hpp>
#ifndef ILISTENER_H
#define ILISTENER_H

class IListener
{
    virtual void handleEvent(sf::Event event) = 0;
    virtual ~IListener() {};
};
#endif