#include <iostream>

class ChessHandler {
public:
    class Move {
    private:
        int piece;
        int row1, col1, row2, col2;
        bool eating = false; //TODO: eating = id фигуры
        bool check = false;
        bool mate = false;
        bool bad = false;
        bool good = false;

    public:
        Move(int piece, int row1, int col1, int row2, int col2, bool check, bool mate) {
            if (row1 > 7 || row1 < 0) throw std::runtime_error("Incorrect piece coordinates");
            if (col1 > 7 || col1 < 0) throw std::runtime_error("Incorrect piece coordinates");
            if (row2 > 7 || row2 < 0) throw std::runtime_error("Incorrect piece coordinates");
            if (col2 > 7 || col2 < 0) throw std::runtime_error("Incorrect piece coordinates");

            this->piece = piece;
            this->row1 = row1;
            this->col1 = col1;
            this->row2 = row2;
            this->col2 = col2;
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
                chessNotation += 'a' + col2;
                chessNotation += '1' + row2;
            }
            else if (eating) {
                chessNotation += col1 + 'a';
                chessNotation += col2 + 'a';
            }
            else {
                chessNotation += 'a' + col2;
                chessNotation += '1' + row2;
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

        int getRow1() const {
            return row1;
        }

        int getCol1() const {
            return col1;
        }

        int getRow2() const {
            return row2;
        }

        int getCol2() const {
            return col2;
        }
    };

    class LongCastlingMove: public Move {
    public:
        LongCastlingMove(int pieceId, int row1, int col1, int row2, int col2, bool check, bool mate) : Move(pieceId,
                                                                                                            row1, col1,
                                                                                                            row2, col2,
                                                                                                            check,
                                                                                                            mate) {}

        std::string toChessNotation() const override {
            return "0-0-0";
        }
    };

    class ShortCastlingMove: public Move {
    public:
        ShortCastlingMove(int pieceId, int row1, int col1, int row2, int col2, bool check, bool mate) : Move(pieceId,
                                                                                                             row1, col1,
                                                                                                             row2, col2,
                                                                                                             check,
                                                                                                             mate) {}

        std::string toChessNotation() const override {
            return "0-0";
        }
    };

private:
    std::vector<const Move*> history;
    bool WhiteToMove = true;

    bool WhiteCanCastleKingside = true;
    bool WhiteCanCastleQueenside = true;
    bool BlackCanCastleKingside = true;
    bool BlackCanCastleQueenside = true;

    int position[8][8] = {
        {5, 4, 3, 2, 1, 3, 4, 5},
        {6, 6, 6, 6, 6, 6, 6, 6},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {-6, -6, -6, -6, -6, -6, -6, -6},
        {-5, -4, -3, -2, -1, -3, -4, -5}
    };

    bool onBoard(int i) {
        return i >= 0 && i < 8;
    }

    //check there is nothing on the way to destination
    bool way_is_free(int i1, int j1, int i2, int j2) {
        if (i1 == i2) {
            for (int j = j1 + (j2 > j1 ? 1: -1); j != j2; j < j2 ? j++ : j--)
                if (position[j][i1] != 0)
                    return false;
        }
        else if (j1 == j2) {
            for (int i = i1 + (i2 > i1 ? 1: -1); i != i2; i < i2 ? i++ : i--)
                if (position[j1][i] != 0)
                    return false;
        }
        else
        for (int i = i1 + (i2 > i1 ? 1: -1), j = j1 + (j2 > j1 ? 1: -1); i != i2 && j != j2; i < i2 ? i++ : i--, j < j2 ? j++: j--) {
            if (position[j][i] != 0)
                return false;
        }

        return true;
    }

    std::pair<int, int> findWhiteKing(int positionAfterMove[8][8]) {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (positionAfterMove[j][i] == 1)
                    return std::pair<int, int>(j, i);
    }

    std::pair<int, int> findBlackKing(int positionAfterMove[8][8]) {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (positionAfterMove[j][i] == -1)
                    return std::pair<int, int>(j, i);
    }

