#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "ChessHandler.h"
#include "Group.h"
#include "Label.h"
#include <string>

using namespace sf;

//TODO: вынести в отдельный namespace
int board_size = 504;
int field_size = 56;
int border = (board_size - field_size * 8) / 2;
ChessHandler game;
Sprite board[32];


int main() {
    //TODO for Kirill: где-то здесь ты должен начать кодить кнопки

    sf::RenderWindow window(sf::VideoMode(board_size, board_size), "ChessSFML", sf::Style::Titlebar | sf::Style::Close);;
    auto desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(Vector2i(desktop.width/2 - window.getSize().x/2, desktop.height/2 - window.getSize().y/2));

    //Загрузка текстур и шрифтов

    Texture t_board_bg;
    t_board_bg.loadFromFile("../board.png");

    Texture t_pieces; //TODO: move
    t_pieces.loadFromFile("../pieces_resized.png");

    //Спрайты

    Group menu;

    Sprite board_bg(t_board_bg);
    Label label(sf::Vector2f(200, 300), "Hi!");
    menu.push_back(label);

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(menu);
        window.display();
    }

    return 0;
}