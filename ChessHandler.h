#include <iostream>

class ChessHandler {
public:
    class Field {
    private:
        int row;
        int column;

    public:
        Field(int row, int column) {
            setRow(row);
            setColumn(column);
        }

        int getRow() const {
            return row;
        }

        void setRow(int row) {
            if (row > 7 || row < 0) throw std::runtime_error("Incorrect piece coordinates");
            Field::row = row;
        }

        int getColumn() const {
            return column;
        }

        void setColumn(int column) {
            if (column > 7 || column < 0) throw std::runtime_error("Incorrect piece coordinates");
            Field::column = column;
        }

        std::string toString() const {
            char f[2];
            f[0] = 'a' + column;
            f[1] = '1' + row;
            return std::string(f);
        }
    };

    class Move {
    private:
        int piece;
        Field start;
        Field destination;
        bool eating = false; //TODO: eating = id фигуры
        bool check = false;
        bool mate = false;
        bool bad = false;
        bool good = false;

    public:
        Move(int piece, Field start, Field destination, bool check, bool mate): start(start), destination(destination) {
            this->piece = piece;
            this->start = start;
            this->destination = destination;
        }

        void setEating(bool eating) {
            this->eating = eating;
        }

//        std::string toString() {
//            std::string result;
//            result += col1 - 'a';
//            result += row1;
//            result += col2 - 'a';
//            result += row2;
//            return result;
//        }

        virtual std::string toChessNotation() const {
            std::string chessNotation;
            //если 2 фигуры на одной строке или столбце, указать какая именно из них
            char letter = ChessHandler::PieceLetters[abs(piece)];
            if (letter != 'p') {
                chessNotation += std::toupper(letter);
                //TODO: если обе фигуры могут встать на эту клетку, добавить координату, уточняющую какой из них ходит
//                if () {
//
//                }

                if (eating)
                    chessNotation += 'x';
                chessNotation += 'a' + destination.getColumn();
                chessNotation += '1' + destination.getRow();
            }
            else if (eating) {
                chessNotation += start.getColumn() + 'a';
                chessNotation += destination.getColumn() + 'a';
            }
            else {
                chessNotation += 'a' + destination.getColumn();
                chessNotation += '1' + destination.getRow();
            }
            if (mate) chessNotation += "#";
            else if (check) chessNotation += "+";

            if (good) chessNotation += "!";
            if (bad) chessNotation += "?";
            return chessNotation;
        }

        void setCheck(bool check) {
            Move::check = check;
        }

        void setMate(bool mate) {
            Move::mate = mate;
        }

        int getPiece() const {
            return piece;
        }

        const Field &getStart() const {
            return start;
        }

        const Field &getDestination() const {
            return destination;
        }

        bool isMate() const {
            return mate;
        }
    };

    class LongCastlingMove: public Move {
    public:
        LongCastlingMove(int pieceId, Field start, Field destination, bool check, bool mate) : Move(pieceId,
                                                                                                            start,
                                                                                                            destination,
                                                                                                            check,
                                                                                                            mate) {}

        std::string toChessNotation() const override {
            return "0-0-0";
        }
    };

    class ShortCastlingMove: public Move {
    public:
        ShortCastlingMove(int pieceId, Field start, Field destination, bool check, bool mate) : Move(pieceId,
                                                                                                             start,
                                                                                                             destination,
                                                                                                             check,
                                                                                                             mate) {}

        std::string toChessNotation() const override {
            return "0-0";
        }
    };

    enum Side {
        WHITE,
        BLACK
    };

    class Position {
    private:
        int position[8][8];
        bool whiteCanCastleKingside;
        bool whiteCanCastleQueenside;
        bool blackCanCastleKingside;
        bool blackCanCastleQueenside;

    public:

        Position(int position[8][8], bool whiteCanCastle, bool blackCanCastle) {
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++)
                    this->position[i][j] = position[i][j];
            }

            //TODO: проверить наличие соответствующей ладьи
            whiteCanCastleKingside = whiteCanCastle;
            whiteCanCastleQueenside = whiteCanCastle;
            blackCanCastleKingside = blackCanCastle;
            blackCanCastleQueenside = blackCanCastle;
        }

        bool onBoard(int i) {
            return i >= 0 && i < 8;
        }

        //check there is nothing on the way between two fields (exclusive!!!)
