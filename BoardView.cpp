//
// Created by dimedrol on 18.04.2020.
//

#include <SFML/Window/Event.hpp>
#include "BoardView.h"

BoardView::BoardView(int game_id): table(game_id, &handler) {
    figures = std::vector<sf::Sprite>();
    t_background.loadFromFile("../board.png");
    t_pieces.loadFromFile("../pieces_resized.png");

    table.setPosition(sf::Vector2f(540, 20));
    loadPosition();
}

void BoardView::loadPosition() {
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


void BoardView::onMouseButtonPressed(sf::RenderWindow* window) {
    startField = nullptr;
    destinationField = nullptr;

    for (int i = 0; i < figures.size(); i++) {
        if (figures[i].getGlobalBounds().contains(initMousePosition.x, initMousePosition.y)) {
            moving = true; movedPiece = i;
            window->draw(figures[i]); //TODO: перерисовка, чтобы двигаемая фигура была сверх
            dx = figures[i].getPosition().x - sf::Mouse::getPosition(*window).x;
            dy = figures[i].getPosition().y - sf::Mouse::getPosition(*window).y;

            int startColumn = (int) (figures[movedPiece].getPosition().x / field_size);
            int startRow = 7 - (int) (figures[movedPiece].getPosition().y / field_size);
            try {
                startField = new ChessHandler::Field(startRow, startColumn);
            }
            catch (std::runtime_error& e) { //TODO: custom exception
                startField = nullptr;
                loadPosition();
            }

        }
    }
}

void BoardView::onLeftMouseButtonReleased() {
    moving = false;

    sf::Vector2f startPosition = figures[movedPiece].getPosition() + sf::Vector2f(field_size / 2 - border, field_size / 2 - border);
    sf::Vector2f destinationPosition = sf::Vector2f(field_size * int(startPosition.x / field_size) + border, field_size * int(startPosition.y / field_size) + border);

    int destinationColumn = (int) (destinationPosition.x / field_size);
    int destinationRow = 7 - (int) (destinationPosition.y / field_size);
    try {
        destinationField = new ChessHandler::Field(destinationRow, destinationColumn);
    }
    catch (std::runtime_error& e) { //TODO: custom exception
        destinationField = nullptr;
        loadPosition();
        return;
    }

    if (startField == nullptr || destinationField == nullptr)
        return;

    std::cout << (handler.isWhiteToMove() ? "White" : "Black") << " are trying move " << startField->toString() << destinationField->toString() << std::endl;
    std::cout << "Moved piece " << movedPiece << std::endl << std::endl;

    // if (game.move(move))
    //     board[movedPiece].setPosition(destinationPosition);

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
    std::cout << movedPiece << std::endl;

    handler.print();
    std::cout << handler.getHistoryString() << std::endl;
}


