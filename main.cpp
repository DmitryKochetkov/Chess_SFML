#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "ChessHandler.h"
#include "Group.h"
#include "Label.h"
#include "ResourceHolder.h"
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

    ResourceHolder::Instance().loadTexture("../board.png", "board");
    ResourceHolder::Instance().loadTexture("../pieces_resized.png", "pieces");
    ResourceHolder::Instance().loadFont("../resources/fonts/PT Sans.ttf", "PT Sans");

    //Спрайты

    Group menu;
    Group game_group;

    Sprite board_bg(ResourceHolder::Instance().getTexture("board"));

    Label start((sf::Vector2f(window.getSize().y * 0.5f - 100, 50)), L"Начать игру");
    Label settings((sf::Vector2f(window.getSize().y * 0.5f - 100, 200)), L"Настройки");
    Label exit((sf::Vector2f(window.getSize().y * 0.5f - 100, 350)), L"Выход");
    menu.push_back(start);
    menu.push_back(settings);
    menu.push_back(exit);

    Label label4((sf::Vector2f(window.getSize().y * 0.5f - 100, 50)), L"Против компьютера");
    Label label5((sf::Vector2f(window.getSize().y * 0.5f - 100, 200)), L"Против пользователя");
    Label label6((sf::Vector2f(window.getSize().y * 0.5f - 100, 350)), L"Лобби");
    game_group.push_back(label4);
    game_group.push_back(label5);
    game_group.push_back(label6);

    Group visible; //отрисовываемая группа
    visible = menu;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && start.contains(sf::Mouse::getPosition(window)))
                visible = game_group;
        }

        window.clear();
        window.draw(visible);
        window.display();
    }

    return 0;
}