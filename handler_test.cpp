#include <iostream>

using namespace std;

class ChessHandler {
    private:

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

    enum Figures {
        Empty = 0,
        King,
        Queen,
        Bishop,
        Knight,
        Rook,
        Pawn
    };

    public:

    void print() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++)
                cout << position[i][j] << " ";
            cout << endl;
        }

        for (int i = 0; i < 15; i++)
            cout << "_";

        cout << endl;
        //TODO: pretty table
    }

    void move(char m[4]) {
        int i1 = m[0] - 'a'; // correct
        int j1 = m[1] - '1';
        int i2 = m[2] - 'a'; // correct
        int j2 = m[3] - '1';

        j1 = 8 - j1;
        j2 = 8 - j2;


        //TODO: check move
        //TODO: fix bug
        position[j2][i2] = position[j1][i1];
        position[j1][i1] = 0;

        print();
    }
};

int main() {
    ChessHandler m;
    m.print();
    
    while (true) {
        char s[4];
        cin >> s;
        m.move(s);
    }

    return 0;
}