    public:

    constexpr static char PieceLetters[8] = {'.', 'k', 'q', 'b', 'n', 'r', 'p', '?'};

    std::vector<sf::CircleShape> circles; //когда очень не хочешь делать нормальную отладку

    void clearLights() {
        circles.clear();
    }

    void addLight(int j, int i) {
        sf::CircleShape circle(56/2);
        circle.setFillColor(sf::Color(255, 210, 210));
        circle.setPosition( (504 - 56 * 8) / 2 + 56 * i, (504 - 56 * 8) / 2 + 56 * j);
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
        int i1 = m[0] - 'a';
        int j1 = m[1] - '1';
        int i2 = m[2] - 'a';
        int j2 = m[3] - '1';

        if (position[j1][i1] > 0 != WhiteToMove || position[j1][i1] == 0 || position[j1][i1] * position[j2][i2] > 0)
            return nullptr;

        if (abs(position[j2][i2]) == 1) //короля нельзя съесть
            return nullptr;

        bool KingCastlingCorrect =
                (i1 == 4 && j1 == WhiteToMove ? 0 : 7) //start position is ok
                && j2 == j1 //horizontal moving
                && (
                        ((i2 == 6) && (WhiteToMove? WhiteCanCastleKingside : BlackCanCastleKingside)) ||
                        ((i2 == 2) && (WhiteToMove? WhiteCanCastleQueenside : BlackCanCastleQueenside))); //check color and ability to castle
        bool KingCorrect = (abs(j2-j1) <= 1 && abs(i2-i1) <= 1) || KingCastlingCorrect;
        bool BishopCorrect = (abs(j2-j1) == abs(i2-i1));
        bool KnightCorrect = ((abs(j2-j1) == 2 && abs(i2-i1) == 1) || (abs(i2-i1) == 2 && abs(j2-j1) == 1));
        bool RookCorrect = (j2 == j1 || i2 == i1);
        bool PawnCorrect = ((i2 == i1) && position[j2][i2] == 0 && (j2 == j1 + (WhiteToMove ? 1 : -1))) ||
                            ((abs(i2-i1)==1) && position[j2][i2] != 0 && (j2 == j1 + (WhiteToMove ? 1 : -1))) ||
                            ((i2 == i1) && (j1 == WhiteToMove ? 1 : 5) && (position[j2][i2] == 0) && ((j2 == j1 + (WhiteToMove ? 1 : -1)) || ((j2 == j1 + (WhiteToMove ? 2 : -2)) && way_is_free(i1, j1, i2, j2)))) ||
                            ((j1 == (WhiteToMove ? 4 : 3) && abs(getLastMove()->getPiece()) == 6 && getLastMove()->getRow1() == (WhiteToMove ? 6 : 1) && abs(getLastMove()->getRow2() - getLastMove()->getRow1()) == 2) && (i2 == getLastMove()->getCol2()) && (j2 == getLastMove()->getRow1() + (WhiteToMove ? -1 : 1))); //взятие на проходе

        bool QueenCorrect = BishopCorrect ^ RookCorrect;

        switch (abs(position[j1][i1]))
        {
        case 1:
            if (!KingCorrect)
                return nullptr;

            //move out of switch?
            if (KingCastlingCorrect) {
                if (WhiteToMove) {
                    WhiteCanCastleKingside = false;
                    WhiteCanCastleQueenside = false;
                }
                else {
                    BlackCanCastleKingside = false;
                    BlackCanCastleQueenside = false;
                }

                position[j2][i2] = position[j1][i1];
                position[j1][i1] = 0;

                if (i2 == 6) { //king side
                    //change rook position
                    position[j2][i2 - 1] = position[j2][i2 + 1];
                    position[j2][i2 + 1] = 0;
                    result = new ShortCastlingMove(position[j2][i2], j1, i1, j2, i2, false, false);
                    history.push_back(result);
                }
                else if (i2 == 2) { //queen side TODO: не помню точно, насколько клеток
                    //change rook position
                    position[j2][i2 + 1] = position[j2][i2 - 2];
                    position[j2][i2 - 2] = 0;
                    result = new LongCastlingMove(position[j2][i2], j1, i1, j2, i2, false, false);
                    history.push_back(result);
                }

                WhiteToMove = !WhiteToMove;
                return result;
            }

            break;

        case 2:
            if (!QueenCorrect)
                return nullptr;
            if (!way_is_free(i1, j1, i2, j2))
                return nullptr;
            break;

        case 3:
            if (!BishopCorrect)
                return nullptr;
            if (!way_is_free(i1, j1, i2, j2))
                return nullptr;

            break;

        case 4:
            if (!KnightCorrect)
                return nullptr;
            break;

        case 5:
            if (!RookCorrect)
                return nullptr;
            if (!way_is_free(i1, j1, i2, j2))
                return nullptr;

            if (j1 == 0) { //handles the first move of the white rook
                if (i1 == 0) //queen side
                    WhiteCanCastleQueenside = false;
                else //king side
                    WhiteCanCastleKingside = false;
            }
            else { //handles the first move of the black rook
                if (i1 == 0) //queen side
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

        result = new Move(position[j1][i1], j1, i1, j2, i2, false, false);

        //проверка шаха TODO: рокировку нельзя произвести если стоит шах, проверка шаха должна быть раньше
        bool WhiteKingCheck = false; //1
        bool BlackKingCheck = false; //-1

        int positionAfterMove[8][8] = {0};
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                positionAfterMove[j][i] = position[j][i];

        positionAfterMove[j2][i2] = position[j1][i1];
        positionAfterMove[j1][i1] = 0;

        int me_j;
        int me_i;
        int opponent_j;
        int opponent_i;

        if (WhiteToMove) {
            me_j = findWhiteKing(positionAfterMove).first;
            me_i = findWhiteKing(positionAfterMove).second;
            opponent_j = findBlackKing(positionAfterMove).first;
            opponent_i = findBlackKing(positionAfterMove).second;
        }
        else {
            opponent_j = findWhiteKing(positionAfterMove).first;
            opponent_i = findWhiteKing(positionAfterMove).second;
            me_j = findBlackKing(positionAfterMove).first;
            me_i = findBlackKing(positionAfterMove).second;
        }

        // проверка фигур по горизонтали
        for (int i = me_i; i < 8 && way_is_free(me_j, me_i, me_j, i); i++) {
            if (positionAfterMove[me_j][i] == (5 * (WhiteToMove ? -1 : 1)))
                return nullptr;
        }

        for (int i = me_i; i >= 0 && way_is_free(me_j, me_i, me_j, i); i--) {

        }

        //clearLights();

//        for (int i = opponent_i; i < 8 && way_is_free(opponent_j, opponent_i, opponent_j, i); i++) {
//            if (positionAfterMove[opponent_j][i] == (-5 * (WhiteToMove ? -1 : 1)))
//                result->setCheck(true);
//            addLight(opponent_j, i);
//        }

        for (int i = 0; i <= 8; i++) {
            if (positionAfterMove[opponent_j][i] == (-5 * (WhiteToMove ? -1 : 1)) && way_is_free(opponent_j, opponent_i, opponent_j, i)) //todo i -> i-1 в конце
                result->setCheck(true);
//            addLight(opponent_j, i);
        }

        // проверка короля
        if (abs(me_i - opponent_i) <= 1 && abs(me_j - opponent_j) <= 1)
            return nullptr;

        // проверка фигур по вертикали

        // проверка фигур по диагонали
        for (int i = opponent_i, j = opponent_j; i < 8 && j < 8; i++, j++) {
            if ((positionAfterMove[j][i] == (-3 * (WhiteToMove ? -1 : 1))) ||
                (positionAfterMove[j][i] == (-2 * (WhiteToMove ? -1 : 1)))) {
                result->setCheck(true);
            }
        }

        for (int i = opponent_i, j = opponent_j; i < 8 && j >= 0; i++, j--) {
            if ((positionAfterMove[j][i] == (-3 * (WhiteToMove ? -1 : 1))) ||
                (positionAfterMove[j][i] == (-2 * (WhiteToMove ? -1 : 1)))) {
                result->setCheck(true);
            }
        }

        //проверка коней
        if ((onBoard(me_j + 2) && onBoard(me_i + 1) && positionAfterMove[me_j + 2][me_i + 1] == 4 * (WhiteToMove ? -1 : 1)) ||
            (onBoard(me_j + 2) && onBoard(me_i - 1) && positionAfterMove[me_j + 2][me_i - 1] == 4 * (WhiteToMove ? -1 : 1)) ||
            (onBoard(me_j - 2) && onBoard(me_i + 1) && positionAfterMove[me_j - 2][me_i + 1] == 4 * (WhiteToMove ? -1 : 1)) ||
            (onBoard(me_j - 2) && onBoard(me_i - 1) && positionAfterMove[me_j - 2][me_i - 1] == 4 * (WhiteToMove ? -1 : 1)) ||
            (onBoard(me_j + 1) && onBoard(me_i + 2) && positionAfterMove[me_j + 1][me_i + 2] == 4 * (WhiteToMove ? -1 : 1)) ||
            (onBoard(me_j + 1) && onBoard(me_i - 2) && positionAfterMove[me_j + 1][me_i - 2] == 4 * (WhiteToMove ? -1 : 1)) ||
            (onBoard(me_j - 1) && onBoard(me_i + 2) && positionAfterMove[me_j - 1][me_i + 2] == 4 * (WhiteToMove ? -1 : 1)) ||
            (onBoard(me_j - 1) && onBoard(me_i - 2) && positionAfterMove[me_j - 1][me_i - 2] == 4 * (WhiteToMove ? -1 : 1)))
            return nullptr;

        if ((onBoard(opponent_j + 2) && onBoard(opponent_i + 1) && positionAfterMove[opponent_j + 2][opponent_i + 1] == -4 * (WhiteToMove ? -1 : 1)) ||
            (onBoard(opponent_j + 2) && onBoard(opponent_i - 1) && positionAfterMove[opponent_j + 2][opponent_i - 1] == -4 * (WhiteToMove ? -1 : 1)) ||
            (onBoard(opponent_j - 2) && onBoard(opponent_i + 1) && positionAfterMove[opponent_j - 2][opponent_i + 1] == -4 * (WhiteToMove ? -1 : 1)) ||
            (onBoard(opponent_j - 2) && onBoard(opponent_i - 1) && positionAfterMove[opponent_j - 2][opponent_i - 1] == -4 * (WhiteToMove ? -1 : 1)) ||
            (onBoard(opponent_j + 1) && onBoard(opponent_i + 2) && positionAfterMove[opponent_j + 1][opponent_i + 2] == -4 * (WhiteToMove ? -1 : 1)) ||
            (onBoard(opponent_j + 1) && onBoard(opponent_i - 2) && positionAfterMove[opponent_j + 1][opponent_i - 2] == -4 * (WhiteToMove ? -1 : 1)) ||
            (onBoard(opponent_j - 1) && onBoard(opponent_i + 2) && positionAfterMove[opponent_j - 1][opponent_i + 2] == -4 * (WhiteToMove ? -1 : 1)) ||
            (onBoard(opponent_j - 1) && onBoard(opponent_i - 2) && positionAfterMove[opponent_j - 1][opponent_i - 2] == -4 * (WhiteToMove ? -1 : 1)))
            result->setCheck(true);
        // проверка пешек

        if (position[j2][i2] != 0)
            result->setEating(true);
        history.push_back(result);

        position[j2][i2] = position[j1][i1];
        position[j1][i1] = 0;
        WhiteToMove = !WhiteToMove;

        return getLastMove();
    }

    bool get_WhiteToMove() {return WhiteToMove;}
    int get_cell(int row, int column) {return position[row][column];}
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