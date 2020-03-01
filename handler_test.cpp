#include <iostream>
#include <iomanip>

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

    public:

    void print() {
        for (int i = 7; i >= 0; i--) {
            cout << i << " | ";
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

    void move(char m[4]) {
        int i1 = m[0] - 'a';
        int j1 = m[1] - '1';
        int i2 = m[2] - 'a';
        int j2 = m[3] - '1';

        //TODO: check move
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