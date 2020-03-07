#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "ChessHandler.h"

using namespace sf;

int board_size = 504;
int field_size = 56;
int border = (board_size - field_size * 8) / 2;
ChessHandler game;
Sprite board[32];

void loadPosition() {
    int k = 0;
    //for (int i = 0; i < 8; i++)
    for (int i = 7; i >= 0; i--)
        for (int j = 0; j < 8; j++)
        //for (int j = 7; j >= 0; j--)
        {
            int piece_id = game.get_cell(i, j);
            if (piece_id != 0) {
                int x = abs(piece_id) - 1;
                int y = piece_id > 0 ? 1 : 0; //TODO: check
                board[k].setTextureRect(IntRect(field_size*x, field_size*y, field_size, field_size));
                board[k].setPosition(field_size*j + border, field_size*i + border);
                k++;
            }
        }
}


int main() {
    sf::RenderWindow window(sf::VideoMode(board_size, board_size), "ChessSFML", sf::Style::Titlebar | sf::Style::Close);;
    auto desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(Vector2i(desktop.width/2 - window.getSize().x/2, desktop.height/2 - window.getSize().y/2));

    Texture t_board_bg;
    t_board_bg.loadFromFile("board.png");

    Texture t_pieces; //TODO: move
    t_pieces.loadFromFile("pieces_resized.png");

    Sprite board_bg(t_board_bg);

    for (int i = 0; i < 32; i++) board[i].setTexture(t_pieces);
    loadPosition();

    float dx = 0, dy = 0;
    bool isMove = false;

    int moved_piece = 0;

    char move[4];

    while (window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            //drag and drop
            if (event.type == sf::Event::MouseButtonPressed)
                if (event.key.code == Mouse::Left)
                    for (int i = 0; i < 32; i++) {
                        if (board[i].getGlobalBounds().contains(pos.x, pos.y)) {
                            isMove = true; moved_piece = i;
                            dx = pos.x - board[i].getPosition().x;
                            dy = pos.y - board[i].getPosition().y;

                            move[0] = static_cast<int>('a') + (int) (board[moved_piece].getPosition().x / field_size);
                            move[1] = std::to_string(8 - (int) (board[moved_piece].getPosition().y / field_size))[0];
                        }
                    }

            if (event.type == Event::MouseButtonReleased)
                if (event.key.code == Mouse::Left)
                {
                    isMove = false;

                    Vector2f p = board[moved_piece].getPosition() + Vector2f(field_size/2 - border, field_size/2 - border);
                    Vector2f newPosition = Vector2f(field_size*int(p.x/field_size) + border, field_size*int(p.y/field_size) + border);

                    move[2] = static_cast<int>('a') + (int) (newPosition.x / field_size);
                    move[3] = std::to_string(8 - (int) (newPosition.y / field_size))[0];

                    std::cout << "Trying move " << move << std::endl;
                    std::cout << "Moved piece " << moved_piece << std::endl << std::endl;

                    // if (game.move(move))
                    //     board[moved_piece].setPosition(newPosition);
                    // else loadPosition();

                    if (game.move(move))
                        board[moved_piece].setPosition(newPosition);
                    //TODO: else board[moved_piece].setPosition(oldPosition);

                    loadPosition();

                    game.print();
                }

            if (isMove) {
                //todo
                board[moved_piece].setPosition(pos.x - dx, pos.y - dy);
            }
            
        }

        window.clear();
        window.draw(board_bg);
        for (int i = 0; i < 32; i++) window.draw(board[i]);
        window.display();
    }

    return 0;
}