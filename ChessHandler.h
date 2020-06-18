#include <iostream>

using namespace std;

class ChessHandler {
    private:

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

    void print() {
        for (int i = 7; i >= 0; i--) {
            cout << i+1 << " | ";
            for (int j = 0; j < 8; j++)
            {
                char out;
                switch (abs(position[i][j]))
                {
                case 0:
                    out = '.';
                    break;

                case 1:
                    out = 'k';
                    break;

                case 2:
                    out = 'q';
                    break;

                case 3:
                    out = 'b';
                    break;

                case 4:
                    out = 'n';
                    break;

                case 5:
                    out = 'r';
                    break;

                case 6:
                    out = 'p';
                    break;
                
                default:
                    out = '?';
                    break;
                }

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

    bool move(char m[4]) {
        int i1 = m[0] - 'a';
        int j1 = m[1] - '1';
        int i2 = m[2] - 'a';
        int j2 = m[3] - '1';

        if (position[j1][i1] > 0 != WhiteToMove || position[j1][i1] == 0 || position[j1][i1] * position[j2][i2] > 0)
            return false;

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
                return false;

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
                }
                else if (i2 == 2) { //queen side
                    //change rook position
                    position[j2][i2 + 1] = position[j2][i2 - 2];
                    position[j2][i2 - 2] = 0;
                }

                WhiteToMove = !WhiteToMove;

                return true;
            }

            //TODO: check enemy king is close - actually this is a part of after move check
            break;

        case 2:
            if (!QueenCorrect)
                return false;
            if (!way_is_free(i1, j1, i2, j2))
                return false;
            break;

        case 3:
            if (!BishopCorrect)
                return false;
            if (!way_is_free(i1, j1, i2, j2))
                return false;
            break;

        case 4:
            if (!KnightCorrect)
                return false;
            break;

        case 5:
            if (!RookCorrect)
                return false;
            if (!way_is_free(i1, j1, i2, j2))
                return false;

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
                return false;
            break;
        
        default:
            return false;
        }

        //TODO: check check and mate:)))

        position[j2][i2] = position[j1][i1];
        position[j1][i1] = 0;
        WhiteToMove = !WhiteToMove;

        return true;
    }

    bool get_WhiteToMove() {return WhiteToMove;}
    int get_cell(int row, int column) {return position[row][column];}
};