#include <iostream>

using namespace std;

class ChessHandler {
    private:

    bool WhiteToMove = true;

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

        //TODO: check the move is possible
        switch (abs(position[j1][i1]))
        {
        case 1:
            if (abs(j2-j1) > 1 || abs(i2-i1) > 1)
                return false;
            //TODO: check enemy king is close
            //TODO: рокировка
            break;

        case 4:
            if (!((abs(j2-j1) == 2 && abs(i2-i1) == 1) || (abs(i2-i1) == 2 && abs(j2-j1) == 1)))
                return false;
            break;

        case 5:
            if (j2 != j1 && i2 != i1) //TODO: исключить диагональ
                return false;
            break;

        case 6:
            //initial row can double the distance
            if ((j2 != j1+1) && ((position[j2][i2] != 0) && (abs(i2-i1) != 1)))
                return false;
            //взятие на проходе
            break;

        //ферзь и слон
        
        default:
            break;
        }

        //TODO: check there is nothing on the way to destination

        position[j2][i2] = position[j1][i1];
        position[j1][i1] = 0;
        WhiteToMove = !WhiteToMove;

        return true;
    }

    //TODO: check check and mate:)))

    bool get_WhiteToMove() {return WhiteToMove;}
    int get_cell(int row, int column) {return position[row][column];}
};