//    bool way_is_free(int position1[8][8], int col1, int row1, int col2, int row2) {
//        if (col1 == col2) {
//            if (abs(row1 - row2) <= 1)
//                return true;
//            for (int j = row1 + (row2 > row1 ? 1 : -1); j != row2 + (row2 > row1 ? -1 : 1); j < row2 ? j++ : j--)
//                if (position1[j][col1] != 0)
//                    return false;
//        }
//        else if (row1 == row2) {
//            if (abs(col1 - col2) <= 1)
//                return true;
//            for (int i = col1 + (col2 > col1 ? 1 : -1); i != col2 + (col2 > col1 ? -1 : 1); i < col2 ? i++ : i--)
//                if (position1[row1][i] != 0)
//                    return false;
//        }
//        else
//        for (int i = col1 + (col2 > col1 ? 1 : -1), j = row1 + (row2 > row1 ? 1 : -1); i != col2 + (col2 > col1 ? -1 : 1) && j != row2 + (row2 > row1 ? -1 : 1) && onBoard(i) && onBoard(j); i < col2 ? i++ : i--, j < row2 ? j++ : j--) {
//            if (position1[j][i] != 0)
//                return false;
//        }
//
//        return true;
//    }

        bool way_is_free(int col1, int row1, int col2, int row2) {
            if (col1 > col2)
                std::swap(col1, col2);

            if (row1 > row2)
                std::swap(row1, row2);

            if (col1 == col2) {
                if (abs(row1 - row2) <= 1)
                    return true;
                for (int j = row1 + 1; j != row2; j++)
                    if (position[j][col1] != 0)
                        return false;
            }
            else if (row1 == row2) {
                if (abs(col1 - col2) <= 1)
                    return true;
                for (int i = col1 + 1; i != col2; i++)
                    if (position[row1][i] != 0)
                        return false;
            }
            else
                for (int i = col1 + 1, j = row1 + 1; i != col2 && j != row2 && onBoard(i) && onBoard(j); i < col2 ? i++ : i--, j < row2 ? j++ : j--) {
                    if (position[j][i] != 0)
                        return false;
                }

            return true;
        }

        Field findKing(Side side) {
            int key = (side == WHITE ? 1 : -1);
            for (int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++)
                    if (position[j][i] == key)
                        return Field(j, i);
        }

        bool kingChecked(Side side) {
            Field* field;
            if (side == WHITE)
                field = new Field(findKing(WHITE));

            if (side == BLACK)
                field = new Field(findKing(BLACK));

            int row = field->getRow();
            int col = field->getColumn();
            delete field;

            //check king attacked horizontally
            for (int i = 0; i < 8; i++) {
                if ((
                            position[row][i] == (-5 * (side == WHITE ? 1 : -1)) ||
                            position[row][i] == (-2 * (side == WHITE ? 1 : -1))) && way_is_free(col, row, i, row))
                    return true;
            }

            //check king attacked vertically
            for (int j = 0; j < 8; j++) {
                if ((
                            position[j][col] == (-5 * (side == WHITE ? 1 : -1)) ||
                            position[j][col] == (-2 * (side == WHITE ? 1 : -1))) && way_is_free(col, row, col, j))
                    return true;
            }

            //check king attacked diagonally
            for (int i = col, j = row; i < 8 && j < 8; i++, j++) {
                if ((
                            position[j][i] == (-3 * (side == WHITE ? 1 : -1)) ||
                            position[j][i] == (-2 * (side == WHITE ? 1 : -1))) && way_is_free(col, row, i, j)) {
                    return true;
                }
            }

            // check kings attacked by knights
            if ((onBoard(row + 2) && onBoard(col + 1) && position[row + 2][col + 1] == 4 * (side == WHITE ? -1 : 1)) ||
                (onBoard(row + 2) && onBoard(col - 1) && position[row + 2][col - 1] == 4 * (side == WHITE ? -1 : 1)) ||
                (onBoard(row - 2) && onBoard(col + 1) && position[row - 2][col + 1] == 4 * (side == WHITE ? -1 : 1)) ||
                (onBoard(row - 2) && onBoard(col - 1) && position[row - 2][col - 1] == 4 * (side == WHITE ? -1 : 1)) ||
                (onBoard(row + 1) && onBoard(col + 2) && position[row + 1][col + 2] == 4 * (side == WHITE ? -1 : 1)) ||
                (onBoard(row + 1) && onBoard(col - 2) && position[row + 1][col - 2] == 4 * (side == WHITE ? -1 : 1)) ||
                (onBoard(row - 1) && onBoard(col + 2) && position[row - 1][col + 2] == 4 * (side == WHITE ? -1 : 1)) ||
                (onBoard(row - 1) && onBoard(col - 2) && position[row - 1][col - 2] == 4 * (side == WHITE ? -1 : 1)))
                return true;

            //check opponent's king
            Field opponent = (side == WHITE ? findKing(BLACK) : findKing(WHITE));
            if (abs(row - opponent.getRow()) <= 1 && abs(col - opponent.getColumn()) <= 1)
                return true;

            // TODO: check king attacked by pawns
            if (position[row + (side == WHITE ? 1 : -1)][col + 1] == (side == WHITE ? -6 : 6))
                return true;

            return false;
        }

        int* operator[] (int x) { return position[x]; }

    };

