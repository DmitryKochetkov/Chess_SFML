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

int main() {
    //TODO for Kirill: где-то здесь ты должен начать кодить кнопки

    sf::ContextSettings appSettings;
    appSettings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(board_size, board_size), "ChessSFML", sf::Style::Titlebar | sf::Style::Close, appSettings);
    auto desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(Vector2i(desktop.width/2 - window.getSize().x/2, desktop.height/2 - window.getSize().y/2));

    //Загрузка текстур и шрифтов

    ResourceHolder::Instance().loadTexture("../board.png", "board");
    ResourceHolder::Instance().loadTexture("../pieces_resized.png", "pieces");
    ResourceHolder::Instance().loadFont("../resources/fonts/PT Sans.ttf", "PT Sans");
    ResourceHolder::Instance().loadFont("../resources/fonts/font_awesome/fa-solid-900.ttf", "Font Awesome Solid");

    //Спрайты

    Group* menu = new Group();
    Group* game_group = new Group();
    Group* auth = new Group();

    sf::RectangleShape background(sf::Vector2f(board_size, board_size));
    background.setFillColor(sf::Color(255, 255, 255, 255));

    Label login((sf::Vector2f(window.getSize().y * 0.5f - 100, 50)), L"Начать игру");
    Label signup((sf::Vector2f(window.getSize().y * 0.5f - 100, 50)), L"Начать игру");
    auth->push_back(login);
    auth->push_back(signup);

    Label start((sf::Vector2f(window.getSize().y * 0.5f - 100, 150)), L"Начать игру");
    Label exit((sf::Vector2f(window.getSize().y * 0.5f - 100, 350)), L"Выход");
    Label settings_icon((sf::Vector2f(window.getSize().y - 100, 20)), L"\uf013", sf::Vector2f(50, 50));
    settings_icon.setFont(ResourceHolder::Instance().getFont("Font Awesome Solid"));

    menu->push_back(start);
    menu->push_back(exit);
    menu->push_back(settings_icon);

    Label label4((sf::Vector2f(window.getSize().y * 0.5f - 100, 50)), L"Против компьютера");
    Label label5((sf::Vector2f(window.getSize().y * 0.5f - 100, 200)), L"Против пользователя");
    Label label6((sf::Vector2f(window.getSize().y * 0.5f - 100, 350)), L"Лобби");
    game_group->push_back(label4);
    game_group->push_back(label5);
    game_group->push_back(label6);

    Group* visible; //отрисовываемая группа
    visible = menu;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (visible == menu) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && exit.contains(sf::Mouse::getPosition(window)))
                    window.close();
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && start.contains(sf::Mouse::getPosition(window)))
                    visible = game_group;
            }

            if (visible == game_group) {

            }

        }

        window.clear();
        window.draw(background);
        window.draw(*visible);
        window.display();
    }

    return 0;
}