//
// Created by dimedrol on 18.04.2020.
//

#ifndef CHESS_SFML_BOARD_H
#define CHESS_SFML_BOARD_H


#include <SFML/Graphics.hpp>
#include <vector>
#include "ChessHandler.h"

class Board : public sf::Drawable {
    ChessHandler handler;
    std::vector<sf::Sprite> figures;

    int board_size = 504;
    int field_size = 56;
    int border = (board_size - field_size * 8) / 2;
    sf::Texture t_background;
    sf::Texture t_pieces;

    //ChessHandler game; //TODO: move out?

    //deprecated variables

    char move[4];
    int moved_piece;
    float dx = 0, dy = 0;

public:
    bool isMove = false;
    Board(int game_id);
    sf::Vector2i initMousePosition;

    void loadPosition();
    void onMouseButtonPressed(sf::RenderWindow* window);
    void onLeftMouseButtonReleased();

    void onMove() {
        //figures[moved_piece].setPosition(figures[moved_piece].getPosition() + sf::Vector2f(dx, dy));
        figures[moved_piece].setPosition(sf::Vector2f(initMousePosition.x, initMousePosition.y) + sf::Vector2f(dx, dy));
    }

private:
    class Table: public sf::Drawable {
    private:
        sf::Font font;
        sf::Text game_name;
        sf::Text opponent;
        sf::RectangleShape border;
        ChessHandler* handler;

    public:
        Table(int game_id, ChessHandler* handler) {
            this->handler = handler;
            font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf");
            game_name = sf::Text(L"Партия #" + std::to_wstring(game_id), font);
            game_name.setCharacterSize(22);
            game_name.setFillColor(sf::Color(0, 0, 0, 255));
            border.setSize(sf::Vector2f(180, 550));
            border.setFillColor(sf::Color(240, 240, 240, 255));
            border.setOutlineColor(sf::Color(255, 255, 255));
            border.setOutlineThickness(1);
            opponent = sf::Text(L"Соперник: someUser", font, 15);
            opponent.setFillColor(sf::Color(0, 0, 0));
        }

        void setPosition(sf::Vector2f position) {
            border.setPosition(position + sf::Vector2f(0, 60));
            game_name.setPosition(position);
            opponent.setPosition(position + sf::Vector2f(0, 30));
        }

    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
            target.draw(game_name);
            target.draw(opponent);
            target.draw(border);
            std::vector<sf::Text> moves;
            for (const ChessHandler::Move* move: handler->getHistory()) {
                sf::Text text(move->toChessNotation(), font, 20);
                text.setFillColor(sf::Color(0, 0, 0, 255));
                moves.push_back(text);
            }
            for (int i = 0; i < moves.size(); i++) {
                moves[i].setPosition(sf::Vector2f(554, 50) + sf::Vector2f(i % 2 == 0 ? 0 : 80, 30*(i/2) + 40));
                target.draw(moves[i]);
            }
        }
    };

    Table table;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        sf::Sprite background(t_background);
        target.draw(background);
        for (int i = 0; i < figures.size(); i++)
            target.draw(figures[i]);
        target.draw(table);
    }
};


#endif //CHESS_SFML_BOARD_H
