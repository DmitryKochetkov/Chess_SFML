//
// Created by dimedrol on 7/14/20.
//

#ifndef CHESS_SFML_TEXTFIELD_H
#define CHESS_SFML_TEXTFIELD_H

#include <SFML/Graphics.hpp>
#include "IListener.h"

class TextField: public sf::Drawable, public IListener {
    //TODO: implement and close issue #18

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    void handleEvent(sf::Event event) override;

public:
    ~TextField() override;
};


#endif //CHESS_SFML_TEXTFIELD_H