private:
    std::vector<const Move*> history;
    Side toMove = WHITE;

    bool WhiteCanCastleKingside = true;
    bool WhiteCanCastleQueenside = true;
    bool BlackCanCastleKingside = true;
    bool BlackCanCastleQueenside = true;

    int testCheckPosition[8][8] = {
        {-5, 0, 0, 0, 0, 0, -3, -4},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, -1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {4, 2, 0, 0, 0, 0, 0, 5},
    };

    int standardPosition[8][8] = {
        {5, 4, 3, 2, 1, 3, 4, 5},
        {6, 6, 6, 6, 6, 6, 6, 6},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {-6, -6, -6, -6, -6, -6, -6, -6},
        {-5, -4, -3, -2, -1, -3, -4, -5}
    };

    Position position = Position(testCheckPosition, false, false);

private:



    public:

    constexpr static char PieceLetters[8] = {'.', 'k', 'q', 'b', 'n', 'r', 'p', '?'};

    std::vector<sf::CircleShape> circles; //когда очень не хочешь делать нормальную отладку

    void clearLights() {
        circles.clear();
    }

    void addLight(int row, int col) {
        sf::CircleShape circle(56/2);
        circle.setFillColor(sf::Color(255, 210, 210, 200));
        circle.setPosition( (504 - 56 * 8) / 2 + 56 * col, (504 - 56 * 8) / 2 + 56 * (7 - row));
        circles.push_back(circle);
    }

    void print() {
        for (int i = 7; i >= 0; i--) {
            std::cout << i+1 << " | ";
            for (int j = 0; j < 8; j++)
            {
                char out;
                if (abs(position[i][j]) < 0 || abs(position[i][j]) > 7)
                    out = '?';
                else out = PieceLetters[abs(position[i][j])];
                out = position[i][j] > 0 ? toupper(out): out;
                std::cout << out << " ";
            }
            std::cout << std::endl;
        }

        std::cout << "   ";
        for (int i = 0; i < 8; i++) {
            std::cout << " _";
        }

        std::cout << std::endl;

        std::cout << "   ";
        for (int i = 0; i < 8; i++) {
            std::cout << " " << char('A' + i);
        }

        std::cout << std::endl;
    }

    const Move* move(char m[4]) {
        Move* result = nullptr;
        int col1 = m[0] - 'a';
        int row1 = m[1] - '1';
        int col2 = m[2] - 'a';
        int row2 = m[3] - '1';

        if (!history.empty() && history.back()->isMate())
            return nullptr;

        if (position[row1][col1] > 0 != (toMove == WHITE) || position[row1][col1] == 0 || position[row1][col1] * position[row2][col2] > 0)
            return nullptr;

        if (abs(position[row2][col2]) == 1) //короля нельзя съесть
            return nullptr;

        //TODO: check rook is near
        bool KingCastlingCorrect =
                (col1 == 4 && row1 == (toMove == WHITE) ? 0 : 7) //start position is ok
                && row2 == row1 //horizontal moving
                && (
                        ((col2 == 6) && ((toMove == WHITE) ? WhiteCanCastleKingside : BlackCanCastleKingside)) ||
                        ((col2 == 2) && ((toMove == WHITE) ? WhiteCanCastleQueenside : BlackCanCastleQueenside))); //check color and ability to castle
        bool KingCorrect = (abs(row2 - row1) <= 1 && abs(col2 - col1) <= 1) || KingCastlingCorrect;
        bool BishopCorrect = (abs(row2 - row1) == abs(col2 - col1));
        bool KnightCorrect = ((abs(row2 - row1) == 2 && abs(col2 - col1) == 1) || (abs(col2 - col1) == 2 && abs(row2 - row1) == 1));
        bool RookCorrect = (row2 == row1 || col2 == col1);
        bool PawnCorrect = ((col2 == col1) && position[row2][col2] == 0 && (row2 == row1 + ((toMove == WHITE) ? 1 : -1))) ||
                           ((abs(col2 - col1) == 1) && position[row2][col2] != 0 && (row2 == row1 + ((toMove == WHITE) ? 1 : -1))) ||
                           ((col2 == col1) && (row1 == (toMove == WHITE) ? 1 : 5) && (position[row2][col2] == 0) && ((row2 == row1 + ((toMove == WHITE) ? 1 : -1)) || ((row2 == row1 + ((toMove == WHITE) ? 2 : -2)) && position.way_is_free(col1, row1, col2, row2)))) ||
                           ((row1 == ((toMove == WHITE) ? 4 : 3) && abs(getLastMove()->getPiece()) == 6 && getLastMove()->getStart().getRow() == ((toMove == WHITE) ? 6 : 1) && abs(getLastMove()->getDestination().getRow() - getLastMove()->getStart().getRow() == 2) && (col2 == getLastMove()->getDestination().getColumn()) && (row2 == getLastMove()->getStart().getRow() + ((toMove == WHITE) ? -1 : 1)))); //взятие на проходе

        bool QueenCorrect = BishopCorrect ^ RookCorrect;

        switch (abs(position[row1][col1]))
        {
        case 1:
            if (!KingCorrect)
                return nullptr;

            //move out of switch?
            if (KingCastlingCorrect) {
                if (toMove == WHITE) {
                    WhiteCanCastleKingside = false;
                    WhiteCanCastleQueenside = false;
                }
                else {
                    BlackCanCastleKingside = false;
                    BlackCanCastleQueenside = false;
                }

                position[row2][col2] = position[row1][col1];
                position[row1][col1] = 0;

                if (col2 == 6) { //king side
                    //change rook position
                    position[row2][col2 - 1] = position[row2][col2 + 1];
                    position[row2][col2 + 1] = 0;
                    result = new ShortCastlingMove(position[row2][col2], Field(row1, col1), Field(row2, col2), false, false);
                    history.push_back(result);
                }
                else if (col2 == 2) { //queen side TODO: не помню точно, насколько клеток
                    //change rook position
                    position[row2][col2 + 1] = position[row2][col2 - 2];
                    position[row2][col2 - 2] = 0;
                    result = new LongCastlingMove(position[row2][col2], Field(row1, col1), Field(row2, col2), false, false);
                    history.push_back(result);
                }

                finishMove();
                return result;
            }

            break;

        case 2:
            if (!QueenCorrect)
                return nullptr;
            if (!position.way_is_free(col1, row1, col2, row2))
                return nullptr;
            break;

        case 3:
            if (!BishopCorrect)
                return nullptr;
            if (!position.way_is_free(col1, row1, col2, row2))
                return nullptr;

            break;

        case 4:
            if (!KnightCorrect)
                return nullptr;
            break;

        case 5:
            if (!RookCorrect)
                return nullptr;
            if (!position.way_is_free(col1, row1, col2, row2))
                return nullptr;

            if (row1 == 0) { //handles the first move of the white rook
                if (col1 == 0) //queen side
                    WhiteCanCastleQueenside = false;
                else //king side
                    WhiteCanCastleKingside = false;
            }
            else { //handles the first move of the black rook
                if (col1 == 0) //queen side
                    BlackCanCastleQueenside = false;
                else //king side
                    BlackCanCastleKingside = false;
            }

            break;

        case 6:
            if (!PawnCorrect)
                return nullptr;
            break;
        
        default:
            return nullptr;
        }

        result = new Move(position[row1][col1], Field(row1, col1), Field(row2, col2), false, false);

        //проверка шаха TODO: рокировку нельзя произвести если стоит шах, проверка шаха должна быть раньше
        bool WhiteKingCheck = false; //1
        bool BlackKingCheck = false; //-1

        Position afterMove = position;

        afterMove[row2][col2] = position[row1][col1];
        afterMove[row1][col1] = 0;

        if (toMove == WHITE) {
            if (afterMove.kingChecked(WHITE))
                return nullptr;
            if (afterMove.kingChecked(BLACK))
                result->setCheck(true);
            //TODO: check mate
        }
        else {
            if (afterMove.kingChecked(BLACK))
                return nullptr;
            if (afterMove.kingChecked(WHITE))
                result->setCheck(true);
            //TODO: check mate
        }

        if (position[row2][col2] != 0)
            result->setEating(true);
        history.push_back(result);

        position[row2][col2] = position[row1][col1];
        position[row1][col1] = 0;
        finishMove();

        return getLastMove();
    }

    const Move* move(Field start, Field destination) {
        char m[4];
        m[0] = start.toString()[0];
        m[1] = start.toString()[1];
        m[2] = destination.toString()[0];
        m[3] = destination.toString()[1];
        return move(m);
    }

    void finishMove() {
        if (toMove == WHITE)
            toMove = BLACK;
        else toMove = WHITE;
    }

    Side getSideToMove() const {return toMove;}
    int getCell(int row, int column) {return position[row][column];}
    //Move getMove(int id) { return history.at(id); }
    const Move* getLastMove() { if (history.empty()) return nullptr; return history.back(); }
    std::string getHistoryString() {
        std::string result;
        for (int i = 0; i < history.size(); i++) {
            if ((i + 1) % 2 != 0)
                result += std::to_string((i + 2) / 2) + ". ";
            result += history[i]->toChessNotation() + " ";
        }
        return result;
    }

    const std::vector<const Move*> &getHistory() const {
        return history;
    }
};