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
    Board();
    sf::Vector2i initMousePosition;

    void loadPosition();
    void onMouseButtonPressed(sf::RenderWindow* window);
    void onLeftMouseButtonReleased();

    void onMove() {
        //figures[moved_piece].setPosition(figures[moved_piece].getPosition() + sf::Vector2f(dx, dy));
        figures[moved_piece].setPosition(sf::Vector2f(initMousePosition.x, initMousePosition.y) + sf::Vector2f(dx, dy));
    }

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        sf::Sprite background(t_background);
        target.draw(background);
        for (int i = 0; i < 32; i++)
            target.draw(figures[i], states);
    }
};


#endif //CHESS_SFML_BOARD_H
