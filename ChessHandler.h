#include <iostream>

using namespace std;

class ChessHandler {
public:
    class Move {
    private:
        int piece_id;
        int row1, col1, row2, col2;
        bool check;
        bool mate;
        bool bad = false;
        bool good = false;
    public:

        Move(int piece_id, int row1, int col1, int row2, int col2, bool check, bool mate) {
            if (row1 > 7 || row1 < 0) throw std::runtime_error("Incorrect piece coordinates");
            if (col1 > 7 || col1 < 0) throw std::runtime_error("Incorrect piece coordinates");
            if (row2 > 7 || row2 < 0) throw std::runtime_error("Incorrect piece coordinates");
            if (col2 > 7 || col2 < 0) throw std::runtime_error("Incorrect piece coordinates");

            this->piece_id = piece_id;
            this->row1 = row1;
            this->col1 = col1;
            this->row2 = row2;
            this->col2 = col2;
        }

//        std::string toString() {
//            std::string result;
//            result += col1 - 'a';
//            result += row1;
//            result += col2 - 'a';
//            result += row2;
//            return result;
//        }

        virtual std::string toChessNotation() {
            std::string chessNotation;
            //если 2 фигуры на одной строке или столбце, указать какая именно из них
            char letter = ChessHandler::PieceLetters[abs(piece_id)];
            if (letter != 'p')
                chessNotation += toupper(letter);
            chessNotation += 'a' + col2;
            chessNotation += '1' + row2;
            if (mate) chessNotation += "#";
            else if (check) chessNotation += "+";

            if (good) chessNotation += "!";
            if (bad) chessNotation += "?";
            return chessNotation;
        }
    };

    class LongCastlingMove: public Move {
    public:
        LongCastlingMove(int pieceId, int row1, int col1, int row2, int col2, bool check, bool mate) : Move(pieceId,
                                                                                                            row1, col1,
                                                                                                            row2, col2,
                                                                                                            check,
                                                                                                            mate) {}

        string toChessNotation() override {
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

        string toChessNotation() override {
            return "0-0";
        }
    };

private:

    std::vector<Move*> history;
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

    public:

    constexpr static char PieceLetters[8] = {'.', 'k', 'q', 'b', 'n', 'r', 'p', '?'};

    void print() {
        for (int i = 7; i >= 0; i--) {
            cout << i+1 << " | ";
            for (int j = 0; j < 8; j++)
            {
                char out;
                if (abs(position[i][j]) < 0 || abs(position[i][j]) > 7)
                    out = '?';
                else out = PieceLetters[abs(position[i][j])];
                out = position[i][j] > 0 ? toupper(out): out;
                cout << out << " ";
            }
            cout << endl;
        }

        cout << "   ";
        for (int i = 0; i < 8; i++) {
            cout << " _";
        }

        cout << endl;

        cout << "   ";
        for (int i = 0; i < 8; i++) {
            cout << " " << char('A' + i);
        }

        cout << endl;
    }

    Move* move(char m[4]) {
        int i1 = m[0] - 'a';
        int j1 = m[1] - '1';
        int i2 = m[2] - 'a';
        int j2 = m[3] - '1';

        if (position[j1][i1] > 0 != WhiteToMove || position[j1][i1] == 0 || position[j1][i1] * position[j2][i2] > 0)
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
        bool PawnCorrect = (j2 == j1 + (WhiteToMove ? 1 : -1)) || (j2 == j1 + (WhiteToMove ? 2 : -2)); //TODO: взятие на проходе

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
                    history.push_back(new ShortCastlingMove(position[j2][i2], j1, i1, j2, i2, false, false));
                }
                else if (i2 == 2) { //queen side
                    //change rook position
                    position[j2][i2 + 1] = position[j2][i2 - 2];
                    position[j2][i2 - 2] = 0;
                    history.push_back(new LongCastlingMove(position[j2][i2], j1, i1, j2, i2, false, false));
                }

                WhiteToMove = !WhiteToMove;
                return getLastMove();
            }

            //TODO: check enemy king is close - actually this is a part of after move check
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

        //TODO: check check and mate:)))

        history.push_back(new Move(position[j1][i1], j1, i1, j2, i2, false, false));

        position[j2][i2] = position[j1][i1];
        position[j1][i1] = 0;
        WhiteToMove = !WhiteToMove;

        return getLastMove();
    }

    bool get_WhiteToMove() {return WhiteToMove;}
    int get_cell(int row, int column) {return position[row][column];}
    //Move getMove(int id) { return history.at(id); }
    Move* getLastMove() { if (history.empty()) return nullptr; return history.back(); }
    std::string getHistoryString() {
        std::string result;
        for (int i = 0; i < history.size(); i++) {
            if ((i + 1) % 2 != 0)
                result += std::to_string((i + 2) / 2) + ". ";
            result += history[i]->toChessNotation() + " ";
        }
        return result;
    }

};