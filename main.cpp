#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
//#include "ChessHandler.h" - error
#include "Group.h"
#include "Board.h"
#include <string>

int main() {
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(504, 504), "ChessSFML", sf::Style::Titlebar | sf::Style::Close);;
    auto desktop = sf::VideoMode::getDesktopMode();
    window->setPosition(sf::Vector2i(
            desktop.width/2 - window->getSize().x/2,
            desktop.height/2 - window->getSize().y/2));

    //Загрузка текстур и шрифтов

    sf::Texture t_board_bg;
    t_board_bg.loadFromFile("../board.png");

    sf::Texture t_pieces; //TODO: move
    t_pieces.loadFromFile("../pieces_resized.png");

    //Спрайты

    Group game_session;

    Board board;

    while (window->isOpen())
    {
        sf::Event event;
        board.initMousePosition = sf::Mouse::getPosition(*window);
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();

            //TODO: for (auto obejct: screen) object.handle_event(event); - так будет выглядеть этот while, если мы удосужимся сделать класс Screen

            //drag and drop
            if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
                board.onMouseButtonPressed(window);

            if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
                board.onLeftMouseButtonReleased();


        }
        if (board.isMove)
            board.onMove();

        window->clear();
        window->draw(board);
        window->display();
    }

    delete window;

    return 0;
}