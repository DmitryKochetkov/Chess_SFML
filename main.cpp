#include <SFML/Graphics.hpp>
#include "Group.h"
#include "BoardView.h"
#include "ResourceHolder.h"
#include "Label.h"
#include <string>

int main() {
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(754, 504), "ChessSFML", sf::Style::Titlebar | sf::Style::Close);;
    auto desktop = sf::VideoMode::getDesktopMode();
    window->setPosition(sf::Vector2i(
            desktop.width/2 - window->getSize().x/2,
            desktop.height/2 - window->getSize().y/2));

    //Загрузка текстур и шрифтов

    ResourceHolder::Instance().loadTexture("../board.png", "board");
    ResourceHolder::Instance().loadTexture("../pieces_resized.png", "pieces");
    ResourceHolder::Instance().loadFont("../resources/fonts/PT Sans.ttf", "PT Sans");
    ResourceHolder::Instance().loadFont("../resources/fonts/font_awesome/fa-solid-900.ttf", "Font Awesome Solid");

    //Спрайты

    Group game_session;

    BoardView boardView(1);
    sf::RectangleShape background(sf::Vector2f(754, 504));
    background.setFillColor(sf::Color(255, 255, 255, 255));

    game_session.push_back(background);
    game_session.push_back(boardView);

    while (window->isOpen())
    {
        sf::Event event;
        boardView.initMousePosition = sf::Mouse::getPosition(*window);
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();

            //TODO: for (auto obejct: screen) object.handle_event(event); - так будет выглядеть этот while, если мы удосужимся сделать класс Screen

            //drag and drop
            //TODO: use IListener for handling this events (after merge)
            if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
                boardView.onMouseButtonPressed(window);

            if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
                boardView.onLeftMouseButtonReleased();
        }
        //TODO: custom event
        if (boardView.isMove())
            boardView.onMove();

        window->clear();
        window->draw(game_session);
        window->display();
    }

    delete window;

    return 0;
}