#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "ChessHandler.h"
#include "Group.h"
#include "Label.h"
#include "ResourceHolder.h"
#include "Button.h"
#include "CheckBox.h"
#include <string>

using namespace sf;

//TODO: вынести в отдельный namespace
int board_size = 504;
int field_size = 56;
int border = (board_size - field_size * 8) / 2;

int main() {
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

    sf::RectangleShape background(sf::Vector2f(board_size, board_size));
    background.setFillColor(sf::Color(255, 255, 255, 255));

    Group* game_group = new Group();
    Group* auth = new Group();
    Group* menu = new Group();

    Button form((sf::Vector2f(window.getSize().y * 0.5f - 100, 50)), L"А тут форма входа");
    Button login((sf::Vector2f(window.getSize().y * 0.5f - 100, 150)), L"Войти");
    Button signup((sf::Vector2f(window.getSize().y * 0.5f - 100, 250)), L"Регистрация");
    Button settings_icon((sf::Vector2f(window.getSize().y - 100, 20)), L"\uf013", sf::Vector2f(50, 50));
    Label label((sf::Vector2f(100, 0)), L"Label");
    settings_icon.setFont(ResourceHolder::Instance().getFont("Font Awesome Solid"));
    CheckBox checkBox(sf::Vector2f(50, 50));
    auth->push_back(form);
    auth->push_back(login);
    auth->push_back(signup);
    auth->push_back(settings_icon);
    auth->push_back(label);
    auth->push_back(checkBox);

    Button start((sf::Vector2f(window.getSize().y * 0.5f - 100, 250)), L"Начать игру");

    menu->push_back(start);
    menu->push_back(settings_icon);

    Group* visible; //отрисовываемая группа
    visible = auth;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (visible == auth) {
                login.handleEvent(event);
                checkBox.handleEvent(event);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && login.contains(sf::Mouse::getPosition(window)))
                    visible = menu;
            }
            else if (visible == menu) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && start.contains(sf::Mouse::getPosition(window)))
                    visible = game_group;
            }

        }

        window.clear();
        window.draw(background);
        window.draw(*visible);
        window.display();
    }

    return 0;
}