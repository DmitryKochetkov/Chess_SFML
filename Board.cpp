//
// Created by dimedrol on 18.04.2020.
//

#include <SFML/Window/Event.hpp>
#include "Board.h"

Board::Board(int game_id): table(game_id, &handler) {
    figures = std::vector<sf::Sprite>();
    t_background.loadFromFile("../board.png");
    t_pieces.loadFromFile("../pieces_resized.png");

    table.setPosition(sf::Vector2f(540, 20));
    loadPosition();
}

void Board::loadPosition() {
    figures.clear();
    int k = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            int piece_id = handler.getCell(i, j);
            if (piece_id != 0) {
                int x = abs(piece_id) - 1;
                int y = piece_id > 0 ? 0 : 1;
                figures.push_back(sf::Sprite(t_pieces));
                figures[k].setTextureRect(sf::IntRect(field_size * x, field_size * y, field_size, field_size));
                figures[k].setPosition(field_size * j + border, field_size * (7 - i) + border);
                k++;
            }
        }
}

//void Board::onMouseButtonPressed(sf::Vector2i mouse_position) {
void Board::onMouseButtonPressed(sf::RenderWindow* window) {
    for (int i = 0; i < 32; i++) {
        if (figures[i].getGlobalBounds().contains(initMousePosition.x, initMousePosition.y)) {
            moving = true; moved_piece = i;
            window->draw(figures[i]); //TODO: перерисовка, чтобы двигаемая фигура была сверх
            dx = figures[i].getPosition().x - sf::Mouse::getPosition(*window).x;
            dy = figures[i].getPosition().y - sf::Mouse::getPosition(*window).y;

            int startRow = (int) (figures[moved_piece].getPosition().x / field_size);
            int startColumn = 7 - (int) (figures[moved_piece].getPosition().y / field_size);
            try {
                startField = new ChessHandler::Field(startRow, startColumn);
            }
            catch (std::runtime_error& e) {
                startField = nullptr;
            }

        }
    }
}

void Board::onLeftMouseButtonReleased() {
    moving = false;

    sf::Vector2f p = figures[moved_piece].getPosition() + sf::Vector2f(field_size/2 - border, field_size/2 - border);
    sf::Vector2f newPosition = sf::Vector2f(field_size*int(p.x/field_size) + border, field_size*int(p.y/field_size) + border);

    int destinationRow = (int) (newPosition.x / field_size);
    int destinationColumn = 7 - (int) (newPosition.y / field_size);
    try {
        destinationField = new ChessHandler::Field(destinationRow, destinationColumn);
    }
    catch (std::runtime_error& e) {
        loadPosition();
        return;
    }

    std::cout << (handler.isWhiteToMove() ? "White" : "Black") << " are trying move " << startField->toString() << destinationField->toString() << std::endl;
    std::cout << "Moved piece " << moved_piece << std::endl << std::endl;

    // if (game.move(move))
    //     board[moved_piece].setPosition(newPosition);

    const ChessHandler::Move* handled_move = handler.move(*startField, *destinationField);
    if (handled_move == nullptr) {
        std::cout << "Unable to perform move" << std::endl;
    }
    if (handled_move != nullptr) {
        std::string title = "ChessSFML (";
        title += (handler.isWhiteToMove() ? "White to move" : "Black to move");
        title += ")";
        //window.setTitle(title);
    }
    if (handled_move != nullptr)
        std::cout << "Performed move " << handled_move->toChessNotation() << std::endl;

    loadPosition();
    std::cout << moved_piece << std::endl;

    handler.print();
    std::cout << handler.getHistoryString() << std::endl;
}


